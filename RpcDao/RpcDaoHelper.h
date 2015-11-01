#pragma once

#include "dlimexp.h"
#include "gen-cpp/cbm_types.h"

#include <vector>
#include <string>
typedef std::vector<std::string> StringArray;
typedef std::vector<int> IntArray;
typedef std::vector<double> DoubleArray;

class RPC_DAO_API RpcDaoHelper
{
public:
	static void QuitServer();

    //��ʼ��ʾ������(����Ŀ󾮺�ú��)
    static void InitSampleRegion();
    //��ѯ�ѵ�¼�û���id
    static int GetOnlineAccountId();
    //��ȡ�ѵ�¼�û��Ŀ�����
    //static cbm::MinePtr GetOnlineMine();
    //��֤�û���������
    static int VerifyMineAccount( const std::string& username, const std::string& pwd );
    //��ѯ���еĻ���
    static void GetAllMineBases( StringArray& bases );
    //��ѯ�������еĿ���
    static void GetAllMineRegions( const std::string& baseName, StringArray& regions );
    //���ݿ����������
    static std::string GetBaseByRegion( const std::string& regionName );
    //��ѯʾ�������������
    //static cbm::MinePtr GetSampleMine( const std::string& regionName );
    //��ѯʾ������������ú��
    //static cbm::CoalPtr GetSampleCoal( const std::string& regionName );
    //��ѯ�����е�ú������
    static void GetCoalNames( int mine_id, StringArray& coals );
    //��ѯ�����е�ú��id
    static void GetCoalIds( int mine_id, IntArray& coals );
    //��ѯ�����еĲ���
    //static orm::RecordPtrListPtr GetWorkAreas( int mine_id );
    //��ѯ�����еĹ�����
    //static orm::RecordPtrListPtr GetWorkSurfs( int mine_id );
    //��ѯ�����еľ����
    //static orm::RecordPtrListPtr GetDrillingSurfs( int mine_id );

    //������׳̶�����
    //static int DifficultEval( cbm::CoalPtr coal );
    //static std::string DifficultEvalString( cbm::CoalPtr coal );
    //�ɲ�ú����˹ӿ��������W1
    //static double MineGasReservesW1( int mine_id );
    //���ɲ�ú����˹ӿ��������W2
    //static double MineGasReservesW2( int mine_id );
    //�����������˹ӿ����
    //static double WorkAreaGasFlow( cbm::WorkAreaPtr work_area, double K1 );
    //����󾮵���˹ӿ����
    //static double MineGasFlow( cbm::MinePtr mine );
    //�����濪�ɲ���˹ӿ����
    //static double WorkSurfGasFlow1( cbm::CoalPtr coal, cbm::WorkAreaPtr work_area, cbm::WorkSurfPtr work_surf );
    //�������ڽ�����˹ӿ����
    //static double WorkSurfGasFlow2( cbm::CoalPtr coal, cbm::WorkAreaPtr work_area, cbm::WorkSurfPtr work_surf );
    //�������˹ӿ����
    //static void DrillingSurfGasFlow( cbm::CoalPtr coal, cbm::DrillingSurfPtr drilling_surf, cbm::TunnelPtr tunnel );
};
