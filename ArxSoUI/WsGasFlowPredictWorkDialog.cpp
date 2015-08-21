#include "stdafx.h"
#include "WsGasFlowPredictWorkDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

WsGasFlowPredictWorkDialog::WsGasFlowPredictWorkDialog(BOOL bModal) : AcadSouiDialog(_T("layout:ws_gas_flow_predict_work"), bModal)
{
	ws_id = 0;
}

WsGasFlowPredictWorkDialog::~WsGasFlowPredictWorkDialog()
{
}

void WsGasFlowPredictWorkDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT WsGasFlowPredictWorkDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_K1Edit = FindChildByName2<SEdit>(L"K1");
	m_K2Edit = FindChildByName2<SEdit>(L"K2");
	m_K3Edit = FindChildByName2<SEdit>(L"K3");
	m_GasW0Edit = FindChildByName2<SEdit>(L"gas_W0");
	m_GasWc2Edit = FindChildByName2<SEdit>(L"gas_Wc2");
	m_KfEdit = FindChildByName2<SEdit>(L"Kf");

	initDatas();

	return 0;
}


void WsGasFlowPredictWorkDialog::OnSaveButtonClick()
{
	WorkSurfPtr work_surf = FIND_BY_ID(WorkSurf, ws_id);
	if(work_surf == 0) return;

	Utils::cstring_to_double((LPCTSTR)m_K1Edit->GetWindowText(), work_surf->k1);
	Utils::cstring_to_double((LPCTSTR)m_K2Edit->GetWindowText(), work_surf->k2);
	Utils::cstring_to_double((LPCTSTR)m_K3Edit->GetWindowText(), work_surf->k3);
	Utils::cstring_to_double((LPCTSTR)m_KfEdit->GetWindowText(), work_surf->kf);

	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, work_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal == 0)
	{
		return;
	}
	else
	{
		Utils::cstring_to_double((LPCTSTR)m_GasW0Edit->GetWindowText(), coal->gas_w0);
		Utils::cstring_to_double((LPCTSTR)m_GasWc2Edit->GetWindowText(), coal->gas_wc2);
	}
	if(work_surf->save())
	{
		SMessageBox(GetSafeWnd(),_T("�������ݳɹ�!"),_T("������ʾ"),MB_OK);
	}
	else
	{
		SMessageBox(GetSafeWnd(),_T("��������ʧ��!"),_T("������ʾ"),MB_OK);
	}
}

void WsGasFlowPredictWorkDialog::OnK3CaclButtonClick()
{
	SMessageBox(GetSafeWnd(),_T("����ʵ��ֵ����Զ����������!"),_T("������ʾ"),MB_OK);
	double K3 = 0;
	
	//���µ�����
	m_K3Edit->SetWindowText(Utils::double_to_cstring(K3));
}

void WsGasFlowPredictWorkDialog::OnKfCaclButtonClick()
{
	SMessageBox(GetSafeWnd(),_T("����ʵ��ֵ����Զ����������!"),_T("������ʾ"),MB_OK);

	double Kf = 0;

	//���µ�����
	m_KfEdit->SetWindowText(Utils::double_to_cstring(Kf));
}

void WsGasFlowPredictWorkDialog::initDatas()
{
	m_K1Edit->SetWindowText(NULL);
	m_K2Edit->SetWindowText(NULL);
	m_K3Edit->SetWindowText(NULL);
	m_GasW0Edit->SetWindowText(NULL);
	m_GasWc2Edit->SetWindowText(NULL);
	m_KfEdit->SetWindowText(NULL);
}

void WsGasFlowPredictWorkDialog::fillDatas()
{
	//����id���ҹ�����
	//����id���һزɹ�����
	WorkSurfPtr work_surf = FIND_BY_ID(WorkSurf, ws_id);
	if(work_surf == 0) return;

	m_K1Edit->SetWindowText(Utils::double_to_cstring(work_surf->k1));
	m_K2Edit->SetWindowText(Utils::double_to_cstring(work_surf->k2));
	m_K3Edit->SetWindowText(Utils::double_to_cstring(work_surf->k3));
	m_KfEdit->SetWindowText(Utils::double_to_cstring(work_surf->kf));

	//������->����->ú��
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, work_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal != 0)
	{
		m_GasW0Edit->SetWindowText(Utils::double_to_cstring(coal->gas_w0));
		m_GasWc2Edit->SetWindowText(Utils::double_to_cstring(coal->gas_wc2));
	}
}
