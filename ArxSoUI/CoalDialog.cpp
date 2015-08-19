#include "stdafx.h"
#include "CoalDialog.h"
#include "DecisionDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

struct ItemData
{
	int id;
	int nItem;
};

CoalDialog::CoalDialog(BOOL bModal) : AcadSouiDialog(_T("layout:coal"), bModal)
{
}

CoalDialog::~CoalDialog()
{
}

void CoalDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT CoalDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_NumberEdit = FindChildByName2<SEdit>(L"number");
	m_FValueEdit = FindChildByName2<SEdit>(L"f_value");
	m_ThickEdit = FindChildByName2<SEdit>(L"thick");
	m_RankCombox = FindChildByName2<SComboBox>(L"rank");
	m_PressureEdit = FindChildByName2<SEdit>(L"pressure");
	m_GasContentEdit = FindChildByName2<SEdit>(L"gas_content");
	m_GasPenetrationEdit = FindChildByName2<SEdit>(L"gas_penetration");
	m_ConstComplexityCombox = FindChildByName2<SComboBox>(L"const_complexity");
	m_VarCoeffEdit = FindChildByName2<SEdit>(L"var_coeff");
	m_DipAngleEdit = FindChildByName2<SEdit>(L"dip_angle");
	m_CavingZoneHeightEdit = FindChildByName2<SEdit>(L"caving_zone_height");
	m_ResAbundanceCombox = FindChildByName2<SComboBox>(L"res_abundance");
	m_LayerGapEdit = FindChildByName2<SEdit>(L"layer_gap");
	m_InfluenceFactorEdit = FindChildByName2<SEdit>(L"influence_factor");
	m_MineIndexEdit = FindChildByName2<SEdit>(L"mine_index");
	m_StabilityCombox = FindChildByName2<SComboBox>(L"stability");
	m_CoalCombox = FindChildByName2<SComboBox>(L"coal");

	initCoalDatas();
	fillCoalList();
	return 0;
}


void CoalDialog::OnNextButtonClick()
{
	AcadSouiDialog::OnOK();
	DecisionDialog* dlg = new DecisionDialog(FALSE);
	dlg->Run(acedGetAcadFrame()->GetSafeHwnd());
}

void CoalDialog::OnCancelButtonClick()
{
	AcadSouiDialog::OnCancel();
}

void CoalDialog::OnSaveButtonClick()
{
	int nCurSel = m_CoalCombox->GetCurSel();
	ItemData* pData = (ItemData*)m_CoalCombox->GetItemData(nCurSel);
	if(pData == 0) return;
	CoalPtr coal = FIND_BY_ID(Coal, pData->id);
	if(coal == 0) return;

	Utils::cstring_to_double((LPCTSTR)m_ThickEdit->GetWindowText(), coal->thick); // ú��
	coal->rank = m_RankCombox->GetCurSel() + 1; // ú��
	Utils::cstring_to_double((LPCTSTR)m_PressureEdit->GetWindowText(), coal->pressure); // ����ѹ��
	Utils::cstring_to_double((LPCTSTR)m_GasContentEdit->GetWindowText(), coal->gas_content); // ������
	Utils::cstring_to_double((LPCTSTR)m_GasPenetrationEdit->GetWindowText(), coal->gas_penetration); // ��͸��
	Utils::cstring_to_double((LPCTSTR)m_FValueEdit->GetWindowText(), coal->f_value); // fֵ
	coal->res_abundance = m_ResAbundanceCombox->GetCurSel() + 1; // ú�����������
	coal->complexity = m_ConstComplexityCombox->GetCurSel() + 1; // ���츴�ӳ̶�
	Utils::cstring_to_double((LPCTSTR)m_MineIndexEdit->GetWindowText(), coal->mine_index); // �ɲ���ָ��
	Utils::cstring_to_double((LPCTSTR)m_VarCoeffEdit->GetWindowText(), coal->var_coeff); // ����ϵ��
	coal->stability = m_StabilityCombox->GetCurSel() + 1; // ú���ȶ���
	Utils::cstring_to_double((LPCTSTR)m_DipAngleEdit->GetWindowText(), coal->dip_angle); // ú�����
	Utils::cstring_to_double((LPCTSTR)m_CavingZoneHeightEdit->GetWindowText(), coal->czh); // ð����߶�
	if(!coal->save()) return;

	SMessageBox(GetSafeWnd(),_T("���³ɹ�!"),_T("������ʾ"),MB_OK);
}

