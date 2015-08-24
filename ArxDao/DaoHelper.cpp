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
	mine->region = Query::FindById<Region>(1);
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
	QueryPtr query(Query::From<Account>());
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
	QueryPtr query(Query::From<Base>());
	RecordPtrListPtr lists = query->find_many<Base>();
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		bases.push_back(lists->at(i)->get(FIELD(name)));
	}
}

void DaoHelper::GetAllMineRegions(const CString& baseName, StringArray& regions)
{
	QueryPtr query(Query::From<Base>());
	RecordPtr base = query->where(FIELD(name), baseName)
		                  ->find_one<Base>();
	if(base == 0) return;

	query.reset(Query::From<Region>());
	RecordPtrListPtr lists = query->where(FKEY(Base), base->getStringID())
		                          ->find_many<Region>();
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		regions.push_back(lists->at(i)->get(FIELD(name)));
	}
}

CString DaoHelper::GetBaeByRegion(const CString& regionName)
{
	RegionPtr region = FIND_ONE(Region, FIELD(name), regionName);
	if(region == 0) return _T("");

	return region->base->get(FIELD(name));
}

MinePtr DaoHelper::GetSampleMine(const CString& regionName)
{
	RecordPtr region = FIND_ONE(Region, FIELD(name), regionName);
	if(region == 0) return MinePtr();

	//����id��ѯ��Ӧ�Ŀ�
	return FIND_ONE(Mine, FKEY(Region), region->getStringID());
}

void DaoHelper::GetCoalNames(const CString& mineName, StringArray& coals)
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

void DaoHelper::GetCoalIds(const CString& mineName, IntArray& coals)
{
	RecordPtr mine = FIND_ONE(Mine, FIELD(name), mineName);
	if(mine == 0) return;

	RecordPtrListPtr lists = FIND_MANY(Coal, FKEY(Mine), mine->getStringID());
	if(lists == 0) return;

	for(int i=0;i<lists->size();i++)
	{
		coals.push_back(lists->at(i)->getID());
	}
}

int DaoHelper::GetOnlineAccountId()
{
	SysInfoPtr sys_info = FIND_FIRST(SysInfo);
	if(sys_info == 0) return 0;

	return sys_info->account->getID();
}

MinePtr DaoHelper::GetOnlineMine()
{
	int account_id = DaoHelper::GetOnlineAccountId();
	if(account_id == 0) return MinePtr();

	return FIND_ONE(Mine, FKEY(Account), Utils::int_to_cstring(account_id));
}

RecordPtrListPtr DaoHelper::GetWorkAreas(const CString& mineName)
{
	//���ҿ󾮵�����ú��
	IntArray ids;
	DaoHelper::GetCoalIds(mineName, ids);

	RecordPtrListPtr lists(new RecordPtrList);
	for(int i=0;i<ids.size();i++)
	{
		//����ú���ϲ��õ����в���
		RecordPtrListPtr wa_lists = FIND_MANY(WorkArea, FKEY(Coal), Utils::int_to_cstring(ids[i]));
		if(wa_lists == 0) continue;;

		for(int j=0;j<wa_lists->size();j++)
		{
			lists->push_back(wa_lists->at(j));
		}
	}
	if(lists->empty()) lists.reset();
	return lists;
}

RecordPtrListPtr DaoHelper::GetWorkSurfs(const CString& mineName)
{
	//��ѯ���еĲ���
	RecordPtrListPtr work_areas = DaoHelper::GetWorkAreas(mineName);
	if(work_areas == 0) return RecordPtrListPtr();

	RecordPtrListPtr lists(new RecordPtrList);
	for(int i=0;i<work_areas->size();i++)
	{
		//��ѯÿ�������ϵĻزɹ�����
		RecordPtrListPtr ws_lists = FIND_MANY(WorkSurf, FKEY(WorkArea), work_areas->at(i)->getStringID());
		if(ws_lists == 0) continue;;

		for(int j=0;j<ws_lists->size();j++)
		{
			lists->push_back(ws_lists->at(j));
		}
	}
	if(lists->empty()) lists.reset();
	return lists;
}

RecordPtrListPtr DaoHelper::GetDrillingSurfs(const CString& mineName)
{
	//��ѯ���еĲ���
	RecordPtrListPtr work_areas = DaoHelper::GetWorkAreas(mineName);
	if(work_areas == 0) return RecordPtrListPtr();

	RecordPtrListPtr lists(new RecordPtrList);
	for(int i=0;i<work_areas->size();i++)
	{
		//��ѯÿ�������ϵľ��������
		RecordPtrListPtr tws_lists = FIND_MANY(DrillingSurf, FKEY(WorkArea), work_areas->at(i)->getStringID());
		if(tws_lists == 0) continue;;

		for(int j=0;j<tws_lists->size();j++)
		{
			lists->push_back(tws_lists->at(j));
		}
	}
	if(lists->empty()) lists.reset();
	return lists;
}
