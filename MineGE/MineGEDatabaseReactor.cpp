#include "StdAfx.h"
#include "MineGEDatabaseReactor.h"
#include "HelperClass.h"
#include "TagGE.h"
#include "ModelGE.h"
#include "LinkedGE.h"
#include "DataObject.h"

#include <ArxHelper/HelperClass.h>

MineGEDatabaseReactor::MineGEDatabaseReactor ( AcDbDatabase* pDb ) : AcDbDatabaseReactor(), mpDatabase( pDb )
{
    if ( pDb )
    {
        //acutPrintf(_T("\nMineGEErase_DbReactor : %ld"), (long)pDb);
        pDb->addReactor ( this ) ;
    }
}

MineGEDatabaseReactor::~MineGEDatabaseReactor ()
{
    Detach () ;
}

void MineGEDatabaseReactor::Attach ( AcDbDatabase* pDb )
{
    Detach () ;
    if ( mpDatabase == NULL )
    {
        if ( ( mpDatabase = pDb ) != NULL )
            pDb->addReactor ( this ) ;
    }
}

void MineGEDatabaseReactor::Detach ()
{
    if ( mpDatabase )
    {
        mpDatabase->removeReactor ( this ) ;
        mpDatabase = NULL ;
    }
}

AcDbDatabase* MineGEDatabaseReactor::Subject () const
{
    return ( mpDatabase ) ;
}

bool MineGEDatabaseReactor::IsAttached () const
{
    return ( mpDatabase != NULL ) ;
}

static void FilterTagGE( const AcDbObjectId& objId,
                         const AcDbObjectIdArray& allObjIds,
                         Adesk::Boolean pErased,
                         AcDbObjectIdArray& objIds )
{
    if( allObjIds.isEmpty() ) return;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = allObjIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, allObjIds[i], AcDb::kForRead, !pErased ) ) continue;

        TagGE* pTag = TagGE::cast( pObj );
        if( pTag == 0 ) continue;

        if( pTag->getRelatedGE() == objId )
        {
            objIds.append( allObjIds[i] );
        }
    }
    actrTransactionManager->endTransaction();
}

static void FilterModelGE( const AcDbObjectId& objId,
                           const AcDbObjectIdArray& allObjIds,
                           Adesk::Boolean pErased,
                           AcDbObjectIdArray& objIds )
{
    if( allObjIds.isEmpty() ) return;

    AcTransaction* pTrans = actrTransactionManager->startTransaction();
    if( pTrans == 0 ) return;

    int len = allObjIds.length();
    for( int i = 0; i < len; i++ )
    {
        AcDbObject* pObj;
        if( Acad::eOk != pTrans->getObject( pObj, allObjIds[i], AcDb::kForRead, !pErased ) ) continue;

        ModelGE* pM = ModelGE::cast( pObj );
        if( pM == 0 ) continue;

        if( pM->getDataObject() == objId )
        {
            objIds.append( allObjIds[i] );
        }
    }
    actrTransactionManager->endTransaction();
}

static void GetEntsByType_Helper( const CString& type, Adesk::Boolean pErased, AcDbObjectIdArray& allObjIds )
{
    if( pErased )
    {
        ArxDataTool::GetEntsByType( type, allObjIds, true );
    }
    else
    {
        ArxDataTool::GetErasedEntsByType( type, allObjIds, true );
    }
}

static void GetAllTagGEById( const AcDbObjectId& objId, Adesk::Boolean pErased, AcDbObjectIdArray& objIds )
{
    //acutPrintf(_T("\n��ʼ��ȡid..."));
    if( objId.isNull() ) return;

    AcDbObjectIdArray allObjIds;
    GetEntsByType_Helper( _T( "TagGE" ), pErased, allObjIds );

    // ����ɸѡ����objId������TagGE
    FilterTagGE( objId, allObjIds, pErased, objIds );

    //acutPrintf(_T("\n������ȡid..."));
}

