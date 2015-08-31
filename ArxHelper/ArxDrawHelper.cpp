#include "stdafx.h"
#include "ArxDrawHelper.h"
#include "ArxUtilHelper.h"

AcGePoint2d ArxDrawHelper::Point3D_To_2D( const AcGePoint3d& pt )
{
	return AcGePoint2d( pt.x, pt.y );
}

AcGePoint3d ArxDrawHelper::Point2D_To_3D( const AcGePoint2d& pt )
{
	return AcGePoint3d( pt.x, pt.y, 0 );
}

CString ArxDrawHelper::MakeUpperText( const CString& inStr )
{
	CString str;
	str.Format( _T( "{\\H0.618x;\\S%s^;}" ), inStr );
	return str;
}

CString ArxDrawHelper::MakeLowerText( const CString& inStr )
{
	CString str;
	str.Format( _T( "{\\H0.618x;\\S^%s;}" ), inStr );
	return str;
}

AcGePoint3d ArxDrawHelper::CaclPt( const AcGePoint3d& pt, 
								  const AcGeVector3d& v1, double width, 
								  const AcGeVector3d& v2, double height )
{
	return ( pt + v1 * width / 2 + v2 * height / 2 );
}

AcGePoint3d ArxDrawHelper::CacLineClosePt( const AcGePoint3d& spt, const AcGePoint3d& ept, const AcGePoint3d& pt)
{
	// ����һ�������߶�
	AcGeLineSeg3d line( spt, ept );
	return line.closestPointTo( pt ); // ���������������ĵ�
}

void ArxDrawHelper::BuildRect( const AcGePoint3d& pt, double angle, double width, double height, AcGePoint3dArray& pts )
{
	AcGeVector3d v1( AcGeVector3d::kXAxis ), v2( AcGeVector3d::kXAxis );
	v1.rotateBy( angle, AcGeVector3d::kZAxis );
	v2.rotateBy( angle + PI / 2, AcGeVector3d::kZAxis );

	pts.append( CaclPt( pt, v1, width, v2, height ) );

	v1.rotateBy( PI, AcGeVector3d::kZAxis );
	pts.append( CaclPt( pt, v1, width, v2, height ) );

	v2.rotateBy( PI, AcGeVector3d::kZAxis );
	pts.append( CaclPt( pt, v1, width, v2, height ) );

	v1.rotateBy( PI, AcGeVector3d::kZAxis );
	pts.append( CaclPt( pt, v1, width, v2, height ) );
}

AcDbObjectId ArxDrawHelper::DrawEllipse( const AcGePoint3d& pt, double width, double height )
{
    AcGeVector3d v( AcGeVector3d::kXAxis );
    v *= width / 2;
    double ratio = height / width;
    AcDbEllipse* pEllipse = new AcDbEllipse( pt, AcGeVector3d::kZAxis, v, ratio );
    if(!ArxUtilHelper::PostToModelSpace( pEllipse ))
	{
		delete pEllipse;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pEllipse->objectId();
	}
}

//AcDbObjectId createTextStyle(CString fontName,CString bigFontName,CString textStyleName)
//{
//	AcGiTextStyle *TextStyle=new AcGiTextStyle
//		(fontName,
//		bigFontName,
//		0,
//		0.67,
//		0,
//		0,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		Adesk::kFalse,
//		textStyleName); //������
//	AcDbObjectId textStyleId;
//	toAcDbTextStyle(*TextStyle,textStyleId);
//	return textStyleId;
//}
//
//AcDbObjectId createMutiText(AcGePoint3d BasePoint,AcDb::TextHorzMode hMode,CString Text,double texthight,double widthfactor,double angle,int color,CString smallFontName,CString bigFontName)
//{
//	AcDbMText *pMText=new AcDbMText();
//	AcDbObjectId TextStyleId;
//	TextStyleId=createTextStyle(smallFontName,bigFontName,"xianlu");
//	pMText->setTextStyle(TextStyleId);
//	pMText->setContents(Text.GetBuffer(Text.GetLength()));
//	pMText->setTextHeight(texthight);
//	pMText->setRotation(angle);
//	pMText->setLineSpacingFactor(0.8);
//	pMText->setColorIndex(color);
//	return TextStyleId;
//}

