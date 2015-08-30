#include "StdAfx.h"
#include "MineGE.h"

#include "config.h"
#include "DataHelperImpl.h"
#include "DefaultCurDrawHelper.h"
#include "HelperClass.h"

#include <MineGEDraw/MineGEDraw_Jig.h>
#include <MineGEDraw/MineGEDrawSystem.h>

static bool HasDataObject( const AcDbObjectId& dictId )
{
    AcDbDictionary* pDict;
    if( Acad::eOk != acdbOpenObject( pDict, dictId, AcDb::kForWrite ) ) return false;

    AcDbObjectId objId;
    bool ret = pDict->has( DATA_OBJECT_EXT_DICT_KEY );
    pDict->close();

    return ret;
}

static AcDbObjectId CreateDataObject( const AcDbObjectId& dictId,
                                      const CString& type,
                                      const AcDbObjectId& objId )
{
    AcDbDictionary* pDict;
    if( Acad::eOk != acdbOpenObject( pDict, dictId, AcDb::kForWrite ) ) return AcDbObjectId::kNull;

    // �������ݶ���
    DataObject* pDO = new DataObject();
    // ����ͼԪid
    pDO->setGE( objId );
    // ��¼��������
    pDO->setType( type );
    // ��ʼ������
    pDO->initData();

    AcDbObjectId dbObjId;
    if( Acad::eOk != pDict->setAt( DATA_OBJECT_EXT_DICT_KEY, pDO, dbObjId ) )
    {
        delete pDO;
    }
    else
    {
        pDO->close();
    }
    pDict->close();

    return dbObjId;
}

static AcDbObjectId GetDataObject( const AcDbObjectId& dictId )
{
    if( dictId.isNull() ) return AcDbObjectId::kNull;

    AcDbDictionary* pDict;
    if( Acad::eOk != acdbOpenObject( pDict, dictId, AcDb::kForRead ) ) return AcDbObjectId::kNull;

    AcDbObjectId objId;
    pDict->getAt( DATA_OBJECT_EXT_DICT_KEY, objId );

    pDict->close();

    return objId;
}

// ��ͼԪ�������еı�ǩͼԪ���б任(�ɼ�ͼԪ����������ɾ������ͼԪ)
static void TransformAllTagGE( const AcDbObjectId& objId, const AcGeMatrix3d& xform )
{
    AcDbObjectIdArray objIds;
    DrawHelper::GetAllTagGEById( objId, objIds );
    ArxEntityHelper::TransformEntities2( objIds, xform );
}

Adesk::UInt32 MineGE::kCurrentVersionNumber = 1 ;

// ���޸ģ�ʹ��MineGE��Ϊ������
ACRX_NO_CONS_DEFINE_MEMBERS ( MineGE, AcDbEntity )

MineGE::MineGE() :m_bFollow( false )
{
    //acutPrintf(_T("\nMineGE::MineGE()..."));
}

MineGE::~MineGE ()
{
    //acutPrintf(_T("\nMineGE::~MineGE()..."));
}

CString MineGE::getTypeName() const
{
    // ������������
    // ʹ�����麯������isA()
    return this->isA()->name();
}

CString MineGE::getCurDraw() const
{
	assertReadEnabled();

	CString curDraw;
	ArxDbgAppXdata xdata( DRAW_PARAMS_XDATA_GROUP, acdbHostApplicationServices()->workingDatabase() );
	xdata.getXdata( ( MineGE* )this ); // ��ȡ��չ���ݵ�xdata������(ǿ��ȥ��const����)
	if( !xdata.isEmpty() ) 
	{
		xdata.getString(0, curDraw);
	}
	else
	{
		//�����û����չ����,�򷵻�ϵͳ�ṩ��Ĭ�Ͽ��ӻ�Ч��
		//GetDefaultCurDraw(getTypeName(), curDraw);
	}
	return curDraw;
}

void MineGE::initPropertyData()
{
    //assertWriteEnabled();
    if( !m_dataObjectId.isNull() ) return;

    Acad::ErrorStatus es = upgradeOpen();
    if( es == Acad::eOk || es == Acad::eWasOpenForWrite )
    {
        createExtensionDictionary();
        AcDbObjectId dictId = extensionDictionary();
        m_dataObjectId = CreateDataObject( dictId, getTypeName(), objectId() );
    }
    if( es == Acad::eOk )
    {
        downgradeOpen();
    }
}

