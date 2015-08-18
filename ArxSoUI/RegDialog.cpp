#include "stdafx.h"
#include "RegDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

RegDialog::RegDialog(BOOL bModal) : AcadSouiDialog(_T("layout:reg"), bModal)
{
}

RegDialog::~RegDialog()
{
}

void RegDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT RegDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);

	m_NameEdit = FindChildByName2<SEdit>(L"name");
	m_ProvinceEdit = FindChildByName2<SEdit>(L"province");
	m_CoalCountEdit = FindChildByName2<SEdit>(L"coal_count");
	m_CityEdit = FindChildByName2<SEdit>(L"city");
	m_CoalNumsEdit = FindChildByName2<SEdit>(L"coal_nums");
	m_UsernameEdit = FindChildByName2<SEdit>(L"username");
	m_PasswordEdit = FindChildByName2<SEdit>(L"password");
	m_BaseCombox = FindChildByName2<SComboBox>(L"base");
	m_RegionCombox = FindChildByName2<SComboBox>(L"region");

	fillBaseCombox();

	return 0;
}

void RegDialog::OnRegButtonClick()
{
	CString user = m_UsernameEdit->GetWindowText();
	CString pwd = m_PasswordEdit->GetWindowText();
	CString name = m_NameEdit->GetWindowText();
	CString region = m_RegionCombox->GetWindowText();
	CString province = m_ProvinceEdit->GetWindowText();
	CString city = m_CityEdit->GetWindowText();
	CString coal_nums = m_CoalNumsEdit->GetWindowText();
	CString coal_count = m_CoalCountEdit->GetWindowText();

	//ע����˻�
	int ret = DaoHelper::VerifyMineAccount(user, pwd);
	if(ret != 0)
	{
		SMessageBox(m_hWnd,_T("�û����Ѵ���!"),_T("������ʾ"),MB_OK);
	}
	else
	{
		AccountPtr account(new Account);
		account->username = user;
		account->password = pwd;

		MinePtr mine(new Mine);
		mine->name = name;
		mine->province = province;
		mine->city = city;

		QueryPtr query(Query::from<Region>());
		mine->region = query->where(FIELD(name), region)->find_one<Region>();
		//���ӵ����ݿⲢ���������е�idֵ
		if(account->save() && mine->save())
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

void RegDialog::OnBaseComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	//���ҵ�ǰú̿���ض�Ӧ�����п���
	CString base = m_BaseCombox->GetLBText(pEvtOfCB->nCurSel);
	fillRegionCombox(base);
}

void RegDialog::OnRegionComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;
}

void RegDialog::fillBaseCombox()
{
	//�������е�ú̿����
	StringArray bases;
	DaoHelper::GetAllMineBases(bases);

	//������е�ú̿�����б�
	m_BaseCombox->ResetContent();
	for(int i=0;i<bases.size();i++)
	{
		m_BaseCombox->InsertItem(i, bases[i], 0, 0);
	}
	//SetCurSel�ᴥ��EVT_CB_SELCHANGE��Ϣ
	m_BaseCombox->SetCurSel(0);
}

void RegDialog::fillRegionCombox(const CString& base)
{
	StringArray regions;
	DaoHelper::GetAllMineRegions(base, regions);

	//��տ��������б�
	m_RegionCombox->ResetContent();
	for(int i=0;i<regions.size();i++)
	{
		m_RegionCombox->InsertItem(i, regions[i], 0, 0);
	}
	m_RegionCombox->SetCurSel(0);      
}
