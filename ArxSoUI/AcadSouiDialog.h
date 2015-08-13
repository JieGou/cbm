#pragma once

/**
 * soui�Ի����װ��.
 * �÷�:
	(1)��ģ̬�Ի���(����new������ᵼ���ڴ����)
    HWND hWnd = getWindowHandle();  // ����Ҫָ����Ч�ĸ����ھ��
	LoginDlg* dlg = new LoginDlg(FALSE);
	dlg->Run(hWnd);
	
	(2)ģ̬�Ի���(������þֲ�����,��Ҫnew)
	HWND hWnd = getWindowHandle();  // ����Ҫָ����Ч�ĸ����ھ��
	LoginDlg dlg(TRUE);
	dlg.Run(hWnd);
*/
class AcadSouiDialog : public SOUI::SHostDialog
{
public:
	//���캯��
	//bModal����ָ����ģ̬�Ի����Ƿ�ģ̬�Ի���
	AcadSouiDialog(LPCTSTR pszXmlName, BOOL bModal = FALSE);
	//��������
	virtual ~AcadSouiDialog(void);
	//���жԻ���
	//ע:��ģ̬�Ի���ķ���ֵû������,���Ժ���
	INT_PTR Run(HWND hParent=NULL);

	//ģ�¶Ի����OK��Cancel��ť����
protected:
	void OnOK();
	void OnCancel();

	/** ������Ϣ */
protected:
	//�Ի����ʼ������
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	//ʵ�ִ��ڵĶ�������Ч��(��С���Ĺ���)
	//ע:ֻ��ģ̬�Ի���ž߱����Ч��
	void OnShowWindow(BOOL bShow, UINT nStatus);
	//����Aero��Ч(Ĭ�ϲ�ʹ��,���Ҫʹ�ø�����,��ȡ��������OnCreate��صĴ���ע��)
	//int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//��ģ̬���ڵ����ٴ���
	//�ο�1:http://bbs.csdn.net/topics/350048650
	//�ο�2:http://blog.csdn.net/candyliuxj/article/details/6736032
	//ע1:souiû��PostNcDestory�麯��,��OnFinalMessage�麯�����!!!
	//ע2:�����ӦWM_NCDESTORY��Ϣ,�ڸ���Ϣ��delete this,�ᵼ���ڴ����!!!
	virtual void OnFinalMessage(HWND hWnd);
	//���ڹر���Ϣ
	void OnClose();
	//���ڴ�Сλ�ñ仯(���/��С/��ԭ��3����ťҪͬ���仯�ߴ�)
	void OnSize(UINT nType, ::CSize size);

	/** CAD������Ϣ */
protected:
	//CAD������Ϣ����
	LRESULT OnAcadKeepFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//����ƶ���Ϣ(�����ж�����Ƿ��ڴ�����)
	//�ο�:http://www.cnblogs.com/greatverve/archive/2013/02/06/TRACKMOUSEEVENT.html
	void OnMouseMove(UINT nFlags, ::CPoint point);
	void OnMouseHover(UINT nFlags, ::CPoint point);
	void OnMouseLeave();

	/** ������4����ť��Ϣ */
protected:
	//void OnClose(); //�ʹ�����ϢWM_CLOSE��Ӧ��������!
	void OnMaximize();
	void OnRestore();
	void OnMinimize();

	/** ������Ϣ */
protected:
	 void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	 /** ��ͨ���� */
protected:
	BOOL isLayoutInited() const;

	/** ��Ա���� */
private:
	//�Ƿ�ģ̬�Ի���(Ĭ�Ϸ�ģ̬FALSE)
	BOOL m_bModal;
	//UI��ɲ��ֱ�־
	BOOL m_bLayoutInited;
	//����Ƿ��ڴ�����
	BOOL m_mouseInWindow;
	//�Ƿ���Ҫ׷������ƶ���Ϣ
	BOOL m_bTracking;

	/** �ؼ���Ϣӳ��� */
	EVENT_MAP_BEGIN()
		//��������4����ť��Ϣ(xml�����ļ��б�������4������!!!)
		EVENT_NAME_COMMAND(_T("btn_close"), OnClose)
		EVENT_NAME_COMMAND(_T("btn_max"), OnMaximize)
		EVENT_NAME_COMMAND(_T("btn_restore"), OnRestore)
		EVENT_NAME_COMMAND(_T("btn_min"), OnMinimize)
	EVENT_MAP_END()

	/** ������Ϣӳ��� */
	BEGIN_MSG_MAP_EX(AcadSouiDialog)
		MESSAGE_HANDLER(WM_ACAD_KEEPFOCUS,OnAcadKeepFocus)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SHOWWINDOW(OnShowWindow)
		MSG_WM_CHAR(OnChar)
		//MSG_WM_CREATE(OnCreate)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(SOUI::SHostDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};