AcDbObjectId MineGE::getDataObject() const
{
    assertReadEnabled();

    return m_dataObjectId;
}

void MineGE::initDraw()
{
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw == 0 )
    {
        Acad::ErrorStatus es = upgradeOpen();
        if( es == Acad::eOk || es == Acad::eWasOpenForWrite )
        {
			if( isNewObject() )
			{
				initAllExtraParamsToXData();
			}
        }
        if( es == Acad::eOk )
        {
            downgradeOpen();
        }
    }
}

void MineGE::updateDrawParams( MineGEDraw* pDraw )
{
    if( pDraw != 0 )
    {
		writeParamToGEDraw(pDraw);
        pDraw->updateExtraParams();
		readParamFromGEDraw(pDraw);
    }
}

void MineGE::switchDraw(const CString& drawName)
{
	assertWriteEnabled();

	MineGEDraw* pDraw = MineGEDrawSystem::GetInstance()->getGEDraw( getTypeName(), drawName );
	if(pDraw != 0)
	{
		ArxDbgAppXdata xdata( DRAW_PARAMS_XDATA_GROUP, acdbHostApplicationServices()->workingDatabase() );
		xdata.getXdata( ( MineGE* )this ); // ��ȡ��չ���ݵ�xdata������(ǿ��ȥ��const����)
		if( !xdata.isEmpty() ) 
		{
			xdata.setString(0, pDraw->isA()->name());
			if(Acad::eOk == xdata.setXdata(this))
			{
				updateDrawParams( pDraw );
			}
		}
	}
}

/*
void MineGE::configDraw( const CString& drawName )
{
    MineGEDraw* pDraw = MineGEDrawSystem::GetInstance()->getGEDraw( getTypeName(), drawName );
    updateDrawParams( pDraw );
}
*/

void MineGE::extractExistedDraw( AcStringArray& existedDraw )
{
    ArxDbgAppXdata xdata( DRAW_PARAMS_XDATA_GROUP, acdbHostApplicationServices()->workingDatabase() );
    xdata.getXdata( this );          // ��ȡ��չ���ݵ�xdata������
    if( xdata.isEmpty() ) return;    // û������

    int len = 0;
    xdata.getInteger( 1, len );      // ����Ч������
    for( int i = 1; i <= len; i++ )
    {
        CString drawName;
        xdata.getString( 2 * i, drawName ); // ����Ч������
        existedDraw.append( drawName );
    }
}

// ���������Ƚϸ���
// ����Ҫ��֤xdata���draw��ȫ�ֵ�draw��ͬ����
// ���ܴ������¼��������
// 1��xdata���draw ���� ȫ�ֵ�draw
// 2��xdata���draw ���� ȫ�ֵ�draw(������draw���)
// 3��xdata���draw С�� ȫ�ֵ�draw(ɾ����draw���)
// 4��xata��Ĳ���draw����ȫ�ֵ�draw��û�У�ȫ�ֵĲ���draw��xdata��û��
// Ŀǰ������򵥵İ취������draw�������ȫ�����ϲ���xdata��
// Ҳ����˵xdata�п��ܴ�������ġ�����ʹ�õ�draw����
// ���ڿ��Կ���ר�ű�дһ������draw�ĳ���
void MineGE::initAllExtraParamsToXData()
{
    // ͨ��assertWriteEnabled�޶�ֻ����write״̬�²���
    assertWriteEnabled();

    // ��ȡ�Ѵ��ڵ�draw
    AcStringArray existedDraw;
    extractExistedDraw( existedDraw );

	//��ȡ��ǰ�Ŀ��ӻ�Ч������
	CString curDraw = getCurDraw();

    MineGEDrawSystem* pGEService = MineGEDrawSystem::GetInstance();
    AcStringArray drawList;
    pGEService->getAllGEDrawsByGEType( getTypeName(), drawList );

    ArxDbgAppXdata xdata( DRAW_PARAMS_XDATA_GROUP, acdbHostApplicationServices()->workingDatabase() );
    xdata.setString( 0, _T( "" ) );                           // ��ǰ����Ч������
    xdata.setInteger( 1, 0 );                                 // ����Ч������(��ʱ����0)

    bool foundNewDraw = false;                                // �Ƿ����µ�draw
    int i = existedDraw.length() + 1;
    int len = drawList.length();
    for( int j = 0; j < len; j++ )
    {
        if( existedDraw.contains( drawList.at( j ) ) ) continue;

        foundNewDraw = true;                                   // �������µ�draw

        MineGEDraw* pDraw = pGEService->getGEDraw( getTypeName(), drawList.at( j ).kACharPtr() );
        writeKeyParamToGEDraw( pDraw );                          // д����Ҫ������draw��
        // ��Щextra param����Ҫ����ģ�
        // �ҿ�����key param�й�
        //pDraw->setAllExtraParamsToDefault();                   // ������ΪĬ��ֵ
        pDraw->updateExtraParams();                              // ���㲢���²���
        xdata.setString( 2 * i, pDraw->isA()->name() );          // ����Ч������

        ArxDbgXdataList dataList;
        DrawParamWriter writer( &dataList );
        pDraw->writeExtraParam( writer );
        xdata.setList( 2 * i + 1, dataList );                      // д�븽�Ӳ���
        i++;
    }
    xdata.setInteger( 1, i - 1 );                                  // ����draw��ʵ�ʸ���

	//���õ�ǰ���ӻ�Ч��
	if(curDraw.GetLength() == 0)
	{
		//if(!foundNewDraw)
		//{
			GetDefaultCurDraw(getTypeName(), curDraw);
		//}
		//else
		//{
			//curDraw = drawList.at(0).kACharPtr();
		//}
		xdata.setString(0, curDraw);
	}
    if( foundNewDraw ) xdata.setXdata( this );                     // ֻ�з����µ�draw�Ż����xdata
}

