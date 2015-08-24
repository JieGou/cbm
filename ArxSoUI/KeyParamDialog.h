#pragma once
#include "AcadSouiDialog.h"

class KeyParamDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	KeyParamDialog(BOOL bModal = FALSE);
	~KeyParamDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnKP1ButtonClick();
	void OnKP2ButtonClick();
	void OnKP3ButtonClick();
	void OnKP4ButtonClick();
	void OnKP6ButtonClick();
	void OnKP7ButtonClick();
	void OnKP8ButtonClick();
	void OnKP9ButtonClick();
	void OnKP10ButtonClick();
	void OnKP11ButtonClick();
	void OnKP5ButtonClick();

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
		EVENT_NAME_COMMAND(_T("KP1"), OnKP1ButtonClick)
		EVENT_NAME_COMMAND(_T("KP2"), OnKP2ButtonClick)
		EVENT_NAME_COMMAND(_T("KP3"), OnKP3ButtonClick)
		EVENT_NAME_COMMAND(_T("KP4"), OnKP4ButtonClick)
		EVENT_NAME_COMMAND(_T("KP6"), OnKP6ButtonClick)
		EVENT_NAME_COMMAND(_T("KP7"), OnKP7ButtonClick)
		EVENT_NAME_COMMAND(_T("KP8"), OnKP8ButtonClick)
		EVENT_NAME_COMMAND(_T("KP9"), OnKP9ButtonClick)
		EVENT_NAME_COMMAND(_T("KP10"), OnKP10ButtonClick)
		EVENT_NAME_COMMAND(_T("KP11"), OnKP11ButtonClick)
		EVENT_NAME_COMMAND(_T("KP5"), OnKP5ButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(KeyParamDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

public:
	int mine_id;
};
