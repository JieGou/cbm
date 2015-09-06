#pragma once
#include "AcadSouiDialog.h"

class GasDesignQuestionDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	GasDesignQuestionDialog(BOOL bModal = FALSE);
	~GasDesignQuestionDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnTechnologyListboxSelChanged(SOUI::EventArgs *pEvt);
	void OnGoButtonClick();
	void OnDesignComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnNewDesignButtonClick();
	void OnDelDesignButtonClick();

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
		EVENT_NAME_HANDLER(_T("technology"), EVT_LB_SELCHANGED, OnTechnologyListboxSelChanged)
		EVENT_NAME_COMMAND(_T("go"), OnGoButtonClick)
		EVENT_NAME_HANDLER(_T("design"), EVT_CB_SELCHANGE, OnDesignComboxSelChanged)
		EVENT_NAME_COMMAND(_T("new_design"), OnNewDesignButtonClick)
		EVENT_NAME_COMMAND(_T("del_design"), OnDelDesignButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(GasDesignQuestionDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SListBox* m_TechnologyListbox;
	SComboBox* m_DesignCombox;

public:
	int coal_id; // ú��id
	int region;  // ����Ĳ���(��ʾ���ĸ����������,�����桢����桢�ɿ���???)
	int tech_id; // �����Ĳ���

protected:
	virtual void OnDestroyWindow();

private:
	void fillDatas();
};
