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

public:
	int region; // ����Ĳ���(���ĸ����������)
	int tech;   // �����Ĳ���(���ֳ�ɼ���,���Ǵ�1��ʼ,�����0��ʾû��ѡ��)
};
