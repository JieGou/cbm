#pragma once

#include "dlimexp.h"
#include "Entity.h"
using namespace orm;
using namespace cbm;

#include <vector>
typedef std::vector<CString> StringArray;
typedef std::vector<int> IntArray;

class ARXDAO_DLLIMPEXP DaoHelper
{
public:
	static void ConfigureDao(const CString& user, const CString& password, const CString& database, const CString& host=_T("localhost"), const CString& port=_T("3306"));
	static void TestDao();

	static int GetOnlineAccountId();
	static MinePtr GetOnlineMine();
	//��֤�û���������
	static int VerifyMineAccount(const CString& username, const CString& pwd);
	//��ѯ���еĻ���
	static void GetAllMineBases(StringArray& bases);
	//��ѯ���ص����п���
	static void GetAllMineRegions(const CString& baseName, StringArray& regions);
	//���ݿ����������
	static CString GetBaeByRegion(const CString& regionName);
	//��ѯʾ�������������
	static MinePtr GetSampleMine(const CString& regionName);
	//��ѯ�󾮵�����ú������
	static void GetCoalNames(const CString& mineName, StringArray& coals);
	//��ѯ�󾮵�����ú��id
	static void GetCoalIds(const CString& mineName, IntArray& coals);
	//��ѯ�󾮵����в���
	static RecordPtrListPtr GetWorkAreas(const CString& mineName);
};
