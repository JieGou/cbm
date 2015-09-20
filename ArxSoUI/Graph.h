#pragma once

//����ͼ���ƻ���
class BaseGraph
{
public:
    //����������
    virtual ~BaseGraph() {}
    //��ͼ(ú�㡢������곡����ס��װ������)
    void draw();
    //���û�ͼ��������
    void setPoint( const AcGePoint3d& pt );
    //��ȡ��ͼ��������
    AcGePoint3d getPoint() const;

protected:
    //ִ�о���Ļ�ͼ����(����ú�㡢������������곡����ס��װ�����ȵ�)
    virtual void subDraw() = 0;

protected:
    //���캯��
    BaseGraph();
    //����ucs����ϵ(������������Ҫ,Ӧ�ڹ��캯���е��ø÷���)
    void setUcs( const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis );

    /** ������ͼ����. */
protected:
    AcDbObjectId drawRect( const AcGePoint3d& cnt, double angle, double width, double height );
    AcDbObjectId drawRect2( const AcGePoint3d& pt, double angle, double width, double height );
    AcDbObjectId drawCircle( const AcGePoint3d& pt, double radius );
    AcDbObjectId drawDoubleLine( const AcGePoint3d& spt, const AcGePoint3d& ept, double width );
    AcDbObjectId drawMText( const AcGePoint3d& pt, double angle, const CString& text, double height );
    AcDbObjectId drawLine( const AcGePoint3d& pt, double angle, double length );
    AcDbObjectId drawLine( const AcGePoint3d& spt, const AcGePoint3d& ept );
    AcDbObjectId drawAlignedDim( const AcGePoint3d& pt1, const AcGePoint3d& pt2, double offset = 30, bool clockwise = true );
    //��¼�����Ƶ�ͼԪ(��BaseGraph���ڲ�ʹ��)
    void addEnt( const AcDbObjectId& objId );

    /** ucs��ص�����. */
private:
    AcGePoint3d m_basePt;      // ��ͼ����
    AcDbObjectIdArray m_ents;  // ���л��Ƶ�ͼԪ
    AcGeMatrix3d m_mat;        // ucs����ϵ�任����

}; // class Graph