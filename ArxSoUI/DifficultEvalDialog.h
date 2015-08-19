#pragma once
#include "AcadSouiDialog.h"

class DifficultEvalDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	DifficultEvalDialog(BOOL bModal = FALSE);
	~DifficultEvalDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnCancelButtonClick();
	void OnEvalButtonClick();
	void OnEvalProofButtonClick();

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
		EVENT_NAME_COMMAND(_T("cancel"), OnCancelButtonClick)
		EVENT_NAME_COMMAND(_T("eval"), OnEvalButtonClick)
		EVENT_NAME_COMMAND(_T("eval_proof"), OnEvalProofButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(DifficultEvalDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_PermeabilityKEdit;
	SEdit* m_DecayAlphaEdit;
	SEdit* m_PermeabilityLambdaEdit;
};
