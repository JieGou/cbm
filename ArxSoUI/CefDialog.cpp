// CefDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CefDialog.h"
#include "CefLaoder.h"

// CefDialog �Ի���

IMPLEMENT_DYNAMIC(CefDialog, CDialog)

CefDialog::CefDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CefDialog::IDD, pParent)
{

}

CefDialog::~CefDialog()
{
}

void CefDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CefDialog, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CefDialog ��Ϣ�������

void CefDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//TODO: �ڴ˴������Ϣ����������
	//���⣺�������ڴ�С��ʱ�������������ű仯��С��
	//�ο�1��http://blog.csdn.net/mushao999/article/details/37606189
	//	CefRefPtr<CefBrowser> browser = CefLaoder::getSingletonPtr()->getApp()->GetBrowser();
	//	if(browser)
	//	{
	//		CefWindowHandle hwnd = browser->GetWindowHandle();
	//		::MoveWindow(hwnd,100,100,800,800, true); 
	//	}
	//}
	//�ο�2��http://www.heycode.com/a13696.html
	//CWnd* cefwindow= FindWindowEx(this->GetSafeHwnd(),NULL,L"CefBrowserWindow",NULL);
	//cefwindow->MoveWindow(0,0,cx,cy);
}

BOOL CefDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	::CRect rt;
	GetWindowRect(&rt);
	CefLaoder::getSingletonPtr()->createWindow(this->GetSafeHwnd(), rt);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