/*
 �ο�����
 https://msdn.microsoft.com/zh-cn/library/ms858335.aspx
 https://msdn.microsoft.com/en-us/library/cc194829.aspx
 http://bbs.mjtd.com/thread-1560-1-1.html
 http://blog.csdn.net/sw283632534/article/details/5401999
 http://blog.csdn.net/jiangdong2007/article/details/39637369
 */

AcDbObjectId ArxDrawHelper::GetTextStyle( const CString& style )
{
    AcDbTextStyleTable* pTextStyleTbl;
    acdbHostApplicationServices()->workingDatabase()->getSymbolTable( pTextStyleTbl, AcDb::kForWrite );
    AcDbObjectId fontId;
    pTextStyleTbl->getAt( style, fontId );
    pTextStyleTbl->close();

    return fontId;
}

AcDbObjectId ArxDrawHelper::CreateTextStyle( const CString& style, const CString& winFont, Adesk::Boolean bold, Adesk::Boolean italic, int charset, int pitchAndFamily )
{
    /*
    //pTextStyleTblRcd->setFileName(_T("simfang.ttf"));
    //pTextStyleTblRcd->setBigFontFileName("hzdx");
    pTextStyleTblRcd->setXScale(0.8);
    //pTextStyleTblRcd->setFont("_T(����_GB2312"),Adesk::kFalse,Adesk::kFalse,GB2312_CHARSET,49);
    //pTextStyleTblRcd->setFont(_T("����"),Adesk::kFalse,Adesk::kFalse,GB2312_CHARSET,2);
    pTextStyleTblRcd->setFont(winFont,Adesk::kFalse,Adesk::kFalse,GB2312_CHARSET,16);
    */

    AcDbTextStyleTable* pTextStyleTbl;
    acdbHostApplicationServices()->workingDatabase()->getSymbolTable( pTextStyleTbl, AcDb::kForWrite );
    AcDbObjectId fontId;
    if( pTextStyleTbl->getAt( style, fontId ) == Acad::eKeyNotFound )
    {
        AcDbTextStyleTableRecord* pTextStyleTblRcd = new AcDbTextStyleTableRecord;
        pTextStyleTblRcd->setName( style );
        pTextStyleTblRcd->setFont( winFont, bold, italic, charset, pitchAndFamily );
        pTextStyleTbl->add( fontId, pTextStyleTblRcd );
        pTextStyleTblRcd->close();
    }
    pTextStyleTbl->close();

    return fontId;
    //acdbHostApplicationServices()->workingDatabase()->setTextstyle(fontId);
}

AcDbObjectId ArxDrawHelper::DrawText( const AcGePoint3d& pt, const CString& text, double height, 
							 AcDb::TextHorzMode hm /*= AcDb::kTextLeft*/, AcDb::TextVertMode vm /*= AcDb::kTextBase*/ )
{
    AcDbText* pText = new AcDbText();
    pText->setTextString( text );
    pText->setHeight( height );
    pText->setHorizontalMode( hm );
    pText->setVerticalMode( vm );
    /*
     * ����AcDbText::setHorizontalMode()��˵��
     * �������ΪAcDb::kTextLeft��Ӧʹ��setPosition()�������ò����
     * �������Ϊ��AcDb::kTextLeft��Ӧʹ��setAlignmentPoint()�������ò����
     * AcDbText::setVerticalMode()����ͬ��!!!
     */
    if( hm != AcDb::kTextLeft || vm == AcDb::kTextBase )
    {
        pText->setAlignmentPoint( pt );
    }
    else
    {
        pText->setPosition( pt );
    }
    // ��������
    /*
    AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kXAxis);
    v1.rotateBy(PI, AcGeVector3d::kZAxis);
    v2.rotateBy(PI*1.5, AcGeVector3d::kZAxis);
    pText->setPosition(pt + (v1*width + v2*height)/2);

    pText->setAlignmentPoint(pt + (v2*height)/2);
    pText->setAlignmentPoint(pt);
    */

    if(!ArxUtilHelper::PostToModelSpace( pText ))
	{
		delete pText;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pText->objectId();
	}
}

