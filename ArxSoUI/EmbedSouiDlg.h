#pragma once

#include "DockBarChildDlg.h"
#include "LoginDlg.h"
#include "resource.h"

/**
* soui����Ƕ�뵽mfc���ڻ�Ի����еļ���Ҫ��:
  (1) soui��xml�����ļ���translucent����Ҫ����0(�м�!!!)
  ���磺
  <SOUI trCtx="dlg_login" title="��¼" width="350" height="190" margin="5,5,5,5" translucent="0" alpha="255">
  (2)������Ϣ�Ĵ����ת��
  ����: soui������Ϊmfc�Ӵ���,�����ǰ�һ������ʱ��,PreTranslateMessage��������˵�WM_CHAR��Ϣ,
        ����soui���ղ���WM_CHAR��Ϣ,ʹ��soui��edit�޷���������
  �ο�: �Ի���İ������� PreTranslateMessage��OnKeyDown��OnChar
         http://blog.csdn.net/wang_cong0214/article/details/8280324
  �������: ����PreTranslateMessage����,ת��WM_CHAR��Ϣ��soui����
*/
class EmbedSouiDlg : public DockBarChildDlg
{
	DECLARE_DYNAMIC(EmbedSouiDlg)

public:
	EmbedSouiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EmbedSouiDlg();

// �Ի�������
	enum { IDD = IDD_SOUI_EMBED_DLG };

	//�ӶԻ���(soui)
public:
	LoginDlg login_dlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	virtual void PostNcDestroy();
	//����ƶ���Ϣ
	afx_msg void OnMouseMove(UINT nFlags, ::CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, ::CPoint point);

	//�ο�:http://www.cnblogs.com/greatverve/archive/2013/02/06/TRACKMOUSEEVENT.html
	BOOL m_mouseInWindow;
	BOOL m_bTracking;
	virtual BOOL keepFocus();
};
