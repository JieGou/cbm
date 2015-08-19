#pragma once
#include "AcadSouiDialog.h"

class RegDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	RegDialog(BOOL bModal = FALSE);
	~RegDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnRegButtonClick();
	void OnBaseComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnRegionComboxSelChanged(SOUI::EventArgs *pEvt);

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
		EVENT_NAME_COMMAND(_T("reg"), OnRegButtonClick)
		EVENT_NAME_HANDLER(_T("base"), EVT_CB_SELCHANGE, OnBaseComboxSelChanged)
		EVENT_NAME_HANDLER(_T("region"), EVT_CB_SELCHANGE, OnRegionComboxSelChanged)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(RegDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_NameEdit;
	SEdit* m_ProvinceEdit;
	SEdit* m_CityEdit;
	SEdit* m_CoalNumsEdit;
	SEdit* m_UsernameEdit;
	SEdit* m_PasswordEdit;
	SComboBox* m_BaseCombox;
	SComboBox* m_RegionCombox;

private:
	void fillBaseCombox();
	void fillRegionCombox(const CString& base);
	void clearBaseCombox();
	void clearRegionCombox();
};
