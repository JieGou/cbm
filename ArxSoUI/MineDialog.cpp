#include "stdafx.h"
#include "MineDialog.h"
#include "CoalDialog.h"

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
	m_TopoGeoCombox = FindChildByName2<SComboBox>(L"topo_geo");
	m_ProvinceEdit = FindChildByName2<SEdit>(L"province");
	m_CityEdit = FindChildByName2<SEdit>(L"city");
	m_HydrGeoCombox = FindChildByName2<SComboBox>(L"hydr_geo");

	fillBaseCombox();

	return 0;
}


void MineDialog::OnNextButtonClick()
{
	CoalDialog dlg(TRUE);
	dlg.Run(this->m_hWnd);
}

void MineDialog::OnCancelButtonClick()
{
	AcadSouiDialog::OnCancel();
}

void MineDialog::OnRegionComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;

	// do something
}

void MineDialog::OnBaseComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;

	// do something
	//���ҵ�ǰú̿���ض�Ӧ�����п���
	CString base = m_BaseCombox->GetLBText(pEvtOfCB->nCurSel);
	fillRegionCombox(base);
}

void MineDialog::OnTopoGeoComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;

	// do something
}

void MineDialog::OnHydrGeoComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;

	// do something
}

void MineDialog::OnSaveButtonClick()
{
	CString name = m_NameEdit->GetWindowText();
	CString regionName = m_RegionCombox->GetWindowText();
	CString province = m_ProvinceEdit->GetWindowText();
	CString city = m_CityEdit->GetWindowText();

	MinePtr mine(new Mine);
	mine->name = name;
	mine->province = province;
	mine->city = city;

	mine->region = FIND_ONE(Region, FIELD(name), regionName);
	if(mine->save())
	{
		SMessageBox(m_hWnd,_T("¼������ݳɹ�!"),_T("������ʾ"),MB_OK);
		AcadSouiDialog::OnOK();
	}
	else
	{
		SMessageBox(m_hWnd,_T("¼�������ʧ��!"),_T("������ʾ"),MB_OK);
	}
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