static void GetAllModelGEById( const AcDbObjectId& objId, Adesk::Boolean pErased, AcDbObjectIdArray& objIds )
{
    //acutPrintf(_T("\n��ʼ��ȡid..."));
    if( objId.isNull() ) return;

    AcDbObjectIdArray allObjIds;
    GetEntsByType_Helper( _T( "ModelGE" ), pErased, allObjIds );

    // ����ɸѡ����objId������ModelGE
    FilterModelGE( objId, allObjIds, pErased, objIds );

    //acutPrintf(_T("\n������ȡid..."));
}

static void EraseAllTagGE( const AcDbObjectId& objId, Adesk::Boolean pErased )
{
    AcDbObjectIdArray objIds;
    GetAllTagGEById( objId, pErased, objIds );
    ArxEntityHelper::EraseObjects2( objIds, pErased );
}

static void EraseAllModelGE( const AcDbObjectId& objId, Adesk::Boolean pErased )
{
    AcDbObjectIdArray objIds;
    GetAllModelGEById( objId, pErased, objIds );
    ArxEntityHelper::EraseObjects2( objIds, pErased );
}

void MineGEDatabaseReactor::objectErased( const AcDbDatabase* dwg, const AcDbObject* dbObj, Adesk::Boolean pErased )
{
    AcDbDatabaseReactor::objectErased ( dwg, dbObj, pErased );

    //acutPrintf(_T("\n��ʼ ==> ���ݿ���ӣ�id:%ld  %s"), dbObj->objectId(), (pErased?_T("ɾ��"):_T("��ɾ��")));
    if( !pErased ) return;

    // ����ͼԪ��Ҫ��������cad���ݿ⣬���Ч�ʽϵ�
    // ��ˣ�һ��Ҫ�����жϣ����߻�Ӱ�쵽����ͼԪ(����ɾ��1000��ֱ��)��ɾ��
    if( dbObj->isKindOf( MineGE::desc() ) )
    {
        // ɾ��ͼԪ�������е�TagGE
        EraseAllTagGE( dbObj->objectId(), pErased );

        // ɾ��ͼԪ�����ݶ���������е�ModelGE
        MineGE* pGE = MineGE::cast( dbObj );
        EraseAllModelGE( pGE->getDataObject(), pErased );
    }
    else if( dbObj->isKindOf( ModelGE::desc() ) )
    {
        // do nothing
    }
    else if( dbObj->isKindOf( DataObject::desc() ) )
    {
        DataObject* pDO = DataObject::cast( dbObj );
        if( !pDO->getGE().isNull() )
        {
            acutPrintf( _T( "\n�����桿��Ŀǰ�ݲ�����ɾ����ͼԪ���������ݶ���" ) );
        }
    }

    //acutPrintf(_T("\n���� ==> ���ݿ���ӣ�id:%ld  %s"), dbObj->objectId(), (pErased?_T("ɾ��"):_T("��ɾ��")));
}

static void DoEdgeGEJunctionClosure( LinkedGE* pEdge )
{
	AcGePoint3d spt, ept;
	pEdge->getSEPoint( spt, ept );

	DrawHelper::LinkedGEJunctionClosure( spt );
	DrawHelper::LinkedGEJunctionClosure( ept );
}

static void DoEdgeGEJunctionClosure2( const AcDbObject* pObj )
{
	LinkedGE* pEdge = LinkedGE::cast( pObj );
	if( pEdge != 0 )
	{
		//DrawHelper::LinkedGEJunctionClosure2(pEdge->objectId());
		DoEdgeGEJunctionClosure( pEdge );
	}
}

// ��objectModified���޷���������
void MineGEDatabaseReactor::objectModified( const AcDbDatabase* dwg, const AcDbObject* dbObj )
{
    AcDbDatabaseReactor::objectModified ( dwg, dbObj );
	DataObject* pDO = DataObject::cast( dbObj );
    if(pDO != 0)
    {
		DrawHelper::Update(pDO->getGE());
		DrawHelper::LinkedGEJunctionClosure2(pDO->getGE());
    }
}

void MineGEDatabaseReactor::objectAppended( const AcDbDatabase* db, const AcDbObject* pObj )
{
	//acutPrintf(_T("\noid:%d call objectAppended()...:%s"), pObj->objectId());

	DoEdgeGEJunctionClosure2( pObj );
}