static MineGEDraw* GetDefaultCurDrawPtr( const CString& type )
{
    MineGEDraw* pDraw = 0;

    CString draw;
    if( GetDefaultCurDraw( type, draw ) )
    {
        MineGEDrawSystem* pDrawSystem = MineGEDrawSystem::GetInstance();
        if( pDrawSystem != 0 )
        {
            pDraw = pDrawSystem->getGEDraw( type, draw );
        }
    }
    return pDraw;
}

void MineGE::updateDraw()
{
    assertWriteEnabled();

	//��ȡ��ǰ�Ŀ��ӻ�����ָ��
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw != 0 )
    {
        updateDrawParams( pDraw );
		//�������º�LinkedGEͼԪ΢��
		onParamsChanged();
    }
}

MineGEDraw* MineGE::getCurDrawPtr() const
{
	CString drawName = getCurDraw();
	return MineGEDrawSystem::GetInstance()->getGEDraw( getTypeName(), drawName );
}

void MineGE::writeExtraParamToGEDraw( MineGEDraw* pDraw ) const
{
    assertReadEnabled();

    ArxDbgAppXdata xdata( DRAW_PARAMS_XDATA_GROUP, acdbHostApplicationServices()->workingDatabase() );
    xdata.getXdata( ( MineGE* )this ); // ��ȡ��չ���ݵ�xdata������(ǿ��ȥ��const����)
	if( xdata.isEmpty() ) return;

    int len = 0;
    xdata.getInteger( 1, len );    // ����Ч������
    for( int i = 1; i <= len; i++ )
    {
        CString drawName;
        xdata.getString( 2 * i, drawName ); // ����Ч������

        if( drawName.CompareNoCase( pDraw->isA()->name() ) == 0 )
        {
            ArxDbgXdataList dataList;
            xdata.getList( 2 * i + 1, dataList ); // ����Ч���Ĳ���

            ArxDbgXdataListIterator paramList( dataList );
            DrawParamReader reader( &paramList );
            pDraw->readExtraParam( reader ); // ����չ�����ж�ȡ����
			break;
        }
    }
}

