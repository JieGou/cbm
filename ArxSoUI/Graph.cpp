#include "StdAfx.h"
#include "Graph.h"

#include <Util/HelperClass.h>
#include <ArxHelper/HelperClass.h>

//����˫��
class DoubleLine
{
public:
	DoubleLine(const AcGePoint3d& spt, const AcGePoint3d& ept, double width)
		: m_spt(spt), m_ept(ept), m_width(width)
	{

	}
	AcDbObjectId draw()
	{
		//����ʼ�˵�2������
		AcGePoint3d m_leftStartPt, m_leftEndPt;
		AcGePoint3d m_rightStartPt, m_rightEndPt;
		caclStartPoint(m_leftStartPt, m_rightStartPt);
		//����ĩ�˵�2������
		caclEndPoint(m_leftEndPt, m_rightEndPt);
		//����2��ֱ��
		AcDbObjectId line1 = ArxDrawHelper::DrawLine( m_leftStartPt, m_leftEndPt );
		AcDbObjectId line2 = ArxDrawHelper::DrawLine( m_rightStartPt, m_rightEndPt );

		//����group
		AcDbObjectIdArray objIds;
		objIds.append(line1);
		objIds.append(line2);
		//������ʱ������
		CString name;
		name.Format(_T("���%d"), count++);
		AcDbObjectId groupId = ArxGroupHelper::CreateGroup(name, objIds);
		if(!groupId.isNull())
		{
			ArxGroupHelper::ConvertToAnonymousGroup(groupId);
		}
		return groupId;
	}

protected:
	void caclStartPoint( AcGePoint3d& startPt1, AcGePoint3d& startPt2 )
	{
		AcGeVector3d v = m_ept - m_spt;
		v.normalize();

		v.rotateBy( PI * 0.5, AcGeVector3d::kZAxis );
		startPt1 = m_spt + v * m_width * 0.5;

		v.rotateBy( PI, AcGeVector3d::kZAxis );
		startPt2 = m_spt + v * m_width * 0.5;
	}

	void caclEndPoint( AcGePoint3d& endPt1, AcGePoint3d& endPt2 )
	{
		AcGeVector3d v = m_ept - m_spt;
		v.normalize();

		v.rotateBy( PI * 0.5, AcGeVector3d::kZAxis );
		endPt1 = m_ept + v * m_width * 0.5;

		v.rotateBy( PI, AcGeVector3d::kZAxis );
		endPt2 = m_ept + v * m_width * 0.5;
	}

private:
	AcGePoint3d m_spt, m_ept;
	double m_width;
	//��̬��Ա����������ͳ�ƶ������
	static int count;
};

int DoubleLine::count = 0;

static AcDbObjectId DrawDoubleLine(const AcGePoint3d& spt, const AcGePoint3d& ept, double width)
{
	DoubleLine line(spt, ept, width);
	return line.draw();
}

Graph::Graph(const cbm::CoalPtr& _coal, const cbm::DesignWorkSurfPtr& _ws, const cbm::DesignTechnologyPtr& _tech)
: coal(_coal), work_surf(_ws), tech(_tech)
{
	left_margin = 20;
	right_margin = 20;
	bottom_margin = 20;
	top_margin = 40;

	//���򳤶Ⱥ����򳤶�
	L1 = work_surf->l1, L2 = work_surf->l2;
	//ú���Ⱥ����(����)
	thick = coal->thick, angle = DegToRad(coal->dip_angle);
	//����������Ŀ�Ⱥ͸߶�
	w = work_surf->w, h = work_surf->h;
	//�װ���Ŀ�Ⱥ͸߶�
	wd = tech->wd, hd = tech->hd;
	//�������°��
	left = tech->left_side, right = tech->right_side;
	top = tech->top_side, bottom = tech->bottom_side;
	//�곡��ȡ��߶Ⱥ����
	ws = tech->ws, hs = tech->hs, ds = tech->ds;
	//����͹������ˮƽͶӰ���롢����
	h_offset = tech->h_offset, v_offset = tech->v_offset;
	//��װ뾶�ͳ�ɰ뾶
	radius = tech->dp*0.5, pore_gap = tech->gp;
	//�곡���
	site_gap = tech->gs;
}

