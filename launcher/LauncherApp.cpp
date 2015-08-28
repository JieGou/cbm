#include "stdafx.h"
#include "LauncherApp.h"
#include "MySoUiLoader.h"
#include "SouiDialog.h"
#include "SouiXmlName.h"

BEGIN_MESSAGE_MAP( CLauncherApp, CWinAppEx )
    ON_COMMAND( ID_HELP, &CWinApp::OnHelp )
END_MESSAGE_MAP()

CLauncherApp::CLauncherApp()
{
}

// Ψһ��һ�� ClauncherApp ����
CLauncherApp theApp;

static void InitSouiEnviroment( HINSTANCE hInstance )
{
    new MySoUiLoader( hInstance );
    SoUILoader::getSingletonPtr()->init();
}

static void UnInitSouiEnviroment()
{
    delete SoUILoader::getSingletonPtr();
}

static void StartFromSoui(SouiDialog* dlg, HWND hParent=NULL)
{
	//dlg->SetWindowTitle(_T("�ı���,�������!"));
	if(dlg->isModal() == TRUE)
	{
		dlg->Run(hParent);
	}
	else
	{
		dlg->Run(hParent);
		//������Ϊ0��һ�㶼��������
		if(hParent == NULL)
		{
			//ֻ�������ڲ���Ҫ��getApp()->Run()������Ϣѭ��
			//MFC��InitInstance()����ִ�е�ʱ��,��ʱ��û����Ϣѭ��,���Ҫ��ʾ������,��ô��Ҫ�����˹�������Ϣѭ��
			//ͬ��,win32�����WinMain������������Ҳ����Ҫ�Ⱥ�MFC�����������Ϣѭ����,����Ҫ��getApp()->Run()������Ϣѭ��
			SoUILoader::getSingletonPtr()->getApp()->Run(dlg->m_hWnd);
		}
	}
}

static void StartFromMFC(CDialog* dlg)
{
	//����MFC������
	AfxGetApp()->m_pMainWnd = dlg;
	//����ģ̬��Ϣѭ��,ֱ���رնԻ���
	INT_PTR nResponse = dlg->DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
}

// ClauncherApp ��ʼ��
BOOL CLauncherApp::InitInstance()
{
    // ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
    // ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
    //����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof( InitCtrls );
    // ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
    // �����ؼ��ࡣ
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx( &InitCtrls );
    CWinAppEx::InitInstance();
    AfxEnableControlContainer();
    AfxInitRichEdit2();
    SetRegistryKey( _T( "Ӧ�ó��������ɵı���Ӧ�ó���" ) );

    //��ʼ��soui����
    InitSouiEnviroment( m_hInstance );

	//(1)��soui����
	if(1)
	{
		//��ģ̬��ʽ����
		SouiDialog dlg(_T("layout:main"), TRUE);
		StartFromSoui(&dlg, NULL);
	}
	else
	{
		// �����Է�ģ̬��ʽ����
		SouiDialog* dlg = new SouiDialog(_T("layout:main"), FALSE);
		StartFromSoui(dlg, NULL);
	}
    //(2)���ߴ�mfc����
	//Cmfc_testDlg dlg;
	//StartFromMFC(&dlg);

    // ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
    //  ����������Ӧ�ó������Ϣ�á�
    return FALSE;
}

int CLauncherApp::ExitInstance()
{
    //�˳�soui����
    UnInitSouiEnviroment();
    return CWinAppEx::ExitInstance();
}
