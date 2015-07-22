// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDlg.h"


// TestDlg �Ի���

IMPLEMENT_DYNAMIC(TestDlg, CDialog)

TestDlg::TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TestDlg::IDD, pParent)
{

}

TestDlg::~TestDlg()
{
}

void TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestDlg, CDialog)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()



// TestDlg ��Ϣ�������

BOOL TestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	MoveWindow(0,0,350,190);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	dlg.Create(GetSafeHwnd(),WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, NULL, 0,0,0,0);
	dlg.GetNative()->SendMessage(WM_INITDIALOG);
	//dlg.CenterWindow();

	//CRect rect(0,0,0,0);
	//GetDlgItem(IDC_SOUI_WND)->GetWindowRect(&rect);
	//ScreenToClient(&rect);
	//dlg.MoveWindow(&rect);

	//͸������
	//Set WS_EX_LAYERED on this window
	::SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, ::GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE | WS_EX_LAYERED));
	//Make this window 70% alpha transparent
	this->SetLayeredWindowAttributes(0,(255*90)/100,LWA_ALPHA);

	dlg.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


LRESULT TestDlg::OnNcHitTest(CPoint point)
{
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
	//return CDialog::OnNcHitTest(point);
}
