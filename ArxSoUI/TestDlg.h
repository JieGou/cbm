#pragma once

#include "LoginDlg.h"
#include "resource.h"
// TestDlg �Ի���

class TestDlg : public CDialog
{
	DECLARE_DYNAMIC(TestDlg)

public:
	TestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TestDlg();
LoginDlg dlg;
// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnNcHitTest(::CPoint point);
};
