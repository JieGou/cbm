#pragma once

// ����ͼ�λ���
extern void DrawCross(AcGiWorldDraw *mode, const AcGePoint3d& pt, double radius);
extern void DrawSin(AcGiWorldDraw *mode, const AcGePoint3d& pt, double angle, double radius);
extern void DrawShaft(AcGiWorldDraw *mode, const AcGePoint3d& pt, double radius);
extern void DrawJoint(AcGiWorldDraw *mode, const AcGePoint3d& pt, double radius, int jdt);
extern void DealSpPoints(CString& value);
extern void DrawBackGround(AcGiWorldDraw* mode ,const AcGePoint3dArray& pts,int colorIndx);
