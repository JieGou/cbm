#pragma once
#include "AcadSouiDialog.h"

class RtfViewerDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	RtfViewerDialog(BOOL bModal = FALSE);
	~RtfViewerDialog(void);

	/** �ؼ���Ϣ���� */
protected:

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
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(RtfViewerDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SRichEdit* m_RtfViewerRichedit;

public:
	void setRtfRes(const CString& rtf_res);
	void setRtfFile(const CString& rtf_file);

private:
	CString m_rtf_res; // rtf��Դ(�ⲿָ��)
	CString m_rtf_file; // rtf�ļ�
	bool m_use_res;     // ʹ����Դ���Ǽ���rtf�ļ�(Ĭ��ʹ����Դ)
};
