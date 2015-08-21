#include "stdafx.h"
#include "TwsGasFlowPredictDialog.h"
#include "SComboxHelper.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

#include <cmath>

TwsGasFlowPredictDialog::TwsGasFlowPredictDialog(BOOL bModal) : AcadSouiDialog(_T("layout:tws_gas_flow_predict"), bModal)
{
}

TwsGasFlowPredictDialog::~TwsGasFlowPredictDialog()
{
}

void TwsGasFlowPredictDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT TwsGasFlowPredictDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_Q3Edit = FindChildByName2<SEdit>(L"q3");
	m_Q4Edit = FindChildByName2<SEdit>(L"q4");
	m_QaEdit = FindChildByName2<SEdit>(L"qa");
	m_Q0Edit = FindChildByName2<SEdit>(L"q0");
	m_DEdit = FindChildByName2<SEdit>(L"D");
	m_VEdit = FindChildByName2<SEdit>(L"V");
	m_LEdit = FindChildByName2<SEdit>(L"L");
	m_VrEdit = FindChildByName2<SEdit>(L"Vr");
	m_GasW0Edit = FindChildByName2<SEdit>(L"gas_W0");
	m_RhoEdit = FindChildByName2<SEdit>(L"rho");
	m_SEdit = FindChildByName2<SEdit>(L"S");
	m_GasWc2Edit = FindChildByName2<SEdit>(L"gas_Wc2");
	m_TwsCombox = FindChildByName2<SComboBox>(L"tws");

	initTwsDatas();
	fillTwsCombox();

	return 0;
}


void TwsGasFlowPredictDialog::OnSaveButtonClick()
{
	//���浱ǰ����������
	DrillingSurfPtr drilling_surf = getCurSelTws();
	if(drilling_surf == 0) return;

	//ע��:�����ľ��������ݱ�����[���]�����,�����Ǿ���汾��
	if(drilling_surf->tunnel == 0)
	{
		drilling_surf->tunnel.reset(new Tunnel);
	}
	TunnelPtr tunnel = DYNAMIC_POINTER_CAST(Tunnel, drilling_surf->tunnel);

	//������������
	Utils::cstring_to_double((LPCTSTR)m_DEdit->GetWindowText(), tunnel->d);
	Utils::cstring_to_double((LPCTSTR)m_VEdit->GetWindowText(), tunnel->v);
	Utils::cstring_to_double((LPCTSTR)m_LEdit->GetWindowText(), tunnel->l);
	Utils::cstring_to_double((LPCTSTR)m_SEdit->GetWindowText(), tunnel->s);
	Utils::cstring_to_double((LPCTSTR)m_Q0Edit->GetWindowText(), tunnel->q0);
	Utils::cstring_to_double((LPCTSTR)m_Q3Edit->GetWindowText(), tunnel->q3);

	//����������
	Utils::cstring_to_double((LPCTSTR)m_Q4Edit->GetWindowText(), drilling_surf->q4);
	Utils::cstring_to_double((LPCTSTR)m_QaEdit->GetWindowText(), drilling_surf->qa);

	//ú������
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, drilling_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	Utils::cstring_to_double((LPCTSTR)m_VrEdit->GetWindowText(), coal->vr);
	Utils::cstring_to_double((LPCTSTR)m_RhoEdit->GetWindowText(), coal->rho);
	Utils::cstring_to_double((LPCTSTR)m_GasW0Edit->GetWindowText(), coal->gas_w0);
	Utils::cstring_to_double((LPCTSTR)m_GasWc2Edit->GetWindowText(), coal->gas_wc2);

	//���α��浽���ݿ�
	if(!drilling_surf->save())
	{
		SMessageBox(GetSafeWnd(),_T("������������ʧ��!"),_T("������ʾ"),MB_OK);
		return;
	}
	if(!tunnel->save())
	{
		SMessageBox(GetSafeWnd(),_T("�������������ʧ��!"),_T("������ʾ"),MB_OK);
		return;
	}
	if(!coal->save())
	{
		SMessageBox(GetSafeWnd(),_T("����ú������ʧ��!"),_T("������ʾ"),MB_OK);
		return;
	}
	SMessageBox(GetSafeWnd(),_T("�������ݳɹ�!"),_T("������ʾ"),MB_OK);
}

