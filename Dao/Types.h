#pragma once

#include "dlimexp.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <functional>

#include <boost/shared_ptr.hpp>
using namespace boost;

#ifndef DISALLOW_COPY_AND_ASSIGN

//��--���ÿ������캯���͸�ֵ���������
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	TypeName& operator=(const TypeName&)

#endif

//share_ptr����ָ��ת��
#define DYNAMIC_POINTER_CAST(DeriveClass, ptrBase) boost::dynamic_pointer_cast<DeriveClass>(ptrBase)
#define STATIC_POINTER_CAST(Class, ptr) boost::static_pointer_cast<Class>(ptr)

namespace orm
{
	#define BOOL_2_INT(condition) condition?1:0

	//id���Ƶ�һ����
	#define KEY_ID _T("id")

	//��ȡ��table������id����(table��һ���ַ���)
	//ע:����id�����ַ�Ϊ2�����,�б�ǰ׺���ޱ�ǰ׺
	//    ���Ե�Db�������øò���(�μ�Db::enableTablePrefix����)
	#define PKEY(table) get_db()->getPrimaryKeyName(table)
	//��ȡ���id����(table��һ���ַ���)
	//ע:һ���������������ֶ��ǣ�����+�»���+id������: mine_id
	#define _FKEY(table) get_db()->getForeignKeyName(table)
	//Klass��һ����������
	#define FKEY(Klass) _FKEY(Klass::Table())
	//�ֶ�����(���ֶ�����д��, name��һ����������)
	//ע:һ���������ĳ�Ա�����ͱ���ֶ���������ͬ��)
	#define FIELD(name) _T(#name)

	//4�������ڼ�query����д��(Klass��������,field��value�����ַ���, id��һ������)
	#define FIND_BY_ID(Klass, id) DYNAMIC_POINTER_CAST(Klass, Query::FindById<Klass>(id))
	#define FIND_FIRST(Klass) DYNAMIC_POINTER_CAST(Klass, Query::FindFirst<Klass>())
	#define FIND_ALL(Klass) Query::FindAll<Klass>()
	#define FIND_ONE(Klass, field, value) DYNAMIC_POINTER_CAST(Klass, QueryPtr(Query::From<Klass>())->where(field, value)->find_one<Klass>())
	#define FIND_MANY(Klass, field, value) QueryPtr(Query::From<Klass>())->where(field, value)->find_many<Klass>()

	#define FIND_ONE2(Klass, field1, value1, field2, value2) DYNAMIC_POINTER_CAST(Klass, QueryPtr(Query::From<Klass>())->where(field1, value1)->where(field2, value2)->find_one<Klass>())
	#define FIND_MANY2(Klass, field1, value1, field2, value2) QueryPtr(Query::From<Klass>())->where(field1, value1)->where(field2, value2)->find_many<Klass>()
	#define DELETE_MANY(Klass, field, value) get_db()->execute(QueryPtr(Query::From<Klass>())->where(field, value)->build_delete())

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
