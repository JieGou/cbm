#pragma once

#include "Data.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

//����ͼ���ƻ���
class Graph
{
public:
	//����������
	virtual ~Graph() {}
	//��ͼ(ú�㡢������곡����ס��װ�����)
	void draw();
	//���û�ͼ��������
	void setPoint(const AcGePoint3d& pt);
	//��ȡ��ͼ��������
	AcGePoint3d getPoint() const;

protected:
	//��ͼ(ú�㡢������������곡����ס��װ�����)
	//���麯����draw()��������
	//�������������������,�����ظ��麯��
	virtual void subDraw();
	//�����곡
	virtual void drawSites() = 0;
	//�������
	virtual void drawPores() = 0;
	//���Ƶװ�����
	virtual void drawRockTunnel() = 0;
	//���ƹ������3�����
	virtual void drawWsTunnel() = 0;
	//����ú��
	virtual void drawCoal() = 0;

protected:
	//���캯��
	Graph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech);
	//��¼�����Ƶ�ͼԪ
	void addEnt(const AcDbObjectId& objId);
	//����ú��ĳߴ�(��-����, ��-����, ��-���)
	void caclCoalExtent(double& Lc, double& Wc, double& Hc) const;
	AcGePoint3d caclCoalBasePoint1() const;
	AcGePoint3d caclCoalBasePoint2() const;
	AcGePoint3d caclCoalBasePoint3() const;
	//������׵ĳߴ�(�����)
	void caclPoreExtent(double& Lp, double& Wp, double& Hp) const;
	AcGePoint3d caclPoreBasePoint1() const;
	AcGePoint3d caclPoreBasePoint2() const;
	AcGePoint3d caclPoreBasePoint3() const;
	//�����곡�Ļ���λ��
	AcGePoint3d caclSiteBasePoint1() const;
	AcGePoint3d caclSiteBasePoint2() const;
	AcGePoint3d caclSiteBasePoint3() const;
	//ͼԪ����ϵ�任
	void tranform(const AcGeMatrix3d& mat);
	//����һ���������ϵ��곡(gap_y������֮��,�����곡���������һ��)
	void drawSitesOnTunnel(const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle=0, bool excludeFirst=true);

protected:
	//����ļ������
	//���򳤶Ⱥ����򳤶�
	double L1, L2;
	//ú���Ⱥ����(����)
	double thick, angle;
	//����������Ŀ�Ⱥ͸߶�
	double w, h;
	//�곡��ȡ��߶Ⱥ����
	double ws, hs, ds, site_gap;
	//�װ���Ŀ�Ⱥ͸߶�
	double wd, hd;
	//�������°��
	double left, right, top, bottom;
	//����͹������ˮƽͶӰ���롢����
	double h_offset, v_offset;
	//��װ뾶�ͳ�ɰ뾶
	double radius, pore_gap;
	//�������ұ߾�(�����ڻ�ͼ����,������ʵ�ʼ���)
	double left_margin, right_margin, top_margin, bottom_margin;
	
protected:
	AcGePoint3d m_basePt;      // ��ͼ����
	AcDbObjectIdArray m_ents;  // ���л��Ƶ�ͼԪ

protected:
	cbm::CoalPtr coal;         // ú��
	cbm::DesignWorkSurfPtr work_surf; // ��ƹ�����
	cbm::DesignTechnologyPtr tech; // ��Ƴ�ɼ�������
};

//ƽ��ͼ(ע:�ڲ��������������Ŀ��ֵ)
//�Թ���������������е�Ϊԭ��,ú��������Ϊx��������,������(����->����)Ϊy��������
class PlanGraph : public Graph
{
public:
	PlanGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech);

protected:
	//�����곡
	virtual void drawSites();
	//�������
	virtual void drawPores();
	//���Ƶװ�����
	virtual void drawRockTunnel();
	//���ƹ������3�����
	virtual void drawWsTunnel();
	//����ú��
	virtual void drawCoal();
};

//��������ͼ
//�Թ����������������������ĵ��е�Ϊԭ��,ú��������Ϊx��������,����ĸ߶ȷ���Ϊy��������
class HeadGraph : public Graph
{
public:
	HeadGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech);

protected:
	//�����곡
	virtual void drawSites();
	//�������
	virtual void drawPores();
	//���Ƶװ�����
	virtual void drawRockTunnel();
	//���ƹ������3�����
	virtual void drawWsTunnel();
	//����ú��
	virtual void drawCoal();
};

//��������ͼ(�����Զ���ucs�򻯼������)
//�Թ���������������е�Ϊԭ��,ú��������(����->����)Ϊx��������,��������Ϸ���Ϊy��������
class DipGraph : public Graph
{
public:
	DipGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech);

protected:
	virtual void subDraw();
	//�����곡
	virtual void drawSites();
	//�������
	virtual void drawPores();
	//���Ƶװ�����
	virtual void drawRockTunnel();
	//���ƹ������3�����
	virtual void drawWsTunnel();
	//����ú��
	virtual void drawCoal();
};