#include "StdAfx.h"
#include "Graph11.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "GraphHelper.h"

namespace P11
{

	PoreHelper::PoreHelper(cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech)
		: coal( _coal ), tech( _tech )
	{
		//���򳤶Ⱥ����򳤶�
		L1 = tech.l1, L2 = tech.l2;
		//ú���Ⱥ����(����)
		thick = coal.thick, angle = DegToRad( coal.dip_angle );
		//����������Ŀ�Ⱥ͸߶�
		w = tech.w, h = tech.h;
		//�װ���Ŀ�Ⱥ͸߶�
		wd = tech.wd, hd = tech.hd;
		//�������°��
		left = tech.left_side, right = tech.right_side;
		top = tech.top_side, bottom = tech.bottom_side;
		//�곡���ȡ���Ⱥ͸߶�
		Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
		//����͹������ˮƽͶӰ���롢����
		h_offset = tech.h_offset, v_offset = tech.v_offset;
		//��װ뾶�ͳ�ɰ뾶(�׾��ĵ�λ��mm)
		radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gp;
		//�곡���
		site_gap = tech.gs;
	}

	void PoreHelper::drawPores1(int region_num, const AcGePoint3dArray& site_pts, const IntArray& nums, const AcGePoint3dArray& pore_pts, int nx, int r1, int r2, int c1, int c2, std::vector<cbm::DesignPore>& pores)
	{
		// (1)������������
		int n = site_pts.length();
		// ��ױ��
		int m = 1;
		for(int i=n-1;i>=0;i--)
		{
			// �곡����x,y,z
			AcGePoint3d site_pt = site_pts[i];

			//�½��곡
			cbm::DesignSite site;
			GraphHelper::CreateSite(site, n-i, site_pt, tech.design_technology_id);
			// �ύ�����ݿ�
			int32_t site_id = SQLClientHelper::AddDesignSite(site);
			if(site_id <= 0) 
			{
				acutPrintf(_T("\n����곡�����ݿ�ʧ��!!!"));
				break;
			}

			// �곡��������ʼλ��
			c2 -= nums[i];
			acutPrintf(_T("\n����---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int j=r1-1;j>=r2;j--)
			{
				for(int k=c1-1;k>=c2;k--)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString num;
					num.Format(_T("%d-%d-%d"), region_num, n-i, m++);
					// �������
					AcGePoint3d pore_pt = pore_pts[j*nx+k];

					// �½����
					cbm::DesignPore pore;
					GraphHelper::CreatePore(pore, num, site_pt, pore_pt, site_id);

					// ��¼�½�����׶���
					pores.push_back(pore);
				}
			}
			c1 = c2;
		}
	}

	void PoreHelper::cacl()
	{
		// ɾ�����е��곡�����
		GraphHelper::DeleteAllSiteAndPore(tech.design_technology_id);

		// ������������е���Ϊԭ��
		AcGePoint3d orig(AcGePoint3d::kOrigin);

		// ��׿��Ʒ�Χ
		double Lc = left + L1, Wc = L2 + top + bottom;
		// ���Ʒ�Χ���½ǵ�����(��׵�ԭ��)
		AcGeVector3d v1(AcGeVector3d::kXAxis), v2(AcGeVector3d::kYAxis), v3(AcGeVector3d::kZAxis);
		AcGePoint3d pore_orig = orig + v1*left*-1 + v2*(0.5*L2+left)*-1 + v3*top;
		
		//�۳��Ұ�
		double Ld = L1 - right;

		// ��������������е��������
		// �������е��տ׶���ͬһ��ˮƽ����
		AcGePoint3dArray pore_pts;
		ArxDrawHelper::MakeGridWithHole( pore_orig, Lc, Wc, pore_gap, pore_gap, 0, Lc, 0, Wc, pore_pts, true );

		//�������������(��)������(��)�ĸ���(�л���)
		int nx = ArxDrawHelper::DivideNum( Lc, pore_gap, true );
		int ny = ArxDrawHelper::DivideNum( Wc, pore_gap, true );
		//��������(��)������곡��(�л���)
		int mx = ArxDrawHelper::DivideNum( Ld, site_gap, true ) - 1;
		//��������(��)������곡��(�л���)
		int my = ArxDrawHelper::DivideNum( L2, site_gap, true ) - 1;
		//�������ﷶΧ�ڵ������(�л���)
		int d1 = ArxDrawHelper::DivideNum( left + right, pore_gap, true );
		//ÿ���곡֮�����׸���
		int d2 = ArxDrawHelper::DivideNum( site_gap, pore_gap, true );

		acutPrintf(_T("\n����������:%d  �������:%d  ��׵��ܸ���:%d"), nx, ny, pore_pts.length());
		acutPrintf(_T("\n�곡�������:%d  �������:%d, ���ﷶΧ��׸���:%d  �곡֮��ĸ���:%d"), mx, my, d1, d2);
		// �����곡������(CaclSitesOnTunnel�����ĺ�3������Ŀǰû���õ�!!!)
		// (0)������װ�������е�����
		AcGePoint3d site_orig = orig + v1*right + v2*h_offset + v3*v_offset*-1;
		// (1)���������곡����
		AcGePoint3dArray site_pts1;
		GraphHelper::CaclSitesOnTunnel( site_pts1, site_orig - v2 * L2 * 0.5, site_orig + v1 * Ld - v2 * 0.5 * L2, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
		// (2)���������곡����
		AcGePoint3dArray site_pts2;
		GraphHelper::CaclSitesOnTunnel( site_pts2, site_orig + v2 * L2 * 0.5, site_orig + v1 * Ld + v2 * L2 * 0.5, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
		// (3)���㹤����װ�������곡����
		AcGePoint3dArray site_pts3;
		GraphHelper::CaclSitesOnTunnel( site_pts3, site_orig - v2 * L2 * 0.5, site_orig + v2 * L2 * 0.5, site_gap, 0.5 * ( Ws + wd ), Ls, Ws, -PI * 0.5 );

		// ������Ƶ��������������
		int row1 = d1; int col1 = nx - d1;
		// ������Ƶ��������������
		int row2 = d1; int col2 = nx - d1;
		// ������װ�������Ƶ��������������
		int row3 = ny; int col3 = d1;

		acutPrintf(_T("\n������������������:%d��%d"), row1, col1);
		acutPrintf(_T("\n������������������:%d��%d"), row2, col2);
		acutPrintf(_T("\n������������������:%d��%d"), row3, col3);

		// ���乤����װ�������Ƶ����(ÿ���곡����xx��)
		IntArray nums3(site_pts3.length(), 0);
		nums3[0] += col3; // ��ֱ����Ҳ����left+right,����ֱ����col3������
		nums3[0] += d2/2;  // ��������������ϵĵ�һ���곡����Ҫ����һ�������(������ذ�)
		for(int i=1;i<site_pts3.length();i++)
		{
			nums3[i] += d2;
		}
		// ΢�����һ���곡����׸���
		int S3 = std::accumulate(nums3.begin(), nums3.end(), 0);
		// ����ж�������û����,ֱ�Ӽӵ����һ���곡��
		// �����ײ���,������һ���곡�ϼ�ȥ�����Ĳ���
		nums3.back() += row3 - S3;
		acutPrintf(_T("\n�������곡���Ƶ��������:"));
		for(int i=0;i<nums3.size();i++)
		{
			acutPrintf(_T("%d  "), nums3[i]);
		}
		acutPrintf(_T("�ܼ�:%d\n"), std::accumulate(nums3.begin(), nums3.end(), 0));

		// ���������Ƶ����(ÿ���곡����xx��)
		IntArray nums1(site_pts1.length(), 0);
		nums1[0] += d2/2;
		for(int i=0;i<nums1.size();i++)
		{
			nums1[i] += d2;
		}
		int S1 = std::accumulate(nums1.begin(), nums1.end(), 0);
		nums1.back() += col1 - S1;
		
		acutPrintf(_T("\n�����곡���Ƶ��������:"));
		for(int i=0;i<nums1.size();i++)
		{
			acutPrintf(_T("%d  "), nums1[i]);
		}
		acutPrintf(_T("�ܼ�:%d\n"), std::accumulate(nums1.begin(), nums1.end(), 0));

		// ���������Ƶ����
		IntArray nums2;
		std::copy(nums1.begin(), nums1.end(), std::back_inserter(nums2));

		acutPrintf(_T("\n���곡���Ƶ��������:"));
		for(int i=0;i<nums2.size();i++)
		{
			acutPrintf(_T("%d  "), nums2[i]);
		}
		acutPrintf(_T("�ܼ�:%d\n"), std::accumulate(nums2.begin(), nums2.end(), 0));

		// ��¼���е����
		std::vector<cbm::DesignPore> pores;
		// ��¼���е��곡
		std::vector<cbm::DesignSite> sites;

		// (1)������������
		drawPores1(1, site_pts1, nums1, pore_pts, nx, row1, 0, nx, nx, pores);
		// (2)������������
		drawPores1(2, site_pts2, nums2, pore_pts, nx, ny, ny-row2, nx, nx, pores);
		// (3)���������װ����������
		drawPores1(3, site_pts3, nums3, pore_pts, nx, 0, ny, col1, 0, pores);
		// ��ӵ����ݿ�
		SQLClientHelper::AddMoreDesignPore(pores);
	}

    Graph::Graph( cbm::Coal& _coal, cbm::DesignDrillingSurfTechnology& _tech )
        : BaseGraph(), coal( _coal ), tech( _tech )
    {
        left_margin = 20;
        right_margin = 20;
        bottom_margin = 20;
        top_margin = 40;

        //���򳤶Ⱥ����򳤶�
        L1 = tech.l1, L2 = tech.l2;
        //ú���Ⱥ����(����)
        thick = coal.thick, angle = DegToRad( coal.dip_angle );
        //����������Ŀ�Ⱥ͸߶�
        w = tech.w, h = tech.h;
        //�װ���Ŀ�Ⱥ͸߶�
        wd = tech.wd, hd = tech.hd;
        //�������°��
        left = tech.left_side, right = tech.right_side;
        top = tech.top_side, bottom = tech.bottom_side;
        //�곡���ȡ���Ⱥ͸߶�
        Ls = tech.ls, Ws = tech.ws, Hs = tech.hs;
        //����͹������ˮƽͶӰ���롢����
        h_offset = tech.h_offset, v_offset = tech.v_offset;
        //��װ뾶�ͳ�ɰ뾶(�׾��ĵ�λ��mm)
        radius = tech.dp * 0.5 * 0.001, pore_gap = tech.gp;
        //�곡���
        site_gap = tech.gs;
    }

    void Graph::subDraw()
    {
        //����ͼ��
        drawCoal();
        drawTunnel();
        drawRockTunnel();
        drawPores();
        drawSites();
    }

    void Graph::caclCoalExtent( double& Lc, double& Wc, double& Hc ) const
    {
        //������(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
        //Lc = (L1 + left + left_margin + right_margin)*cos(angle);
        Lc = L1 + left + left_margin + right_margin;
        Wc = L2 + left + right + bottom_margin + top_margin;
        Hc = thick;
    }

    AcGePoint3d Graph::caclCoalBasePoint1() const
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * ( left + left_margin ), v2, -1 * ( 0.5 * L2 + left + bottom_margin ) );
    }

    AcGePoint3d Graph::caclCoalBasePoint2() const
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * ( left + left_margin ), v2, -0.5 * thick );;
    }

    AcGePoint3d Graph::caclCoalBasePoint3() const
    {
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -0.5 * Wc, v2, -0.5 * thick );;
    }

    void Graph::caclPoreExtent( double& Lp, double& Wp, double& Hp ) const
    {
        //���㳤��(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
        //Lp = (L1 + left)*cos(angle);
        Lp = L1 + left;
        Wp = L2 + left + right;
        Hp = 0.5;
    }

    AcGePoint3d Graph::caclPoreBasePoint1() const
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * left, v2, -1 * ( left + 0.5 * L2 ) );
    }

    AcGePoint3d Graph::caclPoreBasePoint2() const
    {
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        return ArxDrawHelper::CaclPt( getPoint(), v1, -1 * left, v2, 0.5 * thick + Hp );
    }

	//����һ������ϵ��곡
    void Graph::drawSitesOnTunnel( const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle, bool excludeFirst )
    {
        AcGePoint3dArray pts;
        ArxDrawHelper::Divide( spt, ept, gap_x, gap_y, pts, false );
        int start = excludeFirst ? 1 : 0; // �Ƿ���Ƶ�һ���곡
        for( int i = start; i < pts.length(); i++ )
        {
            AcDbObjectId siteId = this->drawRect( pts[i], angle, w, h );
        }
    }

    PlanGraph::PlanGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal, tech )
    {
    }

    void PlanGraph::drawSites()
    {
        //�۳��Ұ�
        double Ld = L1 - right;

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, h_offset );
        //�����곡
        drawSitesOnTunnel( basePt - v2 * L2 * 0.5, basePt + v1 * Ld - v2 * 0.5 * L2, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
        drawSitesOnTunnel( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, site_gap, 0.5 * ( Ws + wd ), Ls, Ws, -PI * 0.5 );
        drawSitesOnTunnel( basePt + v2 * L2 * 0.5, basePt + v1 * Ld + v2 * L2 * 0.5, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
    }

    void PlanGraph::drawPores()
    {
        if( pore_gap <= 0 ) return;

        //�������ƽ��ͶӰ��Χ
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );
        //ƽ��ͼ��׷�Χ�����½ǻ�������
        AcGePoint3d basePt = caclPoreBasePoint1();

        //�������
        AcGePoint3dArray pts;
        ArxDrawHelper::MakeGridWithHole( basePt, Lp, Wp, pore_gap, pore_gap, left + right, 0, left + right, left + right, pts, true );
        for( int i = 0; i < pts.length(); i++ )
        {
            AcDbObjectId poreId = this->drawCircle( pts[i], radius );
        }
    }

    void PlanGraph::drawRockTunnel()
    {
        //�۳�ƫ�ƵĲ���
        double Ld = L1 - right;

        //���Ƶװ�����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, h_offset );
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v1 * Ld - v2 * L2 * 0.5, wd );
        //��������������
        AcDbObjectId t2 = this->drawDoubleLine( basePt + 0.5 * v2 * L2, basePt + v1 * Ld + 0.5 * v2 * L2, wd );
        //��������
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, wd );
        this->drawMText( basePt + v1 * Ld - v2 * L2 * 0.5, 0, _T( "�װ�����" ), 10 );
        this->drawMText( basePt + v1 * Ld + v2 * L2 * 0.5, 0, _T( "����������" ), 10 );
    }

    void PlanGraph::drawTunnel()
    {
        //������������е�λ����Ϊ����
        AcGePoint3d basePt = getPoint();
        //���ƻ���
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v1 * L1 - v2 * L2 * 0.5, w );
        //���Ʒ���
        AcDbObjectId t2 = this->drawDoubleLine( basePt + v2 * L2 * 0.5, basePt + v1 * L1 + v2 * L2 * 0.5, w );
        //���ƹ���������
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v2 * L2 * 0.5, basePt + v2 * L2 * 0.5, w );
        this->drawMText( basePt + v1 * L1 - v2 * L2 * 0.5, 0, _T( "�������" ), 10 );
        this->drawMText( basePt + v1 * L1 + v2 * L2 * 0.5, 0, _T( "�������" ), 10 );
    }

    void PlanGraph::drawCoal()
    {
        //����ú��ĳ����
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );
        //����ƽ��ͼ��ú������½ǻ�������
        AcGePoint3d basePt = caclCoalBasePoint1();

        //����ú����
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Lc, Wc );
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kXAxis * Lc, _T(""), 50, false );
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kYAxis * Wc, _T(""), 30, true );
        //��������
        if( !coalId.isNull() )
        {
            CoalData data;
            data.setDataSource( coalId );
            data.m_name = _T( "����" );
            data.m_thick = coal.thick;
            data.m_angle = coal.dip_angle;
            data.m_width = tech.l1;
            data.m_height = tech.l2;
            data.m_pt = basePt;
            data.update( true );
        }
    }

    HeadGraph::HeadGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal, tech )
    {

    }

    void HeadGraph::drawSites()
    {
        //�۳��Ұ�
        double Ld = L1 - right;

        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, -1 * ( v_offset + 0.5 * thick ) );
        //�����곡
        drawSitesOnTunnel( basePt, basePt + v1 * Ld, site_gap, 0, Ls, Ws, 0, false );
    }

    void HeadGraph::drawPores()
    {
        //�۳��Ұ�
        double Ld = L1 - right;

        //������׷�Χ
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );

        //���������������ĸ���
        int nx = ArxDrawHelper::DivideNum( Lp, pore_gap, true );
        //�����곡�ĸ���
        int nd = ArxDrawHelper::DivideNum( Ld, site_gap, false );

        //��1���곡(����������ϵĲ��õ��곡)
        int n1 = ArxDrawHelper::DivideNum( left + right, pore_gap, true );
        //ÿ���곡֮�����׸���(������)
        int dn = ArxDrawHelper::DivideNum( nx, nd, true );
        //��2���곡
        int n2 = dn + dn / 2;

        //������׺��곡�ĸ�����ϵ
        IntArray nums;
        nums.push_back( n1 );
        nums.push_back( n2 );
        ArxDrawHelper::Shuffle( nx - n1 - n2, nd - 2, nums );

        //������׵Ļ���
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d poreBasePt = caclPoreBasePoint2();

        //���μ����곡����׵Ĺ���
        AcGePoint3d siteBasePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, -1 * ( v_offset + 0.5 * thick ) );
        int start = 0;
        for( int i = 0; i < nd; i++ )
        {
            AcGePoint3d site_pt = siteBasePt + v1 * i * site_gap + v2 * 0;
            int end = start + nums[i];
            for( int j = start; j < end; j++ )
            {
                AcGePoint3d pore_pt = poreBasePt + v1 * j * pore_gap + v2 * 0;
                AcDbObjectId poreId = this->drawLine( site_pt, pore_pt );
            }
            start = end;
        }
    }

    void HeadGraph::drawRockTunnel()
    {
        //�۳�ƫ�ƵĲ���
        double Ld = L1 - right;

        //���Ƶװ�����
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, right, v2, -1 * ( v_offset + 0.5 * thick ) );
        AcDbObjectId t1 = this->drawDoubleLine( basePt - v1 * Hs * 0.5, basePt + v1 * Ld, wd );
    }

    void HeadGraph::drawTunnel()
    {

    }

    void HeadGraph::drawCoal()
    {
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );
        AcGePoint3d basePt = caclCoalBasePoint2();

        //����ú��
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Lc, Hc );
    }

    DipGraph::DipGraph( cbm::Coal& coal, cbm::DesignDrillingSurfTechnology& tech ) : Graph( coal, tech )
    {
        //����ucs
        AcGeVector3d xAxis( AcGeVector3d::kXAxis ), yAxis( AcGeVector3d::kYAxis );
        xAxis.rotateBy( -1 * angle, AcGeVector3d::kZAxis );
        yAxis.rotateBy( -1 * angle, AcGeVector3d::kZAxis );
        setUcs( AcGePoint3d::kOrigin, xAxis, yAxis );
    }

    void DipGraph::drawSites()
    {

    }

    void DipGraph::drawPores()
    {
        //������׷�Χ
        double Lp = 0, Wp = 0, Hp = 0;
        caclPoreExtent( Lp, Wp, Hp );

        //���������������ĸ���(ֻ�����ڿ��Ʒ�Χ�ڵ�)
        int nx = ArxDrawHelper::DivideNum( left + right, pore_gap, true );

        //������׵Ļ���
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

        //�����곡�Ļ���
        AcGePoint3d rockBasePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * h_offset, v2, -1 * v_offset ); //���������е�

        AcGePoint3d poreBasePt1 = ArxDrawHelper::CaclPt( getPoint(), v1, -0.5 * Wp, v2, 0.5 * thick + Hp );
        AcGePoint3d siteBasePt1 = rockBasePt - v1 * L2 * 0.5; // ����������
        for( int i = 0; i < nx; i++ )
        {
            AcGePoint3d pore_pt = poreBasePt1 + v1 * i * pore_gap + v2 * 0; // �������Ҽ���
            AcDbObjectId poreId = this->drawLine( siteBasePt1, pore_pt );
        }

        AcGePoint3d poreBasePt2 = ArxDrawHelper::CaclPt( getPoint(), v1, 0.5 * Wp, v2, 0.5 * thick + Hp );
        AcGePoint3d siteBasePt2 = rockBasePt + v1 * L2 * 0.5; // �װ�����
        for( int i = 0; i < nx; i++ )
        {
            AcGePoint3d pore_pt = poreBasePt2 - v1 * i * pore_gap + v2 * 0; // �����������
            AcDbObjectId poreId = this->drawLine( siteBasePt2, pore_pt );
        }
    }

    void DipGraph::drawRockTunnel()
    {
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        AcGePoint3d basePt = ArxDrawHelper::CaclPt( getPoint(), v1, -1 * h_offset, v2, -1 * v_offset );
        AcDbObjectId t3 = this->drawDoubleLine( basePt - v1 * L2 * 0.5, basePt + v1 * L2 * 0.5, hd ); // �װ�����
        //Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
        AcDbObjectId t2 = this->drawRect( basePt - v1 * L2 * 0.5, angle, wd, hd ); // ����������
        AcDbObjectId t1 = this->drawRect( basePt + v1 * L2 * 0.5, angle, wd, hd ); // �װ�����
    }

    void DipGraph::drawTunnel()
    {
        AcGePoint3d basePt = getPoint();
        AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
        //Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
        AcDbObjectId t1 = this->drawRect( basePt + v1 * L2 * 0.5, angle, w, h ); // �������
        AcDbObjectId t2 = this->drawRect( basePt - v1 * L2 * 0.5, angle, w, h ); // �������
        AcDbObjectId t3 = this->drawDoubleLine( basePt-v1*L2*0.5, basePt+v1*L2*0.5, h ); //����������
    }

    void DipGraph::drawCoal()
    {
        double Lc = 0, Wc = 0, Hc = 0;
        caclCoalExtent( Lc, Wc, Hc );
        AcGePoint3d basePt = caclCoalBasePoint3();

        //����ú��
        AcDbObjectId coalId = this->drawRect2( basePt, 0, Wc, Hc );
    }

} // namespace P11