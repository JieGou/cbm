#include "stdafx.h"
#include "MineDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

MineDialog::MineDialog(BOOL bModal) : AcadSouiDialog(_T("layout:mine"), bModal)
{
}

MineDialog::~MineDialog()
{
}

void MineDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT MineDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_NameEdit = FindChildByName2<SEdit>(L"name");
	m_CapacityEdit = FindChildByName2<SEdit>(L"capacity");
	m_RegionCombox = FindChildByName2<SComboBox>(L"region");
	m_BaseCombox = FindChildByName2<SComboBox>(L"base");
	m_ProvinceEdit = FindChildByName2<SEdit>(L"province");
	m_CityEdit = FindChildByName2<SEdit>(L"city");
	m_TopoGeoCombox = FindChildByName2<SComboBox>(L"topo_geo");
	m_GroundCondCheck = FindChildByName2<SCheckBox>(L"ground_cond");
	m_HydrGeoCombox = FindChildByName2<SComboBox>(L"hydr_geo");

	fillBaseCombox();

	//��ѯ�����û���id
	int account_id = DaoHelper::GetOnlineAccountId();
	//��ѯ�˻������Ŀ�
	MinePtr mine = FIND_ONE(Mine, FKEY(Account), Utils::int_to_cstring(account_id));
	//�������
	m_NameEdit->SetWindowText(mine->name);
	m_CapacityEdit->SetWindowText(Utils::double_to_cstring(mine->capacity));
	CString regionName = mine->region->get(FIELD(name));
	m_RegionCombox->SetCurSel(m_RegionCombox->FindString((LPCTSTR)regionName));
	m_ProvinceEdit->SetWindowText(mine->province);
	m_CityEdit->SetWindowText(mine->city);
	m_TopoGeoCombox->SetCurSel(mine->topo_geo-1);
	m_HydrGeoCombox->SetCurSel(mine->hydr_geo-1);
	m_GroundCondCheck->SetCheck(BOOL_2_INT(mine->ground_condition!=0));

	return 0;
}


void MineDialog::OnNextButtonClick()
{
}

void MineDialog::OnCancelButtonClick()
{
}

void MineDialog::OnRegionComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void MineDialog::OnBaseComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
	//���ҵ�ǰú̿���ض�Ӧ�����п���
	CString base = m_BaseCombox->GetLBText(pEvtOfCB->nCurSel);
	fillRegionCombox(base);
}

void MineDialog::OnSaveButtonClick()
{
}

void MineDialog::OnTopoGeoComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void MineDialog::OnHydrGeoComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void MineDialog::fillBaseCombox()
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

void MineDialog::fillRegionCombox(const CString& base)
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
