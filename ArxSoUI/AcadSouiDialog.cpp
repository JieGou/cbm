#include "stdafx.h"
#include "AcadSouiDialog.h"

using namespace SOUI;

//��OnCreate��Ϣ����������AeroЧ����Ҫdwmapi��֧��
//#include <dwmapi.h>
//#pragma comment(lib,"dwmapi.lib")

AcadSouiDialog::AcadSouiDialog(LPCTSTR pszXmlName, BOOL bModal) 
	: SHostDialog(pszXmlName), 
	  m_mouseInWindow(TRUE), 
	  m_bTracking(FALSE),
	  m_bLayoutInited(FALSE),
	  m_bModal(bModal)
{
}

AcadSouiDialog::~AcadSouiDialog(void)
{
}

INT_PTR AcadSouiDialog::Run(HWND hParent)
{
	if(m_bModal)
	{
		return this->DoModal(hParent);
	}
	else
	{
		Create(hParent,0,0,0,0);
		SendMessage(WM_INITDIALOG);
		//CenterWindow();
		return ShowWindow(SW_SHOWNORMAL);
	}
}

void AcadSouiDialog::OnOK()
{
	m_bTracking = FALSE;
	if(m_bModal)
	{
		SHostDialog::OnOK();
	}
	else
	{
		DestroyWindow();
	}
}

void AcadSouiDialog::OnCancel()
{
	m_bTracking = FALSE;
	if(m_bModal)
	{
		SHostDialog::OnCancel();
	}
	else
	{
		DestroyWindow();
	}
}

LRESULT AcadSouiDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	m_bLayoutInited = TRUE;
	return FALSE;
}

void AcadSouiDialog::OnFinalMessage( HWND hWnd )
{
	SHostDialog::OnFinalMessage(hWnd);
	if(!m_bModal)
	{
		//һ���ģ̬�ĶԻ�����new������,��ģ̬���Ǿֲ�����
		delete this;
	}
	
}

static void SetVisible_Helper(SWindow* wnd, BOOL bVisible)
{
	if(wnd != 0)
	{
		wnd->SetVisible(bVisible);
	}
}

void AcadSouiDialog::OnSize(UINT nType, ::CSize size)
{
	SetMsgHandled(FALSE);   //��һ�к���Ҫ����֤��Ϣ�������ݸ�AcadSouiDialog������ȻҲ������AcadSouiDialog::OnSize(nType,size);���棬��������ʹ�õķ������򵥣�ͨ��
	if(!m_bLayoutInited) return;

	/**
	 *���if������ڴ�����󻯺ͻ�ԭ��ʱ��,��������2����ť����ʾ״̬
	 �÷���Ҫ���������4����ť�ù涨��name��������
		<imgbtn name="btn_close" skin="_skin.sys.btn.close"    pos="-45,0" tip="close" animate="1"/>
		<imgbtn name="btn_max" skin="_skin.sys.btn.maximize"  pos="-83,0" animate="1" />
		<imgbtn name="btn_restore" skin="_skin.sys.btn.restore"  pos="-83,0" show="0" animate="1" />
		<imgbtn name="btn_min" skin="_skin.sys.btn.minimize" pos="-121,0" animate="1" />
	*/
	if(nType==SIZE_MAXIMIZED)
	{
		SetVisible_Helper(FindChildByName(_T("btn_restore")), TRUE);
		SetVisible_Helper(FindChildByName(_T("btn_max")), FALSE);
	}
	else if(nType==SIZE_RESTORED)
	{
		SetVisible_Helper(FindChildByName(_T("btn_restore")), FALSE);
		SetVisible_Helper(FindChildByName(_T("btn_max")), TRUE);
	}
}

void AcadSouiDialog::OnShowWindow( BOOL bShow, UINT nStatus )
{
	SetMsgHandled(FALSE);
	if(m_bModal && bShow)
	{
		//���д�����ʵ�ִ��ڵĶ�������Ч������С���Ĺ��̣�
		AnimateHostWindow(200, AW_CENTER);
	}
}

//int AcadSouiDialog::OnCreate( LPCREATESTRUCT lpCreateStruct )
//{
//	//����AeroЧ��
//	//MARGINS mar = {5,5,30,5};
//	//DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
//
//	SetMsgHandled(FALSE);
//	return 0;
//}

void AcadSouiDialog::OnClose()
{
	m_bTracking = FALSE;
	AcadSouiDialog::OnCancel();
}

void AcadSouiDialog::OnMaximize()
{
	GetNative()->SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
}

void AcadSouiDialog::OnRestore()
{
	GetNative()->SendMessage(WM_SYSCOMMAND,SC_RESTORE);
}

void AcadSouiDialog::OnMinimize()
{
	GetNative()->SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
}

//- Needed for modeless dialogs to keep focus.
//- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT AcadSouiDialog::OnAcadKeepFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//��ģ̬������,�������ڴ�����(m_mouseInWindow=TRUE),����Ϊ����Ӧ�û�ȡ����
	SetMsgHandled(TRUE);
	return m_bModal?TRUE:m_mouseInWindow;
}

void AcadSouiDialog::OnMouseMove(UINT nFlags, ::CPoint point)
{
	SetMsgHandled(FALSE);
	if(m_bModal) return;

	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE | TME_HOVER;//Ҫ��������Ϣ
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = 50;// ������˲��������޷�����mouseHover

		if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER��Ϣ�ɴ˺�������
		{
			m_bTracking = TRUE;   
		}
	}
}

void AcadSouiDialog::OnMouseLeave()
{
	SetMsgHandled(FALSE);
	if(m_bModal) return;

	m_bTracking = FALSE;
	m_mouseInWindow = FALSE;
}

void AcadSouiDialog::OnMouseHover(UINT nFlags, ::CPoint point)
{
	SetMsgHandled(FALSE);
	if(m_bModal) return;

	m_bTracking = FALSE;
	m_mouseInWindow = TRUE;
}