void CoalDialog::OnDelButtonClick()
{
	int nCurSel = m_CoalCombox->GetCurSel();
	ItemData* pData = (ItemData*)m_CoalCombox->GetItemData(nCurSel);
	if(pData == 0) return;
	CoalPtr coal = FIND_BY_ID(Coal, pData->id);
	if(coal == 0) return;

	if(coal->remove())
	{
		//ɾ��ú���б��еĵ�ǰ��
		delete pData;
		m_CoalCombox->DeleteString(nCurSel);

		if(m_CoalCombox->GetCount() > 0)
		{
			m_CoalCombox->SetCurSel(0);
		}
		else
		{
			initCoalDatas();
		}
	}
}

void CoalDialog::OnRankComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void CoalDialog::OnConstComplexityComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void CoalDialog::OnAddCoalButtonClick()
{
	CoalPtr coal(new Coal);
	//ú���������
	coal->mine = DaoHelper::GetOnlineMine();
	if(coal->mine == 0)
	{
		SMessageBox(GetSafeWnd(),_T("ú���������ʧ��!!!"),_T("������ʾ"),MB_OK);
		return ;
	}
	coal->name = m_NumberEdit->GetWindowText(); // ����(���)
	if(coal->name.IsEmpty())
	{
		SMessageBox(GetSafeWnd(),_T("������дú����!!!"),_T("������ʾ"),MB_OK);
		return ;
	}
	else if(isCoalExist(coal->name))
	{
		CString msg;
		msg.Format(_T("ú��%s�Ѵ���!!!"), coal->name);
		SMessageBox(GetSafeWnd(),msg,_T("������ʾ"),MB_OK);
		return ;
	}

	Utils::cstring_to_double((LPCTSTR)m_ThickEdit->GetWindowText(), coal->thick); // ú��
	coal->rank = m_RankCombox->GetCurSel() + 1; // ú��
	Utils::cstring_to_double((LPCTSTR)m_PressureEdit->GetWindowText(), coal->pressure); // ����ѹ��
	Utils::cstring_to_double((LPCTSTR)m_GasContentEdit->GetWindowText(), coal->gas_content); // ������
	Utils::cstring_to_double((LPCTSTR)m_GasPenetrationEdit->GetWindowText(), coal->gas_penetration); // ��͸��
	Utils::cstring_to_double((LPCTSTR)m_FValueEdit->GetWindowText(), coal->f_value); // fֵ
	coal->res_abundance = m_ResAbundanceCombox->GetCurSel() + 1; // ú�����������
	coal->complexity = m_ConstComplexityCombox->GetCurSel() + 1; // ���츴�ӳ̶�
	Utils::cstring_to_double((LPCTSTR)m_MineIndexEdit->GetWindowText(), coal->mine_index); // �ɲ���ָ��
	Utils::cstring_to_double((LPCTSTR)m_VarCoeffEdit->GetWindowText(), coal->var_coeff); // ����ϵ��
	coal->stability = m_StabilityCombox->GetCurSel() + 1; // ú���ȶ���
	Utils::cstring_to_double((LPCTSTR)m_DipAngleEdit->GetWindowText(), coal->dip_angle); // ú�����
	Utils::cstring_to_double((LPCTSTR)m_CavingZoneHeightEdit->GetWindowText(), coal->czh); // ð����߶�

	if(coal->save())
	{
		//��ӵ�ú���б���
		int nIndex = m_CoalCombox->GetCount();
		addCoalToListBox(coal->name, coal->getID(), nIndex);
		//�л���ǰú��
		m_CoalCombox->SetCurSel(nIndex);

		//��ӡ��Ϣ
		CString msg;
		msg.Format(_T("����ú��ɹ�!"));
		msg.AppendFormat(_T("��ú��id:%d"), coal->getID());
		SMessageBox(GetSafeWnd(),msg,_T("������ʾ"),MB_OK);
	}
}

