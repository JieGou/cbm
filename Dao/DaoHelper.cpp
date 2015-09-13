#include "StdAfx.h"
#include "DaoHelper.h"
#include "IniFile.h"
#include "Db.h"
#include "Entity.h"
using namespace orm;
using namespace cbm;

#include <Util/HelperClass.h>

bool DaoHelper::ConfigureFromFile(const CString& cfgFile)
{
	CIniFile iniFile;
	if(FALSE == iniFile.SetPath( cfgFile )) return false;

	CString section = _T("mysql");
	CString host = iniFile.GetKeyValue(section, _T("host"));
	CString port = iniFile.GetKeyValue(section, _T("port"));
	CString username = iniFile.GetKeyValue(section, _T("username"));
	CString password = iniFile.GetKeyValue(section, _T("password"));
	CString database = iniFile.GetKeyValue(section, _T("database"));

	return DaoHelper::ConfigureDao(username, password, database, host, port);
}

bool DaoHelper::ConfigureDao( const CString& username, const CString& password, const CString& database, const CString& host/*=_T("localhost")*/, const CString& port/*=_T("3306")*/ )
{
    return Db::Instance()->config( username, password, database, host, port );
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
    //cout<<"��������:"<<region->name;

    MinePtr mine2( new Mine );
    mine->clone( mine2 );
    //cout<<"������:%s" <<mine2->name;
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

static int DifficultEval1( double decay_alpha )
{
	if( decay_alpha < 0.003 )
		return 1;
	else if( decay_alpha < 0.05 )
		return 2;
	else
		return 3;
}

static int DifficultEval2( double permeability_lambda )
{
	if( permeability_lambda > 10 )
		return 1;
	else if( permeability_lambda > 0.1 )
		return 2;
	else
		return 3;
}

static int DifficultEvalHelper( int k1, int k2 )
{
	static int ret[] = { 1, 4, 5, 4, 2, 6, 5, 6, 3 };
	if( k1 < 1 || k1 > 3 || k2 < 1 || k2 > 3 ) return 0;
	return ret[k1 * 3 + k2 - 4];
}

int DaoHelper::DifficultEval(CoalPtr coal)
{
	//�����������˥��ϵ�� �� ú��͸����ϵ����������
	int k1 = DifficultEval1( coal->decay_alpha );
	int k2 = DifficultEval2( coal->permeability_lambda );
	return DifficultEvalHelper( k1, k2 );
}

static CString PermeabilityString( double permeability_k )
{
	if( permeability_k < 5 )
		return _T( "����ú��" );
	else if( permeability_k < 20 )
		return _T( "����ú��" );
	else
		return _T( "����ú��" );
}

static CString EvalDifficultString( int eval )
{
	static CString ret[] =
	{
		_T( "���׳��" ),               // 1
		_T( "���Գ��" ),               // 2
		_T( "���ѳ��" ),               // 3
		_T( "���׳��~���Գ��" ),     // 4
		_T( "���׳��~���ѳ��" ),     // 5
		_T( "���Գ��~���ѳ��" )      // 6
	};
	if( eval < 1 || eval > 6 )
	{
		return _T( "NULL" );
	}
	else
	{
		return ret[eval - 1];
	}
}

CString DaoHelper::DifficultEvalString(cbm::CoalPtr coal)
{
	CString msg;
	msg.Format( _T( "��ú������:%s\\n" ), PermeabilityString( coal->permeability_k ) );
	msg.AppendFormat( _T( "��˹������׳̶�:%s" ), EvalDifficultString(coal->eval_difficult ));
	return msg;
}

double DaoHelper::MineGasReservesW1(int mine_id)
{
	//�������еĿɲ�ú��
	RecordPtrListPtr lists = FIND_MANY2( Coal, FKEY( Mine ), Utils::int_to_cstring( mine_id ), FIELD( minable ), _T( "1" ) );
	if( lists == 0 ) return 0;

	//����ɲ�ú�����˹����
	double S = 0;
	for( int i = 0; i < lists->size(); i++ )
	{
		CoalPtr coal = DYNAMIC_POINTER_CAST( Coal, lists->at( i ) );
		S += coal->res_a1 * coal->gas_x1;
	}
	return S;
}

double DaoHelper::MineGasReservesW2(int mine_id)
{
	//�������еĿɲ�ú��
	RecordPtrListPtr lists = FIND_MANY2( Coal, FKEY( Mine ), Utils::int_to_cstring( mine_id ), FIELD( minable ), _T( "0" ) );
	if( lists == 0 ) return 0;

	//����ɲ�ú�����˹����
	double S = 0;
	for( int i = 0; i < lists->size(); i++ )
	{
		CoalPtr coal = DYNAMIC_POINTER_CAST( Coal, lists->at( i ) );
		S += coal->res_a1 * coal->gas_x1;
	}
	return S;
}

double DaoHelper::WorkAreaGasFlow(WorkAreaPtr work_area, double K1)
{
	//�������еĻزɹ�����
	double S1 = 0;
	RecordPtrListPtr ws_lists = FIND_MANY( WorkSurf, FKEY( WorkArea ), work_area->getStringID() );
	if( ws_lists != 0 )
	{
		for( int i = 0; i < ws_lists->size(); i++ )
		{
			WorkSurfPtr ws = DYNAMIC_POINTER_CAST( WorkSurf, ws_lists->at( i ) );
			if( ws == 0 ) continue;

			double qr = ws->qr;
			double A = ws->a;
			S1 += A * qr;
		}
	}
	//�������еľ����
	double S2 = 0;
	RecordPtrListPtr tws_lists = FIND_MANY( DrillingSurf, FKEY( WorkArea ), work_area->getStringID() );
	if( tws_lists != 0 )
	{
		for( int i = 0; i < tws_lists->size(); i++ )
		{
			DrillingSurfPtr tws = DYNAMIC_POINTER_CAST( DrillingSurf, tws_lists->at( i ) );
			if( tws == 0 ) continue;

			double qr = tws->qa;
			S2 += qr;
		}
	}
	//����ƽ���ղ���
	double A0 = work_area->a;
	if( A0 <= 0 )
	{
		return -1;
	}
	else
	{
		return K1 * ( S1 + S2 ) / A0;
	}
}

double DaoHelper::MineGasFlow(MinePtr mine)
{
	//���Ҹÿ����еĲ���
	RecordPtrListPtr lists = DaoHelper::GetWorkAreas( mine->getID() );
	if( lists == 0 ) return 0;

	double S1 = 0, S2 = 0;
	for( int i = 0; i < lists->size(); i++ )
	{
		WorkAreaPtr work_area = DYNAMIC_POINTER_CAST( WorkArea, lists->at( i ) );
		double qr = work_area->qr;
		double A0 = work_area->a;
		S1 += qr * A0;
		S2 += A0;
	}
	if( S2 <= 0 )
	{
		return -1;
	}
	else
	{
		double K2 = mine->gas_k2;;
		//���㲢���¿󾮵���˹ӿ����
		return K2 * S1 / S2;
	}
}
