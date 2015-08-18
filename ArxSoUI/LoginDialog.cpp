#include "stdafx.h"
#include "LoginDialog.h"
#include "RegDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

LoginDialog::LoginDialog(BOOL bModal) : AcadSouiDialog(_T("layout:login"), bModal)
{
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT LoginDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);

	m_UsernameEdit = FindChildByName2<SEdit>(L"username");
	m_PasswordEdit = FindChildByName2<SEdit>(L"password");

	return 0;
}

void LoginDialog::OnRegButtonClick()
{
	RegDialog dlg(TRUE);
	dlg.Run(this->m_hWnd);
	//SMessageBox(m_hWnd,_T("ע�����Ϣ"),_T("����"),MB_OK);
}

void LoginDialog::OnLoginButtonClick()
{
	CString user = m_UsernameEdit->GetWindowText();
	CString pwd = m_PasswordEdit->GetWindowText();

	int ret = DaoHelper::VerifyMineAccount(user, pwd);
	if(user.IsEmpty())
	{
		SMessageBox(m_hWnd,_T("�������û���!"),_T("������ʾ"),MB_OK);
	}
	else if(pwd.IsEmpty())
	{
		SMessageBox(m_hWnd,_T("����������!"),_T("������ʾ"),MB_OK);
	}
	else if(ret == 0)
	{
		CString msg;
		msg.Format(_T("�û���:%s������,��ע��!"), user);
		SMessageBox(m_hWnd,msg,_T("������ʾ"),MB_OK);
	}
	else if(ret == 1)
	{
		SMessageBox(m_hWnd,_T("��������ȷ������!"),_T("������ʾ"),MB_OK);
	}
	else
	{
		int account_id = DaoHelper::GetOnlineAccountId();
		if(account_id == 0)
		{
			//���õ�ǰ��¼�û�
			SysInfoPtr sys_info(new SysInfo);
			sys_info->account = FIND_ONE(Account, FIELD(username), user);
			sys_info->save();
			SMessageBox(m_hWnd,_T("��¼�ɹ�!"),_T("������ʾ"),MB_OK);
			AcadSouiDialog::OnOK();
		}
		else
		{
			//����id�����û�
			AccountPtr account = FIND_BY_ID(Account, account_id);
			if(account == 0)
			{
				SMessageBox(m_hWnd,_T("��¼ʧ��!"),_T("������ʾ"),MB_OK);
			}
			else if(account->username == user)
			{
				SMessageBox(m_hWnd,_T("��ǰ�û��ѵ�¼!"),_T("������ʾ"),MB_OK);
			}
			else
			{
				CString msg;
				msg.Format(_T("�Ƿ�ע����ǰ�û�%s���л����û�%s???"), account->username, user);
				if(IDYES == SMessageBox(m_hWnd,msg,_T("������ʾ"),MB_YESNO))
				{
					//���õ�ǰ��¼�û�
					SysInfoPtr sys_info = FIND_FIRST(SysInfo);
					sys_info->account = FIND_ONE(Account, FIELD(username), user);
					sys_info->save();
					msg.Format(_T("�ɹ��л����û�:%s"), user);
					SMessageBox(m_hWnd,msg,_T("������ʾ"),MB_OK);
					AcadSouiDialog::OnOK();
				}
			}
		}
	}
}
