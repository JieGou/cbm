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
	CString regionName = m_RegionCombox->GetWindowText();
	CString province = m_ProvinceEdit->GetWindowText();
	CString city = m_CityEdit->GetWindowText();
	//CString coal_nums = m_CoalNumsEdit->GetWindowText();
	//�ֽ�ú����(�ո����)
	StringArray coal_nums;
	Utils::cstring_explode((LPCTSTR)m_CoalNumsEdit->GetWindowText(), _T(" "), coal_nums);

	//ע����˻�
	int ret = DaoHelper::VerifyMineAccount(user, pwd);
	if(ret != 0)
	{
		SMessageBox(m_hWnd,_T("�û����Ѵ���,��ʹ����������!"),_T("������ʾ"),MB_OK);
	}
	else
	{
		//�½��˻�
		AccountPtr account(new Account);
		account->username = user;
		account->password = pwd;

		//�½���
		MinePtr mine(new Mine);
		mine->name = name;
		mine->province = province;
		mine->city = city;

		//�󾮹����˻�
		mine->account = account;

		//�󾮹�������
		mine->region = FIND_ONE(Region, FIELD(name), regionName);
		//���ӵ����ݿⲢ���������е�idֵ
		if(account->save() && mine->save())
		{
			//�½�ú��
			for(int i=0;i<coal_nums.size();i++)
			{
				CoalPtr coal(new Coal);
				//ú���������
				coal->mine = mine;
				//����ú������
				coal->name = coal_nums[i];
				//���浽���ݿ�
				coal->save();
			}

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
	clearBaseCombox();
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
	clearRegionCombox();
	for(int i=0;i<regions.size();i++)
	{
		m_RegionCombox->InsertItem(i, regions[i], 0, 0);
	}
	m_RegionCombox->SetCurSel(0);      
}

void RegDialog::clearBaseCombox()
{
	m_BaseCombox->ResetContent();
}

void RegDialog::clearRegionCombox()
{
	m_RegionCombox->ResetContent();
}