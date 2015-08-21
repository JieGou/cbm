#include "stdafx.h"
#include "SampleManageDialog.h"
#include "TechModeDialog.h"
#include "TechnologyDialog.h"
#include "SComboxHelper.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

SampleManageDialog::SampleManageDialog(BOOL bModal) : AcadSouiDialog(_T("layout:sample_manage"), bModal)
{
}

SampleManageDialog::~SampleManageDialog()
{
}

void SampleManageDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT SampleManageDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);

	//do something
	m_RegionCombox = FindChildByName2<SComboBox>(L"region");
	m_TopoGeoCombox = FindChildByName2<SComboBox>(L"topo_geo");
	m_GroundCondCheck = FindChildByName2<SCheckBox>(L"ground_cond");
	m_HydrGeoCombox = FindChildByName2<SComboBox>(L"hydr_geo");
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
	m_MinableCheck = FindChildByName2<SCheckBox>(L"minable");

	//在OnInitDialog里直接调用SetCurSel无效!!!(原因未知)
	//m_RegionCombox->SetCurSel(0);
	EventCBSelChange evtCBSelChange(m_RegionCombox, 0);
	FireEvent(evtCBSelChange);

	return 0;
}


void SampleManageDialog::OnRegionComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;

	//初始化煤层信息字段
	initMineDatas();
	initCoalDatas();

	//得到示范矿区的虚拟矿井
	CString regionName = m_RegionCombox->GetLBText(pEvtOfCB->nCurSel);
	MinePtr mine = DaoHelper::GetSampleMine(regionName);
	if(mine == 0) return;

	//填充矿井开采数据
	m_TopoGeoCombox->SetCurSel(mine->topo_geo-1);
	m_HydrGeoCombox->SetCurSel(mine->hydr_geo-1);
	m_GroundCondCheck->SetCheck(mine->ground_condition!=0?TRUE:FALSE);

	//填充煤层列表数据
	fillCoalCombox();
}

void SampleManageDialog::OnTopoGeoComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void SampleManageDialog::OnHydrGeoComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void SampleManageDialog::OnDelButtonClick()
{
	int coal_id = SComboBoxHelper::GetCurSelItemID(m_CoalCombox);
	if(coal_id == 0) return;
	CoalPtr coal = FIND_BY_ID(Coal, coal_id);
	if(coal == 0) return;
	
	if(coal->remove())
	{
		//删除煤层列表中的当前项
		SComboBoxHelper::DeleteCurSel(m_CoalCombox);
		SComboBoxHelper::Select(m_CoalCombox, 0);
		if(m_CoalCombox->GetCount() == 0)
		{
			initCoalDatas();
		}
	}
}

void SampleManageDialog::OnRankComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void SampleManageDialog::OnConstComplexityComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void SampleManageDialog::OnAddCoalButtonClick()
{
	CString regionName = m_RegionCombox->GetLBText(m_RegionCombox->GetCurSel());

	CoalPtr coal(new Coal);
	//煤层关联到矿井
	coal->mine = DaoHelper::GetSampleMine(regionName);
	if(coal->mine == 0)
	{
		SMessageBox(GetSafeWnd(),_T("煤层关联到矿井失败!!!"),_T("友情提示"),MB_OK);
		return ;
	}
	coal->name = m_NumberEdit->GetWindowText(); // 名称(编号)
	if(coal->name.IsEmpty())
	{
		SMessageBox(GetSafeWnd(),_T("必须填写煤层编号!!!"),_T("友情提示"),MB_OK);
		return ;
	}
	else if(m_CoalCombox->FindString(coal->name) != -1)
	{
		CString msg;
		msg.Format(_T("煤层%s已存在!!!"), coal->name);
		SMessageBox(GetSafeWnd(),msg,_T("友情提示"),MB_OK);
		return ;
	}

	Utils::cstring_to_double((LPCTSTR)m_ThickEdit->GetWindowText(), coal->thick); // 煤厚
	coal->rank = m_RankCombox->GetCurSel() + 1; // 煤阶
	Utils::cstring_to_double((LPCTSTR)m_PressureEdit->GetWindowText(), coal->pressure); // 储层压力
	Utils::cstring_to_double((LPCTSTR)m_GasContentEdit->GetWindowText(), coal->gas_content); // 含气量
	Utils::cstring_to_double((LPCTSTR)m_GasPenetrationEdit->GetWindowText(), coal->gas_penetration); // 渗透率
	Utils::cstring_to_double((LPCTSTR)m_FValueEdit->GetWindowText(), coal->f_value); // f值
	coal->res_abundance = m_ResAbundanceCombox->GetCurSel() + 1; // 煤层气储量丰度
	coal->complexity = m_ConstComplexityCombox->GetCurSel() + 1; // 构造复杂程度
	Utils::cstring_to_double((LPCTSTR)m_MineIndexEdit->GetWindowText(), coal->mine_index); // 可采性指数
	Utils::cstring_to_double((LPCTSTR)m_VarCoeffEdit->GetWindowText(), coal->var_coeff); // 变异系数
	coal->stability = m_StabilityCombox->GetCurSel() + 1; // 煤层稳定性
	Utils::cstring_to_double((LPCTSTR)m_DipAngleEdit->GetWindowText(), coal->dip_angle); // 煤层倾角
	Utils::cstring_to_double((LPCTSTR)m_CavingZoneHeightEdit->GetWindowText(), coal->czh); // 冒落带高度
	coal->minable = m_MinableCheck->IsChecked();

	if(coal->save())
	{
		//添加到煤层列表中
		int nItem = SComboBoxHelper::Add(m_CoalCombox, coal->name, coal->getID());
		SComboBoxHelper::Select(m_CoalCombox, nItem);

		//打印消息
		CString msg;
		msg.Format(_T("增加煤层成功!"));
		msg.AppendFormat(_T("新煤层id:%d"), coal->getID());
		SMessageBox(GetSafeWnd(),msg,_T("友情提示"),MB_OK);
	}
}

