// report.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "report.h"
#include "ReportHelper.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;
void jsonTest()
{
	//�ַ���
	const char* str = 
		"{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\","
		"\"born\":-100,\"died\":-44}";

	Json::Reader reader;
	Json::Value root;

	//���ַ����ж�ȡ����
	if(reader.parse(str,root))
	{
		string praenomen = root["praenomen"].asString();
		string nomen = root["nomen"].asString();
		string cognomen = root["cognomen"].asString();
		int born = root["born"].asInt();
		int died = root["died"].asInt();

		cout << praenomen + " " + nomen + " " + cognomen
			<< " was born in year " << born 
			<< ", died in year " << died << endl;
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		//wcout << argv[1] <<endl;
		//�ַ���
		const char* str = 
			"{\"tplPath\":\"E:\\\\test\\\\git\\\\cbm\\\\x64\\\\Debug\\\\Datas\\\\JL\\\\tpl\\\\tplBase.doc\",\"EPCMFD_Method\":\"��ǩ��xxx\",\"cognomen\":\"Caezar\",\"born\":-100,\"died\":-44}";

		//WordHelper rptHelper;
		//rptHelper.creat(str);
		//CString tplPath = _T("E:\\test\\git\\cbm\\x64\\Debug\\Datas\\JL\\tpl\\tplBase.doc");
		CString jsonPath = _T("E:\\test\\git\\cbm\\x64\\Debug\\Datas\\jsDatas.json");
		ReportHelper::CreatReport(jsonPath);
		jsonTest();
	}

	return nRetCode;
}

