#pragma once
#include "AcadSouiDialog.h"

class ReservesPredictDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	ReservesPredictDialog(BOOL bModal = FALSE);
	~ReservesPredictDialog(void);

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
	BEGIN_MSG_MAP_EX(ReservesPredictDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_ReserveGasEdit;
	SEdit* m_ReserveW1Edit;
	SEdit* m_ReserveW2Edit;
	SEdit* m_ReserveW3Edit;
	SEdit* m_PumpWcEdit;
	SEdit* m_PumpKdEdit;
	SEdit* m_PumpK1Edit;
	SEdit* m_PumpK2Edit;
	SEdit* m_PumpK4Edit;
	SEdit* m_PumpK3Edit;
	SEdit* m_PumpMyEdit;
	SEdit* m_PumpMcEdit;
};
