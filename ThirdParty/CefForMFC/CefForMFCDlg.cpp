#include "stdafx.h"
#include "CefForMFC.h"
#include "CefForMFCDlg.h"

#include "ClientApp.h"
#include "ClientHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CefForMFCDlg::CefForMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CefForMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CefForMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CefForMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CefForMFCDlg ��Ϣ�������
BOOL CefForMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CefMainArgs main_args(AfxGetApp()->m_hInstance);  

	CefRefPtr<ClientApp> app(new ClientApp);  

	int exit_code = CefExecuteProcess(main_args, app.get(), NULL);  
	if (exit_code >= 0){  
		exit(exit_code);  
	}  

	CefSettings settings;  
	CefSettingsTraits::init(&settings);  
	settings.multi_threaded_message_loop = true;  
	CefInitialize(main_args, settings, app.get(), NULL);  

	CefWindowInfo info;
	RECT rect;  
	this->GetClientRect(&rect);  
	info.SetAsChild(this->GetSafeHwnd(), rect);  

	CefBrowserSettings b_settings;  
	CefRefPtr<CefClient> client(new ClientHandler);  

	std::string url = "https://www.baidu.com";  
	CefBrowserHost::CreateBrowser(info, client.get(), url, b_settings, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CefForMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND,reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CefForMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CefForMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

int CefForMFCDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

void CefForMFCDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// CefShutdown();
	CDialog::OnClose();
}

void CefForMFCDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	// TODO: �ڴ˴������Ϣ����������
	// CefShutdown();
}
