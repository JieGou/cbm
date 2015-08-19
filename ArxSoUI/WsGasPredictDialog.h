#pragma once
#include "AcadSouiDialog.h"

class WsGasPredictDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	WsGasPredictDialog(BOOL bModal = FALSE);
	~WsGasPredictDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnWorkCaclButtonClick();
	void OnAdjCaclButtonClick();
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
		EVENT_NAME_COMMAND(_T("work_cacl"), OnWorkCaclButtonClick)
		EVENT_NAME_COMMAND(_T("adj_cacl"), OnAdjCaclButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(WsGasPredictDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_Qr1Edit;
	SEdit* m_Qr2Edit;
	SEdit* m_QrEdit;
	SRadioBox* m_Radio68;
	SRadioBox* m_Radio69;
};
