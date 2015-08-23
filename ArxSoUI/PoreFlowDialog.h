#pragma once
#include "AcadSouiDialog.h"

class PoreFlowDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	PoreFlowDialog(BOOL bModal = FALSE);
	~PoreFlowDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
	void OnKCaclButtonClick();
	void OnBCaclButtonClick();
	void OnDeltaPCaclButtonClick();
	void OnDeltaTCaclButtonClick();
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
		EVENT_NAME_COMMAND(_T("K_cacl"), OnKCaclButtonClick)
		EVENT_NAME_COMMAND(_T("b_cacl"), OnBCaclButtonClick)
		EVENT_NAME_COMMAND(_T("delta_p_cacl"), OnDeltaPCaclButtonClick)
		EVENT_NAME_COMMAND(_T("delta_T_cacl"), OnDeltaTCaclButtonClick)
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(PoreFlowDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_KEdit;
	SEdit* m_BEdit;
	SEdit* m_DeltaPEdit;
	SEdit* m_DeltaTEdit;
	SEdit* m_DhEdit;
	SEdit* m_XEdit;
	SEdit* m_QHunEdit;
	SEdit* m_QChunEdit;
	SEdit* m_TEdit;

protected:
	virtual void OnDestroyWindow();

private:
	void initDatas();
	int pore_flow_id; // �ڲ�ʹ��
};
