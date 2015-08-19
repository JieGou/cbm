#pragma once
#include "AcadSouiDialog.h"

class DrillingRadiusQmDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	DrillingRadiusQmDialog(BOOL bModal = FALSE);
	~DrillingRadiusQmDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();

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
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(DrillingRadiusQmDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_K1Edit;
	SEdit* m_RhoEdit;
	SEdit* m_AEdit;
	SEdit* m_TEdit;
	SEdit* m_Edit12;
	SEdit* m_QmEdit;
	SEdit* m_Q0Edit;
	SEdit* m_REdit;
};
