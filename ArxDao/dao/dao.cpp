#include "stdafx.h"
#include "dao.h"
#include <mysql/soci-mysql.h>

DaoPrt Dao::instance;

bool Dao::Configure(const string& url, const string& user, const string& password, const string& dataBase)
{
	bool ret = true;
	try
	{
		DaoPrt dao = Dao::GetInstance(url, user, password, dataBase);
		//���mysql������������
		dao->executeQuery("set names 'gbk';");
		//dao->executeQuery("set character_set_client=utf8;");
		//dao->executeQuery("set character_set_results=utf8;");
		//dao->executeQuery("set character_set_connection=utf8;");
	}
	catch(soci::soci_error const & e)
	{
		ret = false;
		//cerr << "MySQL error: " << e.err_num_<< " " << e.what() << endl;
		LOG_DEBUG_FMT(_T("�������ݿ��쳣:%s"), EncodeHelper::ANSIToUnicode(e.what()));
	}
	catch (std::exception const & e)
	{
		ret = false;
		//cerr << "Some other error: " << e.what() << endl;
		LOG_DEBUG_FMT(_T("�����쳣:%s"), EncodeHelper::ANSIToUnicode(e.what()));
	}
	return ret;
}

Dao::Dao(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
{
	sql.open(soci::mysql, "host="+host+" db="+database+" user="+user+" password=\'"+password+"\'");
}

DaoPrt Dao::GetInstance(const std::string& url, const std::string& user, const std::string& password, const std::string& database)
{
    if( ! instance ) {
		if(!url.empty() && !user.empty()) {
            instance.reset(new Dao(url, user, password, database));
		}
		else {
            throw std::runtime_error("Passe a URL, Usuario e Senha na primeira vez que chamar: Dao::getInstance");
		}
    }
    return instance;
}

Dao::~Dao()
{
}

soci::session* Dao::getConnection()
{
    return &sql;
}

ResultSet Dao::executeQuery(const std::string &sql)
{
	soci::session* connection = getConnection();
	//ִ��һ��ʲôҲ�ò�����sql���(ǰ��cbm_dummy��������!!!)
	//�����������д���!!!
    ResultSet rs = (connection->prepare << "select * from cbm_dummy where 0");
    try
    {
		LOG_DEBUG_FMT(_T("ִ��executeQuery����쳣:%s"), EncodeHelper::ANSIToUnicode(sql));

		ResultSet temp_rs = (connection->prepare << sql);
        rs = temp_rs;
    }
    catch(soci::soci_error const & e)
    {
		//cerr << "MySQL error: " << e.err_num_<< " " << e.what() << endl;
		LOG_DEBUG_FMT(_T("ִ��sql��ѯ����쳣:%s"), EncodeHelper::ANSIToUnicode(e.what()));
    }
	catch (std::exception const & e)
	{
		//cerr << "Some other error: " << e.what() << endl;
		LOG_DEBUG_FMT(_T("�����쳣:%s"), EncodeHelper::ANSIToUnicode(e.what()));
	}
    return rs;
}

void Dao::executeUpdate(const std::string& sql)
{
    try
    {
		LOG_DEBUG_FMT(_T("ִ��executeUpdate����쳣:%s"), EncodeHelper::ANSIToUnicode(sql));
        soci::session* connection = getConnection();

        *connection << sql;
        connection->commit();
    }
    catch(soci::soci_error const & e)
    {
		//cerr << "MySQL error: " << e.err_num_<< " " << e.what() << endl;
		LOG_DEBUG_FMT(_T("ִ��sql��������쳣:%s"), EncodeHelper::ANSIToUnicode(e.what()));
    }
	catch (std::exception const & e)
	{
		//cerr << "Some other error: " << e.what() << endl;
		LOG_DEBUG_FMT(_T("�����쳣:%s"), EncodeHelper::ANSIToUnicode(e.what()));
	}
}