// ������write״̬�²���
void MineGE::readExtraParamFromGEDraw( MineGEDraw* pDraw )
{
    assertWriteEnabled();

    ArxDbgAppXdata xdata( DRAW_PARAMS_XDATA_GROUP, acdbHostApplicationServices()->workingDatabase() );
    xdata.getXdata( this ); // ��ȡ��չ���ݵ�xdata������
	if( xdata.isEmpty() ) return;

    // �����滻����չ����
    // ˼·����ԭ�е���չ���ݸ���һ�ݣ������޸ĵ�draw�������Ƚ����޸ģ�Ȼ���ٱ��浽�µ���չ������
    ArxDbgAppXdata xdata2( DRAW_PARAMS_XDATA_GROUP, acdbHostApplicationServices()->workingDatabase() );

	CString curDraw;
	xdata.getString(0, curDraw);
    xdata2.setString( 0, curDraw ); // ���Ƶ�ǰ����Ч������

    int len = 0;
    xdata.getInteger( 1, len );     // ���ƻ���Ч������
    xdata2.setInteger( 1, len );

    for( int i = 1; i <= len; i++ )
    {
        CString drawName;
        xdata.getString( 2 * i, drawName ); // ����Ч������
        xdata2.setString( 2 * i, drawName );

        if( drawName.CompareNoCase( pDraw->isA()->name() ) == 0 )
        {
            ArxDbgXdataList dataList;
            DrawParamWriter writer( &dataList );
            pDraw->writeExtraParam( writer );

            xdata2.setList( 2 * i + 1, dataList ); // �޸Ĳ��������Ч���Ĳ���
        }
        else
        {
            ArxDbgXdataList dataList;
            xdata.getList( 2 * i + 1, dataList );
            xdata2.setList( 2 * i + 1, dataList );
        }
    }
    xdata2.setXdata( this );
}

void MineGE::readKeyParamFromGEDraw( MineGEDraw* pDraw )
{
    assertWriteEnabled();

    // ��MineGEDraw�ж�ȡ����֮��Ĺؼ�����
    ArxDbgXdataList dataList;
    DrawParamWriter writer( &dataList );
    pDraw->writeKeyParam( writer );

    ArxDbgXdataListIterator dataListIter( dataList );
    DrawParamReader reader( &dataListIter );
    readKeyParam( reader );
}

void MineGE::writeKeyParamToGEDraw( MineGEDraw* pDraw ) const
{
    assertReadEnabled();

    // ���ؼ��������µ�MineGEDraw��
    ArxDbgXdataList dataList;
    DrawParamWriter writer( &dataList );
    writeKeyParam( writer );

    ArxDbgXdataListIterator dataListIter( dataList );
    DrawParamReader reader( &dataListIter );
    pDraw->readKeyParam( reader );
}

static bool GetPropertyDataFromDataObject( const AcDbObjectId& objId, const AcStringArray& names, AcStringArray& values )
{
    DataObject* pDO;
    if( Acad::eOk != acdbOpenObject( pDO, objId, AcDb::kForRead ) ) return false;

    DataHelperImpl dh( pDO );
    int len = names.length();
    for( int i = 0; i < len; i++ )
    {
        CString value;
        bool ret = dh.getPropertyData( names[i].kACharPtr(), value );
        values.append( value );
    }
    pDO->close();

    return true;
}

void MineGE::writePropertyDataToGEDraw( MineGEDraw* pDraw ) const
{
    assertReadEnabled();

    // ��ȡҪ��ѯ���ֶ����Ƽ���
    AcStringArray names;
    pDraw->regPropertyDataNames( names );
    if( names.isEmpty() ) return;

    // ��ѯ���ݣ���д�뵽values��
    AcStringArray values;
    if( !GetPropertyDataFromDataObject( getDataObject(), names, values ) )
    {
        int len = names.length();
        for( int i = 0; i < len; i++ )
        {
            // �����ȡ����ʧ�ܣ������names�ȳ��Ŀ��ַ���
            values.append( _T( "" ) );
        }
    }
    //int len = names.length();
    //for( int i = 0; i < len; i++ )
    //{
    //	acutPrintf(_T("\n�ֶ���:%s\tֵ:%s\n"),names[i].kACharPtr(),values[i].kACharPtr());
    //}

    // ����ѯ�������ݷ��ص�pDraw
    pDraw->readPropertyDataFromGE( values );
}

void MineGE::writeParamToGEDraw( MineGEDraw* pDraw ) const
{
    assertReadEnabled();

    // 1�����ؼ��������µ�MineGEDraw��
    writeKeyParamToGEDraw( pDraw );

    // 2������չ��������ȡ����
    writeExtraParamToGEDraw( pDraw );

    // 3����ȡ�������ݣ������ݸ�MineGEDraw
    writePropertyDataToGEDraw( pDraw );
}

