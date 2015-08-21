#pragma once
#include "AcadSouiDialog.h"

class TwsGasFlowPredictDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	TwsGasFlowPredictDialog(BOOL bModal = FALSE);
	~TwsGasFlowPredictDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
	void OnCaclButtonClick();
	void OnWcCaclButtonClick();
	void OnTwsComboxSelChanged(SOUI::EventArgs *pEvt);

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
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		EVENT_NAME_COMMAND(_T("wc_cacl"), OnWcCaclButtonClick)
		EVENT_NAME_HANDLER(_T("tws"), EVT_CB_SELCHANGE, OnTwsComboxSelChanged)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(TwsGasFlowPredictDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_Q3Edit;
	SEdit* m_Q4Edit;
	SEdit* m_QaEdit;
	SEdit* m_Q0Edit;
	SEdit* m_DEdit;
	SEdit* m_VEdit;
	SEdit* m_LEdit;
	SEdit* m_VrEdit;
	SEdit* m_GasW0Edit;
	SEdit* m_RhoEdit;
	SEdit* m_SEdit;
	SEdit* m_GasWc2Edit;
	SComboBox* m_TwsCombox;

protected:
	virtual void OnDestroyWindow();

private:
	void initTwsDatas();
	void fillTwsCombox();
	DrillingSurfPtr getCurSelTws();
};
