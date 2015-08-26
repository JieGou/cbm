#include "stdafx.h"
#include "WsGasFlowPredictAdjDialog.h"
#include "NameDialog.h"
#include "SouiListHelper.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

WsGasFlowPredictAdjDialog::WsGasFlowPredictAdjDialog(BOOL bModal) : AcadSouiDialog(_T("layout:ws_gas_flow_predict_adj"), bModal)
{
	ws_id = 0;
}

WsGasFlowPredictAdjDialog::~WsGasFlowPredictAdjDialog()
{
}

void WsGasFlowPredictAdjDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT WsGasFlowPredictAdjDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_GasW0Edit = FindChildByName2<SEdit>(L"gas_W0");
	m_ThickEdit = FindChildByName2<SEdit>(L"thick");
	m_GasEtaEdit = FindChildByName2<SEdit>(L"gas_eta");
	m_GasWc2Edit = FindChildByName2<SEdit>(L"gas_Wc2");
	m_AdjLayerCombox = FindChildByName2<SComboBox>(L"adj_layer");
	m_HEdit = FindChildByName2<SEdit>(L"h");
	m_HpEdit = FindChildByName2<SEdit>(L"hp");
	m_InCzCheck = FindChildByName2<SCheckBox>(L"in_cz");

	initAdjLayerDatas();
	fillAdjLayerCombox();

	return 0;
}


void WsGasFlowPredictAdjDialog::OnSaveButtonClick()
{
	AdjLayerPtr adj_layer = getCurSelAdjLayer();
	if(adj_layer == 0) return;

	//�����ڽ�������
	Utils::cstring_to_double((LPCTSTR)m_HEdit->GetWindowText(), adj_layer->h);
	Utils::cstring_to_double((LPCTSTR)m_HpEdit->GetWindowText(), adj_layer->hp);
	adj_layer->in_cz = m_InCzCheck->IsChecked();

	//����ú������
	if(adj_layer->coal == 0)
	{
		adj_layer->coal.reset(new Coal);
	}
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, adj_layer->coal);
	Utils::cstring_to_double((LPCTSTR)m_ThickEdit->GetWindowText(), coal->thick);
	Utils::cstring_to_double((LPCTSTR)m_GasEtaEdit->GetWindowText(), coal->gas_eta);
	Utils::cstring_to_double((LPCTSTR)m_GasW0Edit->GetWindowText(), coal->gas_w0);
	Utils::cstring_to_double((LPCTSTR)m_GasWc2Edit->GetWindowText(), coal->gas_wc2);

	//���浽���ݿ�
	if(!adj_layer->save())
	{
		SMessageBox(GetSafeHwnd(),_T("�����ڽ�������ʧ��"),_T("������ʾ"),MB_OK);
		return;
	}
	if(!coal->save())
	{
		SMessageBox(GetSafeHwnd(),_T("�����ڽ����ú������ʧ��"),_T("������ʾ"),MB_OK);
	}
	SMessageBox(GetSafeHwnd(),_T("�������ݳɹ�!"),_T("������ʾ"),MB_OK);
}

void WsGasFlowPredictAdjDialog::OnAdjLayerComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void WsGasFlowPredictAdjDialog::OnDelAdjLayerButtonClick()
{
	AdjLayerPtr adj_layer = getCurSelAdjLayer();
	if(adj_layer == 0) return;

	//�����ݿ���ɾ��
	if(adj_layer->remove())
	{
		//���ڽ����б���ɾ��
		SComboBoxHelper::DeleteCurSel(m_AdjLayerCombox);
		SComboBoxHelper::Select(m_AdjLayerCombox, 0);
		if(m_AdjLayerCombox->GetCount() == 0)
		{
			initAdjLayerDatas();
		}
	}
}

void WsGasFlowPredictAdjDialog::OnAddAdjLayerButtonClick()
{
	NameDialog dlg(TRUE);
	dlg.SetWindowTitle(_T("�����ڽ���"));
	if(IDOK != dlg.Run(GetSafeHwnd())) return;

	CString name = dlg.name;
	if(name.IsEmpty()) return;
	if(m_AdjLayerCombox->FindString(name) != -1)
	{
		CString msg;
		msg.Format(_T("�ڽ���%s�Ѵ���!"), name);
		SMessageBox(GetSafeHwnd(),msg,_T("������ʾ"),MB_OK);
	}
	else
	{
		//�ύ�����ݿ�
		AdjLayerPtr adj_layer(new AdjLayer);
		adj_layer->name = name;
		adj_layer->work_surf = FIND_BY_ID(WorkSurf, ws_id);
		if(adj_layer->save())
		{
			//���뵽�ڽ����б�
			int nItem = SComboBoxHelper::Add(m_AdjLayerCombox, adj_layer->name, adj_layer->getID());
			SComboBoxHelper::Select(m_AdjLayerCombox, nItem);
		}
	}
}

void WsGasFlowPredictAdjDialog::OnEtaCaclButtonClick()
{
	SMessageBox(GetSafeHwnd(),_T("����Զ����������"),_T("������ʾ"),MB_OK);
	double eta = 0;
	
	//���µ�����
	m_GasEtaEdit->SetWindowText(Utils::double_to_cstring(eta));	
}

void WsGasFlowPredictAdjDialog::OnDestroyWindow()
{
	//ɾ�����еĸ�������
	SComboBoxHelper::Clear(m_AdjLayerCombox);
	AcadSouiDialog::OnDestroyWindow();
}

void WsGasFlowPredictAdjDialog::initAdjLayerDatas()
{
	m_GasW0Edit->SetWindowText(NULL);
	m_ThickEdit->SetWindowText(NULL);
	m_GasEtaEdit->SetWindowText(NULL);
	m_GasWc2Edit->SetWindowText(NULL);
	//m_AdjLayerCombox->SetCurSel(-1);
	m_HEdit->SetWindowText(NULL);
	m_HpEdit->SetWindowText(NULL);
	m_InCzCheck->SetWindowText(NULL);
}

void WsGasFlowPredictAdjDialog::fillAdjLayerCombox()
{
	SComboBoxHelper::Clear(m_AdjLayerCombox);

	//����id���ҹ�����
	//����id���һزɹ�����
	WorkSurfPtr work_surf = FIND_BY_ID(WorkSurf, ws_id);
	if(work_surf == 0) return;

	//�������е��ڽ���
	RecordPtrListPtr lists = FIND_MANY(AdjLayer, FKEY(WorkSurf), work_surf->getStringID());
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		AdjLayerPtr adj_layer = DYNAMIC_POINTER_CAST(AdjLayer, lists->at(i));
		if(adj_layer == 0) continue;
		//CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, adj_layer->coal);
		//if(coal == 0) continue;

		//�����ڽ���
		SComboBoxHelper::Add(m_AdjLayerCombox, adj_layer->name, adj_layer->getID());
	}
	SComboBoxHelper::Select(m_AdjLayerCombox, 0);
}

AdjLayerPtr WsGasFlowPredictAdjDialog::getCurSelAdjLayer()
{
	int adj_layer_id = SComboBoxHelper::GetCurSelItemID(m_AdjLayerCombox);
	if(adj_layer_id == 0) return AdjLayerPtr();
	return FIND_BY_ID(AdjLayer, adj_layer_id);
}