void MineGE::readParamFromGEDraw( MineGEDraw* pDraw )
{
    assertWriteEnabled();

    // 1����MineGEDraw�ж�ȡ���º�Ĺؼ�����
    readKeyParamFromGEDraw( pDraw );

    // 2����draw�Ĳ������浽��չ������
    readExtraParamFromGEDraw( pDraw );
}

void MineGE::updateDrawParam( MineGEDraw* pDraw, bool readOrWrite ) const
{
    if( readOrWrite )
    {
        ( ( MineGE* )this )->readParamFromGEDraw( pDraw ); // ǿ��ȥ��const����
    }
    else
    {
        writeParamToGEDraw( pDraw );
    }
}

Acad::ErrorStatus MineGE::dwgOutFields( AcDbDwgFiler* pFiler ) const
{
    //acutPrintf(_T("\nid:%d call MineGE::dwgOutFields()..."), objectId());

    assertReadEnabled () ;
    Acad::ErrorStatus es = AcDbEntity::dwgOutFields ( pFiler ) ;
    if ( es != Acad::eOk )
        return ( es ) ;

    if ( ( es = pFiler->writeUInt32 ( MineGE::kCurrentVersionNumber ) ) != Acad::eOk )
        return ( es ) ;

    pFiler->writeSoftPointerId( m_dataObjectId );
    pFiler->writeBool( m_bFollow );

    return ( pFiler->filerStatus () ) ;
}

Acad::ErrorStatus MineGE::dwgInFields( AcDbDwgFiler* pFiler )
{
    //acutPrintf(_T("\nid:%d call MineGE::dwgInFields()..."), objectId());

    assertWriteEnabled () ;
    Acad::ErrorStatus es = AcDbEntity::dwgInFields ( pFiler );
    if ( es != Acad::eOk )
        return ( es ) ;

    Adesk::UInt32 version = 0 ;
    if ( ( es = pFiler->readUInt32 ( &version ) ) != Acad::eOk )
        return ( es ) ;
    if ( version > MineGE::kCurrentVersionNumber )
        return ( Acad::eMakeMeProxy ) ;

    /* 199֮ǰ(����199)�İ汾ʹ�� */
    //AcString str;
    //pFiler->readString(str);
    //pFiler->readString(str);

    /* 199֮��(������199)�İ汾ʹ�� */
    AcDbSoftPointerId id;
    pFiler->readSoftPointerId( &id );
    m_dataObjectId = id;

    pFiler->readBool( &m_bFollow );

    initDraw();

    return ( pFiler->filerStatus () ) ;
}

// DWORD <==> Adesk::UInt32 <==> unsigned long
// Adesk::UInt8 <==> unsigned char
static void LONG2RGB( Adesk::UInt32 rgbColor, Adesk::UInt8& r, Adesk::UInt8& g, Adesk::UInt8& b )
{
    // ����2�δ����ǵȼ۵�

    /*r = ( rgbColor & 0xffL );
    g = ( rgbColor & 0xff00L ) >> 8;
    b = rgbColor >> 16;*/

    r = GetRValue( rgbColor );
    g = GetGValue( rgbColor );
    b = GetBValue( rgbColor );
}

// ��ȡcad��ͼ���ڱ���ɫ
static bool GetBackgroundColor( Adesk::UInt8& r, Adesk::UInt8& g, Adesk::UInt8& b )
{
    // ��ȡcad��ǰ���е���ɫ����
    // �Ҽ�"ѡ��"->"��ʾ"->"��ɫ"
    AcColorSettings cs;
    if( !acedGetCurrentColors( &cs ) ) return false;

    // ��ȡ������ɫ
    DWORD rgbColor = cs.dwGfxModelBkColor;
    LONG2RGB( rgbColor, r, g, b );
    return true;
}

// ��������
/*
Adesk::UInt32 rgbColor = AcCmEntityColor::lookUpRGB(cl.colorIndex()); // ת����rgb��ɫ

AcCmEntityColor bgColor(255-r, 255-g, 255-b); // RGB��ɫ

AcCmEntityColor bgColor;
bgColor.setRGB(0, 0, 0);
if(layerColor.colorIndex() == 7) bgColor.setRGB(r, g, b); // RGB��ɫ
else bgColor.setRGB(255-r, 255-g, 255-b);
 */

