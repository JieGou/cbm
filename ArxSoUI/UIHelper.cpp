#include "StdAfx.h"
#include "UIHelper.h"

#include <ArxHelper/HelperClass.h>
#include <Util/HelperClass.h>

#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

#include "MySoUiLoader.h"
#include "DemoDialog.h"
#include "LoginDialog.h"
#include "SampleManageDialog.h"
#include "MineDialog.h"
#include "KeyParamDialog.h"
#include "PolicyDialog.h"
#include "MainDialog.h"
using namespace SOUI;

void UIHelper::InitAllData()
{
	//��ʼ����������(�����ʵ䡢��չ����appname��)
	SystemHelper::Start();
	//��ȡ�ֶ�
    CString appDir = ArxUtilHelper::GetAppPathDir( _hdllInstance );
    FieldHelper::InitDataField( ArxUtilHelper::BuildPath( appDir, _T( "Datas\\ú�������-�ֶ�-ͼԪ����.txt" ) ) );
	//��������
	acdbHostApplicationServices()->workingDatabase()->loadLineTypeFile(_T("JIS_02_0.7"), _T("acadiso.lin"));
}

void UIHelper::InitSouiEnviroment()
{
    LOG_TRACE( _T( "��ʼ��soui����..." ) );
    new MySoUiLoader( _hdllInstance );
    SoUILoader::getSingletonPtr()->init();
}

void UIHelper::UnInitSouiEnviroment()
{
    LOG_TRACE( _T( "�˳�soui����..." ) );
    delete SoUILoader::getSingletonPtr();
}

void UIHelper::ShowModelessDemo()
{
    // �л���Դ
    CAcModuleResourceOverride myResources;

    LOG_TRACE( _T( "����soui��ģ̬�Ի���" ) );
    DemoDialog* dlg = new DemoDialog( FALSE );
    dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void UIHelper::ShowModalDemo()
{
    CAcModuleResourceOverride myResources;

    LOG_TRACE( _T( "����souiģ̬�Ի���" ) );
    DemoDialog dlg( TRUE );
    dlg.Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void UIHelper::Login()
{
    CAcModuleResourceOverride myResources;

    LoginDialog dlg( TRUE );
    dlg.Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void UIHelper::Logout()
{
    //���cbm_sys_info��
    RecordPtrListPtr lists = FIND_ALL( SysInfo );
    if( lists == 0 ) return;

    for( int i = 0; i < lists->size(); i++ )
    {
        lists->at( i )->remove();
    }
}

void UIHelper::SampleManage()
{
    //���ҹ���Ա�ʻ�
    AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
    if( admin == 0 ) return;

    int account_id = DaoHelper::GetOnlineAccountId();
    if( account_id == 0 || account_id != admin->getID() )
    {
        SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���Թ���Ա(admin)��ݵ�¼!" ), _T( "������ʾ" ), MB_OK );
        //���õ�¼����
        UIHelper::Login();
    }
    else
    {
        CAcModuleResourceOverride myResources;

        SampleManageDialog* dlg = new SampleManageDialog( FALSE );
        dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
    }
}

void UIHelper::GasTechModeDecision()
{
    int account_id = DaoHelper::GetOnlineAccountId();
    if( account_id == 0 )
    {
        SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
        //���õ�¼����
        UIHelper::Login();
    }
    else
    {
        CAcModuleResourceOverride myResources;

        MineDialog* dlg = new MineDialog( FALSE );
        //��ѯ�˻������Ŀ�
        MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
        dlg->mine_id = mine->getID();
        dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
    }
}

void UIHelper::KeyParamCacl()
{
    int account_id = DaoHelper::GetOnlineAccountId();
    if( account_id == 0 )
    {
        SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
        //���õ�¼����
        UIHelper::Login();
    }
    else
    {
        CAcModuleResourceOverride myResources;

        KeyParamDialog* dlg = new KeyParamDialog( FALSE );
        //��ѯ�˻������Ŀ�
        MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
        dlg->mine_id = mine->getID();
        dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
    }
}

void UIHelper::PolicyHelp()
{
    CAcModuleResourceOverride myResources;

    PolicyDialog* dlg = new PolicyDialog( FALSE );
    dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
}

static void test_ucs()
{
	AcGePoint3d pt(100,20,0);
	ArxUcsSwitch ucs_switch(pt, AcGeVector3d(1,1,0), AcGeVector3d(-1,1,0));

	AcDbObjectIdArray ents;
	//AcGePoint3d spt(0, 0, 0), ept(100,100,0);
	//spt = ArxUcsHelper::ucsToWcs(spt);
	//ept = ArxUcsHelper::ucsToWcs(ept);
	ents.append(ArxDrawHelper::DrawLine(AcGePoint3d(0, 0, 0), AcGePoint3d(100,100,0)));
	ents.append(ArxDrawHelper::DrawLine(AcGePoint3d(100, 100, 0), AcGePoint3d(100,0,0)));
	ents.append(ArxDrawHelper::DrawLine(AcGePoint3d(100, 0, 0), AcGePoint3d(0,100,0)));

	ArxUcsHelper::ucsToWcs(ents);
}

#include "Graph2.h"
static void test()
{
	int coal_id = 4;
	CoalPtr coal = FIND_BY_ID( Coal, coal_id );
	if( coal == 0 ) return;

	//����ú���������ƹ�����
	DesignWorkSurfPtr work_surf = FIND_ONE( DesignWorkSurf, FKEY( Coal ), coal->getStringID() );
	if( work_surf == 0 ) return;

	//���ҳ�ɼ���
	DesignTechnologyPtr technology = FIND_ONE( DesignTechnology, FKEY( Coal ), coal->getStringID() );
	if( technology == 0 ) return;

	technology->l_stripe = 60;
	technology->leading = 30;
	technology->gbp = 3;

	//����ѡ���������
	AcGePoint3d pt;
	ArxUtilHelper::PromptPt(_T("��ѡ��һ��:"), pt);

	//����ƽ��ͼ
	P2::PlanGraph graph(coal, work_surf, technology);
	graph.setPoint(pt);
	graph.draw();
}

void UIHelper::Main()
{
	test();
	return;

    int account_id = DaoHelper::GetOnlineAccountId();
    if( account_id == 0 )
    {
        SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
        //���õ�¼����
        UIHelper::Login();
    }
    else
    {
        CAcModuleResourceOverride myResources;

        MainDialog* dlg = new MainDialog( FALSE );
        //��ѯ�˻������Ŀ�
        MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
        dlg->mine_id = mine->getID();
        dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
    }
}
