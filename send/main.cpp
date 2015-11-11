#include "stdafx.h"
#include "CADHelper.h"
#include "ThreadHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		if(argc > 1)
		{
			//���͵�cad
			CString cmd;
			for(int i=1;i<argc;i++)
			{
				cmd.AppendFormat(_T("%s"), argv[i]);
				if(i < argc-1)
				{
					cmd.AppendFormat(_T(" "));
				}
			}
			CADHelper::SendCommandToAutoCAD(cmd);
		}
	}

	return nRetCode;
}
