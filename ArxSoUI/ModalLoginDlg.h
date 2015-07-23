#pragma once

//ģ̬��¼�Ի���
class ModalLoginDlg : public SOUI::SHostDialog
{
public:
    ModalLoginDlg(void);
    ~ModalLoginDlg(void);
    
	//�ؼ���Ϣ����
protected:
	void OnLogin();
	void OnReg();

	//�˵���Ϣ����
protected:
	//����˵���Ϣ(�˵���һ��������xml�ļ���������ÿ���˵����һ��id��)
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	//������4����ť����Ϣ
protected:
	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();

	//������Ϣ����
protected:
	//�Ի����ʼ������
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	//����Aero��Ч
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//���ڽ��Թ���
	void OnShowWindow(BOOL bShow, UINT nStatus);
	//���ٴ��ڻ�Ի���
	void OnDestory();
	//���ڴ�С�仯
	void OnSize(UINT nType, SOUI::CSize size);
    EVENT_MAP_BEGIN()
		//��������4����ť��Ϣ(������id�ţ�Ҳ���������֣�����xml�ļ�ʵ�ʶ�������)
		EVENT_NAME_COMMAND(_T("btn_close"), OnClose)
		//EVENT_ID_COMMAND(1, OnClose)
		//EVENT_ID_COMMAND(2, OnMaximize)
		//EVENT_ID_COMMAND(3, OnRestore)
		//EVENT_ID_COMMAND(5, OnMinimize)
        EVENT_NAME_COMMAND(_T("btn_login"),OnLogin)
		EVENT_NAME_COMMAND(_T("btn_reg"),OnReg)
    EVENT_MAP_END()

	//HOST��Ϣ����Ӧ����ӳ���
	BEGIN_MSG_MAP_EX(ModalLoginDlg)
		MSG_WM_INITDIALOG(OnInitDialog)	
		MSG_WM_CREATE(OnCreate)
		MSG_WM_SHOWWINDOW(OnShowWindow)
		MSG_WM_DESTROY(OnDestory)
		MSG_WM_SIZE(OnSize)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(SOUI::SHostDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

private:
	bool m_bLayoutInited;/**<UI��ɲ��ֱ�־ */
};

