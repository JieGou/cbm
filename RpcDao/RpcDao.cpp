// RpcDao.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "RpcDao.h"


// ���ǵ���������һ��ʾ��
RPCDAO_API int nRpcDao=0;

// ���ǵ���������һ��ʾ����
RPCDAO_API int fnRpcDao(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� RpcDao.h
CRpcDao::CRpcDao()
{
	return;
}
