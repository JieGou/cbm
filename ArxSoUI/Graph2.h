#pragma once

#include "Data.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

namespace P2
{

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
		//ִ�о���Ļ�ͼ����(��������ϵ������ú�㡢������������곡����ס��װ�����)
		//���麯����draw()�������á���������������������������Ҫ,�����ظ��麯��
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
		//����ucs����ϵ(������������Ҫ,Ӧ�ڹ��캯���е��ø÷���)
		void setUcs(const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis);

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
		AcGePoint3d caclPoreBasePoint3() const;
		//�����곡�Ļ���λ��
		AcGePoint3d caclSiteBasePoint1() const;
		AcGePoint3d caclSiteBasePoint2() const;
		AcGePoint3d caclSiteBasePoint3() const;
		//����һ���������ϵ��곡(gap_y������֮��,�����곡���������һ��)
		void drawSitesOnTunnel(const AcGePoint3d& spt, const AcGePoint3d& ept, double gap_x, double gap_y, double w, double h, double angle=0, bool excludeFirst=true);

		/** ������ͼ����. */
	protected:
		AcDbObjectId drawRect(const AcGePoint3d& cnt, double angle, double width, double height);
		AcDbObjectId drawRect2(const AcGePoint3d& pt, double angle, double width, double height);
		AcDbObjectId drawCircle(const AcGePoint3d& pt, double radius);
		AcDbObjectId drawDoubleLine(const AcGePoint3d& spt, const AcGePoint3d& ept, double width);
		AcDbObjectId drawMText(const AcGePoint3d& pt, double angle, const CString& text, double height);
		AcDbObjectId drawLine(const AcGePoint3d& pt, double angle, double length);
		AcDbObjectId drawLine(const AcGePoint3d& spt, const AcGePoint3d& ept);
		AcDbObjectId drawAlignedDim(const AcGePoint3d& pt1,const AcGePoint3d& pt2,double offset=30,bool clockwise=true);
		//��¼�����Ƶ�ͼԪ(��Graph�ڲ�ʹ��)
		void addEnt(const AcDbObjectId& objId);

		/** ����ͻ�ͼ�õ��Ĳ���. */
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

		/** ��������������Ǵ���3������ָ������ȡ������. */
	protected:
		cbm::CoalPtr coal;                 // ú��ָ��
		cbm::DesignWorkSurfPtr work_surf;  // ��ƹ�����ָ��
		cbm::DesignTechnologyPtr tech;     // ��Ƴ�ɼ�������ָ��

		/** ucs��ص�����. */
	private:
		AcGePoint3d m_basePt;      // ��ͼ����
		AcDbObjectIdArray m_ents;  // ���л��Ƶ�ͼԪ
		AcGeMatrix3d m_mat;        // ucs����ϵ�任����
	}; // class Graph

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
	}; // class PlanGraph

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
	}; // class HeadGraph

	//��������ͼ(�����Զ���ucs�򻯼������)
	//�Թ���������������е�Ϊԭ��,ú��������(����->����)Ϊx��������,��������Ϸ���Ϊy��������
	class DipGraph : public Graph
	{
	public:
		DipGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfPtr& work_surf, const cbm::DesignTechnologyPtr& tech);

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
	}; // class DipGraph

} // namespace P2