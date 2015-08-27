#include "stdafx.h"
#include "mfc_test.h"
#include "mfc_testDlg.h"
#include "MySoUiLoader.h"
#include "SouiDialog.h"
#include "SouiXmlName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cmfc_testApp
BEGIN_MESSAGE_MAP(Cmfc_testApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cmfc_testApp ����

Cmfc_testApp::Cmfc_testApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cmfc_testApp ����

Cmfc_testApp theApp;


static void InitSouiEnviroment(HINSTANCE hInstance)
{
	new MySoUiLoader(hInstance);
	SoUILoader::getSingletonPtr()->init();
}

static void UnInitSouiEnviroment()
{
	delete SoUILoader::getSingletonPtr();
}

static void StartFromSoui(LPCTSTR pszXmlName, HWND hParent=NULL, bool bModal=true)
{
	if(bModal)
	{
		SouiDialog dlg(pszXmlName, TRUE);
		dlg.SetWindowTitle(_T("�ı���,�������!"));
		dlg.Run(hParent);
	}
	else
	{
		SouiDialog* dlg = new SouiDialog(pszXmlName, FALSE);
		dlg->SetWindowTitle(_T("�ı���,�������!"));
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

static void StartFromMFC(CWnd*& m_pMainWnd)
{
	//����mfc���Ի���
	Cmfc_testDlg dlg;
	m_pMainWnd = &dlg;
	//����ģ̬��Ϣѭ��,ֱ���رնԻ���
	INT_PTR nResponse = dlg.DoModal();
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

BOOL Cmfc_testApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();
	AfxEnableControlContainer();
	AfxInitRichEdit2();
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	InitSouiEnviroment(m_hInstance);

	if(IDYES == MessageBox(NULL, _T("������soui���� ���� MFC�Ի���???"), _T("ѯ��"), MB_YESNO))
	{
		// ��ģ̬��ʽ����
	 	//StartFromSoui(RES_NAME, NULL, true);
		
		// �����Է�ģ̬��ʽ����
		StartFromSoui(RES_NAME, NULL, false);
	}
	else
	{
		StartFromMFC(m_pMainWnd);
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int Cmfc_testApp::ExitInstance()
{
	UnInitSouiEnviroment();
	return CWinAppEx::ExitInstance();
}
