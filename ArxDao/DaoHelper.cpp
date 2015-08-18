#include "StdAfx.h"
#include "DaoHelper.h"

#include "Db.h"
using namespace orm;

#include "Entity.h"
using namespace cbm;

#include <ArxHelper/HelperClass.h>

void DaoHelper::ConfigureDao(const CString& user, const CString& password, const CString& database, const CString& host/*=_T("localhost")*/, const CString& port/*=_T("3306")*/)
{
	if(!Db::Instance()->config(user, password, database, host, port))
	{
		AfxMessageBox(_T("����MySQL���ݿ�ʧ�ܣ�����ϵ������Ա!!!"));
	}
}

void DaoHelper::TestDao()
{
	MinePtr mine(new Mine);
	//mine->username = _T("dlj");
	//mine->password = _T("123");
	mine->name = _T("��ú����");
	mine->region = Query::find<Region>(1);
	mine->set(FIELD(name), _T("xxxú���Ź�˾"));
	mine->region->set(FIELD(name), _T("��������"));
	mine->region->setID(_T("2"), true);
	mine->save();

	RegionPtr region = DYNAMIC_POINTER_CAST(Region, mine->region);
	acutPrintf(_T("��������:%s"), region->name);

	MinePtr mine2(new Mine);
	mine->clone(mine2);
	acutPrintf(_T("\n������:%s"), mine2->name);
}

int DaoHelper::VerifyMineAccount(const CString& username, const CString& pwd)
{
	QueryPtr query(Query::from<Account>());
	RecordPtr account = query->where(FIELD(username), username)
		                  ->find_one<Account>();
	if(account == 0) 
		return 0; // �û���������
	else if(account->get(FIELD(password)) != pwd) 
		return 1; // �������
	else
		return 2; // �û�����ע��
}

void DaoHelper::GetAllMineBases(StringArray& bases)
{
	QueryPtr query(Query::from<Base>());
	RecordPtrListPtr lists = query->find_many<Base>();
	for(int i=0;i<lists->size();i++)
	{
		bases.push_back(lists->at(i)->get(FIELD(name)));
	}
}

void DaoHelper::GetAllMineRegions(const CString& baseName, StringArray& regions)
{
	QueryPtr query(Query::from<Base>());
	RecordPtr base = query->where(FIELD(name), baseName)
		                  ->find_one<Base>();
	if(base == 0) return;

	query.reset(Query::from<Region>());
	RecordPtrListPtr lists = query->where(FKEY(Base), base->getStringID())
		                          ->find_many<Region>();
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		regions.push_back(lists->at(i)->get(FIELD(name)));
	}
}

MinePtr DaoHelper::GetSampleMine(const CString& regionName)
{
	RecordPtr region = FIND_ONE(Region, FIELD(name), regionName);
	if(region == 0) return MinePtr();

	//����id��ѯ��Ӧ�Ŀ�
	RecordPtr ptr = FIND_ONE(Mine, FKEY(Region), region->getStringID());
	if(ptr == 0) return MinePtr();

	return DYNAMIC_POINTER_CAST(Mine, ptr);
}

void DaoHelper::GetCoals(const CString& mineName, StringArray& coals)
{
	RecordPtr mine = FIND_ONE(Mine, FIELD(name), mineName);
	if(mine == 0) return;

	RecordPtrListPtr lists = FIND_MANY(Coal, FKEY(Mine), mine->getStringID());
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		coals.push_back(lists->at(i)->get(FIELD(name)));
	}
}
