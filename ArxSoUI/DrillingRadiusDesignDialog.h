#pragma once
#include "AcadSouiDialog.h"

class DrillingRadiusDesignDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	DrillingRadiusDesignDialog(BOOL bModal = FALSE);
	~DrillingRadiusDesignDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnCaclButtonClick();
	void OnSaveButtonClick();
	void OnCoalComboxSelChanged(SOUI::EventArgs *pEvt);

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
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_NAME_HANDLER(_T("coal"), EVT_CB_SELCHANGE, OnCoalComboxSelChanged)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(DrillingRadiusDesignDialog)
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
	SEdit* m_LEdit;
	SEdit* m_Q0Edit;
	SEdit* m_REdit;
	SEdit* m_QmEdit;
	SEdit* m_GasW0Edit;
	SEdit* m_QSumEdit;
	SEdit* m_EtaEdit;
	SEdit* m_GasWc3Edit;
	SEdit* m_HwEdit;
	SComboBox* m_CoalCombox;

protected:
	virtual void OnDestroyWindow();

private:
	void fillCoalCombox();
	void initCoalDatas();
	void initDrillingRadiusDatas();
};