void TwsGasFlowPredictDialog::OnCaclButtonClick()
{
	//������ȫ����ȡ������������
	//��ǰ�����
	DrillingSurfPtr drilling_surf = getCurSelTws();
	if(drilling_surf == 0) return;

	//ע��:�����ľ��������ݱ�����[���]�����,�����Ǿ���汾��
	if(drilling_surf->tunnel == 0)
	{
		drilling_surf->tunnel.reset(new Tunnel);
	}
	TunnelPtr tunnel = DYNAMIC_POINTER_CAST(Tunnel, drilling_surf->tunnel);

	//������������
	Utils::cstring_to_double((LPCTSTR)m_DEdit->GetWindowText(), tunnel->d);
	Utils::cstring_to_double((LPCTSTR)m_VEdit->GetWindowText(), tunnel->v);
	Utils::cstring_to_double((LPCTSTR)m_LEdit->GetWindowText(), tunnel->l);
	Utils::cstring_to_double((LPCTSTR)m_SEdit->GetWindowText(), tunnel->s);
	Utils::cstring_to_double((LPCTSTR)m_Q0Edit->GetWindowText(), tunnel->q0);
	Utils::cstring_to_double((LPCTSTR)m_Q3Edit->GetWindowText(), tunnel->q3);

	//����������
	Utils::cstring_to_double((LPCTSTR)m_Q4Edit->GetWindowText(), drilling_surf->q4);
	Utils::cstring_to_double((LPCTSTR)m_QaEdit->GetWindowText(), drilling_surf->qa);

	//ú������
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, drilling_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	Utils::cstring_to_double((LPCTSTR)m_VrEdit->GetWindowText(), coal->vr);
	Utils::cstring_to_double((LPCTSTR)m_RhoEdit->GetWindowText(), coal->rho);
	Utils::cstring_to_double((LPCTSTR)m_GasW0Edit->GetWindowText(), coal->gas_w0);
	Utils::cstring_to_double((LPCTSTR)m_GasWc2Edit->GetWindowText(), coal->gas_wc2);

	//����q0
	double Vr = coal->vr;
	double W0 = coal->gas_w0;
	double D = tunnel->d;
	double v = tunnel->v;
	double L = tunnel->l;
	double S = tunnel->s;
	double r = coal->rho;
	double Wc = coal->gas_wc2;
	double q0 = (0.0004*pow(Vr, 2)+0.16)*0.026*W0;
	double q3 = D*v*q0*(2*sqrt(L/v)-1);
	double q4 = S*v*r*(W0-Wc);
	double qa = q3+q4; // �������˹ӿ����

	//q0��q3��q4��qa���µ�����
	m_Q0Edit->SetWindowText(Utils::double_to_cstring(tunnel->q0));
	m_Q3Edit->SetWindowText(Utils::double_to_cstring(tunnel->q3));
	m_Q4Edit->SetWindowText(Utils::double_to_cstring(drilling_surf->q4));
	m_QaEdit->SetWindowText(Utils::double_to_cstring(drilling_surf->qa));
}

void TwsGasFlowPredictDialog::OnWcCaclButtonClick()
{
	//�鿴ú��
	int tws_id = SComboBoxHelper::GetCurSelItemID(m_TwsCombox);
	if(tws_id == 0) return;

	//����id���Ҿ����
	DrillingSurfPtr drilling_surf = FIND_BY_ID(DrillingSurf, tws_id);
	if(drilling_surf == 0) return;

	//�õ�ú��
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, drilling_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal == 0) return;

	if(coal->quality < 3 || coal->gas_w0 > 10) // �еͱ���ú��߱���ú,W0>10
	{
		SMessageBox(GetSafeWnd(),_T("�����Ի������û�ѡ��!"),_T("������ʾ"),MB_OK);
		//���µ�����
		//coal->gas_wc2 = Wc;
	}
	else
	{
		//ͨ�����鹫ʽ����
		double W0 = coal->gas_w0;
		double Wc = 10.385*exp(-7.207*W0);
		coal->gas_wc2 = Wc;
	}
	//���µ�����
	m_GasWc2Edit->SetWindowText(Utils::double_to_cstring(coal->gas_wc2));
}

