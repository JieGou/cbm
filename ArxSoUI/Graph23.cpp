#include "StdAfx.h"
#include "Graph23.h"

#include <Util/HelperClass.h>
#include <ArxHelper/HelperClass.h>

namespace P23
{

    Graph::Graph( const cbm::CoalPtr& _coal, const cbm::DesignWorkSurfTechnologyPtr& _tech )
        : BaseGraph(), coal( _coal ), tech( _tech )
    {
        left_margin = 8;
        right_margin = 8;
        bottom_margin = 8;
        top_margin = 8;

        //���򳤶Ⱥ����򳤶�
        L1 = tech->l1, L2 = tech->l2;
        //ú���Ⱥ����(����)
        thick = coal->thick, angle = DegToRad( coal->dip_angle );
        //����������Ŀ�Ⱥ͸߶�
        w = tech->w, h = tech->h;
        //��װ뾶����׵׼��(�׾��ĵ�λ��mm)
        radius = tech->dp * 0.5 * 0.001, pore_gap = tech->gp;
        //���ѹ�糤��
        pore_stubble = tech->pore_stubble;
        //˳��б��������
        pore_angle = DegToRad( tech->pore_angle );
        //˳���������
        pore_type = tech->pore_type;
    }

    void Graph::subDraw()
    {
        //����ͼ��
        drawCoal();
        drawTunnel();
        drawPores();
    }

    void Graph::caclCoalExtent( double& Lc, double& Wc, double& Hc ) const
    {
        //������(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
        //Lc = (L1 + left_margin + right_margin)*cos(angle);
        Lc = L1 + left_margin + right_margin;
        Wc = L2 + bottom_margin + top_margin;
        Hc = thick;
    }

    PlanGraph::PlanGraph( const cbm::CoalPtr& coal, const cbm::DesignWorkSurfTechnologyPtr& tech ) : Graph( coal,  tech )
    {
    }

    void PlanGraph::drawParallelPores()
    {
        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        double PL = pore_stubble + L2 * 0.5;
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( basePt + v1 * w * 0.5 + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, pore_gap, 0, pts );
        v2.rotateBy( PI, AcGeVector3d::kZAxis );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcGePoint3d pt = pts[i];
            this->drawLine( pt, pt + v2 * PL );
        }
        v2.rotateBy( PI, AcGeVector3d::kZAxis );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcGePoint3d pt = pts[i] - v2 * L2 + v1 * pore_gap * 0.5;
            this->drawLine( pt, pt + v2 * PL );
        }
    }

    void PlanGraph::drawCrossPores()
    {
        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        double d = 0.5 * L2 / tan( pore_angle );
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( basePt + v1 * 0.5 * w, basePt + v1 * ( L1 - d ), pore_gap, 0, pts, true );
        AcGePoint3dArray pts1;
        ArxDrawHelper::Divide( basePt + v1 * ( d + w * 0.5 ) + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, pore_gap, 0, pts1, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            this->drawLine( pts1[i], pts[i] );
        }
        AcGePoint3dArray pts2;
        ArxDrawHelper::Divide( basePt + v1 * ( d + w * 0.5 ) - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, pore_gap, 0, pts2, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            this->drawLine( pts2[i] + v1 * pore_gap * 0.5, pts[i] + v1 * pore_gap * 0.5 );
        }
    }

    void PlanGraph::drawPores()
    {
        if( pore_gap <= 0 ) return;

        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        //˳��ƽ�����
        if( pore_type == 1 )
        {
            drawParallelPores();
        }
        //˳����бƽ�����
        else if( pore_type == 2 )
        {
            drawCrossPores();
        }
        else if( pore_type == 3 )
        {

        }
        else if( pore_type == 4 )
        {
            drawParallelPores();
            drawCrossPores();
        }
    }

    void PlanGraph::drawTunnel()
    {
        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        //���ƹ�����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, w );
        //���Ʒ���
        AcDbObjectId t2 = this->drawDoubleLine( basePt + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, w );
        //���ƹ���������
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, w );
    }

    void PlanGraph::drawCoal()
    {
        //����ú��ĳ����
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );

        //����ƽ��ͼ��ú������½ǻ�������
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * left_margin, v2, -0.5 * Wc );

        //����ú����
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Lc, Wc );
        this->drawAlignedDim( basePt, basePt + v1 * Lc, 50, false );
        this->drawAlignedDim( basePt, basePt + v2 * Wc, 30, true );
    }
} // namespace P23