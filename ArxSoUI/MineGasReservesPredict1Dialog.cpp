#include "stdafx.h"
#include "MineGasReservesPredict1Dialog.h"
#include "MineGasReservesPredictInputDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

MineGasReservesPredict1Dialog::MineGasReservesPredict1Dialog(BOOL bModal) : AcadSouiDialog(_T("layout:mine_gas_reserves_predict_1"), bModal)
{
}

MineGasReservesPredict1Dialog::~MineGasReservesPredict1Dialog()
{
}

void MineGasReservesPredict1Dialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT MineGasReservesPredict1Dialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_ReserveGasEdit = FindChildByName2<SEdit>(L"reserve_gas");
	m_ReserveW1Edit = FindChildByName2<SEdit>(L"reserve_w1");
	m_ReserveW2Edit = FindChildByName2<SEdit>(L"reserve_w2");
	m_ReserveW3Edit = FindChildByName2<SEdit>(L"reserve_w3");
	m_RockGasK2Edit = FindChildByName2<SEdit>(L"rock_gas_K2");

	//�������
	fillMineDatas();

	return 0;
}


void MineGasReservesPredict1Dialog::OnSaveButtonClick()
{
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	Utils::cstring_to_double((LPCTSTR)m_ReserveW1Edit->GetWindowText(), mine->reserve_w1);
	Utils::cstring_to_double((LPCTSTR)m_ReserveW1Edit->GetWindowText(), mine->reserve_w2);
	Utils::cstring_to_double((LPCTSTR)m_ReserveW1Edit->GetWindowText(), mine->reserve_w3);
	Utils::cstring_to_double((LPCTSTR)m_ReserveW1Edit->GetWindowText(), mine->rock_gas_k2);

	//���浽���ݿ�
	if(mine->save())
	{
		SMessageBox(GetSafeWnd(),_T("�������ݳɹ�"),_T("������ʾ"),MB_OK);
	}
}

void MineGasReservesPredict1Dialog::OnW1CaclButtonClick()
{
	MineGasReservesPredictInputDialog dlg(TRUE);
	dlg.Run(GetSafeWnd());

	//��ȡ���ݽ��м���
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	//�������еĿɲ�ú��
	RecordPtrListPtr lists = FIND_MANY2(Coal, FKEY(Mine), mine->getStringID(), FIELD(minable), _T("1"));
	if(lists == 0) return;
	//����ɲ�ú�����˹����
	double S = 0;
	for(int i=0;i<lists->size();i++)
	{
		CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, lists->at(i));
		S += coal->res_a1 * coal->gas_x1;
	}
	mine->reserve_w1 = S;

	//���µ�����
	m_ReserveW1Edit->SetWindowText(Utils::double_to_cstring(mine->reserve_w1));
}

void MineGasReservesPredict1Dialog::OnW2CaclButtonClick()
{
	MineGasReservesPredictInputDialog dlg(TRUE);
	dlg.Run(GetSafeWnd());

	//��ȡ���ݽ��м���
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	//�������еĲ��ɲ�ú��
	RecordPtrListPtr lists = FIND_MANY2(Coal, FKEY(Mine), mine->getStringID(), FIELD(minable), _T("0"));
	if(lists == 0) return;
	//���㲻�ɲ�ú�����˹����
	double S = 0;
	for(int i=0;i<lists->size();i++)
	{
		CoalPtr coal = DYNAMIC_POINTER_CAST(Coal, lists->at(i));
		S += coal->res_a1 * coal->gas_x1;
	}
	mine->reserve_w1 = S;

	//���µ�����
	m_ReserveW2Edit->SetWindowText(Utils::double_to_cstring(mine->reserve_w2));
}

void MineGasReservesPredict1Dialog::OnW3CaclButtonClick()
{
	//��ȡ���ݽ��м���
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	//��ȡ��������ݽ��м���(�������ݿ�����ȡ����)
	double w1 = 0, w2 = 0, k = 0;
	Utils::cstring_to_double((LPCTSTR)m_ReserveW1Edit->GetWindowText(), w1);
	Utils::cstring_to_double((LPCTSTR)m_ReserveW2Edit->GetWindowText(), w2);
	Utils::cstring_to_double((LPCTSTR)m_RockGasK2Edit->GetWindowText(), k);
	mine->reserve_w3 = k*(w1+w2);

	//���µ�����
	m_ReserveW3Edit->SetWindowText(Utils::double_to_cstring(mine->reserve_w3));

}

void MineGasReservesPredict1Dialog::OnGasCaclButtonClick()
{
	MineGasReservesPredictInputDialog dlg(TRUE);
	dlg.Run(GetSafeWnd());

	//��ȡ���ݽ��м���
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	//��ȡ��������ݽ��м���(�������ݿ�����ȡ����)
	double w1 = 0, w2 = 0, w3 = 0, k = 0;
	Utils::cstring_to_double((LPCTSTR)m_ReserveW1Edit->GetWindowText(), w1);
	Utils::cstring_to_double((LPCTSTR)m_ReserveW2Edit->GetWindowText(), w2);
	Utils::cstring_to_double((LPCTSTR)m_ReserveW3Edit->GetWindowText(), w3);
	Utils::cstring_to_double((LPCTSTR)m_RockGasK2Edit->GetWindowText(), k);
	mine->reserve_gas = w1 + w2 + w3;

	//���µ�����
	m_ReserveGasEdit->SetWindowText(Utils::double_to_cstring(mine->reserve_gas));
}

void MineGasReservesPredict1Dialog::fillMineDatas()
{
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	m_ReserveW1Edit->SetWindowText(Utils::double_to_cstring(mine->reserve_w1));
	m_ReserveW2Edit->SetWindowText(Utils::double_to_cstring(mine->reserve_w2));
	m_ReserveW3Edit->SetWindowText(Utils::double_to_cstring(mine->reserve_w3));
	m_RockGasK2Edit->SetWindowText(Utils::double_to_cstring(mine->rock_gas_k2));
}