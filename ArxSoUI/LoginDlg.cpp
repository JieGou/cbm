#include "stdafx.h"
#include "LoginDlg.h"
#include "RegDlg.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>

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
    CString user = FindChildByName2<SEdit>(L"username")->GetWindowText();
	CString pwd = FindChildByName2<SEdit>(L"password")->GetWindowText();
	int ret = DaoHelper::VerifyMineAccount(user, pwd);
	if(user.IsEmpty())
	{
		SMessageBox(m_hWnd,_T("�������û���!"),_T("������ʾ"),MB_OK);
	}
	else if(pwd.IsEmpty())
	{
		SMessageBox(m_hWnd,_T("����������!"),_T("������ʾ"),MB_OK);
	}
	else if(ret == 0)
	{
		CString msg;
		msg.Format(_T("�û���:%s������,��ע��!"), user);
		SMessageBox(m_hWnd,msg,_T("������ʾ"),MB_OK);
	}
	else if(ret == 1)
	{
		SMessageBox(m_hWnd,_T("��������ȷ������!"),_T("������ʾ"),MB_OK);
	}
	else
	{
		SMessageBox(m_hWnd,_T("��¼�ɹ�!"),_T("������ʾ"),MB_OK);
		AcadSouiDialog::OnOK();
	}

    //pEdit->SetWindowText(_T("dlj"));
}

void LoginDlg::OnReg()
{
	RegDlg dlg(TRUE);
	dlg.Run(this->m_hWnd);
	//SMessageBox(m_hWnd,_T("ע�����Ϣ"),_T("����"),MB_OK);
}
