#pragma once
#include "AcadSouiDialog.h"

class HighDrillingTunnelDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	HighDrillingTunnelDialog(BOOL bModal = FALSE);
	~HighDrillingTunnelDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnRockComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnSaveButtonClick();
	void OnWsComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnCaclButtonClick();

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
		EVENT_NAME_HANDLER(_T("rock"), EVT_CB_SELCHANGE, OnRockComboxSelChanged)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_NAME_HANDLER(_T("ws"), EVT_CB_SELCHANGE, OnWsComboxSelChanged)
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(HighDrillingTunnelDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_HwEdit;
	SEdit* m_CzkEdit;
	SEdit* m_DipAngleEdit;
	SComboBox* m_RockCombox;
	SEdit* m_HzMinEdit;
	SEdit* m_HzMaxEdit;
	SComboBox* m_WsCombox;

protected:
	virtual void OnDestroyWindow();

private:
	void initWsDatas();
	void fillWsCombox();
	WorkSurfPtr getCurSelWs();
};
