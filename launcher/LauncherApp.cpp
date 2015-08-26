#include "stdafx.h"
#include "LauncherApp.h"
#include "MySoUiLoader.h"
#include "SouiDialog.h"
#include "SouiXmlName.h"

BEGIN_MESSAGE_MAP(CLauncherApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CLauncherApp::CLauncherApp()
{
}

// Ψһ��һ�� ClauncherApp ����
CLauncherApp theApp;

static void InitSouiEnviroment(HINSTANCE hInstance)
{
	new MySoUiLoader(hInstance);
	SoUILoader::getSingletonPtr()->init();
}

static void UnInitSouiEnviroment()
{
	delete SoUILoader::getSingletonPtr();
}

static void StartFromSoui()
{
	//SouiDialog�༰��������Ĺ��캯��������һ������,����ָ��xml��Դ������
	//��������Դ�����Ƕ�̬��ȡ��
	//�û�ʹ�õ�ʱ����Դ�SouiDialog������,����������Ĺ��캯����ָ��xml��Դ�ļ���
	//��ϸ�÷��ο�ArxSoUI��Ŀ�еĶԻ�����
	SouiDialog dlg(RES_NAME, TRUE);
	dlg.Run(GetActiveWindow());
	//MFC�����������Ϣѭ����,����Ҫ��getApp()->Run()������Ϣѭ��
	//ֻ�д����win32�������Ҫ��getApp()->Run()������Ϣѭ��
	//SoUILoader::getSingletonPtr()->getApp()->Run(dlg->m_hWnd);
}

//static void StartFromMFC(CWnd*& m_pMainWnd)
//{
//	//����mfc���Ի���
//	Cmfc_testDlg dlg;
//	m_pMainWnd = &dlg;
//	//����ģ̬��Ϣѭ��,ֱ���رնԻ���
//	INT_PTR nResponse = dlg.DoModal();
//	if (nResponse == IDOK)
//	{
//		// TODO: �ڴ˷��ô����ʱ��
//		//  ��ȷ�������رնԻ���Ĵ���
//	}
//	else if (nResponse == IDCANCEL)
//	{
//		// TODO: �ڴ˷��ô����ʱ��
//		//  ��ȡ�������رնԻ���Ĵ���
//	}
//}

// ClauncherApp ��ʼ��
BOOL CLauncherApp::InitInstance()
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

	//��ʼ��soui����
	InitSouiEnviroment(m_hInstance);

	//(1)��soui����
	StartFromSoui();
	//(2)���ߴ�mfc����
	//StartFromMFC(m_pMainWnd);

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
