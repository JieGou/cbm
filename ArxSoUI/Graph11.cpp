#include "StdAfx.h"
#include "Graph11.h"

#include <ArxHelper/HelperClass.h>
#include "CbmClientHelper.h"
#include "SQLClientHelper.h"

#include <numeric>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "AcFstream.h"

#include <sstream>
std::string Int2Str(int i)
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}

namespace P11
{
	// ɾ����ɼ����µ������곡�����
	static void DeleteAllSiteAndPore(int design_id)
	{
		// ������ü�������������
		std::vector<int32_t> site_ids;
		SQLClientHelper::GetDesignSiteIdListByForeignKey(site_ids, "design_technology_id", design_id);

		// ɾ�����е��곡(���ݿ���Զ�ɾ�����������)
		SQLClientHelper::DeleteMoreDesignSite(site_ids);
	}

	static void CaclSitesOnTunnel( AcGePoint3dArray& pts, const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w=0, double h=0, double angle=0, bool excludeFirst=true )
	{
		AcGePoint3dArray temp_pts;
		ArxDrawHelper::Divide( spt, ept, gap_x, gap_y, temp_pts, true );
		//acutPrintf(_T("\n�����곡����ʱ�����:%d"), temp_pts.length());
		int start = excludeFirst ? 1 : 0; // �Ƿ���Ƶ�һ���곡
		for(int i=start;i<temp_pts.length();i++)
		{
			pts.append(temp_pts[i]);
		}
	}

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

