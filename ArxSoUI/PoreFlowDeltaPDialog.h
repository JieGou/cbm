#pragma once
#include "AcadSouiDialog.h"

class PoreFlowDeltaPDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	PoreFlowDeltaPDialog(BOOL bModal = FALSE);
	~PoreFlowDeltaPDialog(void);

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
	BEGIN_MSG_MAP_EX(PoreFlowDeltaPDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_PTestEdit;
	SEdit* m_PCurEdit;
	SEdit* m_PTEdit;
	SEdit* m_DeltaPEdit;
};