void Graph::setPoint(const AcGePoint3d& pt)
{
	this->m_basePt = pt;
}

AcGePoint3d Graph::getPoint() const
{
	return this->m_basePt;
}

void Graph::addEnt(const AcDbObjectId& objId)
{
	if(objId.isNull()) return;
	if(ArxUtilHelper::IsEqualType(_T("AcDbGroup"), objId))
	{
		ArxGroupHelper::GetObjectIds(objId, m_ents);
	}
	else if(ArxUtilHelper::IsEqualType(_T("AcDbEntity"), objId))
	{
		m_ents.append(objId);
	}
}

void Graph::subDraw()
{
	drawCoal();
	drawWsTunnel();
	drawRockTunnel();
	drawPores();
	drawSites();
}

void Graph::draw()
{
	ArxDocLockSwitch lock_switch;
	subDraw();
}

void Graph::caclCoalExtent(double& Lc, double& Wc, double& Hc) const
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
	return ArxDrawHelper::CaclPt(getPoint(),v1,-1*(left+left_margin),v2,-1*(0.5*L2+left+bottom_margin));
}

AcGePoint3d Graph::caclCoalBasePoint2() const
{
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	return ArxDrawHelper::CaclPt(getPoint(),v1,-1*(left+left_margin),v2,-0.5*thick);;
}

AcGePoint3d Graph::caclCoalBasePoint3() const
{
	double Lc = 0, Wc = 0, Hc = 0;
	caclCoalExtent(Lc, Wc, Hc);

	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	return ArxDrawHelper::CaclPt(getPoint(),v1,-0.5*Wc,v2,-0.5*thick);;
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
	return ArxDrawHelper::CaclPt(getPoint(), v1, -1*left, v2, -1*(left+0.5*L2));
}

AcGePoint3d Graph::caclPoreBasePoint2() const
{
	double Lp = 0, Wp = 0, Hp = 0;
	caclPoreExtent(Lp, Wp, Hp);
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	return ArxDrawHelper::CaclPt(getPoint(), v1, -1*left, v2, 0.5*thick+Hp);
}

AcGePoint3d Graph::caclPoreBasePoint3() const
{
	return getPoint();
}

AcGePoint3d Graph::caclSiteBasePoint1() const
{
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	return ArxDrawHelper::CaclPt(getPoint(), v1, right, v2, h_offset);
}

AcGePoint3d Graph::caclSiteBasePoint2() const
{
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	return ArxDrawHelper::CaclPt(getPoint(), v1, right, v2, -1*(v_offset+0.5*thick));
}

AcGePoint3d Graph::caclSiteBasePoint3() const
{
	return getPoint();
}

void Graph::tranform(const AcGeMatrix3d& mat)
{
	//�任����ϵ
	ArxUcsHelper::TransformEntities(m_ents, mat);
}

PlanGraph::PlanGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech) : Graph(coal, work_surf, tech)
{
}

//����һ������ϵ��곡
void Graph::drawSitesOnTunnel(const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle, bool excludeFirst)
{
	AcGePoint3dArray pts;
	ArxDrawHelper::Divide(spt, ept, gap_x, gap_y, pts,false);
	int start = excludeFirst?1:0; // �Ƿ���Ƶ�һ���곡
	for(int i=start;i<pts.length();i++)
	{
		AcDbObjectId siteId = ArxDrawHelper::DrawRect(pts[i], angle, w, h);
		//��¼�ڰ�
		addEnt(siteId);
	}
}

void PlanGraph::drawSites()
{	
	//�۳��Ұ�
	double Ld = L1 - right;

	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcGePoint3d basePt = caclSiteBasePoint1();
	//�����곡
	drawSitesOnTunnel(basePt-v2*L2*0.5, basePt+v1*Ld-v2*0.5*L2, site_gap, -0.5*(hs+wd), ws, hs, 0);
	drawSitesOnTunnel(basePt-v2*L2*0.5, basePt+v2*L2*0.5, site_gap, 0.5*(hs+wd), ws, hs, -PI*0.5);
	drawSitesOnTunnel(basePt+v2*L2*0.5, basePt+v1*Ld+v2*L2*0.5, site_gap, -0.5*(hs+wd), ws, hs, 0);
}

