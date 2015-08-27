#include "stdafx.h"
#include "WsGasFlowPredictDialog.h"
#include "WsGasFlowPredictWorkDialog.h"
#include "WsGasFlowPredictAdjDialog.h"
#include "SouiListHelper.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

WsGasFlowPredictDialog::WsGasFlowPredictDialog(BOOL bModal) : AcadSouiDialog(_T("layout:ws_gas_flow_predict"), bModal)
{
	mine_id = 0;
}

WsGasFlowPredictDialog::~WsGasFlowPredictDialog()
{
}

void WsGasFlowPredictDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT WsGasFlowPredictDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_Qr1Edit = FindChildByName2<SEdit>(L"qr1");
	m_Qr2Edit = FindChildByName2<SEdit>(L"qr2");
	m_QrEdit = FindChildByName2<SEdit>(L"qr");
	m_MethodThinRadio = FindChildByName2<SRadioBox>(L"method_thin");
	m_MethodThickRadio = FindChildByName2<SRadioBox>(L"method_thick");
	m_WsCombox = FindChildByName2<SComboBox>(L"ws");
	m_ThickEdit = FindChildByName2<SEdit>(L"thick");
	m_HwEdit = FindChildByName2<SEdit>(L"hw");
	m_LEdit = FindChildByName2<SEdit>(L"L");
	m_WsThickEdit = FindChildByName2<SEdit>(L"ws_thick");

	initWsDatas();
	fillWsCombox();

	return 0;
}


void WsGasFlowPredictDialog::OnQr1CaclButtonClick()
{
	//��ʾ�Ի���
	WsGasFlowPredictWorkDialog dlg(TRUE);
	dlg.Run(GetSafeHwnd());

	int ws_id = SComboBoxHelper::GetCurSelItemID(m_WsCombox);
	if(ws_id == 0) return;

	//����id���һزɹ�����
	WorkSurfPtr work_surf = FIND_BY_ID(WorkSurf, ws_id);
	if(work_surf == 0) return;
	//������->����->ú��
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, work_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal == 0) return;

	double K1 = work_surf->k1;
	double K2 = work_surf->k1;
	double K3 = work_surf->k1;
	double kf = work_surf->kf;
	//���ɲ���(????�ֲ���ο���???)
	double m = coal->thick;
	Utils::cstring_to_double((LPCTSTR)m_WsThickEdit->GetWindowText(), m);
	//������ɸ�
	double M = coal->hw;
	double W0 = coal->gas_w0;
	double Wc = coal->gas_wc2;
	//���㿪�ɲ������˹ӿ����q1
	double q1 = 0;
	if(m_MethodThinRadio->IsChecked())
	{
		q1 = K1*K2*K3*(W0-Wc)*m/M;
	}
	else
	{
		q1 = K1*K2*K3*(W0-Wc)*kf;
	}
	//���µ�����
	m_Qr1Edit->SetWindowText(Utils::double_to_cstring(q1));
}

void WsGasFlowPredictDialog::OnQr2CaclButtonClick()
{
	//��ʾ�Ի���
	WsGasFlowPredictAdjDialog dlg(TRUE);
	dlg.Run(GetSafeHwnd());

	int ws_id = SComboBoxHelper::GetCurSelItemID(m_WsCombox);
	if(ws_id == 0) return;

	//����id���һزɹ�����
	WorkSurfPtr work_surf = FIND_BY_ID(WorkSurf, ws_id);
	if(work_surf == 0) return;
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, work_surf->work_area);
	if(work_area == 0) return;
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal == 0) return;

	//�������е��ڽ���
	RecordPtrListPtr lists = FIND_MANY(AdjLayer, FKEY(WorkSurf), work_surf->getStringID());
	if(lists == 0) return;

	double S = 0;
	for(int i=0;i<lists->size();i++)
	{
		AdjLayerPtr adj_layer = DYNAMIC_POINTER_CAST(AdjLayer, lists->at(i));
		if(adj_layer == 0) continue;
		CoalPtr adj_coal = DYNAMIC_POINTER_CAST(Coal, adj_layer->coal);
		if(adj_coal == 0) continue;

		double W0 = adj_coal->gas_w0;
		double Wc = adj_coal->gas_wc2;
		double m = adj_coal->thick;
		double eta = adj_coal->gas_eta;

		S += (W0-Wc)*m*eta;
	}
	double M = coal->hw;
	double q2 = S/M;

	//���µ�����
	m_Qr2Edit->SetWindowText(Utils::double_to_cstring(q2));
}

