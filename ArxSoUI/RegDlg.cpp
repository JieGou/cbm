#include "stdafx.h"
#include "RegDlg.h"

using namespace SOUI;

RegDlg::RegDlg(BOOL bModal) 
	: AcadSouiDialog(_T("layout:reg"), bModal)
{
}

RegDlg::~RegDlg(void)
{
}

void RegDlg::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
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

LRESULT RegDlg::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	SetMsgHandled(FALSE);
	return 0;
}

void RegDlg::OnReg()
{
	SMessageBox(m_hWnd,_T("ע�����Ϣ"),_T("����"),MB_OK);
}
