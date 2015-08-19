#pragma once
#include "AcadSouiDialog.h"

class MineGasPredictDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	MineGasPredictDialog(BOOL bModal = FALSE);
	~MineGasPredictDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnK1HelpButtonClick();
	void OnSaveButtonClick();
	void OnK2HelpButtonClick();
	void OnWorkAreaComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnInputButtonClick();

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
		EVENT_NAME_COMMAND(_T("k1_help"), OnK1HelpButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_NAME_COMMAND(_T("k2_help"), OnK2HelpButtonClick)
		EVENT_NAME_HANDLER(_T("work_area"), EVT_CB_SELCHANGE, OnWorkAreaComboxSelChanged)
		EVENT_NAME_COMMAND(_T("input"), OnInputButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(MineGasPredictDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_WorkAreaAEdit;
	SEdit* m_K1GasEdit;
	SEdit* m_QrEdit;
	SEdit* m_K2GasEdit;
	SComboBox* m_WorkAreaCombox;
	SEdit* m_WorkAreaQrEdit;
};
