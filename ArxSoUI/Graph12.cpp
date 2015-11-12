#include "StdAfx.h"
#include "Graph12.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"

namespace P12
{

    Graph::Graph( cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech )
        : BaseGraph(), coal( _coal ), tech( _tech )
    {
        left_margin = 20;
        right_margin = 20;
        bottom_margin = 20;
        top_margin = 20;

        //���򳤶Ⱥ����򳤶�
        L1 = tech.l1, L2 = tech.l2;
        //ú���Ⱥ����(����)
        thick = coal.thick, angle = DegToRad( coal.dip_angle );
        //����������Ŀ�Ⱥ͸߶�
        w = tech.w, h = tech.h;
        //�������°��
        left = tech.left_side, right = tech.right_side;
        top = tech.top_side, bottom = tech.bottom_side;
        //��װ뾶����׵׼��(�׾��ĵ�λ��mm)
        radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gbp;
        //��׳�ǰ��
        leading = tech.leading_dist;
        //��׿�����������
        L_stripe = tech.l_stripe;
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
        //Lc = (L1 + left + left_margin + right_margin)*cos(angle);
        Lc = L1 + left + left_margin + right_margin;
        //Wc = L2 + left + right + bottom_margin + top_margin;
        Wc = w + left + right + bottom_margin + top_margin;
        Hc = thick;
    }

    PlanGraph::PlanGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal,  tech )
    {
    }

    void PlanGraph::drawPores()
    {
        if( pore_gap <= 0 ) return;

        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        //������׳�ɿ��Ʒ�Χ
        double Lp = 0, Wp = 0, Hp = 0;
        Lp = L1;
        Wp = left + right + w;
        drawLine( basePt + v1 * 0 + v2 * Wp * 0.5, 0, Lp );
        drawLine( basePt + v1 * 0 - v2 * Wp * 0.5, 0, Lp );

        //������������ڳ�������ߵ�ˮƽ���
        double L0 = leading, W0 = left, D = pore_gap, Ls = L_stripe;
        DoubleArray h_dists;
        ArxDrawHelper::Solve1( L0, W0, D, L_stripe - leading, h_dists );

        //������������������߽��ϵĴ�ֱ���
        DoubleArray v_dists;
        ArxDrawHelper::Solve2( Ls, W0, D, v_dists );

        //��ע
        this->drawAlignedDim( basePt, basePt + v1 * Ls, 50, false );      //������Χ
        this->drawAlignedDim( basePt + v1 * ( Ls - L0 ), basePt + v1 * Ls, 30, false ); //��׳�ǰ��

        //����ÿ����������ʼλ��
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( basePt, basePt + v1 * L1, L_stripe - leading, 0, pts, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            //���ƾ����
            AcGePoint3d pt = pts[i];
            drawLine( pt - v2 * w * 0.5, pt + v2 * w * 0.5 );
            //���ƾ�������ʼ����
            drawLine( pt - v2 * W0, pt + v2 * W0 );

            //��¼���ͼԪid
            AcDbObjectIdArray objIds;

            //��ǰ��Ķ������ĵ�����
            AcGePoint3d poreBeginPt = pt + v1 * L0;
            //�����ϲ������ߵ��������
            double pore_dist = 0;
            for( int j = 0; j < h_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, poreBeginPt + v1 * pore_dist + v2 * W0 );
                pore_dist += h_dists[j];
                objIds.append( poreId );
            }
            //�����²������ߵ��������
            pore_dist = 0;
            for( int j = 0; j < h_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, poreBeginPt + v1 * pore_dist - v2 * W0 );
                pore_dist += h_dists[j];
                objIds.append( poreId );
            }

            //�����ϲ�����������������
            pore_dist = 0;
            for( int j = 0; j < v_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls + v2 * ( W0 + pore_dist ) );
                pore_dist -= v_dists[j];
                objIds.append( poreId );
            }
            //�����²�����������������
            pore_dist = 0;
            for( int j = 0; j < v_dists.size(); j++ )
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls - v2 * ( W0 + pore_dist ) );
                pore_dist -= v_dists[j];
                objIds.append( poreId );
            }

            //���������ߵ����
            {
                AcDbObjectId poreId = drawLine( pt, pt + v1 * Ls );
                objIds.append( poreId );
            }

            // ������������
            AcGePoint3d poreEndPt = pt + v1 * L_stripe;
            drawLine( poreEndPt - v2 * W0, poreEndPt + v2 * W0 );

            //iΪ�����޸�����Ϊ����
            if( i % 2 != 0 )
            {
                ArxDrawHelper::SetLineType( objIds, _T( "JIS_02_0.7" ) );
            }
            objIds.removeAll();
        }
    }

    void PlanGraph::drawTunnel()
    {
        //������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        //���ƾ����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcDbObjectId t1 = this->drawDoubleLine( basePt, basePt + v1 * L1, w );
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
} // namespace P12