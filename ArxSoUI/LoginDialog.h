#pragma once
#include "AcadSouiDialog.h"

class LoginDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	LoginDialog(BOOL bModal = FALSE);
	~LoginDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnRegButtonClick();
	void OnLoginButtonClick();

	/** �˵���Ϣ */
protected:
	//����˵���Ϣ(�˵���һ��������xml�ļ���������ÿ���˵����һ��id��)
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	/** ������Ϣ */
protected:
	//�Ի����ʼ������
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	//�ؼ���Ϣӳ���
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(_T("reg"), OnRegButtonClick)
		EVENT_NAME_COMMAND(_T("login"), OnLoginButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(LoginDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_UsernameEdit;
	SEdit* m_PasswordEdit;
};
