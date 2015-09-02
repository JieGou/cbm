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

class Graph
{
public:
	virtual ~Graph() {}
	virtual void draw() = 0;

	void setPoint(const AcGePoint3d& pt);
	AcGePoint3d getPoint() const;

public:
	cbm::CoalPtr coal;         // ú��
	cbm::DesignWorkSurfPtr ws; // ��ƹ�����
	cbm::DesignTechnologyPtr tech; // ��Ƴ�ɼ�������

protected:
	Graph();
	AcGePoint3d m_basePt; // �����������߻���
	//��������ƫ��(�����ڻ�ͼ����,������ʵ�ʼ���)
	double m_left_offset, m_right_offset, m_top_offset, m_bottom_offset;
};

class PlanGraph : public Graph
{
public:
	PlanGraph();
	virtual void draw();

private:
	//�����곡
	void drawSites();
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
};

class SectionGraph : public Graph
{
public:
	SectionGraph();
	virtual void draw();

private:
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
};