void CoalDialog::OnResAbundanceComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void CoalDialog::OnStabilityComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void CoalDialog::OnCoalComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
	ItemData* pData = (ItemData*)m_CoalCombox->GetItemData(nCurSel);
	if(pData == 0) return;
	CoalPtr coal = FIND_BY_ID(Coal, pData->id);
	if(coal == 0) return;

	m_NumberEdit->SetWindowText(coal->name);
	m_ThickEdit->SetWindowText(Utils::double_to_cstring(coal->thick));
	m_RankCombox->SetCurSel(coal->rank-1);
	m_PressureEdit->SetWindowText(Utils::double_to_cstring(coal->pressure));
	m_GasContentEdit->SetWindowText(Utils::double_to_cstring(coal->gas_content));
	m_GasPenetrationEdit->SetWindowText(Utils::double_to_cstring(coal->gas_penetration));
	m_FValueEdit->SetWindowText(Utils::double_to_cstring(coal->f_value));
	m_ResAbundanceCombox->SetCurSel(coal->res_abundance-1);
	m_ConstComplexityCombox->SetCurSel(coal->complexity-1);
	m_MineIndexEdit->SetWindowText(Utils::double_to_cstring(coal->mine_index));
	m_VarCoeffEdit->SetWindowText(Utils::double_to_cstring(coal->var_coeff));
	m_StabilityCombox->SetCurSel(coal->stability-1);
	m_DipAngleEdit->SetWindowText(Utils::double_to_cstring(coal->dip_angle));
	m_CavingZoneHeightEdit->SetWindowText(Utils::double_to_cstring(coal->czh));
}

void CoalDialog::OnDestroyWindow()
{
	//ɾ�����еĸ�������
	int n = m_CoalCombox->GetCount();
	for(int i=0;i<n;i++)
	{
		ItemData* pData = (ItemData*)m_CoalCombox->GetItemData(i);
		delete pData;
	}
	AcadSouiDialog::OnDestroyWindow();
}

void CoalDialog::fillCoalList()
{
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	StringArray coal_names;
	IntArray coal_ids;
	DaoHelper::GetCoalIds(mine->name, coal_ids);
	DaoHelper::GetCoalNames(mine->name, coal_names);

	m_CoalCombox->ResetContent();
	for(int i=0;i<coal_names.size();i++)
	{
		addCoalToListBox(coal_names[i], coal_ids[i], i);
	}
	m_CoalCombox->SetCurSel(0);
}

void CoalDialog::addCoalToListBox(const CString& name, int id, int i)
{
	m_CoalCombox->InsertItem(i, name, 0, 0);
	//��������
	ItemData* pData = new ItemData;
	pData->id = id;
	pData->nItem = i;
	m_CoalCombox->SetItemData(i, (LPARAM)pData);
}

bool CoalDialog::isCoalExist(const CString& name)
{
	return m_CoalCombox->FindString(name)!=-1;
}

void CoalDialog::initCoalDatas()
{
	m_CoalCombox->ResetContent();
	m_NumberEdit->SetWindowText(_T(""));
	m_ThickEdit->SetWindowText(_T(""));
	m_RankCombox->SetCurSel(-1);
	m_PressureEdit->SetWindowText(_T(""));
	m_GasContentEdit->SetWindowText(_T(""));
	m_GasPenetrationEdit->SetWindowText(_T(""));
	m_FValueEdit->SetWindowText(_T(""));
	m_ResAbundanceCombox->SetCurSel(-1);
	m_ConstComplexityCombox->SetCurSel(-1);
	m_MineIndexEdit->SetWindowText(_T(""));
	m_VarCoeffEdit->SetWindowText(_T(""));
	m_StabilityCombox->SetCurSel(-1);
	m_DipAngleEdit->SetWindowText(_T(""));
	m_CavingZoneHeightEdit->SetWindowText(_T(""));
}