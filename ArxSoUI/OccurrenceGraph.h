#pragma once

#include "Data.h"
#include "Graph.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>

using namespace orm;
using namespace cbm;

// ú�㸳��ʾ��ͼ
class OccurrenceGraph : public BaseGraph
{
public:
	OccurrenceGraph(cbm::MinePtr mine);

protected:
	virtual void subDraw();
	//��������ú��
	void drawAllCoals(cbm::MinePtr mine);
	//����һ��ú��
	void drawCoal(cbm::CoalPtr coal, const AcGePoint3d& basePt);
protected:
	// ������
	cbm::MinePtr mine;
	// ú�����򳤶�
	//�����ݲ����ڣ�Ϊ�˻�ͼЧ�����ۣ��ڲ��趨һ��ֵ
	double L1;
};