void PlanGraph::drawPores()
{
	if(pore_gap <= 0) return;

	//�������ƽ��ͶӰ��Χ
	double Lp = 0, Wp = 0, Hp = 0;
	caclPoreExtent(Lp, Wp, Hp);
	//ƽ��ͼ��׷�Χ�����½ǻ�������
	AcGePoint3d basePt = caclPoreBasePoint1();

	//�������
	AcGePoint3dArray pts;
	ArxDrawHelper::MakeGridWithHole(basePt, Lp, Wp, pore_gap, pore_gap, left+right, 0, left+right, left+right, pts, true);
	for(int i=0;i<pts.length();i++)
	{
		AcDbObjectId poreId = ArxDrawHelper::DrawCircle(pts[i], radius);
		//��¼�ڰ�
		addEnt(poreId);
	}
}

void PlanGraph::drawRockTunnel()
{
	//�۳�ƫ�ƵĲ���
	double Ld = L1 - right;
	
	//���Ƶװ�����
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcGePoint3d basePt = ArxDrawHelper::CaclPt(getPoint(), v1, right, v2, h_offset);
	AcDbObjectId t1 = DrawDoubleLine(basePt-v2*L2*0.5, basePt+v1*Ld-v2*L2*0.5, wd);
	//��������������
	AcDbObjectId t2 = DrawDoubleLine(basePt+0.5*v2*L2, basePt+v1*Ld+0.5*v2*L2, wd);
	//��������
	AcDbObjectId t3 = DrawDoubleLine(basePt-v2*L2*0.5, basePt+v2*L2*0.5, wd);
	ArxDrawHelper::DrawMText(basePt+v1*Ld-v2*L2*0.5, 0, _T("�װ�����"), 10);
	ArxDrawHelper::DrawMText(basePt+v1*Ld+v2*L2*0.5, 0, _T("����������"), 10);
	//��¼�ڰ�
	addEnt(t1);
	addEnt(t2);
	addEnt(t3);
}

void PlanGraph::drawWsTunnel()
{
	//������������е�λ����Ϊ����
	AcGePoint3d basePt = getPoint();
	//���ƻ���
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcDbObjectId t1 = DrawDoubleLine(basePt-v2*L2*0.5, basePt+v1*L1-v2*L2*0.5, w);
	//���Ʒ���
	AcDbObjectId t2 = DrawDoubleLine(basePt+v2*L2*0.5, basePt+v1*L1+v2*L2*0.5, w);
	//���ƹ���������
	AcDbObjectId t3 = DrawDoubleLine(basePt-v2*L2*0.5, basePt+v2*L2*0.5, w);
	ArxDrawHelper::DrawMText(basePt+v1*L1-v2*L2*0.5, 0, _T("�������"), 10);
	ArxDrawHelper::DrawMText(basePt+v1*L1+v2*L2*0.5, 0, _T("�������"), 10);
	//��¼�ڰ�
	addEnt(t1);
	addEnt(t2);
	addEnt(t3);
}

void PlanGraph::drawCoal()
{
	//����ú��ĳ����
	double Lc = 0, Wc = 0, Hc = 0;
	caclCoalExtent(Lc, Wc, Hc);
	//����ƽ��ͼ��ú������½ǻ�������
	AcGePoint3d basePt = caclCoalBasePoint1();

	//����ú����
	AcDbObjectId coalId = ArxDrawHelper::DrawRect2(basePt, 0, Lc, Wc);
	//��¼�ڰ�
	addEnt(coalId);
	ArxDrawHelper::MakeAlignedDim(basePt, basePt+AcGeVector3d::kXAxis*Lc, 50, false);
	ArxDrawHelper::MakeAlignedDim(basePt, basePt+AcGeVector3d::kYAxis*Wc, 30, true);
	//��������
	if(!coalId.isNull())
	{
		CoalData data;
		data.setDataSource(coalId);
		data.m_name = _T("����");
		data.m_thick = coal->thick;
		data.m_angle = coal->dip_angle;
		data.m_width = work_surf->l1;
		data.m_height = work_surf->l2;
		data.m_pt = basePt;
		data.update(true);
	}
}