void TwsGasFlowPredictDialog::OnTwsComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
	initTwsDatas();
	int tws_id = SComboBoxHelper::GetCurSelItemID(m_TwsCombox);
	if(tws_id == 0) return;

	//����id���Ҿ����
	DrillingSurfPtr drilling_surf = FIND_BY_ID(DrillingSurf, tws_id);
	if(drilling_surf == 0) return;

	//������������
	m_Q4Edit->SetWindowText(Utils::double_to_cstring(drilling_surf->q4));
	m_QaEdit->SetWindowText(Utils::double_to_cstring(drilling_surf->qa));

	//���ú������
	WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, drilling_surf->work_area);
	CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, work_area->coal);
	if(coal != 0)
	{
		m_VrEdit->SetWindowText(Utils::double_to_cstring(coal->vr));
		m_RhoEdit->SetWindowText(Utils::double_to_cstring(coal->rho));
		m_GasW0Edit->SetWindowText(Utils::double_to_cstring(coal->gas_w0));
		m_GasWc2Edit->SetWindowText(Utils::double_to_cstring(coal->gas_wc2));
	}

	//������������
	if(drilling_surf->tunnel != 0)
	{
		TunnelPtr tunnel = DYNAMIC_POINTER_CAST(Tunnel, drilling_surf->tunnel);
		m_DEdit->SetWindowText(Utils::double_to_cstring(tunnel->d));
		m_LEdit->SetWindowText(Utils::double_to_cstring(tunnel->l));
		m_SEdit->SetWindowText(Utils::double_to_cstring(tunnel->s));
		m_Q0Edit->SetWindowText(Utils::double_to_cstring(tunnel->q0));
		m_Q3Edit->SetWindowText(Utils::double_to_cstring(tunnel->q3));
	}
}

void TwsGasFlowPredictDialog::OnDestroyWindow()
{
	//ɾ�����еĸ�������
	SComboBoxHelper::Clear(m_TwsCombox);
	AcadSouiDialog::OnDestroyWindow();
}

void TwsGasFlowPredictDialog::initTwsDatas()
{
	m_Q3Edit->SetWindowText(NULL);
	m_Q4Edit->SetWindowText(NULL);
	m_QaEdit->SetWindowText(NULL);
	m_Q0Edit->SetWindowText(NULL);
	m_DEdit->SetWindowText(NULL);
	m_VEdit->SetWindowText(NULL);
	m_LEdit->SetWindowText(NULL);
	m_VrEdit->SetWindowText(NULL);
	m_GasW0Edit->SetWindowText(NULL);
	m_RhoEdit->SetWindowText(NULL);
	m_SEdit->SetWindowText(NULL);
	m_GasWc2Edit->SetWindowText(NULL);
	m_TwsCombox->SetCurSel(-1);
}

void TwsGasFlowPredictDialog::fillTwsCombox()
{
	SComboBoxHelper::Clear(m_TwsCombox);

	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	//��ѯ���еľ��������
	RecordPtrListPtr lists = DaoHelper::GetDrillingSurfs(mine->name);
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		DrillingSurfPtr drilling_surf = DYNAMIC_POINTER_CAST(DrillingSurf, lists->at(i));
		if(drilling_surf == 0) continue;

		SComboBoxHelper::Add(m_TwsCombox, drilling_surf->name, drilling_surf->getID());
	}
	SComboBoxHelper::Select(m_TwsCombox, 0);
}

DrillingSurfPtr TwsGasFlowPredictDialog::getCurSelTws()
{
	int tws_id = SComboBoxHelper::GetCurSelItemID(m_TwsCombox);
	if(tws_id == 0) return DrillingSurfPtr();
	return FIND_BY_ID(DrillingSurf, tws_id);
}