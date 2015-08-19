#pragma once
#include "AcadSouiDialog.h"

class TwsGasPredictDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	TwsGasPredictDialog(BOOL bModal = FALSE);
	~TwsGasPredictDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnQ3CaclButtonClick();
	void OnQ4CaclButtonClick();
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
		EVENT_NAME_COMMAND(_T("q3_cacl"), OnQ3CaclButtonClick)
		EVENT_NAME_COMMAND(_T("q4_cacl"), OnQ4CaclButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(TwsGasPredictDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_TwQ3Edit;
	SEdit* m_TwQ4Edit;
};
