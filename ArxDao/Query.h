#pragma once

#include "QueryHelper.h"

namespace orm
{
    class ARXDAO_DLLIMPEXP Query
    {
	public:
		template<typename Klass>		
		static Query* from()
		{
			return Query::from(Klass::Table());
		}
		template<typename Klass>
		static RecordPtr find(int id)
		{
			return orm::helper::find<Klass>(id);
		}
	public:
		template<typename Klass>
		RecordPtr find_one()
		{
			return orm::helper::find_one<Klass>(this);
		}
		template<typename Klass>
		RecordPtr find_many()
		{
			return orm::helper::find_many<Klass>(this);
		}
    public:
		static Query* from( const CString& table );
		~Query();
        Query* where( const CString& col, const CString& value );
        Query* where_equal( const CString& col, const CString& value );
        Query* where_not_equal( const CString& col, const CString& value );
        Query* where_like( const CString& col, const CString& value );
        Query* where_not_like( const CString& col, const CString& value );
        Query* where_gt( const CString& col, const CString& value );
        Query* where_gte( const CString& col, const CString& value );
        Query* where_lt( const CString& col, const CString& value );
        Query* where_lte( const CString& col, const CString& value );
        Query* where_raw( const CString& query );

        Query* select( const CString& col );

		Query* limit( int n_limit );

        Query* order_by_expr( const CString& expr );
        Query* order_by_asc( const CString& col );
        Query* order_by_desc( const CString& col );

		Query* find_min( const CString& col );
		Query* find_max( const CString& col );
		Query* find_avg( const CString& col );
		Query* find_sum( const CString& col );
		
		void set(const CString &key, const CString &value);
		CString& get(const CString &key);	
		CString& operator[](const CString &key);

		CString build_select();
		CString build_update();
		CString build_delete();
		CString build_insert();

    protected:
        Query();

        void set_table( const CString& table );
        void set_limit( int n_limit );

        void add_result_column( const CString& col );
        void add_condition(const CString& col, const CString& op, const CString& value );
        void add_condition( const CString& condition );
        void add_order_by( const CString& col, const CString& order );
        void add_group_by( const CString& col );

        CString build_result_columns();
        CString build_conditions();
        CString build_field_keys();
        CString build_field_values();
        CString build_changes();
        CString build_order_by();
        CString build_group_by();

        CString build_from();
        CString build_into();

        CString build_limit();

		void set_with_no_dirt( const CString& key, const CString& value );
        void dirt_field( const CString& field_name );
		void clean_dirty_fields();

    protected:
        CString table;
        std::vector<CString> conditions;
        std::vector<CString> results;
        std::vector<CString> dirty_fields;
        std::vector<CString> order_by;
        std::vector<CString> group_by;
        std::map<CString, CString> fields;
        int n_limit;
	private:
		DISALLOW_COPY_AND_ASSIGN(Query);
    };
};