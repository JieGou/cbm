#pragma once

#include "Db.h"
#include "Row.h"
#include "Query.h"
#include "Utils.h"

namespace orm
{
    //��ʾ���ݿ���е�һ����¼
    //������Կ�����һ����ʽ��״�ṹ
    class DAO_DLLIMPEXP Record
    {
    public:
        //��������
        virtual ~Record();

        //��¡һ���µĶ���
        bool clone( RecordPtr ptr );

        //ִ��insert����
        bool save();
        //����idִ��delete����
        bool remove();

        //��������id(����fetch��ʾ�Ƿ���Ҫͨ��id�����ݿ���ȡ����)
        bool setID( int id, bool fetch = false );
        bool setID( const CString& id, bool fetch = false );
        //��ȡ����id
        int getID() const;
        CString getStringID() const;
        //��ȡ���ݿ����
        CString getTable() const;

        //�ж϶������½��Ļ���ͨ��select�õ���
        //�ò�������������ͨ��insert����update�ύ�����ݿ�
        void setNewlyRecord( bool isNewly );
        bool isNewlyRecord() const;

        //��/д�ֶ�(Ŀǰֻ֧��int��double��CString�������ͣ����������)
        void set( const CString& name, int v );
        void set( const CString& name, double v );
        void set( const CString& name, CString v );
        bool get( const CString& name, int& v ) const;
        bool get( const CString& name, double& v ) const;
        bool get( const CString& name, CString& v ) const;
        //��ȡ���ݲ��Զ�ת����string����(����ʹ��)
        CString get( const CString& name ) const;

        /** ����ļ������������ڲ�ʹ��. */
        //��row�ж�ȡ����(���ݿ�һ��row����һ����¼)
        bool fetchByRow( RowPtr& row );
    protected:
        Record( const CString& table );
        void map_field( const CString& name, int& v );
        void map_field( const CString& name, double& v );
        void map_field( const CString& name, CString& v );
        void map_foreign_key( const CString& name, RecordPtr& ptr, CreateFunc cf );
    private:
        //�ֶκ��������
        void attributes( KVMap& fields, bool all = false );
        bool setAttrib( const CString& name, const Attribute& attrib );
        void updateAttrib( const CString& name );
        bool isForeignKey( const CString& name ) const;
        bool isPrimaryKey( const CString& name ) const;
        bool setForeignKey( const CString& name, const CString& id );
        //����id�����ݿ������ȡ����
        //����һ���ݹ����,����������,��ʼ������ȡ���������
        bool fetchById( int id );
    private:
        DISALLOW_COPY_AND_ASSIGN( Record );
        class Row* row;
        class ForeignKey* fk;
        bool m_isNewlyRecord;
        CString m_table;
        int m_id;
    };
}

//ע���ֶ�(���������)
#define REG_ATTRIB(field_name, var_name) this->map_field(_T(#field_name), var_name)
//ע�����
#define REG_FOREGIN_KEY(field_name, var_name, create_func) this->map_foreign_key(_T(#field_name), var_name, create_func);
