#pragma once
#include "AcadSouiDialog.h"

class MineGasReservesPredict1Dialog : public AcadSouiDialog
{

	/** ������������� */
public:
	MineGasReservesPredict1Dialog(BOOL bModal = FALSE);
	~MineGasReservesPredict1Dialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
	void OnW1CaclButtonClick();
	void OnW2CaclButtonClick();
	void OnCaclButtonClick();

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
		EVENT_NAME_COMMAND(_T("w1_cacl"), OnW1CaclButtonClick)
		EVENT_NAME_COMMAND(_T("w2_cacl"), OnW2CaclButtonClick)
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(MineGasReservesPredict1Dialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

public:
	int mine_id; 

protected:
	SEdit* m_ReserveW1Edit;
	SEdit* m_ReserveW2Edit;
	SEdit* m_ReserveW3Edit;
	SEdit* m_RockGasK2Edit;

private:
	void fillMineDatas();
};
