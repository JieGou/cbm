#pragma once

#include "resource.h"
#include "simple_app.h"

// CefDialog �Ի���

class CefDialog : public CDialog
{
	DECLARE_DYNAMIC(CefDialog)

public:
	CefDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CefDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual BOOL OnInitDialog();
};
