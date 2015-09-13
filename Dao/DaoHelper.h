#pragma once

#include "dlimexp.h"
#include "Entity.h"

#include <vector>
typedef std::vector<CString> StringArray;
typedef std::vector<int> IntArray;
typedef std::vector<double> DoubleArray;

class DAO_DLLIMPEXP DaoHelper
{
public:
	static bool ConfigureFromFile(const CString& cfgFile);
	static bool ConfigureDao(const CString& username, const CString& password, const CString& database, const CString& host=_T("localhost"), const CString& port=_T("3306"));
	static void TestDao();

	//��ʼ��ʾ������(����Ŀ󾮺�ú��)
	static void InitSampleRegion();
	//��ѯ�ѵ�¼�û���id
	static int GetOnlineAccountId();
	//��ȡ�ѵ�¼�û��Ŀ�����
	static cbm::MinePtr GetOnlineMine();
	//��֤�û���������
	static int VerifyMineAccount(const CString& username, const CString& pwd);
	//��ѯ���еĻ���
	static void GetAllMineBases(StringArray& bases);
	//��ѯ�������еĿ���
	static void GetAllMineRegions(const CString& baseName, StringArray& regions);
	//���ݿ����������
	static CString GetBaeByRegion(const CString& regionName);
	//��ѯʾ�������������
	static cbm::MinePtr GetSampleMine(const CString& regionName);
	//��ѯʾ������������ú��
	static cbm::CoalPtr GetSampleCoal(const CString& regionName);
	//��ѯ�����е�ú������
	static void GetCoalNames(int mine_id, StringArray& coals);
	//��ѯ�����е�ú��id
	static void GetCoalIds(int mine_id, IntArray& coals);
	//��ѯ�����еĲ���
	static orm::RecordPtrListPtr GetWorkAreas(int mine_id);
	//��ѯ�����еĹ�����
	static orm::RecordPtrListPtr GetWorkSurfs(int mine_id);
	//��ѯ�����еľ����
	static orm::RecordPtrListPtr GetDrillingSurfs(int mine_id);

	static int DifficultEval(cbm::CoalPtr coal);
	static CString DifficultEvalString(cbm::CoalPtr coal);
};
