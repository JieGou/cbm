#pragma once

#include "Data.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

//������ص�һЩ��

class Draw
{
public:
	static AcDbObjectId CreateDoubleLine(const AcGePoint3d& spt, const AcGePoint3d& ept, double width);
};

class CoalProxy
{
public:
	CoalProxy();
	void draw();

private:
	//�������
	void drawPores();
	//���Ƶװ�����
	void drawRockTunnel();
	//���ƹ������3�����
	void drawWsTunnel();
	//����ú��ͶӰƽ��
	void drawCoal();
	//����ú���ƽ��ͶӰ��Χ
	void caclCoalExtent(AcGePoint3d& insertPt, double& Wc, double& Hc);
	//������׵�ƽ��ͶӰ��Χ
	void caclPoreExtent(AcGePoint3d& insertPt, double& Wp, double& Hp);

public:
	AcGePoint3d pt;
	cbm::CoalPtr coal;         // ú��
	cbm::DesignWorkSurfPtr ws; // ��ƹ�����
	cbm::DesignTechnologyPtr tech; // ��Ƴ�ɼ�������

	//��������ƫ��(�����ڻ�ͼ����,������ʵ�ʼ���)
	double left_offset, right_offset, top_offset, bottom_offset;
};