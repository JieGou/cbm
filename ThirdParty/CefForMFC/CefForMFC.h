
// CefForMFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"

class CefForMFCApp : public CWinAppEx
{
public:
	CefForMFCApp();

public:
	virtual BOOL InitInstance();
	virtual int CefForMFCApp::ExitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CefForMFCApp theApp;