#include "StdAfx.h"
#include "Proxy.h"

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

AcDbObjectId Draw::CreateDoubleLine(const AcGePoint3d& spt, const AcGePoint3d& ept, double width)
{
	DoubleLine line(spt, ept, width);
	return line.draw();
}


CoalProxy::CoalProxy()
{
	left_offset = 20;
	right_offset = 20;
	bottom_offset = 20;
	top_offset = 40;
}

void CoalProxy::drawPores()
{
	double radius = tech->dp, gap = tech->gp;
	double left = tech->left_side, right = tech->right_side;
	double top = tech->top_side, bottom = tech->bottom_side;
	if(gap <= 0) return;

	//�������ƽ��ͶӰ��Χ
	AcGePoint3d basePt;
	double Wp = 0, Hp = 0;
	caclPoreExtent(basePt, Wp, Hp);

	//�������
	AcGePoint3dArray pts;
	ArxDrawHelper::MakeGridWithHole(basePt, Wp, Hp, gap, gap, left+right, 0, left+right, left+right, pts);
	for(int i=0;i<pts.length();i++)
	{
		ArxDrawHelper::DrawCircle(pts[i], radius);
	}
}

void CoalProxy::drawRockTunnel()
{
	double angle = DegToRad(coal->dip_angle);
	//double L1 = ws->l1, L2 = ws->l2*cos(angle);
	double L1 = ws->l1, L2 = ws->l2;
	double w = tech->wd, h = tech->hd;
	double h_offset = tech->h_offset;
	double left = tech->left_side, right = tech->right_side;

	//���ƻ���
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcGePoint3d basePt = ArxDrawHelper::CaclPt(pt, v1, right, v2, h_offset);
	AcDbObjectId t1 = Draw::CreateDoubleLine(basePt, basePt+v1*L2, w);
	//���ƹ���������
	AcDbObjectId t2 = Draw::CreateDoubleLine(basePt, basePt+v2*L1, w);
	//���Ʒ���
	AcDbObjectId t3 = Draw::CreateDoubleLine(basePt+v2*L1, basePt+v1*L2+v2*L1, w);
	ArxDrawHelper::DrawMText(basePt+v1*L2, 0, _T("�װ�����"), 10);
	//ArxDrawHelper::DrawMText(basePt+v2*L1, 0, _T("����"), 10);
	ArxDrawHelper::DrawMText(basePt+v1*L2+v2*L1, 0, _T("����������"), 10);
}

void CoalProxy::drawWsTunnel()
{
	double angle = DegToRad(coal->dip_angle);
	//double L1 = ws->l1, L2 = ws->l2*cos(angle);
	double L1 = ws->l1, L2 = ws->l2;
	double w = ws->w, h = ws->h;
	
	//���ƻ���
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	AcDbObjectId t1 = Draw::CreateDoubleLine(pt, pt+v1*L2, w);
	//���ƹ���������
	AcDbObjectId t2 = Draw::CreateDoubleLine(pt, pt+v2*L1, w);
	//���Ʒ���
	AcDbObjectId t3 = Draw::CreateDoubleLine(pt+v2*L1, pt+v1*L2+v2*L1, w);
	ArxDrawHelper::DrawMText(pt+v1*L2, 0, _T("�������"), 10);
	//ArxDrawHelper::DrawMText(pt+v2*L1, 0, _T("����"), 10);
	ArxDrawHelper::DrawMText(pt+v1*L2+v2*L1, 0, _T("�������"), 10);
}

void CoalProxy::drawCoal()
{
	//����ú�����ƽ��ͶӰ��Χ
	AcGePoint3d basePt;
	double Wc = 0, Hc = 0;
	caclCoalExtent(basePt, Wc, Hc);

	//��ͼú����
	AcGePoint3d insertPt = ArxDrawHelper::CaclPt(basePt,AcGeVector3d::kXAxis,0.5*Wc,AcGeVector3d::kYAxis,0.5*Hc);
	AcDbObjectId objId = ArxDrawHelper::DrawRect(insertPt, 0, Wc, Hc);
	ArxDrawHelper::MakeAlignedDim(basePt, basePt+AcGeVector3d::kXAxis*Wc, 50, false);
	ArxDrawHelper::MakeAlignedDim(basePt, basePt+AcGeVector3d::kYAxis*Hc, 30, true);
	//��������
	if(!objId.isNull())
	{
		CoalData data;
		data.setDataSource(objId);
		data.m_name = _T("����");
		data.m_thick = coal->thick;
		data.m_angle = coal->dip_angle;
		data.m_width = ws->l1;
		data.m_height = ws->l2;
		data.m_pt = basePt;
		data.update(true);
	}
}

//���㹤�����ƽ��ߴ�
void CoalProxy::caclCoalExtent( AcGePoint3d& insertPt, double& Wc, double& Hc )
{
	double L1 = ws->l1, L2 = ws->l2;
	double w = ws->w, h = ws->h;
	double left = tech->left_side, right = tech->right_side;
	double top = tech->top_side, bottom = tech->bottom_side;
	double thick = coal->thick, angle = DegToRad(coal->dip_angle);

	//������(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
	//Wc = (L2 + w + left + left_offset + right_offset)*cos(angle);
	Wc = L2 + w + left + left_offset + right_offset;
	Hc = L1 + 2 * w + left + right + bottom_offset + top_offset;
	
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	insertPt = ArxDrawHelper::CaclPt(pt,v1,-1*(w*0.5+left+left_offset),v2,-1*(w*0.5+left+bottom_offset));
}

void CoalProxy::caclPoreExtent( AcGePoint3d& insertPt, double& Wp, double& Hp )
{
	double L1 = ws->l1, L2 = ws->l2;
	double w = ws->w, h = ws->h;
	double left = tech->left_side, right = tech->right_side;
	double top = tech->top_side, bottom = tech->bottom_side;
	double thick = coal->thick, angle = DegToRad(coal->dip_angle);

	//������(���򳤶�L2+�����������Ʒ�Χleft+ƫ��)
	//Wp = (L2 + w + left)*cos(angle);
	Wp = L2 + w + left;
	Hp = L1 + 2 * w + left + right;

	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	insertPt = ArxDrawHelper::CaclPt(pt,v1,-1*(w*0.5+left),v2,-1*(w*0.5+left));
}

void CoalProxy::draw()
{
	ArxDocLockSwitch lock_switch;
	drawCoal();
	drawWsTunnel();
	drawRockTunnel();
	drawPores();
}