AcDbObjectId ArxDrawHelper::DrawMText( const AcGePoint3d& pt, double angle, const CString& text, double height )
{
    AcDbMText* pMText = new AcDbMText;
    //AcDbObjectId style; // ������ʽ
    //pMText->setTextStyle(style);
    pMText->setLocation( pt );
    pMText->setRotation( angle );
    //pMText->setWidth(width); // �����ÿ�ȣ��Զ�����
    pMText->setTextHeight( height );
    pMText->setAttachment( AcDbMText::kMiddleCenter ); // Ĭ�Ͼ���
    pMText->setContents( text );

    //acutPrintf(_T("\n���ֿ��:%.3f"), pMText->actualWidth());

    if(!ArxUtilHelper::PostToModelSpace( pMText ))
	{
		delete pMText;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pMText->objectId();
	}
}

void ArxDrawHelper::DrawLines( const AcGePoint3dArray& pts )
{
    // ������ֱͨ��
    // �ö���ֱ�����ӳ�һ����֧
    int len = pts.length();
    AcDbPolyline* pPline = new AcDbPolyline( len );
    for( int i = 0; i < len - 1; i++ )
    {
        AcDbLine* pLine = new AcDbLine( pts[i], pts[i + 1] );
        ArxUtilHelper::PostToModelSpace( pLine );
    }
}

AcDbObjectId ArxDrawHelper::DrawPolyLine( const AcGePoint3dArray& pts, bool isClosed )
{
    // ���ƶ����
    int len = pts.length();
	if( len < 2 ) return AcDbObjectId::kNull;

    AcDbPolyline* pPline = new AcDbPolyline( len );
    for( int i = 0; i < len; i++ )
    {
        AcGePoint2d pt;
        pt.set( pts[i].x, pts[i].y );
        pPline->addVertexAt( i, pt );
    }
    pPline->setClosed( isClosed );
    if(!ArxUtilHelper::PostToModelSpace( pPline ))
	{
		delete pPline;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pPline->objectId();
	}
}

AcDbObjectId ArxDrawHelper::DrawSpline( const AcGePoint3dArray& pts )
{
    // ������������
    AcDbSpline* pSpline = new AcDbSpline( pts );
    if(!ArxUtilHelper::PostToModelSpace( pSpline ))
	{
		delete pSpline;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pSpline->objectId();
	}
}

static void Swap( double& a, double& b )
{
    double temp = a;
    a = b;
    b = temp;
}

AcDbObjectId ArxDrawHelper::DrawArc( const AcGePoint3d& spt, const AcGePoint3d& pt, const AcGePoint3d& ept )
{
    AcGeCircArc3d arc( spt, pt, ept );
    AcGePoint3d cnt = arc.center();
    double radius = arc.radius();
    AcGeVector3d sv = spt - cnt;
    AcGeVector3d ev = ept - cnt;
    double sa = sv.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
    double ea = ev.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );

    if( arc.normal().z <= 0 )
    {
        Swap( sa, ea );
    }

    AcDbArc* pArc = new AcDbArc( cnt, radius, sa, ea );
   if(!ArxUtilHelper::PostToModelSpace( pArc ))
   {
	   delete pArc;
	   return AcDbObjectId::kNull;
   }
   else
   {
		return pArc->objectId();
   }
}

AcDbObjectId ArxDrawHelper::DrawLine( const AcGePoint3d& spt, const AcGePoint3d& ept )
{
    AcDbLine* pLine = new AcDbLine( spt, ept );
    if(!ArxUtilHelper::PostToModelSpace( pLine ))
	{
		delete pLine;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pLine->objectId();
	}
}

AcDbObjectId ArxDrawHelper::DrawLine( const AcGePoint3d& pt, double angle, double length )
{
	AcGeVector3d v( AcGeVector3d::kXAxis );
	v.rotateBy( angle, AcGeVector3d::kZAxis );
	return DrawLine( pt, pt + v * length );
}

