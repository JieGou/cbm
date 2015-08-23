#pragma once
#include "AcadSouiDialog.h"

class PolicyDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	PolicyDialog(BOOL bModal = FALSE);
	~PolicyDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnP1ButtonClick();
	void OnP2ButtonClick();
	void OnP3ButtonClick();
	void OnP4ButtonClick();
	void OnP6ButtonClick();
	void OnP7ButtonClick();
	void OnP8ButtonClick();
	void OnP5ButtonClick();

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
		EVENT_NAME_COMMAND(_T("P1"), OnP1ButtonClick)
		EVENT_NAME_COMMAND(_T("P2"), OnP2ButtonClick)
		EVENT_NAME_COMMAND(_T("P3"), OnP3ButtonClick)
		EVENT_NAME_COMMAND(_T("P4"), OnP4ButtonClick)
		EVENT_NAME_COMMAND(_T("P6"), OnP6ButtonClick)
		EVENT_NAME_COMMAND(_T("P7"), OnP7ButtonClick)
		EVENT_NAME_COMMAND(_T("P8"), OnP8ButtonClick)
		EVENT_NAME_COMMAND(_T("P5"), OnP5ButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(PolicyDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SLink* m_Link14;
};
