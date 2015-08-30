#pragma once

#include "dlimexp.h"

#include <MineGEDraw/MineGEDraw.h>
#include <ArxHelper/HelperClass.h>

// ��ϵͳͼԪ����(������)
class MINEGE_DLLIMPEXP MineGE : public AcDbEntity 
{
public:
	ACRX_DECLARE_MEMBERS(MineGE) ;

protected:
	static Adesk::UInt32 kCurrentVersionNumber;

	// �����ӿ�
public:
	virtual ~MineGE ();	

	// ��ȡ��������
	CString getTypeName() const;

	//�л����ӻ�Ч��
	void switchDraw(const CString& drawName);

	// ��ȫ������extra param�Ĳ����󣬸���ͼԪ�Ĳ���
	//void configDraw(const CString& drawName);

	// ����ͼԪ���ӻ�Ч��
	void updateDraw();

	// ��ȡ���ݶ���id
	AcDbObjectId getDataObject() const;

	//����/�رո���Ч��
	void enableFollow(bool bFollow);

	// ����Ҫ����ʵ�ֵ��麯��
protected:
	// ���ؼ�����д�뵽writer��
	virtual void writeKeyParam(DrawParamWriter& writer) const = 0;

	// ��reader�ж�ȡ�ؼ�����
	virtual void readKeyParam(DrawParamReader& reader) = 0;

	//��DataObject�е����ݱ��޸ĺ�MineGE�����¼�����ӻ�����
	//��ЩͼԪ��Ҫ�Բ������ж���ĵ���(����LinkedGE)
	virtual void onParamsChanged() {}

	// AcDbObject���غ���
public:
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);

	// AcDbEntity�����غ���
protected:
	// ͼԪ����
	virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode);

	// �任����(�ƶ���ѡ�񡢾���)--Ŀǰ�ݲ�����"����"����
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d & xform);

	// ��ȡ��׽��
	virtual Acad::ErrorStatus subGetOsnapPoints(
		AcDb::OsnapMode osnapMode,
		Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint,
		const AcGePoint3d &lastPoint,
		const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints,
		AcDbIntArray &geomIds) const ;

	// ��ȡ�е�
	virtual Acad::ErrorStatus subGetGripPoints(
		AcGePoint3dArray &gripPoints, 
		AcDbIntArray &osnapModes, 
		AcDbIntArray &geomIds) const ;

	// �е�༭��Ϊ
	virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbIntArray &indices, const AcGeVector3d &offset) ;

	// ��Χ������(����ȷ�����ŵķ�Χ)
	// һ��"����"��3d��Χ��(������)
	virtual Acad::ErrorStatus subGetGeomExtents(AcDbExtents& extents) const;

	virtual Acad::ErrorStatus subClose(void);
	virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing);

protected:
	// ���캯��
	MineGE();

	// ���²���(��������)
	// true  -- ������д�뵽draw��
	// false -- ��������ȡ������ge��
	// ��writeParamToGEDraw��readParamFromGEDraw�����ڹ������ظ�(***)
	void updateDrawParam(MineGEDraw* pDraw, bool readOrWrite = true) const;

	// ��ȡ��ǰdraw����(��������ʹ�ã�����ֱ�Ӳ���˽������)
	MineGEDraw* getCurDrawPtr() const;

private:
	// ���Ʊ�������
	void drawBackground(MineGEDraw* pDraw, AcGiWorldDraw *mode);

	// ��д�ؼ�����
	void readKeyParamFromGEDraw(MineGEDraw* pDraw);
	void writeKeyParamToGEDraw(MineGEDraw* pDraw) const;

	// ��д����ͼԪ���Ӳ���
	void readExtraParamFromGEDraw(MineGEDraw* pDraw);
	void writeExtraParamToGEDraw(MineGEDraw* pDraw) const;	

	// ��д����(�ؼ������͸��Ӳ���)-- ��������
	void readParamFromGEDraw(MineGEDraw* pDraw);
	void writeParamToGEDraw(MineGEDraw* pDraw) const;

	// ��ʼ�����еĸ��Ӳ�����xdata��
	void initAllExtraParamsToXData();

	// ��ȡ�Ѵ��ڵ�draw
	void extractExistedDraw(AcStringArray& existedDraw);

	// ��ʼ�����ӻ�Ч��
	void initDraw();

	// ��ʼ����������
	void initPropertyData();

	//���¿��ӻ�����
	//ע:ĳЩ������������ݱ仯��,Ӧ���¼��㸽�Ӳ���,�����ǹؼ�����
	void updateDrawParams(MineGEDraw* pDraw);

	//��ȡͼԪ��ǰ���ӻ�Ч������
	CString getCurDraw() const;

	//�任���еĹ���ͼԪ
	void transformAllTagGE(const AcGeMatrix3d& xform);

protected:
	// д���������ݵ�MineGEDraw��
	virtual void writePropertyDataToGEDraw(MineGEDraw* pDraw) const;

private:
	// ͼԪ���������ݶ���
	AcDbObjectId m_dataObjectId;
	//�Ƿ�ʵ�ָ���Ч��(����ͼԪTagGE�����ƶ�,Ĭ���ǽ��õ�!)
	bool m_bFollow;
};

#ifdef MINEGE_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(MineGE)
#endif