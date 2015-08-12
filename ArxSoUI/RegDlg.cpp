#include "stdafx.h"
#include "RegDlg.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

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
	SComboBox* baseCombox = FindChildByName2<SComboBox>(L"base");

	//�������е�ú̿����
	StringArray bases;
	DaoHelper::GetAllMineBases(bases);

	//������е�ú̿�����б�
	baseCombox->ResetContent();
	for(int i=0;i<bases.size();i++)
	{
		baseCombox->InsertItem(i, bases[i], 0, 0);
	}
	//SetCurSel�ᴥ��EVT_CB_SELCHANGE��Ϣ
	baseCombox->SetCurSel(0);

	SetMsgHandled(FALSE);
	return 0;
}

void RegDlg::OnReg()
{
	CString user = FindChildByName2<SEdit>(L"username")->GetWindowText();
	CString pwd = FindChildByName2<SEdit>(L"password")->GetWindowText();
	CString name = FindChildByName2<SEdit>(L"name")->GetWindowText();
	CString region = FindChildByName2<SComboBox>(L"region")->GetWindowText();
	//CString base = FindChildByName2<SComboBox>(L"base")->GetWindowText();
	CString province = FindChildByName2<SEdit>(L"province")->GetWindowText();
	CString city = FindChildByName2<SEdit>(L"city")->GetWindowText();
	CString coal_nums = FindChildByName2<SEdit>(L"coal_nums")->GetWindowText();
	CString coal_count = FindChildByName2<SEdit>(L"coal_count")->GetWindowText();

	//ע����˻�
	int ret = DaoHelper::VerifyMineAccount(user, pwd);
	if(ret != 0)
	{
		SMessageBox(m_hWnd,_T("�û����Ѵ���!"),_T("������ʾ"),MB_OK);
	}
	else
	{
		MinePtr mine(new Mine);
		mine->username = user;
		mine->password = pwd;
		mine->name = name;
		mine->province = province;
		mine->city = city;

		QueryPtr query(Query::from<Region>());
		mine->region = query->where(FIELD(name), region)->find_one<Region>();
		//���ӵ����ݿⲢ���������е�idֵ
		if(mine->save())
		{
			SMessageBox(m_hWnd,_T("ע����˻��ɹ�!"),_T("������ʾ"),MB_OK);
			AcadSouiDialog::OnOK();
		}
		else
		{
			SMessageBox(m_hWnd,_T("ע����˻�ʧ��!"),_T("������ʾ"),MB_OK);
		}
	}
}

void RegDlg::OnSelChanged( EventArgs *pEvt )
{
	SComboBox* baseCombox = FindChildByName2<SComboBox>(L"base");
	SComboBox* regionCombox = FindChildByName2<SComboBox>(L"region");
	if(baseCombox == 0 || regionCombox == 0) return;

	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB != 0)
	{
		//���ҵ�ǰú̿���ض�Ӧ�����п���
		StringArray regions;
		CString base = baseCombox->GetLBText(pEvtOfCB->nCurSel);
		DaoHelper::GetAllMineRegions(base, regions);

		//��տ��������б�
		regionCombox->ResetContent();
		for(int i=0;i<regions.size();i++)
		{
			regionCombox->InsertItem(i, regions[i], 0, 0);
		}
		regionCombox->SetCurSel(0);      
	}
}