void WsGasFlowPredictDialog::OnSaveButtonClick()
{
	int ws_id = SComboBoxHelper::GetCurSelItemID(m_WsCombox);
	if(ws_id == 0) return;

	//����id���һزɹ�����
	WorkSurfPtr work_surf = FIND_BY_ID(WorkSurf, ws_id);
	if(work_surf == 0) return;
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, work_surf->work_area);
	if(work_area == 0) return;
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal == 0) return;

	work_surf->layerable = BOOL_2_INT(m_MethodThickRadio->IsChecked() == 0);
	Utils::cstring_to_double((LPCTSTR)m_LEdit->GetWindowText(), work_surf->l1); // ���򳤶�
	Utils::cstring_to_double((LPCTSTR)m_HwEdit->GetWindowText(), coal->hw);
	Utils::cstring_to_double((LPCTSTR)m_Qr1Edit->GetWindowText(), work_surf->qr1);
	Utils::cstring_to_double((LPCTSTR)m_Qr2Edit->GetWindowText(), work_surf->qr2);
	Utils::cstring_to_double((LPCTSTR)m_QrEdit->GetWindowText(), work_surf->qr);
	if(work_surf->save())
	{
		SMessageBox(GetSafeHwnd(),_T("�������ݳɹ�!"),_T("������ʾ"),MB_OK);
	}
	else
	{
		SMessageBox(GetSafeHwnd(),_T("��������ʧ��!"),_T("������ʾ"),MB_OK);
	}
}

void WsGasFlowPredictDialog::OnWsComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
	initWsDatas();
	int ws_id = SComboBoxHelper::GetCurSelItemID(m_WsCombox);
	if(ws_id == 0) return;

	//����id���һزɹ�����
	WorkSurfPtr work_surf = FIND_BY_ID(WorkSurf, ws_id);
	if(work_surf == 0) return;

	//���زɹ����������
	//�Ƿ�ֲ㿪��
	m_MethodThickRadio->SetCheck(BOOL_2_INT(work_surf->layerable == 0));
	m_MethodThickRadio->SetCheck(BOOL_2_INT(work_surf->layerable != 0));
	//�����泤�ȺͲɸ�
	m_LEdit->SetWindowText(Utils::double_to_cstring(work_surf->l1)); // ���򳤶�
	//m_HwEdit->SetWindowText(Utils::double_to_cstring(coal->hw));
	//��������˹ӿ��������
	m_Qr1Edit->SetWindowText(Utils::double_to_cstring(work_surf->qr1));
	m_Qr2Edit->SetWindowText(Utils::double_to_cstring(work_surf->qr2));
	m_QrEdit->SetWindowText(Utils::double_to_cstring(work_surf->qr));

	//ú����
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, work_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal != 0)
	{
		m_HwEdit->SetWindowText(Utils::double_to_cstring(coal->hw));
		m_ThickEdit->SetWindowText(Utils::double_to_cstring(coal->thick));
		m_WsThickEdit->SetWindowText(Utils::double_to_cstring(coal->thick));
	}
}

void WsGasFlowPredictDialog::OnQrCaclButtonClick()
{
}

void WsGasFlowPredictDialog::OnRadioGroup1Switch(int nID)
{
	if(!isLayoutInited()) return;

	m_Qr2Edit->EnableWindow(nID-100 != 0);
	SWindow* btn = FindChildByName(L"qr2_cacl");
	if(btn != 0)
	{
		btn->EnableWindow(nID-100 != 0);
	}
}


void WsGasFlowPredictDialog::OnDestroyWindow()
{
	//ɾ�����еĸ�������
	SComboBoxHelper::Clear(m_WsCombox);
	AcadSouiDialog::OnDestroyWindow();
}

void WsGasFlowPredictDialog::initWsDatas()
{
	m_Qr1Edit->SetWindowText(NULL);
	m_Qr2Edit->SetWindowText(NULL);
	m_QrEdit->SetWindowText(NULL);
	m_MethodThinRadio->SetCheck(TRUE);
	m_MethodThickRadio->SetCheck(FALSE);
	//m_WsCombox->SetCurSel(-1);
	m_ThickEdit->SetWindowText(NULL);
	m_HwEdit->SetWindowText(NULL);
	m_LEdit->SetWindowText(NULL);
	m_WsThickEdit->SetWindowText(NULL);
}

void WsGasFlowPredictDialog::fillWsCombox()
{
	MinePtr mine = FIND_BY_ID(Mine, mine_id);
	if(mine == 0) return;

	//��ѯ���еĻزɹ�����
	RecordPtrListPtr lists = DaoHelper::GetWorkSurfs(mine->getID());
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		WorkSurfPtr work_surf = DYNAMIC_POINTER_CAST(WorkSurf, lists->at(i));
		if(work_surf == 0) continue;

		SComboBoxHelper::Add(m_WsCombox, work_surf->name, work_surf->getID());
	}
	SComboBoxHelper::Select(m_WsCombox, 0);
}

WorkSurfPtr WsGasFlowPredictDialog::getCurSelWs()
{
	int ws_id = SComboBoxHelper::GetCurSelItemID(m_WsCombox);
	if(ws_id == 0) return WorkSurfPtr();
	return FIND_BY_ID(WorkSurf, ws_id);
}
