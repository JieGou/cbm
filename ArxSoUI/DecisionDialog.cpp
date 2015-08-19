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
	MinePtr mine = DaoHelper::GetOnlineMine();
	if(mine == 0) return;

	StringArray coal_names;
	IntArray coal_ids;
	DaoHelper::GetCoalIds(mine->name, coal_ids);
	DaoHelper::GetCoalNames(mine->name, coal_names);

	CString msg;
	msg.Format(_T("��:%s,��������:%s\\n"), mine->name, mine->region->get(FIELD(name)));
	msg.AppendFormat(_T("ú�����:%d\\n"), coal_names.size());
	msg.AppendFormat(_T("ú����(������):"));
	for(int i=0;i<coal_names.size();i++)
	{
		msg.AppendFormat(_T("  %s"), coal_names[i]);
	}
	msg.AppendFormat(_T("\\n"));
	msg.AppendFormat(_T("��ξ����в���ȷ???"));
	SMessageBox(GetSafeWnd(),msg,_T("������ʾ"),MB_OK);
}
