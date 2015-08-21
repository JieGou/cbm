#pragma once
#include "AcadSouiDialog.h"

class MineGasReservesPredictDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	MineGasReservesPredictDialog(BOOL bModal = FALSE);
	~MineGasReservesPredictDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
	void OnGasCaclButtonClick();
	void OnPumpWcCaclButtonClick();

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
		EVENT_NAME_COMMAND(_T("gas_cacl"), OnGasCaclButtonClick)
		EVENT_NAME_COMMAND(_T("pump_wc_cacl"), OnPumpWcCaclButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(MineGasReservesPredictDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_ReserveGasEdit;
	SEdit* m_PumpWcEdit;

private:
	void fillMineDatas();
};
