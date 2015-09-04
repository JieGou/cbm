#include "StdAfx.h"
#include "Graph.h"
#include "DoubleLine.h"

#include <Util/HelperClass.h>
#include <ArxHelper/HelperClass.h>

BaseGraph::BaseGraph()
{
	//Ĭ��Ϊ��λ����(�������κα任)
	m_mat.setToIdentity();
}

void BaseGraph::setPoint(const AcGePoint3d& pt)
{
	this->m_basePt = pt;
}

AcGePoint3d BaseGraph::getPoint() const
{
	return this->m_basePt;
}

void BaseGraph::addEnt(const AcDbObjectId& objId)
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

void BaseGraph::draw()
{
	ArxDocLockSwitch lock_switch;
	//����ϵ�任Ϊucs
	m_mat.setTranslation(getPoint().asVector());

	//��ǰ����ϵΪucs,��Ҫ����������Ϊԭ��
	setPoint(AcGePoint3d::kOrigin);

	//����ͼ��(�����������ʵ��)
	subDraw();
	
	//��ucs����ϵ�»��Ƶ�ͼ�α任��wcs����ϵ
	ArxUcsHelper::TransformEntities(m_ents, m_mat);
}

void BaseGraph::setUcs(const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis)
{
	ArxUcsHelper::MakeTransformMatrix(m_mat, origin, xAxis, yAxis);
}

AcDbObjectId BaseGraph::drawRect(const AcGePoint3d& cnt, double angle, double width, double height)
{
	AcDbObjectId objId = ArxDrawHelper::DrawRect(cnt, angle, width, height);
	this->addEnt(objId);
	return objId;
}

AcDbObjectId BaseGraph::drawRect2(const AcGePoint3d& pt, double angle, double width, double height)
{
	AcDbObjectId objId = ArxDrawHelper::DrawRect2(pt, angle, width, height);
	this->addEnt(objId);
	return objId;
}

AcDbObjectId BaseGraph::drawCircle(const AcGePoint3d& pt, double radius)
{
	AcDbObjectId objId = ArxDrawHelper::DrawCircle(pt, radius);
	this->addEnt(objId);
	return objId;
}

AcDbObjectId BaseGraph::drawDoubleLine(const AcGePoint3d& spt, const AcGePoint3d& ept, double width)
{
	AcDbObjectId objId = DoubleLine::Draw(spt, ept, width);
	this->addEnt(objId);
	return objId;
}

AcDbObjectId BaseGraph::drawMText(const AcGePoint3d& pt, double angle, const CString& text, double height)
{
	AcDbObjectId objId = ArxDrawHelper::DrawMText(pt, angle, text, height);
	this->addEnt(objId);
	return objId;
}

AcDbObjectId BaseGraph::drawLine(const AcGePoint3d& pt, double angle, double length)
{
	AcDbObjectId objId = ArxDrawHelper::DrawLine(pt, angle, length);
	this->addEnt(objId);
	return objId;
}

AcDbObjectId BaseGraph::drawLine(const AcGePoint3d& spt, const AcGePoint3d& ept)
{
	AcDbObjectId objId = ArxDrawHelper::DrawLine(spt, ept);
	this->addEnt(objId);
	return objId;
}

AcDbObjectId BaseGraph::drawAlignedDim(const AcGePoint3d& pt1, const AcGePoint3d& pt2, double offset /*= 30*/, bool clockwise/*=true*/)
{
	AcDbObjectId objId = ArxDrawHelper::MakeAlignedDim(pt1, pt2, offset, clockwise);
	this->addEnt(objId);
	return objId;
}