HeadGraph::HeadGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech) : Graph(coal, work_surf, tech)
{

}

void HeadGraph::drawSites()
{
	//�۳��Ұ�
	double Ld = L1 - right;

	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcGePoint3d basePt = caclSiteBasePoint2();
	//�����곡
	drawSitesOnTunnel(basePt, basePt+v1*Ld, site_gap, 0, ws, hs, 0, false);
}

void HeadGraph::drawPores()
{
	//�۳��Ұ�
	double Ld = L1 - right;

	//������׷�Χ
	double Lp = 0, Wp = 0, Hp = 0;
	caclPoreExtent(Lp, Wp, Hp);

	//���������������ĸ���
	int nx = ArxDrawHelper::DivideNum(Lp, pore_gap, true);
	//�����곡�ĸ���
	int nd = ArxDrawHelper::DivideNum(Ld, site_gap, false);

	//��1���곡(����������ϵĲ��õ��곡)
	int n1 = ArxDrawHelper::DivideNum(left+right, pore_gap, true);
	//ÿ���곡֮�����׸���(������)
	int dn = ArxDrawHelper::DivideNum(nx, nd, true);
	//��2���곡
	int n2 = dn + dn/2;

	//������׺��곡�ĸ�����ϵ
	IntArray nums;
	nums.push_back(n1);
	nums.push_back(n2);
	ArxDrawHelper::Shuffle(nx-n1-n2, nd-2, nums);

	//������׵Ļ���
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcGePoint3d poreBasePt = caclPoreBasePoint2();

	//���μ����곡����׵Ĺ���
	AcGePoint3d siteBasePt = caclSiteBasePoint2();
	int start = 0;
	for(int i=0;i<nd;i++)
	{
		AcGePoint3d site_pt = siteBasePt + v1*i*site_gap + v2*0;
		int end = start + nums[i];
		for(int j=start;j<end;j++)
		{
			AcGePoint3d pore_pt = poreBasePt + v1*j*pore_gap + v2*0;
			AcDbObjectId poreId = ArxDrawHelper::DrawLine(site_pt, pore_pt);
			//��¼�ڰ�
			addEnt(poreId);
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
	AcGePoint3d basePt = ArxDrawHelper::CaclPt(getPoint(), v1, right, v2, -1*(v_offset+0.5*thick));
	AcDbObjectId t1 = DrawDoubleLine(basePt-v1*ds*0.5, basePt+v1*Ld, wd);
	//��¼�ڰ�
	addEnt(t1);
}

void HeadGraph::drawWsTunnel()
{

}

void HeadGraph::drawCoal()
{
	double Lc = 0, Wc = 0, Hc = 0;
	caclCoalExtent(Lc, Wc, Hc);
	AcGePoint3d basePt = caclCoalBasePoint2();

	//����ú��
	AcDbObjectId coalId = ArxDrawHelper::DrawRect2(basePt, 0, Lc, Hc);
	//��¼�ڰ�
	addEnt(coalId);
}

DipGraph::DipGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech) : Graph(coal, work_surf, tech)
{

}

void DipGraph::drawSites()
{

}

void DipGraph::drawPores()
{
	//������׷�Χ
	double Lp = 0, Wp = 0, Hp = 0;
	caclPoreExtent(Lp, Wp, Hp);

	//���������������ĸ���(ֻ�����ڿ��Ʒ�Χ�ڵ�)
	int nx = ArxDrawHelper::DivideNum(left+right, pore_gap, true);

	//������׵Ļ���
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcGePoint3d poreBasePt1 = ArxDrawHelper::CaclPt(getPoint(), v1, -0.5*Wp, v2, 0.5*thick+Hp);
	AcGePoint3d poreBasePt2 = ArxDrawHelper::CaclPt(getPoint(), v1, 0.5*Wp, v2, 0.5*thick+Hp);

	//�����곡�Ļ���
	AcGePoint3d rockBasePt = ArxDrawHelper::CaclPt(getPoint(), v1, -1*h_offset, v2, -1*v_offset); //���������е�
	AcGePoint3d siteBasePt1 = rockBasePt-v1*L2*0.5; // ����������
	AcGePoint3d siteBasePt2 = rockBasePt+v1*L2*0.5; // �װ�����

	for(int i=0;i<nx;i++)
	{
		AcGePoint3d pore_pt = poreBasePt1 + v1*i*pore_gap + v2*0; // �������Ҽ���
		AcDbObjectId poreId = ArxDrawHelper::DrawLine(siteBasePt1, pore_pt);
		//��¼�ڰ�
		addEnt(poreId);
	}
	for(int i=0;i<nx;i++)
	{
		AcGePoint3d pore_pt = poreBasePt2 - v1*i*pore_gap + v2*0; // �����������
		AcDbObjectId poreId = ArxDrawHelper::DrawLine(siteBasePt2, pore_pt);
		//��¼�ڰ�
		addEnt(poreId);
	}
}

void DipGraph::drawRockTunnel()
{
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcGePoint3d basePt = ArxDrawHelper::CaclPt(getPoint(), v1, -1*h_offset, v2, -1*v_offset);
	AcDbObjectId t3 = DrawDoubleLine(basePt-v1*L2*0.5, basePt+v1*L2*0.5, hd); // �װ�����
	//Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
	AcDbObjectId t2 = ArxDrawHelper::DrawRect(basePt-v1*L2*0.5, angle, wd, hd); // ����������
	AcDbObjectId t1 = ArxDrawHelper::DrawRect(basePt+v1*L2*0.5, angle, wd, hd); // �װ�����
	//��¼�ڰ�
	addEnt(t1);
	addEnt(t2);
	addEnt(t3);
}

void DipGraph::drawWsTunnel()
{
	AcGePoint3d basePt = getPoint();
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	//Ϊ�˻����������(����)��ˮƽ��,���⴦����(��ת)
	AcDbObjectId t1 = ArxDrawHelper::DrawRect(basePt+v1*L2*0.5, angle, w, h); // �������
	AcDbObjectId t2 = ArxDrawHelper::DrawRect(basePt-v1*L2*0.5, angle, w, h); // �������
	AcDbObjectId t3 = DrawDoubleLine(basePt-v1*L2*0.5, basePt+v1*L2*0.5, h); // ����������
	//��¼�ڰ�
	addEnt(t1);
	addEnt(t2);
	addEnt(t3);
}

void DipGraph::drawCoal()
{
	double Lc = 0, Wc = 0, Hc = 0;
	caclCoalExtent(Lc, Wc, Hc);
	AcGePoint3d basePt = caclCoalBasePoint3();

	//����ú��
	AcDbObjectId coalId = ArxDrawHelper::DrawRect2(basePt, 0, Wc, Hc);
	//��¼�ڰ�
	addEnt(coalId);
}

void DipGraph::subDraw()
{
	//����ucs����ϵ
	AcGePoint3d origin = getPoint();
	AcGeVector3d xAxis(AcGeVector3d::kXAxis), yAxis(AcGeVector3d::kYAxis);
	xAxis.rotateBy(-1*angle, AcGeVector3d::kZAxis);
	yAxis.rotateBy(-1*angle, AcGeVector3d::kZAxis);
	//�õ�ucs�任����
	AcGeMatrix3d mat;
	ArxUcsHelper::MakeTransformMatrix(mat, origin, xAxis, yAxis);

	//���ڸı�������ϵ,��Ҫ����������Ϊԭ��
	setPoint(AcGePoint3d::kOrigin);

	//���û��෽����ͼͼ��
	Graph::subDraw();

	//��ucs����ϵ�»��Ƶ�ͼ�α任��wcs����ϵ
	Graph::tranform(mat);
}