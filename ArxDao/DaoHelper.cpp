#include "StdAfx.h"
#include "DaoHelper.h"

#include "Db.h"
using namespace orm;

#include "Entity.h"
using namespace cbm;

#include <ArxHelper/HelperClass.h>
#include <Util/HelperClass.h>

bool DaoHelper::ConfigureFromFile(const CString& cfgFile)
{
	std::string strfile = W2C((LPCTSTR)cfgFile);

	////�������ļ��ж�ȡ����
	//ConfigParser setting(strfile);
	//std::string host="localhost",username="root",password="", database="cbm";
	//int port = 3306;
	////������url
	//host = setting.Read("host", host);
	////�˿�
	//port = setting.Read("port", port);
	////�û���
	//username = setting.Read("username", username);
	////����
	//password = setting.Read("password", password);
	
	return false;
}

bool DaoHelper::ConfigureDao( const CString& user, const CString& password, const CString& database, const CString& host/*=_T("localhost")*/, const CString& port/*=_T("3306")*/ )
{
    return Db::Instance()->config( user, password, database, host, port );
}

void DaoHelper::TestDao()
{
    MinePtr mine( new Mine );
    //mine->username = _T("dlj");
    //mine->password = _T("123");
    mine->name = _T( "��ú����" );
    mine->region = Query::FindById<Region>( 1 );
    mine->set( FIELD( name ), _T( "xxxú���Ź�˾" ) );
    mine->region->set( FIELD( name ), _T( "��������" ) );
    mine->region->setID( _T( "2" ), true );
    mine->save();

    RegionPtr region = DYNAMIC_POINTER_CAST( Region, mine->region );
    acutPrintf( _T( "��������:%s" ), region->name );

    MinePtr mine2( new Mine );
    mine->clone( mine2 );
    acutPrintf( _T( "\n������:%s" ), mine2->name );
}

int DaoHelper::VerifyMineAccount( const CString& username, const CString& pwd )
{
    QueryPtr query( Query::From<Account>() );
    RecordPtr account = query->where( FIELD( username ), username )
                        ->find_one<Account>();
    if( account == 0 )
        return 0; // �û���������
    else if( account->get( FIELD( password ) ) != pwd )
        return 1; // �������
    else
        return 2; // �û�����ע��
}

void DaoHelper::GetAllMineBases( StringArray& bases )
{
    QueryPtr query( Query::From<Base>() );
    RecordPtrListPtr lists = query->find_many<Base>();
    if( lists == 0 ) return;

    for( int i = 0; i < lists->size(); i++ )
    {
        bases.push_back( lists->at( i )->get( FIELD( name ) ) );
    }
}

void DaoHelper::GetAllMineRegions( const CString& baseName, StringArray& regions )
{
    QueryPtr query( Query::From<Base>() );
    RecordPtr base = query->where( FIELD( name ), baseName )
                     ->find_one<Base>();
    if( base == 0 ) return;

    query.reset( Query::From<Region>() );
    RecordPtrListPtr lists = query->where( FKEY( Base ), base->getStringID() )
                             ->find_many<Region>();
    if( lists == 0 ) return;

    for( int i = 0; i < lists->size(); i++ )
    {
        regions.push_back( lists->at( i )->get( FIELD( name ) ) );
    }
}

CString DaoHelper::GetBaeByRegion( const CString& regionName )
{
    RegionPtr region = FIND_ONE( Region, FIELD( name ), regionName );
    if( region == 0 ) return _T( "" );

    return region->base->get( FIELD( name ) );
}

MinePtr DaoHelper::GetSampleMine( const CString& regionName )
{
    RecordPtr region = FIND_ONE( Region, FIELD( name ), regionName );
    if( region == 0 ) return MinePtr();

    //����id��ѯ��Ӧ�Ŀ�
    return FIND_ONE( Mine, FKEY( Region ), region->getStringID() );
}

CoalPtr DaoHelper::GetSampleCoal( const CString& regionName )
{
    MinePtr mine = DaoHelper::GetSampleMine( regionName );
    if( mine == 0 ) return CoalPtr();

    return FIND_ONE( Coal, FKEY( Mine ), mine->getStringID() );
}

void DaoHelper::GetCoalNames( int mine_id, StringArray& coals )
{
    RecordPtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    RecordPtrListPtr lists = FIND_MANY( Coal, FKEY( Mine ), mine->getStringID() );
    if( lists == 0 ) return;

    for( int i = 0; i < lists->size(); i++ )
    {
        coals.push_back( lists->at( i )->get( FIELD( name ) ) );
    }
}

void DaoHelper::GetCoalIds( int mine_id, IntArray& coals )
{
    RecordPtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    RecordPtrListPtr lists = FIND_MANY( Coal, FKEY( Mine ), mine->getStringID() );
    if( lists == 0 ) return;

    for( int i = 0; i < lists->size(); i++ )
    {
        coals.push_back( lists->at( i )->getID() );
    }
}