void SampleManageDialog::OnResAbundanceComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void SampleManageDialog::OnStabilityComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void SampleManageDialog::OnCoalComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	int coal_id = SComboBoxHelper::GetCurSelItemID(m_CoalCombox);
	if(coal_id == 0) return;
	CoalPtr coal = FIND_BY_ID(Coal, coal_id);
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
	m_MinableCheck->SetCheck(BOOL_2_INT(coal->minable != 0));
}

void SampleManageDialog::OnSaveButtonClick()
{
	CString regionName = m_RegionCombox->GetLBText(m_RegionCombox->GetCurSel());
	MinePtr mine = DaoHelper::GetSampleMine(regionName);
	if(mine == 0) return;

	mine->topo_geo = m_TopoGeoCombox->GetCurSel() + 1;
	mine->hydr_geo = m_HydrGeoCombox->GetCurSel() + 1;
	mine->ground_condition = m_GroundCondCheck->IsChecked();
	if(!mine->save()) return;

	int coal_id = SComboBoxHelper::GetCurSelItemID(m_CoalCombox);
	if(coal_id == 0) return;
	CoalPtr coal = FIND_BY_ID(Coal, coal_id);
	if(coal == 0) return;

	Utils::cstring_to_double((LPCTSTR)m_ThickEdit->GetWindowText(), coal->thick); // 煤厚
	coal->rank = m_RankCombox->GetCurSel() + 1; // 煤阶
	Utils::cstring_to_double((LPCTSTR)m_PressureEdit->GetWindowText(), coal->pressure); // 储层压力
	Utils::cstring_to_double((LPCTSTR)m_GasContentEdit->GetWindowText(), coal->gas_content); // 含气量
	Utils::cstring_to_double((LPCTSTR)m_GasPenetrationEdit->GetWindowText(), coal->gas_penetration); // 渗透率
	Utils::cstring_to_double((LPCTSTR)m_FValueEdit->GetWindowText(), coal->f_value); // f值
	coal->res_abundance = m_ResAbundanceCombox->GetCurSel() + 1; // 煤层气储量丰度
	coal->complexity = m_ConstComplexityCombox->GetCurSel() + 1; // 构造复杂程度
	Utils::cstring_to_double((LPCTSTR)m_MineIndexEdit->GetWindowText(), coal->mine_index); // 可采性指数
	Utils::cstring_to_double((LPCTSTR)m_VarCoeffEdit->GetWindowText(), coal->var_coeff); // 变异系数
	coal->stability = m_StabilityCombox->GetCurSel() + 1; // 煤层稳定性
	Utils::cstring_to_double((LPCTSTR)m_DipAngleEdit->GetWindowText(), coal->dip_angle); // 煤层倾角
	Utils::cstring_to_double((LPCTSTR)m_CavingZoneHeightEdit->GetWindowText(), coal->czh); // 冒落带高度
	coal->minable = m_MinableCheck->IsChecked(); // 是否可采煤层
	if(!coal->save()) return;

	SMessageBox(GetSafeWnd(),_T("更新成功!"),_T("友情提示"),MB_OK);
}

void SampleManageDialog::OnTechModeButtonClick()
{
	CString regionName = m_RegionCombox->GetLBText(m_RegionCombox->GetCurSel());
	TechModeDialog dlg(TRUE);
	dlg.regionName = regionName; // 传入示范矿区的名称
	dlg.Run(GetSafeWnd());
}

void SampleManageDialog::OnTechnologyButtonClick()
{
	CString regionName = SComboBoxHelper::GetCurSelString(m_RegionCombox);
	TechnologyDialog dlg(TRUE);
	dlg.regionName = regionName; // 传入示范矿区的名称
	dlg.Run(GetSafeWnd());
}

void SampleManageDialog::fillCoalCombox()
{
	CString regionName = SComboBoxHelper::GetCurSelString(m_RegionCombox);
	MinePtr mine = DaoHelper::GetSampleMine(regionName);
	if(mine == 0) return;

	StringArray coal_names;
	IntArray coal_ids;
	DaoHelper::GetCoalIds(mine->name, coal_ids);
	DaoHelper::GetCoalNames(mine->name, coal_names);

	SComboBoxHelper::Clear(m_CoalCombox);
	SComboBoxHelper::Append(m_CoalCombox, coal_names, coal_ids);
	SComboBoxHelper::Select(m_CoalCombox, 0);
}

void SampleManageDialog::OnDestroyWindow()
{
	//删除所有的附加数据
	SComboBoxHelper::Clear(m_CoalCombox);
	AcadSouiDialog::OnDestroyWindow();
}

void SampleManageDialog::initMineDatas()
{
	m_HydrGeoCombox->SetCurSel(-1);
	m_TopoGeoCombox->SetCurSel(-1);
	m_GroundCondCheck->SetCheck(FALSE);
}

void SampleManageDialog::initCoalDatas()
{
	m_CoalCombox->SetCurSel(-1);
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
	m_MinableCheck->SetCheck(FALSE);
}
