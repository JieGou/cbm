#include "stdafx.h"
#include "LoginDlg.h"
#include "RegDlg.h"

using namespace SOUI;

LoginDlg::LoginDlg(BOOL bModal) 
	: AcadSouiDialog(_T("layout:login"), bModal)
{
}

LoginDlg::~LoginDlg(void)
{
}

void LoginDlg::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//	//nID==6��Ӧmenu_test����Ĳ˵���exit�
		//	PostMessage(WM_CLOSE);
		//}
		//else if(nID==54)
		//{
		//	//about SOUI
		//	STabCtrl *pTabCtrl = FindChildByName2<STabCtrl>(L"tab_main");
		//	if(pTabCtrl) pTabCtrl->SetCurSel(_T("about"));
		//}
	}
}

LRESULT LoginDlg::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	SetMsgHandled(FALSE);
	return 0;
}

void LoginDlg::OnLogin()
{
	CString msg;
	msg.Format(_T("�û��ɹ���¼"));
	SMessageBox(m_hWnd,msg,_T("����"),MB_OK);
    SEdit *pEdit = FindChildByName2<SEdit>(L"username");
    pEdit->SetWindowText(_T("dlj"));
	AcadSouiDialog::OnOK();
}

void LoginDlg::OnReg()
{
	RegDlg dlg(TRUE);
	dlg.Run(this->m_hWnd);

	SMessageBox(m_hWnd,_T("ע�����Ϣ"),_T("����"),MB_OK);
}