AcDbObjectId ArxDrawHelper::DrawCircle( const AcGePoint3d& pt, double radius )
{
    AcDbCircle* pCircle = new AcDbCircle( pt, AcGeVector3d::kZAxis, radius );
    if(!ArxUtilHelper::PostToModelSpace( pCircle ))
	{
		delete pCircle;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pCircle->objectId();
	}
}

AcDbObjectId ArxDrawHelper::DrawPolyLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width )
{
	AcDbPolyline* pl = new AcDbPolyline( 2 );
	pl->addVertexAt( 0, Point3D_To_2D( spt ) );
	pl->addVertexAt( 1, Point3D_To_2D( ept ) );
	pl->setConstantWidth( width );
	if(!ArxUtilHelper::PostToModelSpace( pl ))
	{
		delete pl;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pl->objectId();
	}
}

AcDbObjectId ArxDrawHelper::DrawPolyLine( const AcGePoint3d& pt, double angle, double length, double width )
{
	AcGeVector3d v( AcGeVector3d::kXAxis );
	v.rotateBy( angle, AcGeVector3d::kZAxis );

	AcDbPolyline* pl = new AcDbPolyline( 2 );
	pl->addVertexAt( 0, Point3D_To_2D( pt ) );
	pl->addVertexAt( 1, Point3D_To_2D( pt + v * length ) );
	pl->setConstantWidth( width );
	if(!ArxUtilHelper::PostToModelSpace( pl ))
	{
		delete pl;
		return AcDbObjectId::kNull;
	}
	else
	{
		return pl->objectId();
	}
}

// ���Ƽ�ͷ
void ArxDrawHelper::DrawArrow( const AcGePoint3d& pt, double angle, double width, double length )
{
	AcGeVector3d v( AcGeVector3d::kXAxis );
	v.rotateBy( angle, AcGeVector3d::kZAxis );

	AcDbPolyline* pl = new AcDbPolyline( 2 );
	pl->addVertexAt( 0, Point3D_To_2D( pt ) );
	pl->addVertexAt( 1, Point3D_To_2D( pt + v * length ) );
	pl->setWidthsAt( 0, width, 0 );
	pl->setWidthsAt( 1, 0, 0 );
	ArxUtilHelper::PostToModelSpace( pl );
}

AcDbObjectId ArxDrawHelper::DrawRect( const AcGePoint3d& pt, double angle, double width, double height )
{
	AcGePoint3dArray pts;
	BuildRect( pt, angle, width, height, pts );
	return ArxDrawHelper::DrawPolyLine(pts, true);
}

void ArxDrawHelper::CreatePolygonLoop( AcDbHatch* pHatch, const AcGePoint3dArray& pts )
{
	AcGeIntArray edgeTypes;
	AcGeVoidPointerArray edgePtrs;

	int n = pts.length();
	for( int i = 0; i < n; i++ )
	{
		AcGePoint2d p1 = Point3D_To_2D( pts[i] );
		AcGePoint2d p2 = Point3D_To_2D( pts[( i + 1 ) % n] );
		AcGeLineSeg2d* pLine = new AcGeLineSeg2d( p1, p2 );

		edgePtrs.append( pLine );
		edgeTypes.append( AcDbHatch::kLine );
	}

	pHatch->appendLoop( AcDbHatch::kDefault, edgePtrs, edgeTypes );
}

void ArxDrawHelper::CreateCircleLoop( AcDbHatch* pHatch, const AcGePoint3d& pt, double radius )
{
	AcGeCircArc2d* cirArc = new AcGeCircArc2d();
	cirArc->setCenter( Point3D_To_2D( pt ) );
	cirArc->setRadius( radius );
	cirArc->setAngles( 0.0, PI * 2 );

	AcGeIntArray edgeTypes;
	AcGeVoidPointerArray edgePtrs;

	edgeTypes.append( AcDbHatch::kCirArc );
	edgePtrs.append( ( void* )cirArc );

	pHatch->appendLoop( AcDbHatch::kDefault, edgePtrs, edgeTypes );
}