/*
 * �ڻ��Ʊպ�ͼ��ʱ��AcGiFillTypeĬ��ΪkAcGiFillAlways (ʼ�����)
 * �պ�ͼ�ΰ�����Բ������Ρ������
 * �μ���AcGiSubEntityTraits::fillType()����˵��
 * ���磬����һ��Բ����ǰ��ɫ�Ǻڵװ�ɫ����ô�����Զ���ʵ����Ƶ�Բ��2�����:
 *	    1) arx������ص������-- �ױ�+�ڵ����(����Ч������cad��Բ��һ����)
 *		2) arx����ж�أ�cad���ô���ʵ��ģʽ��ʾͼԪ -- �ױ�+�׵����
 * ����μ����������Բ��һЩ˵��.doc
 */

// ����AcCmColor::colorIndex()��������Ϊcolor index�ܹ�ֻ��256�֣��Ұ�/�ڶ�ʹ��7��ʾ���޷�����
// ���Ҫʹ��rgb��ɫ��Ӧʹ��AcCmEntityColor��AcCmColor����
void MineGE::drawBackground( MineGEDraw* pDraw, AcGiWorldDraw* mode )
{
    if( isNewObject() ) return;

    AcGePoint3dArray pts;
    pDraw->caclBackGroundMinPolygon( pts );

    // �û�û�ж���߽�
    if( pts.isEmpty() ) return;

    // ��ȡcad��ͼ���ڱ���ɫ
    Adesk::UInt8 r, g, b;
    if( !GetBackgroundColor( r, g, b ) ) return;

    AcGiSubEntityTraits& traits = mode->subEntityTraits();
    // ����ԭ�е�����
    Adesk::UInt16 cl = traits.color();;
    AcGiFillType ft = traits.fillType();

    AcCmEntityColor bgColor( r, g, b );
    traits.setTrueColor( bgColor );
    traits.setFillType( kAcGiFillAlways ); // ���
    //acutPrintf(_T("\n��ɫ������%d"), bgColor.colorIndex());
    mode->geometry().polygon( pts.length(), pts.asArrayPtr() );

    // �ָ�����
    traits.setFillType( ft );
    traits.setColor( cl );
}

Adesk::Boolean MineGE::subWorldDraw( AcGiWorldDraw* mode )
{
    assertReadEnabled () ;

	//��ȡ��ǰ�Ŀ��ӻ�����ָ��
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw == 0 ) return Adesk::kTrue;

    //acutPrintf(_T("\ncall id:%d MineGE::subWorldDraw()..."), objectId());
    // acutPrintf(_T("\ncall drawname:%s..."), pDraw->isA()->name());

    // 1�����²�����MineGEDraw��
    updateDrawParam( pDraw, false );
    // 2�����Ʊ�����
    // �÷����ڶ�̬Ч���п��ܻ���һЩ����,�ر���jig
    // �²�ԭ��:�������Ķ���ο��ܱȽ���
    drawBackground( pDraw, mode );

    // 3��draw���������ʵ��ͼ��
    pDraw->worldDraw( mode );

    return Adesk::kTrue;
}

Acad::ErrorStatus MineGE::subTransformBy( const AcGeMatrix3d& xform )
{
	//��ȡ��ǰ�Ŀ��ӻ�����ָ��
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw == 0 ) return Acad::eOk;

    //acutPrintf(_T("\ncall id:%d MineGE::subTransformBy()..."), objectId());

    // 1�����²�����MineGEDraw��
    updateDrawParam( pDraw, false );

    // 2��ִ�б任
    pDraw->transformBy( xform );

    // 3����MineGEDraw�ж�ȡ���º�Ĳ���
    updateDrawParam( pDraw, true );

	//�����仯��ĸ��Ӳ���
	onParamsChanged();

    // 4�����������е�TagGE
    //transformAllTagGE( xform );

    return Acad::eOk;
}

Acad::ErrorStatus MineGE::subGetOsnapPoints (
    AcDb::OsnapMode osnapMode,
    Adesk::GsMarker gsSelectionMark,
    const AcGePoint3d& pickPoint,
    const AcGePoint3d& lastPoint,
    const AcGeMatrix3d& viewXform,
    AcGePoint3dArray& snapPoints,
    AcDbIntArray& geomIds ) const
{
    assertReadEnabled () ;

	//��ȡ��ǰ�Ŀ��ӻ�����ָ��
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw == 0 ) return Acad::eOk;

    // 1�����²�����MineGEDraw��
    updateDrawParam( pDraw, false );

    // 2��draw���������ʵ��ͼ��
    pDraw->getOsnapPoints( osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds );

    return Acad::eOk;
}

