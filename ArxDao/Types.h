#pragma once

#include "dlimexp.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <functional>

#include <boost/shared_ptr.hpp>
using namespace boost;

//��--���ÿ������캯���͸�ֵ���������
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	TypeName& operator=(const TypeName&)

//share_ptr����ָ��ת��
#define DYNAMIC_POINTER_CAST(DeriveClass, ptrBase) boost::dynamic_pointer_cast<DeriveClass>(ptrBase)
#define STATIC_POINTER_CAST(Class, ptr) boost::static_pointer_cast<Class>(ptr)

namespace orm
{
	//����id��һ����
	#define PRIMARY_KEY_ID _T("id")

	//��ȡ��table������id����
	#define PRIMARY_KEY_NAME(table) get_db()->getPrimaryKeyName(table)

	class Record;
	typedef shared_ptr<Record> RecordPtr;
	typedef std::vector<RecordPtr> RecordPtrList;
	typedef shared_ptr<RecordPtrList> RecordPtrListPtr;

	class Query;
	typedef shared_ptr<Query> QueryPtr;

	//����ָ�붨��
	typedef RecordPtr (*CreateFunc)();

	class Attribute;
	typedef std::map<CString, Attribute> KVMap;

	class Row;
	typedef shared_ptr<Row> RowPtr;
	typedef std::vector<RowPtr> RowSet;

	class Db;
	typedef shared_ptr<Db> DbPrt;
}
