#pragma once

//�������Ƿ����
#include <tlhelp32.h> 
//���� -1 û���ҵ�
//����  0 �ҵ�����
//����  1 �ҵ������������һ��

enum pathType
{
	CURRENT_USER = 0, //�õ���Ŀ¼C:\Users\hd\AppData\Roaming\Autodesk\AutoCAD 2010\R18.0\chs\Support
	LOCAL_MACHINE = 1, //�õ���Ŀ¼��CAD�İ�װĿ¼
};

class LaucherHelper
{
	public:
		static int FindProcess(TCHAR* appName);
		static BOOL IsAutoCADExist();
		static CString GetCADPath();
		static BOOL copyCadFile();
		static BOOL recoverCadFile();
		static BOOL writeReg();
		static BOOL deleteReg();
};
