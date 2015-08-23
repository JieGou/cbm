#pragma once
#include "AcadSouiDialog.h"

class PoreSizeDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	PoreSizeDialog(BOOL bModal = FALSE);
	~PoreSizeDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnSaveButtonClick();
	void OnHintButtonClick();
	void OnCaclButtonClick();
	void OnHint2ButtonClick();

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
		EVENT_NAME_COMMAND(_T("hint"), OnHintButtonClick)
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		EVENT_NAME_COMMAND(_T("hint2"), OnHint2ButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(PoreSizeDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	virtual void OnDestroyWindow();

protected:
	SEdit* m_QEdit;
	SEdit* m_DeltaEdit;
	SEdit* m_VEdit;
	SEdit* m_SigmaEdit;
	SEdit* m_PEdit;
	SEdit* m_DEdit;

private:
	void initDatas();
	int pore_size_id; // �ڲ�ʹ��
};
