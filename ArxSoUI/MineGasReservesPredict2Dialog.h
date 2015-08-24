#pragma once
#include "AcadSouiDialog.h"

class MineGasReservesPredict2Dialog : public AcadSouiDialog
{

	/** ������������� */
public:
	MineGasReservesPredict2Dialog(BOOL bModal = FALSE);
	~MineGasReservesPredict2Dialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
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
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(MineGasReservesPredict2Dialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_PumpWcEdit;
	SEdit* m_PumpKdEdit;
	SEdit* m_PumpK1Edit;
	SEdit* m_PumpK2Edit;
	SEdit* m_PumpK4Edit;
	SEdit* m_PumpK3Edit;
	SEdit* m_GasW0Edit;
	SEdit* m_GasWc2Edit;

public:
	int mine_id;
	double W; // �ⲿ����(����˹����W=W1+W2+W3)

private:
	void initDatas();
};