void ArxDrawHelper::CreatePreDefinedHatch( AcDbHatch* pHatch, const CString& patName, double scale )
{
	// Set hatch plane
	pHatch->setNormal( AcGeVector3d::kZAxis );
	pHatch->setElevation( 0.0 );

	// Set non associative hatch
	pHatch->setAssociative( Adesk::kFalse );

	// Set hatch pattern to SolidFill type
	// ����hatch pattern֮���ٵ���setPattern������Ч
	pHatch->setPatternScale( scale );
	pHatch->setPattern( AcDbHatch::kPreDefined, patName );

	// Set hatch style to kNormal
	pHatch->setHatchStyle( AcDbHatch::kNormal );
}

void ArxDrawHelper::CreateGradientObject( AcDbHatch* pHatch, const CString& gradName, const AcCmColor& c1, const AcCmColor& c2 )
{
	// Set hatch plane
	pHatch->setNormal( AcGeVector3d::kZAxis );
	pHatch->setElevation( 0.0 );

	// Set non associative hatch
	pHatch->setAssociative( Adesk::kFalse );

	// Set hatch pattern to SolidFill type
	//pHatch->setPattern(AcDbHatch::kPreDefined, _T("SOLID"));

	// Set hatch style to kNormal
	//pHatch->setHatchStyle(AcDbHatch::kNormal);

	// ����Ϊ����ɫ���
	pHatch->setHatchObjectType( AcDbHatch::kGradientObject );

	// set gradient
	pHatch->setGradient( AcDbHatch::kPreDefinedGradient, gradName );
	pHatch->setGradientOneColorMode( false ); // ʵ���϶���˫ɫ

	AcCmColor colors[2] = {c1, c2};
	float values[2] = {0.0f, 1.0f};

	pHatch->setGradientColors( 2, colors, values );
}

AcDbObjectId ArxDrawHelper::DrawPolygonHatch( const AcGePoint3dArray& pts, const CString& patName, double scale )
{
	if( pts.isEmpty() ) return AcDbObjectId::kNull;

	AcDbHatch* hatch = new AcDbHatch;
	// set color
	//AcCmColor color;
	//color.setRGB(r, g, b);
	//pHatch->setColor(color);

	CreatePreDefinedHatch( hatch, patName, scale );
	CreatePolygonLoop( hatch, pts );

	// Elaborate solid fill
	hatch->evaluateHatch();
	if(!ArxUtilHelper::PostToModelSpace(hatch))
	{
		delete hatch;
		return AcDbObjectId::kNull;
	}
	else
	{
		return hatch->objectId();
	}
}

AcDbObjectId ArxDrawHelper::DrawCircleGradient( const AcGePoint3d& pt, double radius, const CString& gradName, const AcCmColor& c1, const AcCmColor& c2 )
{
	AcDbHatch* hatch = new AcDbHatch;

	CreateGradientObject( hatch, gradName, c1, c2 );
	CreateCircleLoop( hatch, pt, radius );

	//pHatch->evaluateHatch();
	if(!ArxUtilHelper::PostToModelSpace(hatch))
	{
		delete hatch;
		return AcDbObjectId::kNull;
	}
	else
	{
		return hatch->objectId();
	}
}

// ����ֵ:
//		0  -- ����
//		1  -- ˳ʱ��
//	   -1  -- ��ʱ��
int ArxDrawHelper::ClockWise( const AcGePoint3dArray& polygon )
{
	int n = polygon.length();
	if ( n < 3 ) return 0;

	int count = 0;
	for( int i = 0; i < n; i++ )
	{
		int j = ( i + 1 ) % n;
		int k = ( i + 2 ) % n;
		double z  = ( polygon[j].x - polygon[i].x ) * ( polygon[k].y - polygon[j].y );
		z -= ( polygon[j].y - polygon[i].y ) * ( polygon[k].x - polygon[j].x );
		if ( z < 0 )
		{
			count--;
		}
		else if ( z > 0 )
		{
			count++;
		}
	}
	if ( count > 0 )
		return -1;
	else if ( count < 0 )
		return 1;
	else
		return 0;
}

