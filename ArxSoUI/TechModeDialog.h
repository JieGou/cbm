#pragma once
#include "AcadSouiDialog.h"

class TechModeDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	TechModeDialog(BOOL bModal = FALSE);
	~TechModeDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnTechModeComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnSaveButtonClick();
	void OnRadioGroup1Switch(int nID);
	void OnRadioGroup2Switch(int nID);
	void OnRadioGroup3Switch(int nID);

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
		EVENT_NAME_HANDLER(_T("tech_mode"), EVT_CB_SELCHANGE, OnTechModeComboxSelChanged)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_ID_COMMAND_RANGE(110, 111, OnRadioGroup1Switch)
		EVENT_ID_COMMAND_RANGE(120, 121, OnRadioGroup2Switch)
		EVENT_ID_COMMAND_RANGE(100, 101, OnRadioGroup3Switch)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(TechModeDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SComboBox* m_TechModeCombox;
	SRadioBox* m_C2YesRadio;
	SRadioBox* m_C2NoRadio;
	SRadioBox* m_C3YesRadio;
	SRadioBox* m_C3NoRadio;
	SStatic* m_RegionLabel;
	SRadioBox* m_C1YesRadio;
	SRadioBox* m_C1NoRadio;

public:
	CString regionName; // ʾ������(�ⲿ����)

protected:
	virtual void OnDestroyWindow();

private:
	void fillTechModeCombox();
};
