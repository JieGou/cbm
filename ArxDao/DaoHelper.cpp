#include "StdAfx.h"
#include "DaoHelper.h"

#include "entity/entities.h"
#include "model/models.h"
using namespace cbm;

#include "../ArxHelper/HelperClass.h"

void DaoHelper::ConfigureDao(const string& url, const string& user, const string& password, const string& dataBase)
{
	if(!Dao::Configure(url, user, password, dataBase))
	{
		AfxMessageBox(_T("����MySQL���ݿ�ʧ�ܣ�����ϵ������Ա!!!"));
	}
}

void DaoHelper::TestDao()
{
	Mine mine;
	mine.setUsername("dlj");
	mine.setPassword("123");
	//std::string xx = EncodeHelper::ANSIToUtf8("test��ú����");
	mine.setMineName(EncodeHelper::UnicodeToANSI(_T("test��ú����")));

	MineDao dao;
	dao.insert(mine);
}