// �պ϶��������ƫ��
bool ArxDrawHelper::OffSetPolygon( const AcGePoint3dArray& polygon, double offset, bool is_inner, AcGePoint3dArray& offset_polygon )
{
	// �ж϶���η���
	int dir = ClockWise( polygon );
	if( dir == 0 ) return false;

	// ���ڻ�����???
	int c = ( is_inner ? -1 : 1 );

	// ƫ�Ʒ���Ƕ�
	//		1) �����εķ����й�(dir)
	//		2) ��Ҫƫ�Ƶķ����й�(is_inner)
	double angle = c * dir * PI * 0.5;

	bool ret = true;

	int n = polygon.length();
	for( int i = 0; i < n; i++ )
	{
		int p1 = ( n + i - 1 ) % n, p2 = i % n, p3 = ( i + 1 ) % n;

		// �Ե����ƫ��
		// ����ƫ������
		AcGeVector3d v1 = polygon[p2] - polygon[p1];
		v1.normalize();
		v1.rotateBy( angle, AcGeVector3d::kZAxis );

		AcGeVector3d v2 = polygon[p3] - polygon[p2];
		v2.normalize();
		v2.rotateBy( angle, AcGeVector3d::kZAxis );

		// �����������ļн�
		double angle = v1.angleTo( v2 );
		double L = abs( offset / cos( angle * 0.5 ) );

		AcGeVector3d v = v1 + v2;
		v.normalize();

		offset_polygon.append( polygon[p2] + v * L );
	}
	return ret;
}

static Acad::ErrorStatus GetLinetypeId( const CString& linetype, AcDbObjectId& linetypeId )
{
	AcDbLinetypeTable* pLtpTbl;
	acdbHostApplicationServices()->workingDatabase()->getLinetypeTable( pLtpTbl, AcDb::kForRead );
	if ( !pLtpTbl->has( linetype ) )
	{
		pLtpTbl->close();
		return Acad::eBadLinetypeName;
	}
	pLtpTbl->getAt( linetype, linetypeId );
	pLtpTbl->close();
	return Acad::eOk;
}

static void AddLineType( CString lineTypeName )
{
	// �������ͣ����ַ�����
	Acad::ErrorStatus es;
	//es = acdbHostApplicationServices()->workingDatabase()->loadLineTypeFile(_T("CENTER"), _T("acadiso.lin"));
	es = acdbLoadLineTypeFile( lineTypeName, _T( "acadiso.lin" ), acdbHostApplicationServices()->workingDatabase() );
	// �����µ�AcDbMlineStyle����
	AcDbMlineStyle* pMlStyle = new AcDbMlineStyle;
	pMlStyle->initMlineStyle();
	pMlStyle->setName( _T( "NewStyle" ) );
	int index; // ������ʽ�е�Ԫ������
	//AcCmColor color; // ��ɫ
	AcDbObjectId linetypeId; // ���͵�ID
	// ��ӵ�һ��Ԫ�أ���ɫ�������ߣ�
	//color.setColorIndex(1); // ��ɫ
	GetLinetypeId( lineTypeName, linetypeId );
	//pMlStyle->addElement(index, 0, color, linetypeId);
	//// ��ӵڶ���Ԫ�أ���ɫ�����ߣ�
	//color.setColorIndex(5); // ��ɫ
	//GetLinetypeId("HIDDEN", linetypeId);
	//pMlStyle->addElement(index, 0.5, color, linetypeId);
	//// ��ӵ�����Ԫ�أ���ɫ�����ߣ�
	//pMlStyle->addElement(index, -0.5, color, linetypeId);
	//// ��������ʽ��ӵ�������ʽ�ֵ���
	AcDbDictionary* pDict;
	acdbHostApplicationServices()->workingDatabase()->getMLStyleDictionary( pDict, AcDb::kForWrite );
	AcDbObjectId mlStyleId;
	es = pDict->setAt( _T( "NewStyle" ), pMlStyle, mlStyleId );
	pDict->close();
	pMlStyle->close();
}

static void DrawDotLine( const AcGePoint3d& spt, const AcGePoint3d& ept )
{
	AddLineType( _T( "CENTER" ) );
	AcDbLine line( spt, ept );
	line.setLinetype( _T( "CENTER" ) );
}