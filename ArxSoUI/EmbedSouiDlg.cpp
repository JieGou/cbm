#include "stdafx.h"
#include "EmbedSouiDlg.h"

// EmbedSouiDlg �Ի���
IMPLEMENT_DYNAMIC(EmbedSouiDlg, DockBarChildDlg)

EmbedSouiDlg::EmbedSouiDlg(CWnd* pParent /*=NULL*/)
	: DockBarChildDlg(EmbedSouiDlg::IDD, pParent)
{
	m_mouseInWindow = TRUE;
	m_bTracking = FALSE;
}

EmbedSouiDlg::~EmbedSouiDlg()
{
}

void EmbedSouiDlg::DoDataExchange(CDataExchange* pDX)
{
	DockBarChildDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EmbedSouiDlg, DockBarChildDlg)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()


// EmbedSouiDlg ��Ϣ�������

BOOL EmbedSouiDlg::OnInitDialog()
{
	DockBarChildDlg::OnInitDialog();

	login_dlg.Create(GetSafeHwnd(), WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, NULL, 0,0,0,0);
	login_dlg.SendMessage(WM_INITDIALOG);
	//login_dlg.CenterWindow();
	login_dlg.ShowWindow(SW_SHOW);

	//SWindow& wnd = login_dlg;
	//CRect rect = wnd.GetWindowRect();
	//MoveWindow(&rect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL EmbedSouiDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_CHAR)
	{
		return login_dlg.SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	}
	else
	{
		return DockBarChildDlg::PreTranslateMessage(pMsg);
	}
}

void EmbedSouiDlg::OnCancel()
{
	DestroyWindow();
}

void EmbedSouiDlg::PostNcDestroy()
{
	DockBarChildDlg::PostNcDestroy();
	delete this;
}

void EmbedSouiDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE | TME_HOVER;//Ҫ��������Ϣ
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = 10;// ������˲��������޷�����mouseHover

		if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER��Ϣ�ɴ˺�������
		{
			m_bTracking = TRUE;   
		}
	}
	DockBarChildDlg::OnMouseMove(nFlags, point);
}

void EmbedSouiDlg::OnMouseLeave()
{
	m_bTracking = FALSE;
	m_mouseInWindow = FALSE;
	DockBarChildDlg::OnMouseLeave();
}

void EmbedSouiDlg::OnMouseHover(UINT nFlags, CPoint point)
{
	m_bTracking = FALSE;
	m_mouseInWindow = TRUE;
	DockBarChildDlg::OnMouseHover(nFlags, point);
}

BOOL EmbedSouiDlg::keepFocus()
{
	return m_mouseInWindow;
}