	void PoreHelper::cacl()
	{
		// ɾ�����е��곡�����
		DeleteAllSiteAndPore(tech.design_technology_id);

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
		int ny = ArxDrawHelper::DivideNum(Wc, pore_gap, true);
		//��������(��)������곡��(�л���)
		int nd = ArxDrawHelper::DivideNum( Ld, site_gap, true ) - 1;
		//��������(��)������곡��(�л���)
		int nk = ArxDrawHelper::DivideNum( L2, site_gap, true ) - 1;
		//�������ﷶΧ�ڵ������(�л���)
		int n1 = ArxDrawHelper::DivideNum( left + right, pore_gap, true );
		//ÿ���곡֮�����׸���
		int dn = ArxDrawHelper::DivideNum( site_gap, pore_gap, true );

		acutPrintf(_T("\n����������:%d  �������:%d  ��׵��ܸ���:%d"), nx, ny, pore_pts.length());
		acutPrintf(_T("\n�곡�������:%d  �������:%d, ���ﷶΧ��׸���:%d  �곡֮��ĸ���:%d"), nd, nk, n1, dn);
		// �����곡������(CaclSitesOnTunnel�����ĺ�3������Ŀǰû���õ�!!!)
		// (0)������װ�������е�����
		AcGePoint3d site_orig = orig + v1*right + v2*h_offset + v3*v_offset*-1;
		// (1)���������곡����
		AcGePoint3dArray site_pts1;
		CaclSitesOnTunnel( site_pts1, site_orig - v2 * L2 * 0.5, site_orig + v1 * Ld - v2 * 0.5 * L2, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
		// (2)���������곡����
		AcGePoint3dArray site_pts2;
		CaclSitesOnTunnel( site_pts2, site_orig + v2 * L2 * 0.5, site_orig + v1 * Ld + v2 * L2 * 0.5, site_gap, -0.5 * ( Ws + wd ), Ls, Ws, 0 );
		// (3)���㹤����װ�������곡����
		AcGePoint3dArray site_pts3;
		CaclSitesOnTunnel( site_pts3, site_orig - v2 * L2 * 0.5, site_orig + v2 * L2 * 0.5, site_gap, 0.5 * ( Ws + wd ), Ls, Ws, -PI * 0.5 );

		// ������Ƶ��������������
		int row1 = n1;
		int col1 = nx - n1;
		// ������Ƶ��������������
		int row2 = n1;
		int col2 = nx - n1;
		// ������װ�������Ƶ��������������
		int row3 = ny;
		int col3 = n1;

		acutPrintf(_T("\n������������������:%d��%d"), row1, col1);
		acutPrintf(_T("\n������������������:%d��%d"), row2, col2);
		acutPrintf(_T("\n������������������:%d��%d"), row3, col3);

		// ���乤����װ�������Ƶ����(ÿ���곡����xx��)
		IntArray nums3(site_pts3.length(), 0);
		nums3[0] += col3; // ��ֱ����Ҳ����left+right,����ֱ����col3������
		nums3[0] += dn/2;  // ��������������ϵĵ�һ���곡����Ҫ����һ�������(������ذ�)
		for(int i=1;i<site_pts3.length();i++)
		{
			nums3[i] += dn;
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
		nums1[0] += dn/2;
		for(int i=0;i<nums1.size();i++)
		{
			nums1[i] += dn;
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

		// �����������ļ�(��json��ʽ)
		AcOfstream outfile(_T("test.txt"));

		// ��¼���е����
		std::vector<cbm::DesignPore> pores;
		// ��¼���е��곡
		std::vector<cbm::DesignSite> sites;

		// (1)������������
		int n = site_pts1.length();
		// ��ױ��
		int m = 1;
		// ���������(��������)
		int r1 = row1;
		int r2 = 0;
		int c1 = nx;
		int c2 = nx;
		for(int i=n-1;i>=0;i--)
		{
			// �곡����x,y,z
			AcGePoint3d site_pt = site_pts1[i];

			//�½��곡
			cbm::DesignSite site;
			site.name = Int2Str(n-i);
			site.x = site_pt.x;
			site.y = site_pt.y;
			site.z = site_pt.z;
			site.design_technology_id = tech.design_technology_id; // ��������id
			// �ύ�����ݿ�
			int32_t site_id = SQLClientHelper::AddDesignSite(site);
			if(site_id <= 0) 
			{
				acutPrintf(_T("\n����곡�����ݿ�ʧ��!!!"));
				break;
			}

			// �곡��������ʼλ��
			c2 -= nums1[i];
			acutPrintf(_T("\n����---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int j=r1-1;j>=r2;j--)
			{
				for(int k=c1-1;k>=c2;k--)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString num;
					num.Format(_T("%d-%d-%d"), 1, n-i, m);
					outfile << (LPCTSTR)num << _T('\t');
					outfile << site_pt.x << _T('\t') << site_pt.y << _T('\t') << site_pt.z << _T('\t');
					AcGePoint3d pore_pt = pore_pts[j*nx+k];
					outfile<<pore_pt.x<<_T('\t')<<pore_pt.y<<_T('\t')<<pore_pt.z<<_T('\n');

					// �½����
					cbm::DesignPore pore;
					pore.name = W2C((LPCTSTR)num);
					pore.x1 = site_pt.x;
					pore.y1 = site_pt.y;
					pore.z1 = site_pt.z;
					pore.x2 = pore_pt.x;
					pore.y2 = pore_pt.y;
					pore.z2 = pore_pt.z;
					AcGeVector3d v = pore_pt - site_pt;
					pore.length = v.length();  // ��׳���
					ArxDrawHelper::VectorToAngle(v, pore.angle1, pore.angle2);  // ��׽Ƕ�
					pore.design_site_id = site_id;
					// ��¼�½�����׶���
					pores.push_back(pore);
					// ��ױ�ż�1
					m++;
				}
			}
			c1 = c2;
		}
		outfile<< _T("END\n");

		// (2)������������
		/*int*/ n = site_pts2.length();
		// ��ױ��
		/*int*/ m = 1;
		// ���������(��������)
		/*int*/ r1 = ny;
		/*int*/ r2 = ny - row2;;
		/*int*/ c1 = nx;
		/*int*/ c2 = nx;
		for(int i=n-1;i>=0;i--)
		{
			// �곡����x,y,z
			AcGePoint3d site_pt = site_pts2[i];

			//�½��곡
			cbm::DesignSite site;
			site.name = Int2Str(n-i);
			site.x = site_pt.x;
			site.y = site_pt.y;
			site.z = site_pt.z;
			site.design_technology_id = tech.design_technology_id; // ��������id
			// �ύ�����ݿ�
			int32_t site_id = SQLClientHelper::AddDesignSite(site);
			if(site_id <= 0) 
			{
				acutPrintf(_T("\n����곡�����ݿ�ʧ��!!!"));
				break;
			}

			// �곡��������ʼλ��
			c2 -= nums2[i];
			acutPrintf(_T("\n����---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int j=r1-1;j>=r2;j--)
			{
				for(int k=c1-1;k>=c2;k--)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString num;
					num.Format(_T("%d-%d-%d"), 2, n-i, m);
					outfile << (LPCTSTR)num << _T('\t');
					outfile << site_pt.x << _T('\t') << site_pt.y << _T('\t') << site_pt.z << _T('\t');
					AcGePoint3d pore_pt = pore_pts[j*nx+k];
					outfile<<pore_pt.x<<_T('\t')<<pore_pt.y<<_T('\t')<<pore_pt.z<<_T('\n');

					// �½����
					cbm::DesignPore pore;
					pore.name = W2C((LPCTSTR)num);
					pore.x1 = site_pt.x;
					pore.y1 = site_pt.y;
					pore.z1 = site_pt.z;
					pore.x2 = pore_pt.x;
					pore.y2 = pore_pt.y;
					pore.z2 = pore_pt.z;
					AcGeVector3d v = pore_pt - site_pt;
					pore.length = v.length();  // ��׳���
					ArxDrawHelper::VectorToAngle(v, pore.angle1, pore.angle2);  // ��׽Ƕ�
					pore.design_site_id = site_id;
					// ��¼�½�����׶���
					pores.push_back(pore);
					// ��ױ�ż�1
					m++;
				}
			}
			c1 = c2;
		}
		outfile<< _T("END\n");

		// (3)���������װ����������
		/*int*/ n = site_pts3.length();
		// ��ױ��
		/*int*/ m = 1;
		// ���������(��������)
		/*int*/ r1 = 0;
		/*int*/ r2 = 0;
		/*int*/ c1 = col1;
		/*int*/ c2 = 0;
		for(int i=0;i<n;i++)
		{
			// �곡����(x,y,z
			AcGePoint3d site_pt = site_pts3[i];
			//�½��곡
			cbm::DesignSite site;
			site.name = Int2Str(n-i);
			site.x = site_pt.x;
			site.y = site_pt.y;
			site.z = site_pt.z;
			site.design_technology_id = tech.design_technology_id; // ��������id
			// �ύ�����ݿ�
			int32_t site_id = SQLClientHelper::AddDesignSite(site);
			if(site_id <= 0) 
			{
				acutPrintf(_T("\n����곡�����ݿ�ʧ��!!!"));
				break;
			}

			// �곡��������ʼλ��
			r2 += nums3[i];
			acutPrintf(_T("\n����������---�곡%d����:%d~%d, ��:%d~%d"), n-i, r1, r2, c1, c2);
			// �������
			for(int j=r1;j<r2;j++)
			{
				for(int k=c1-1;k>=c2;k--)
				{
					// ��Ź���: ������-�곡���-��ױ��
					CString num;
					num.Format(_T("%d-%d-%d"), 3, i+1, m);
					outfile << (LPCTSTR)num << _T('\t');
					outfile << site_pt.x << _T('\t') << site_pt.y << _T('\t') << site_pt.z << _T('\t');
					AcGePoint3d pore_pt = pore_pts[j*nx+k];
					outfile<<pore_pt.x<<_T('\t')<<pore_pt.y<<_T('\t')<<pore_pt.z<<_T('\n');

					// �½����
					cbm::DesignPore pore;
					pore.name = W2C((LPCTSTR)num);
					pore.x1 = site_pt.x;
					pore.y1 = site_pt.y;
					pore.z1 = site_pt.z;
					pore.x2 = pore_pt.x;
					pore.y2 = pore_pt.y;
					pore.z2 = pore_pt.z;
					AcGeVector3d v = pore_pt - site_pt;
					pore.length = v.length();  // ��׳���
					ArxDrawHelper::VectorToAngle(v, pore.angle1, pore.angle2);  // ��׽Ƕ�
					pore.design_site_id = site_id;
					// ��¼�½�����׶���
					pores.push_back(pore);
					// ��ױ�ż�1
					m++;
				}
			}
			r1 = r2;
		}
		outfile<< _T("END\n");
		outfile.close();

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
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kXAxis * Lc, 50, false );
        this->drawAlignedDim( basePt, basePt + AcGeVector3d::kYAxis * Wc, 30, true );
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