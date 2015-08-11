#pragma once

#include "Db.h"
#include "Row.h"
#include "Query.h"
#include "Utils.h"

namespace orm 
{
	class ARXDAO_DLLIMPEXP Record
	{
	public:
		//ִ��insert����
		bool save();
		//����idִ��delete����
		bool remove();
		//����id�����ݿ������ȡ����
		bool fetch();

		//��ȡ���ݿ����
		CString getTable() const;
		//��ȡid
		int getID() const;
		
		//��/д�ֶ�(Ŀǰֻ֧��int��double��CString��������)
		void set(const CString& name, int v);
		void set(const CString& name, double v);
		void set(const CString& name, CString v);
		bool get(const CString& name, int& v) const;
		bool get(const CString& name, double& v) const;
		bool get(const CString& name, CString& v) const;

		//��row�ж�ȡ����(���ݿ�һ��row����һ����¼,�ڲ�ʹ��)
		bool fetchByRow(RowPtr& row);
		//�ж϶������½��Ļ���ͨ��select�õ���(�ڲ�ʹ��)
		void setNewlyRecord(bool isNewly);
		bool isNewlyRecord() const;
		//�ֶκ��������(�ڲ�ʹ��)
		void attributes(KVMap& fields, bool all=false);
		bool setAttrib(const CString& name, const Attribute& attrib);
		bool setForeignKey(const CString& name, const CString& id);
		bool isForeignKey(const CString& name) const;
		virtual ~Record();
	protected:
		Record(const CString& table);
		void map_field(const CString& name, int& v);
		void map_field(const CString& name, double& v);
		void map_field(const CString& name, CString& v);
		void map_foreign_key(const CString& name, RecordPtr& ptr, CreateFunc cf);
		class Row* row;
		class ForeignKey* fk;
		bool m_isNewlyRecord;
		CString m_table;
	private:
		DISALLOW_COPY_AND_ASSIGN(Record);
	};
}

//ע���ֶ�(���������)
#define REG_ATTRIB(field_name, var_name) this->map_field(_T(#field_name), var_name)
//ע�����
#define REG_FOREGIN_KEY(field_name, var_name, create_func) this->map_foreign_key(_T(#field_name), var_name, create_func);
