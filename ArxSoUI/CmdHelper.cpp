#include "StdAfx.h"
#include "CmdHelper.h"

#include "SQLClientHelper.h"
#include "CbmClientHelper.h"
#include <WinHttpClient.h>
#include <ArxHelper/HelperClass.h>

#include <fstream>

void CmdHelper::PostJsonDatasToRpc()
{
	TCHAR strFileName[MAX_PATH];
	if(acedGetString(0, _T("��ָ�������ļ�����:"), strFileName) != RTNORM) return;

	std::ifstream infile(W2C(strFileName));
	if(!infile) return;

	//��Щ���������Ҫ���ݸ�cadһЩ����
	std::string input_datas = "{}";
	infile >> input_datas;

	//���������ɵ���Կ
	std::string secret_key = "#";
	infile >> secret_key;
	infile.close();

	acutPrintf(_T("\n1:%s\n2:%s"), C2W(input_datas), C2W(secret_key));
	if(secret_key == "#") return;

	// �ռ�����(����input_datas�����ݽ����ж�:input_datas��һ��json����)

	//����rpc���������л���
	std::string out_datas = "{'name':'dlj'}";
	CbmClientHelper::PostJsonDatasFromCAD(secret_key, input_datas, out_datas);
}

void CmdHelper::xxx()
{
	std::string json_data = CbmClientHelper::GetJsonDatasFromCAD("{}");
	//int ret = CbmClientHelper::VerifyMineAccount("dlj", "123");
	//acutPrintf(_T("\n��֤���:%d"), ret);	
	CbmClientHelper::SendCommandToCAD("regen");
}

void CmdHelper::TestWinHttpClient()
{
	// Set URL.
	WinHttpClient client(_T("http://localhost/tt/test.php"));

	// Send http request, a GET request by default.
	client.SendHttpRequest();
	string data = "title=����1&content=�������";
	client.SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());

	// The response header.
	CString httpResponseHeader = client.GetResponseHeader().c_str();
	// The response content.
	CString httpResponseContent = client.GetResponseContent().c_str();
}
