// Dao.h : Dao DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDaoApp
// �йش���ʵ�ֵ���Ϣ������� Dao.cpp
//

class CDaoApp : public CWinApp
{
public:
    CDaoApp();

// ��д
public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};
