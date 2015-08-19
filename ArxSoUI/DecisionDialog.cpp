#include "stdafx.h"
#include "DecisionDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

DecisionDialog::DecisionDialog(BOOL bModal) : AcadSouiDialog(_T("layout:decision"), bModal)
{
}

DecisionDialog::~DecisionDialog()
{
}

void DecisionDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT DecisionDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_TechModeLabel = FindChildByName2<SStatic>(L"tech_mode");
	m_TechModeLabel->SetWindowText(_T("")); // ���
	return 0;
}


void DecisionDialog::OnGraphButtonClick()
{
	SMessageBox(GetSafeWnd(),_T("��β鿴ú�㸳��ͼ???"),_T("������ʾ"),MB_OK);
}

void DecisionDialog::OnTechnologyButtonClick()
{
	SMessageBox(GetSafeWnd(),_T("�������߻�������,�μ����ϵ���ע"),_T("������ʾ"),MB_OK);
}
