#include "stdafx.h"
#include "OccurrenceGraph.h"

OccurrenceGraph::OccurrenceGraph(cbm::MinePtr _mine) : mine(_mine)
{
	L1 = 1000;
}

void OccurrenceGraph::subDraw()
{
	//����ͼ��
	drawAllCoals(this->mine);
}

void OccurrenceGraph::drawCoal(cbm::CoalPtr coal, const AcGePoint3d& basePt)
{
	//ú�����
	double angle = DegToRad( coal->dip_angle );
	//ú����
	double thick = coal->thick;
	
	//����ú��(��ú������½�λ��Ϊ����)
	AcDbObjectId coalId = this->drawRect2( basePt, angle, L1, thick );
	//��עú����
	AcGeVector3d v1 = AcGeVector3d::kXAxis, v2 = AcGeVector3d::kYAxis;
	v1.rotateBy(angle, AcGeVector3d::kZAxis);
	v2.rotateBy(angle, AcGeVector3d::kZAxis);

	this->drawMText( basePt + v1 * L1 *0.5 + v2 * thick * 0.5, angle, coal->name, 10 );
	//��עú����
	this->drawAlignedDim(basePt+v1*L1, basePt+v1*L1+v2*thick, 30, false);
}

void OccurrenceGraph::drawAllCoals(cbm::MinePtr mine)
{
	//���ҿ󾮵�����ú��
	orm::RecordPtrListPtr coal_lists = FIND_MANY(Coal, FKEY(Mine), mine->getStringID());
	if(coal_lists == 0) return;
	
	AcGePoint3d basePt;
	for( int i = 0; i < coal_lists->size(); i++ )
	{
		cbm::CoalPtr coal = DYNAMIC_POINTER_CAST( cbm::Coal, coal_lists->at( i ) );
		if(coal == 0) continue;
		
		//���ϸ�ú��ļ��
		double layer_gap = coal->layer_gap;
		//��ǰú��Ļ���
		AcGePoint3d pt = basePt - AcGeVector3d::kYAxis*layer_gap;
		//��עú����(��һ��ú��ļ�಻��ע)
		if(i > 0)
		{
			this->drawAlignedDim(basePt, pt, 30, false);
		}
		//���µ�ǰú��Ļ���
		basePt  = pt;
		//����ú��
		this->drawCoal(coal, basePt);
	}
}
