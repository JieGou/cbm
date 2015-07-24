#pragma once

#include "AcadSouiDialog.h"

/** 
 * ��¼�Ի���.
 * ��2����̬:ģ̬�Ի���ͷ�ģ̬�Ի���,ͨ�����캯���Ĳ���bModal����
 */
class LoginDlg : public AcadSouiDialog
{
public:
    LoginDlg(BOOL bModal = FALSE);
    ~LoginDlg(void);
    
	/** �ؼ���Ϣ���� */
protected:
	//��¼
	void OnLogin();
	//ע��
	void OnReg();

	/** �˵���Ϣ */
protected:
	//����˵���Ϣ(�˵���һ��������xml�ļ���������ÿ���˵����һ��id��)
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	/** ������Ϣ */
protected:
	//�Ի����ʼ������
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

    EVENT_MAP_BEGIN()
        EVENT_NAME_COMMAND(_T("btn_login"), OnLogin)
		EVENT_NAME_COMMAND(_T("btn_reg"), OnReg)
		CHAIN_EVENT_MAP(AcadSouiDialog)
    EVENT_MAP_END()

	//HOST��Ϣ����Ӧ����ӳ���
	BEGIN_MSG_MAP_EX(LoginDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};

