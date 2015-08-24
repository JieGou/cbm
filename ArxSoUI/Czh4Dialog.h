#pragma once
#include "AcadSouiDialog.h"

class Czh4Dialog : public AcadSouiDialog
{

	/** ������������� */
public:
	Czh4Dialog(BOOL bModal = FALSE);
	~Czh4Dialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
	void OnRockComboxSelChanged(SOUI::EventArgs *pEvt);

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
		EVENT_NAME_HANDLER(_T("rock"), EVT_CB_SELCHANGE, OnRockComboxSelChanged)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(Czh4Dialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_HwEdit;
	SEdit* m_HEdit;
	SEdit* m_CavingZoneHeightEdit;
	SComboBox* m_RockCombox;
	SEdit* m_ToleranceEdit;

public:
	int coal_id;

private:
	void initDatas();
};
