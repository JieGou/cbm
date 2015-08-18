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
	//id���Ƶ�һ����
	#define KEY_ID _T("id")

	//��ȡ��table������id����
	//ע:����id�����ַ�Ϊ2�����,�б�ǰ׺���ޱ�ǰ׺
	//    ���Ե�Db�������øò���(�μ�Db::enableTablePrefix����)
	#define PKEY(table) get_db()->getPrimaryKeyName(table)
	//��ȡ���id����
	//ע:һ���������������ֶ��ǣ�����+�»���+id������: mine_id
	#define FKEY(table) get_db()->getForeignKeyName(table)
	#define FKEY2(Klass) FKEY(Klass::Table())
	//�ֶ�����(���ֶ�����д��)
	//ע:һ���������ĳ�Ա�����ͱ���ֶ���������ͬ��)
	#define FIELD(name) _T(#name)

	//3�������ڼ�query����д��
	#define FIND_BY_ID(Klass, id) Query::find<Klass>(id)
	#define FIND_ONE(Klass, field, value) QueryPtr(Query::from<Klass>())->where(field, value)->find_one<Klass>()
	#define FIND_MANY(Klass, field, value) QueryPtr(Query::from<Klass>())->where(field, value)->find_many<Klass>()

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
