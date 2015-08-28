#pragma once
#include "SouiDialog.h"

class MainuiDialog : public SouiDialog
{

	/** ������������� */
public:
	MainuiDialog(BOOL bModal = FALSE);
	~MainuiDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnCadButtonClick();
	void OnCadfileButtonClick();

	/** �˵���Ϣ */
protected:
	//����˵���Ϣ(�˵���һ��������xml�ļ���������ÿ���˵����һ��id��)
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	/** ������Ϣ */
protected:
	//�Ի����ʼ������
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	//���ڹر�ǰ��һЩ������
	virtual void OnDestroyWindow();

	//�ؼ���Ϣӳ���
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(_T("cad"), OnCadButtonClick)
		EVENT_NAME_COMMAND(_T("cadfile"), OnCadfileButtonClick)
		CHAIN_EVENT_MAP(SouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(MainuiDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(SouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

private:
	void RunCADApp(CString& sPath,LPTSTR arg = NULL);
};