int DaoHelper::GetOnlineAccountId()
{
    SysInfoPtr sys_info = FIND_FIRST( SysInfo );
    if( sys_info == 0 ) return 0;

    return sys_info->account->getID();
}

MinePtr DaoHelper::GetOnlineMine()
{
    int account_id = DaoHelper::GetOnlineAccountId();
    if( account_id == 0 ) return MinePtr();

    return FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
}

RecordPtrListPtr DaoHelper::GetWorkAreas( int mine_id )
{
    //���ҿ����е�ú��
    IntArray ids;
    DaoHelper::GetCoalIds( mine_id, ids );

    RecordPtrListPtr lists( new RecordPtrList );
    for( int i = 0; i < ids.size(); i++ )
    {
        //����ú���ϲ������еĲ���
        RecordPtrListPtr wa_lists = FIND_MANY( WorkArea, FKEY( Coal ), Utils::int_to_cstring( ids[i] ) );
        if( wa_lists == 0 ) continue;;

        for( int j = 0; j < wa_lists->size(); j++ )
        {
            lists->push_back( wa_lists->at( j ) );
        }
    }
    if( lists->empty() ) lists.reset();
    return lists;
}

RecordPtrListPtr DaoHelper::GetWorkSurfs( int mine_id )
{
    //��ѯ���еĲ���
    RecordPtrListPtr work_areas = DaoHelper::GetWorkAreas( mine_id );
    if( work_areas == 0 ) return RecordPtrListPtr();

    RecordPtrListPtr lists( new RecordPtrList );
    for( int i = 0; i < work_areas->size(); i++ )
    {
        //��ѯÿ�������ϵĻزɹ�����
        RecordPtrListPtr ws_lists = FIND_MANY( WorkSurf, FKEY( WorkArea ), work_areas->at( i )->getStringID() );
        if( ws_lists == 0 ) continue;;

        for( int j = 0; j < ws_lists->size(); j++ )
        {
            lists->push_back( ws_lists->at( j ) );
        }
    }
    if( lists->empty() ) lists.reset();
    return lists;
}

RecordPtrListPtr DaoHelper::GetDrillingSurfs( int mine_id )
{
    //��ѯ���еĲ���
    RecordPtrListPtr work_areas = DaoHelper::GetWorkAreas( mine_id );
    if( work_areas == 0 ) return RecordPtrListPtr();

    RecordPtrListPtr lists( new RecordPtrList );
    for( int i = 0; i < work_areas->size(); i++ )
    {
        //��ѯÿ�������ϵľ��������
        RecordPtrListPtr tws_lists = FIND_MANY( DrillingSurf, FKEY( WorkArea ), work_areas->at( i )->getStringID() );
        if( tws_lists == 0 ) continue;;

        for( int j = 0; j < tws_lists->size(); j++ )
        {
            lists->push_back( tws_lists->at( j ) );
        }
    }
    if( lists->empty() ) lists.reset();
    return lists;
}

//��ʼ��ʾ������������󾮺�����ú��
static void InitSampleMine( int region_id, int account_id, const CString& name )
{
    MinePtr mine = FIND_ONE2( Mine, FKEY( Region ), Utils::int_to_cstring( region_id ), FKEY( Account ), Utils::int_to_cstring( account_id ) );
    if( mine == 0 )
    {
        CString mineName;
        mineName.Format( _T( "ʾ��������-%s" ), name );
        //������
        mine.reset( new Mine );
        mine->name = mineName;
        mine->region = FIND_BY_ID( Region, region_id );
        mine->account = FIND_BY_ID( Account, account_id );
        mine->save();

        CString coalName;
        coalName.Format( _T( "ʾ������ú��-%s" ), name );
        //����ú��
        CoalPtr coal( new Coal );
        coal->mine = mine;
        coal->name = coalName;
        coal->save();
    }
}

void DaoHelper::InitSampleRegion()
{
    //���ҹ���Ա�ʻ�
    AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
    if( admin == 0 )
    {
        admin.reset( new Account );
        admin->username = _T( "admin" );
        admin->password = _T( "123" );
        admin->comment = _T( "��������Ա�˻�" );
        if( !admin->save() ) return;
    }

    //��������ʾ������
    RegionPtr jincheng = FIND_ONE( Region, FIELD( name ), _T( "����" ) );
    if( jincheng == 0 ) return;
    RegionPtr lianghuai = FIND_ONE( Region, FIELD( name ), _T( "����" ) );
    if( lianghuai == 0 ) return;
    RegionPtr songzao = FIND_ONE( Region, FIELD( name ), _T( "����" ) );
    if( songzao == 0 ) return;

    //����id���γ�ʼ��ʾ������������
    InitSampleMine( jincheng->getID(), admin->getID(), _T( "����" ) );
    InitSampleMine( lianghuai->getID(), admin->getID(), _T( "����" ) );
    InitSampleMine( songzao->getID(), admin->getID(), _T( "����" ) );
}
