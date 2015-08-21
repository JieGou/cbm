#pragma once
#include "AcadSouiDialog.h"

class WsGasFlowPredictWorkDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	WsGasFlowPredictWorkDialog(BOOL bModal = FALSE);
	~WsGasFlowPredictWorkDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
	void OnK3CaclButtonClick();
	void OnKfCaclButtonClick();

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
		EVENT_NAME_COMMAND(_T("k3_cacl"), OnK3CaclButtonClick)
		EVENT_NAME_COMMAND(_T("kf_cacl"), OnKfCaclButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(WsGasFlowPredictWorkDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_K1Edit;
	SEdit* m_K2Edit;
	SEdit* m_K3Edit;
	SEdit* m_GasW0Edit;
	SEdit* m_GasWc2Edit;
	SEdit* m_KfEdit;

public:
	int ws_id; // �ⲿ����(������id)

private:
	void initDatas();
	void fillDatas();
};
