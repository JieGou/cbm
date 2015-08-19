#pragma once

#include "dlimexp.h"
#include "Entity.h"
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
	//验证用户名和密码
	static int VerifyMineAccount(const CString& username, const CString& pwd);
	//查询所有的基地
	static void GetAllMineBases(StringArray& bases);
	//查询基地的所有矿区
	static void GetAllMineRegions(const CString& baseName, StringArray& regions);
	//根据矿区反查基地
	static CString GetBaeByRegion(const CString& regionName);
	//查询示范矿区的虚拟矿井
	static MinePtr GetSampleMine(const CString& regionName);
	//查询矿井的所有煤层名称
	static void GetCoalNames(const CString& mineName, StringArray& coals);
	//查询矿井的所有煤层id
	static void GetCoalIds(const CString& mineName, IntArray& coals);
};
