#include "stdafx.h"
#include "helloworld.h"
#include "MySoUiLoader.h"
#include "SouiDialog.h"
//#include "SouiXmlName.h"

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

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	InitSouiEnviroment(hInstance);
	// ��ģ̬��ʽ����
	//StartFromSoui(_T("layout:main"), NULL, true);
	// �����Է�ģ̬��ʽ����
	StartFromSoui(_T("layout:main"), NULL, false);
	UnInitSouiEnviroment();

	return 0;
}