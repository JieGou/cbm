#pragma once
#include "AcadSouiDialog.h"

class TwsGasPredictQ4Dialog : public AcadSouiDialog
{

	/** ������������� */
public:
	TwsGasPredictQ4Dialog(BOOL bModal = FALSE);
	~TwsGasPredictQ4Dialog(void);

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
	BEGIN_MSG_MAP_EX(TwsGasPredictQ4Dialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_GasW0Edit;
	SEdit* m_TwSEdit;
	SEdit* m_TwVEdit;
	SEdit* m_CoalREdit;
	SEdit* m_GasWc2Edit;
	SEdit* m_Q4Edit;
};
