#include "stdafx.h"
#include "PoreSizeDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

#include <cmath>

PoreSizeDialog::PoreSizeDialog(BOOL bModal) : AcadSouiDialog(_T("layout:pore_size"), bModal)
{
	mine_id = 0;
	pore_size_id = 0;
}

PoreSizeDialog::~PoreSizeDialog()
{
}

void PoreSizeDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT PoreSizeDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_QEdit = FindChildByName2<SEdit>(L"Q");
	m_DeltaEdit = FindChildByName2<SEdit>(L"delta");
	m_VEdit = FindChildByName2<SEdit>(L"V");
	m_SigmaEdit = FindChildByName2<SEdit>(L"sigma");
	m_PEdit = FindChildByName2<SEdit>(L"P");
	m_DEdit = FindChildByName2<SEdit>(L"D");

	initDatas();

	return 0;
}


void PoreSizeDialog::OnSaveButtonClick()
{
	PoreSizePtr pore_size = FIND_BY_ID(PoreSize, pore_size_id);
	if(pore_size == 0) return;

	Utils::cstring_to_double((LPCTSTR)m_QEdit->GetWindowText(), pore_size->q);
	Utils::cstring_to_double((LPCTSTR)m_VEdit->GetWindowText(), pore_size->v);
	Utils::cstring_to_double((LPCTSTR)m_DEdit->GetWindowText(), pore_size->d);
	Utils::cstring_to_double((LPCTSTR)m_PEdit->GetWindowText(), pore_size->p);
	Utils::cstring_to_double((LPCTSTR)m_SigmaEdit->GetWindowText(), pore_size->sigma);
	Utils::cstring_to_double((LPCTSTR)m_DeltaEdit->GetWindowText(), pore_size->delta);
	//���浽���ݿ�
	if(pore_size->save())
	{
		SMessageBox(GetSafeWnd(), _T("�������ݳɹ�!!!"), _T("������ʾ"), MB_OK);
	}
	else
	{
		SMessageBox(GetSafeWnd(), _T("��������ʧ��!!!"), _T("������ʾ"), MB_OK);
	}
}

void PoreSizeDialog::OnHintButtonClick()
{
	SMessageBox(GetSafeWnd(), _T("ע�������·������Ӧ������ʹ�����޻���������ڵ����ֵȷ��\\n��Ӧ��1.2~1.8�ĸ���ϵ��!!!"), _T("������ʾ"), MB_OK);
}

void PoreSizeDialog::OnCaclButtonClick()
{
	//��ȡ��������
	double Q = 0, V = 0, D = 0, P = 0, sigma = 0, delta = 0;
	Utils::cstring_to_double((LPCTSTR)m_QEdit->GetWindowText(), Q);
	Utils::cstring_to_double((LPCTSTR)m_VEdit->GetWindowText(), V);
	//Utils::cstring_to_double((LPCTSTR)m_DEdit->GetWindowText(), D);
	Utils::cstring_to_double((LPCTSTR)m_PEdit->GetWindowText(), P);
	Utils::cstring_to_double((LPCTSTR)m_SigmaEdit->GetWindowText(), sigma);
	//Utils::cstring_to_double((LPCTSTR)m_DeltaEdit->GetWindowText(), delta);

	if(sigma == 0 || V == 0)
	{
		SMessageBox(GetSafeWnd(), _T("�������ٻ�����ѹ��ȡֵ����Ϊ0!!!"), _T("������ʾ"), MB_OK);
		return;
	}

	D = 0.1457*sqrt(Q/V);
	delta = 0.5*P*D/sigma;

	//���µ�����
	m_DEdit->SetWindowText(Utils::double_to_cstring(D));
	m_DeltaEdit->SetWindowText(Utils::double_to_cstring(delta));
}

void PoreSizeDialog::OnHint2ButtonClick()
{
	SMessageBox(GetSafeWnd(), _T("ע:��ȡ��������ǿ�ȵ�60%��ȱ�ٴ�ֵʱ:\\n�����ܿ�ȡ20MPa\\n���Ӹֹܿ�ȡ60MPa\\n�޷�ֹܿ�ȡ80MPa"), _T("������ʾ"), MB_OK);
}

void PoreSizeDialog::OnDestroyWindow()
{
	if(pore_size_id != 0)
	{
		PoreSizePtr pore_size = FIND_BY_ID(PoreSize, pore_size_id);
		if(pore_size_id != 0)
		{
			pore_size->remove();
		}
	}
	AcadSouiDialog::OnDestroyWindow();
}

void PoreSizeDialog::initDatas()
{
	m_QEdit->SetWindowText(NULL);
	m_DeltaEdit->SetWindowText(NULL);
	m_VEdit->SetWindowText(NULL);
	m_SigmaEdit->SetWindowText(NULL);
	m_PEdit->SetWindowText(NULL);
	m_DEdit->SetWindowText(NULL);

	pore_size_id = 0;
	PoreSizePtr pore_size(new PoreSize);
	pore_size->name = _T("");
	if(pore_size->save())
	{
		pore_size_id = pore_size->getID();
	}
}
