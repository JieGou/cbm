#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

namespace P1
{

//����ͼ���ƻ���
class Graph : public BaseGraph
{
protected:
	//�����곡
	virtual void drawSites() = 0;
	//�������
	virtual void drawPores() = 0;
	//���Ƶװ�����
	virtual void drawRockTunnel() = 0;
	//���ƹ������3�����
	virtual void drawTunnel() = 0;
	//����ú��
	virtual void drawCoal() = 0;

protected:
	//���캯��
	Graph(const cbm::CoalPtr& coal, const cbm::DesignDrillingSurfTechnologyPtr& tech);
	//ִ�о���Ļ�ͼ����(����ú�㡢������������곡����ס��װ�����)
	virtual void subDraw();

	/** �������㷽��. */
protected:
	//����ú��ĳߴ�(��-����, ��-����, ��-���)
	void caclCoalExtent(double& Lc, double& Wc, double& Hc) const;
	AcGePoint3d caclCoalBasePoint1() const;
	AcGePoint3d caclCoalBasePoint2() const;
	AcGePoint3d caclCoalBasePoint3() const;
	//������׵ĳߴ�(�����)
	void caclPoreExtent(double& Lp, double& Wp, double& Hp) const;
	AcGePoint3d caclPoreBasePoint1() const;
	AcGePoint3d caclPoreBasePoint2() const;
	//�����곡�Ļ���λ��
	//����һ���������ϵ��곡(gap_y������֮��,�����곡���������һ��)
	void drawSitesOnTunnel(const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle=0, bool excludeFirst=true);

	/** ����ͻ�ͼ�õ��Ĳ���. */
protected:
	//���򳤶Ⱥ����򳤶�
	double L1, L2;
	//ú���Ⱥ����(����)
	double thick, angle;
	//����������Ŀ�Ⱥ͸߶�
	double w, h;
	//�곡������Լ��곡���
	double Ls, Ws, Hs, site_gap;
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

	/** ��������������Ǵ���2������ָ������ȡ������. */
protected:
	cbm::CoalPtr coal;                 // ú��ָ��
	cbm::DesignDrillingSurfTechnologyPtr tech;  // ��ƾ��������ָ��

}; // class Graph

//ƽ��ͼ(ע:�ڲ��������������Ŀ��ֵ)
//�Թ���������������е�Ϊԭ��,ú��������Ϊx��������,������(����->����)Ϊy��������
class PlanGraph : public Graph
{
public:
	PlanGraph(const cbm::CoalPtr& coal, const cbm::DesignDrillingSurfTechnologyPtr& tech);

protected:
	//�����곡
	virtual void drawSites();
	//�������
	virtual void drawPores();
	//���Ƶװ�����
	virtual void drawRockTunnel();
	//���ƹ������3�����
	virtual void drawTunnel();
	//����ú��
	virtual void drawCoal();
}; // class PlanGraph

//��������ͼ
//�Թ����������������������ĵ��е�Ϊԭ��,ú��������Ϊx��������,����ĸ߶ȷ���Ϊy��������
class HeadGraph : public Graph
{
public:
	HeadGraph(const cbm::CoalPtr& coal, const cbm::DesignDrillingSurfTechnologyPtr& tech);

protected:
	//�����곡
	virtual void drawSites();
	//�������
	virtual void drawPores();
	//���Ƶװ�����
	virtual void drawRockTunnel();
	//���ƹ������3�����
	virtual void drawTunnel();
	//����ú��
	virtual void drawCoal();
}; // class HeadGraph

//��������ͼ(�����Զ���ucs�򻯼������)
//�Թ���������������е�Ϊԭ��,ú��������(����->����)Ϊx��������,��������Ϸ���Ϊy��������
class DipGraph : public Graph
{
public:
	DipGraph(const cbm::CoalPtr& coal, const cbm::DesignDrillingSurfTechnologyPtr& tech);

protected:
	//�����곡
	virtual void drawSites();
	//�������
	virtual void drawPores();
	//���Ƶװ�����
	virtual void drawRockTunnel();
	//���ƹ������3�����
	virtual void drawTunnel();
	//����ú��
	virtual void drawCoal();
}; // class DipGraph

} // namespace P1