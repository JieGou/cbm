#pragma once
#include "AcadSouiDialog.h"

class FunctionManageDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	FunctionManageDialog(BOOL bModal = FALSE);
	~FunctionManageDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnF1ButtonClick();
	void OnF2ButtonClick();
	void OnF3ButtonClick();

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
		EVENT_NAME_COMMAND(_T("f1"), OnF1ButtonClick)
		EVENT_NAME_COMMAND(_T("f2"), OnF2ButtonClick)
		EVENT_NAME_COMMAND(_T("f3"), OnF3ButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(FunctionManageDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
};