Acad::ErrorStatus MineGE::subGetGripPoints(
    AcGePoint3dArray& gripPoints,
    AcDbIntArray& osnapModes,
    AcDbIntArray& geomIds ) const
{
    assertReadEnabled () ;

	//��ȡ��ǰ�Ŀ��ӻ�����ָ��
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw == 0 ) return Acad::eOk;

    // 1�����²�����MineGEDraw��
    updateDrawParam( pDraw, false );

    // 2��draw���������ʵ��ͼ��
    pDraw->getGripPoints( gripPoints, osnapModes, geomIds );

    return Acad::eOk;
}

Acad::ErrorStatus MineGE::subMoveGripPointsAt ( const AcDbIntArray& indices, const AcGeVector3d& offset )
{
    assertWriteEnabled () ;

	//��ȡ��ǰ�Ŀ��ӻ�����ָ��
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw == 0 ) return Acad::eOk;

    //acutPrintf(_T("\ncall id:%d MineGE::subMoveGripPointsAt()..."), objectId());

    // 1�����²�����MineGEDraw��
    updateDrawParam( pDraw, false );

    // 2��ִ�б任
    pDraw->moveGripPointsAt( indices, offset );

    // 3����MineGEDraw�ж�ȡ���º�Ĳ���
    updateDrawParam( pDraw, true );

	//�����仯��ĸ��Ӳ���
	onParamsChanged();

    // ���еı�ǩͼԪҲ���б任
    // �任���ƫ��ϴ󣬲������ڳ�����ʹ��
    //transformAllTagGE( AcGeMatrix3d::translation( offset ) );

    return Acad::eOk;
}

Acad::ErrorStatus MineGE::subGetGeomExtents( AcDbExtents& extents ) const
{
    assertReadEnabled () ;

	//��ȡ��ǰ�Ŀ��ӻ�����ָ��
	MineGEDraw* pDraw = getCurDrawPtr();
    if( pDraw == 0 ) return AcDbEntity::subGetGeomExtents( extents );

    // 1�����²�����MineGEDraw��
    updateDrawParam( pDraw, false );

    Acad::ErrorStatus es = pDraw->getGeomExtents( extents );
    // Drawû������ʵ��subGetGeomExtents
    if( Acad::eOk != es )
    {
        //acutPrintf(_T("\nʹ�ñ�����������μ�����������...\n"));
        // ʹ��caclBackGroundMinPolygon()��������Ķ���δ���
        AcGePoint3dArray pts;
        pDraw->caclBackGroundMinPolygon( pts );
        if( pts.isEmpty() )
        {
            es = Acad::eInvalidExtents;
        }
        else
        {
            int len = pts.length();
            for( int i = 0; i < len; i++ )
            {
                extents.addPoint( pts[i] );
            }
            es = Acad::eOk;
        }
    }

    return es;
}

// cad��Ƶ���ĵ���subClose
Acad::ErrorStatus MineGE::subClose( void )
{
    //acutPrintf(_T("\nid:%d call MineGE::subClose()...\n"), objectId());
	if(!isReallyClosing()) return Acad::eOk;

    Acad::ErrorStatus es = AcDbEntity::subClose () ;

    // new���󲢳ɹ��ύ�����ݿ�֮��
    // ��ʼ�����ӻ�Ч������(��չ����)
    // �������ݶ���(��չ�ʵ�)
    if( es == Acad::eOk )
    {
		initDraw();
		initPropertyData();
    }
    return es;
}

Acad::ErrorStatus MineGE::subErase(Adesk::Boolean erasing)
{
	Acad::ErrorStatus retCode = AcDbEntity::subErase ( erasing ) ;

	if( Acad::eOk == retCode )
	{
		onParamsChanged();
	}
	return Acad::eOk;
}

void MineGE::transformAllTagGE( const AcGeMatrix3d& xform )
{
    if( m_bFollow )
    {
        TransformAllTagGE( this->objectId(), xform );
    }
}

void MineGE::enableFollow( bool bFollow )
{
    assertWriteEnabled () ;
    m_bFollow = bFollow;
}