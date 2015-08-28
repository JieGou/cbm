#pragma once

#include "dlimexp.h"

// ϵͳ����������
// ���ڵ����ꡢ����������ж�
class ARXHELPER_DLLIMPEXP ArxTolSetter
{
public:
	ArxTolSetter(double eq)
	{
		m_originEq = AcGeContext::gTol.equalPoint();
		setEq(eq);
	}

	void setEq(double eq)
	{
		AcGeContext::gTol.setEqualPoint(eq);
	}

	~ArxTolSetter()
	{
		AcGeContext::gTol.setEqualPoint(m_originEq);
	}

private:
	double m_originEq;
};

/*
ʹ�÷���:
ArxTolSetter ts(0.001); // ����������ʱ���Զ���ԭϵͳ���

�ȼ���:
// ����ϵͳ���
double ep = AcGeContext::gTol.equalPoint();
// �������
AcGeContext::gTol.setEqualPoint(0.001); // 10-3

// do something
// ...

// ��ԭϵͳ���
AcGeContext::gTol.setEqualPoint(ep);
*/