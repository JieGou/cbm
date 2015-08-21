#pragma once
#include "AcadSouiDialog.h"

class TechnologyDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	TechnologyDialog(BOOL bModal = FALSE);
	~TechnologyDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnTechnologyListboxSelChanged(SOUI::EventArgs *pEvt);
	void OnDocReadButtonClick();
	void OnVideoPlayButtonClick();
	void OnDocSelectButtonClick();
	void OnVideoSelectButtonClick();
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
		EVENT_NAME_HANDLER(_T("technology"), EVT_LB_SELCHANGED, OnTechnologyListboxSelChanged)
		EVENT_NAME_COMMAND(_T("doc_read"), OnDocReadButtonClick)
		EVENT_NAME_COMMAND(_T("video_play"), OnVideoPlayButtonClick)
		EVENT_NAME_COMMAND(_T("doc_select"), OnDocSelectButtonClick)
		EVENT_NAME_COMMAND(_T("video_select"), OnVideoSelectButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(TechnologyDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SListBox* m_TechnologyListbox;
	SCheckBox* m_IsKeyCheck;
	SEdit* m_DocEdit;
	SEdit* m_VideoEdit;
	SStatic* m_RegionLabel;

public:
	CString regionName; // ʾ������(�ⲿ����)

protected:
	virtual void OnDestroyWindow();

private:
	void fillTechnologyListBox();
};
