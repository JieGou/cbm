#include "StdAfx.h"
#include "Graph23.h"

#include <Util/HelperClass.h>
#include <ArxHelper/HelperClass.h>

namespace P23
{

	Graph::Graph(const cbm::CoalPtr& _coal, const cbm::DesignWorkSurfTechnologyPtr& _tech)
		: BaseGraph(), coal(_coal), tech(_tech)
	{
		left_margin = 20;
		right_margin = 20;
		bottom_margin = 20;
		top_margin = 20;

		//倾向长度和走向长度
		L1 = tech->l1, L2 = tech->l2;
		//煤层厚度和倾角(弧度)
		thick = coal->thick, angle = DegToRad(coal->dip_angle);
		//工作面巷道的宽度和高度
		w = tech->w, h = tech->h;
		//钻孔半径和钻孔底间距(孔径的单位是mm)
		radius = tech->dp*0.5*0.001, pore_gap = tech->gp;
		//钻孔压茬长度
		pore_stubble = tech->pore_stubble;
		//顺层斜交钻孔倾角
		pore_angle = tech->pore_angle;
		//顺层钻孔类型
		pore_type = tech->pore_type;
	}

	void Graph::subDraw()
	{
		//绘制图形
		drawCoal();
		drawTunnel();
		drawPores();
	}

	void Graph::caclCoalExtent(double& Lc, double& Wc, double& Hc) const
	{
		//计算宽度(倾向长度L2+工作面左帮控制范围left+偏移)
		//Lc = (L1 + left_margin + right_margin)*cos(angle);
		Lc = L1 + left_margin + right_margin;
		Wc = w + bottom_margin + top_margin;
		Hc = thick;
	}

	PlanGraph::PlanGraph(const cbm::CoalPtr& coal, const cbm::DesignWorkSurfTechnologyPtr& tech) : Graph(coal,  tech)
	{
	}

	void PlanGraph::drawPores()
	{
		if(pore_gap <= 0) return;

		//巷道的中点位置作为基点
		AcGePoint3d basePt = getPoint();
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;

	}

	void PlanGraph::drawTunnel()
	{
		//巷道的中点位置作为基点
		AcGePoint3d basePt = getPoint();
		//绘制掘进巷
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		AcDbObjectId t1 = this->drawDoubleLine(basePt, basePt+v1*L1, w);
	}

	void PlanGraph::drawCoal()
	{
		//计算煤层的长宽高
		double Lc = 0, Wc = 0, Hc = 0;
		caclCoalExtent(Lc, Wc, Hc);

		//计算平面图中煤层的左下角基点坐标
		AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
		AcGePoint3d basePt = ArxDrawHelper::CaclPt(getPoint(),v1,-1*left_margin,v2,-0.5*Wc);

		//绘制煤层面
		AcDbObjectId coalId = this->drawRect2(basePt, 0, Lc, Wc);
		this->drawAlignedDim(basePt, basePt+v1*Lc, 50, false);
		this->drawAlignedDim(basePt, basePt+v2*Wc, 30, true);
	}
} // namespace P23