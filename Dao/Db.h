#pragma once

#include "Row.h"

namespace orm
{
    //����ģʽ
    class DAO_API Db
    {
    public:
        //��̬����--��ȡʵ��ָ��
        static DbPrt Instance();

    public:
        virtual ~Db() {}
        virtual bool config( const CString& user, const CString& password, const CString& database, const CString& host = _T( "localhost" ), const CString& port = _T( "3306" ) ) = 0;
        virtual bool execute( const CString& sql ) = 0;
        virtual bool query( const CString& sql, RowSet& rs ) = 0;
        virtual int lastInsertId( const CString& table ) = 0;

    public:
        //����IDʹ�ñ�ǰ׺(Ĭ�ϲ�ʹ��)
        //���ʹ�ñ�ǰ׺,������id���ֶ���Ϊ: ��ǰ׺+�»���+id,����"cbm_mine_id"
        //�����ʹ�ñ�ǰ׺��������id���ֶ���Ϊ:id������"id"
        void enableTablePrefix( bool use = false )
        {
            m_useTablePrefix = use;
        }

        //��ȡ�̶�������ID��
        CString getPrimaryKeyName( const CString& table ) const
        {
            if( m_useTablePrefix )
            {
                //ȫ�����Сд
                return Utils::cstring_tolower( table + _T( "_" ) + KEY_ID );
            }
            else
            {
                return KEY_ID;
            }
        }
        CString getForeignKeyName( const CString& table ) const
        {
            //ȫ�����Сд
            return Utils::cstring_tolower( table + _T( "_" ) + KEY_ID );
        }
    protected:
        static DbPrt instance;
        Db() : m_useTablePrefix( false ) {}
    private:
        DISALLOW_COPY_AND_ASSIGN( Db );
        bool m_useTablePrefix;
    };

    //ȫ�ֺ���
    extern DAO_API DbPrt get_db();
}
