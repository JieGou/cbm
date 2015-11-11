#include "StdAfx.h"
#include "UIHelper.h"
#include "Path.h"

#include "MySoUiLoader.h"
#include "DemoDialog.h"
#include "PicViewerDialog.h"
#include "RtfViewerDialog.h"

#include "LoginDialog.h"
//#include "RegDialog.h"
//#include "SampleManageDialog.h"
//#include "MineDesignDialog.h"
//#include "MineDialog.h"
//#include "KeyParamDialog.h"
//#include "PolicyDialog.h"
//#include "MainDialog.h"
//#include "DifficultEvalDialog.h"
//#include "MineGasReservesPredictDialog.h"
//#include "MineGasFlowPredictDialog.h"
//#include "TwsGasFlowPredictDialog.h"
//#include "WsGasFlowPredictDialog.h"
//#include "HighDrillingTunnelDialog.h"
//#include "HighDrillingDesignDialog.h"
//#include "DrillingRadiusDesignDialog.h"
//#include "PoreSizeDialog.h"
//#include "PoreFlowDialog.h"
//#include "GasDesignDialog.h"

using namespace SOUI;

#include <ArxHelper/HelperClass.h>
#include <Util/HelperClass.h>

#include "SQLClientHelper.h"
#include "CbmClientHelper.h"
#include <WinHttpClient.h>

void TestWinHttpClient()
{
	// Set URL.
	WinHttpClient client(_T("http://localhost/tt/test.php"));

	// Send http request, a GET request by default.
	client.SendHttpRequest();
	string data = "title=����1&content=�������";
	client.SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());

	// The response header.
	CString httpResponseHeader = client.GetResponseHeader().c_str();
	// The response content.
	CString httpResponseContent = client.GetResponseContent().c_str();
}

void UIHelper::InitAllData()
{
    //��ʼ����������(�����ʵ䡢��չ����appname��)
    SystemHelper::Start();
    //��ȡ�ֶ�
    CString appDir = ArxUtilHelper::GetAppPathDir( _hdllInstance );
    FieldHelper::InitDataField( ArxUtilHelper::BuildPath( appDir, _T( "Datas\\ú�������-�ֶ�-ͼԪ����.txt" ) ) );
    //��������
    acdbHostApplicationServices()->workingDatabase()->loadLineTypeFile( _T( "JIS_02_0.7" ), _T( "acadiso.lin" ) );
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
	dlg.SetWindowTitle(_T("Demo�Ի���"));
    dlg.Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void UIHelper::TestRtfViewer()
{
    RtfViewerDialog dlg( TRUE );
	dlg.SetWindowTitle(_T("RTF�ĵ��Ķ���"));
    //ֱ��ָ��rtf��Դ(��  rtf:  ǰ׺)
    dlg.setRtfRes( _T( "HELP1" ) );
    //����ֱ��һ��rtf�ļ�(�����ʹ�þ���·��)
    //dlg.setRtfFile(ArxUtilHelper::BuildPath(ArxUtilHelper::GetAppPathDir(_hdllInstance), _T("help2.rtf")));
    dlg.Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void UIHelper::TestPicViewer()
{
    PicViewerDialog dlg( TRUE );
	dlg.SetWindowTitle(_T("ͼƬ�鿴��"));
    dlg.setPicSkin( _T( "skin_eval_proof" ) );
    dlg.Run( acedGetAcadFrame()->GetSafeHwnd() );

    CString picFile = ArxUtilHelper::BuildPath(
                          ArxUtilHelper::GetAppPathDir( _hdllInstance ),
                          _T( "..\\..\\ArxSoUI\\uires\\image\\bk.png" ) );
    UIHelper::ShowImgView( picFile );
}

void UIHelper::ShowImgView( const CString& bstrFileName )
{
	//imgview.exe��·��
	CString strExeName = ArxUtilHelper::BuildPath( ArxUtilHelper::GetAppPathDir( _hdllInstance ), _T( "ImageView.exe" ) );

	//exe�Ĳ���
	CString strArg = _T( "\"" );
	strArg += bstrFileName;
	strArg += _T( "\"" );

	if ( cbm::CPath::IsFileExist( strExeName ) )
	{
		HWND hWnd = ::FindWindow( _T( "DUI_WINDOW" ), _T( "ImageView" ) );
		if ( ::IsWindow( hWnd ) )
			::SendMessage( hWnd, WM_CLOSE, 0, 0 );
		::ShellExecute( NULL, NULL, strExeName, strArg, NULL, SW_SHOWNORMAL );
	}
	else
		::ShellExecute( NULL, _T( "open" ), bstrFileName, NULL, NULL, SW_SHOWNORMAL );
}

void UIHelper::Login()
{
    CAcModuleResourceOverride myResources;

    LoginDialog dlg( TRUE );
	dlg.SetWindowTitle(_T("ϵͳ�û���¼"));
    dlg.Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void UIHelper::RegMine()
{
 //   CAcModuleResourceOverride myResources;

 //   RegDialog dlg( TRUE );
	//dlg.SetWindowTitle(_T("ע���¿󾮼����û�"));
 //   dlg.Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void UIHelper::Logout()
{
    ////���cbm_sys_info��
    //RecordPtrListPtr lists = FIND_ALL( SysInfo );
    //if( lists == 0 ) return;

    //for( int i = 0; i < lists->size(); i++ )
    //{
    //    lists->at( i )->remove();
    //}
    //AfxMessageBox( _T( "�ɹ�ע�����˳�ϵͳ!" ) );
}

void UIHelper::SampleManage()
{
    //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 || account_id != admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���Թ���Ա(admin)��ݵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      SampleManageDialog* dlg = new SampleManageDialog( FALSE );
		//dlg->SetWindowTitle(_T("ʾ���������������"));
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::MineDesign()
{
    //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  //else if( account_id == admin->getID() )
  //  //{
  //  //    SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //  //    //���õ�¼����
  //  //    UIHelper::Login();
  //  //}
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      MineDesignDialog* dlg = new MineDesignDialog( FALSE );
		//dlg->SetWindowTitle(_T("�����"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::GasTechModeDecision()
{
    //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      MineDialog* dlg = new MineDialog( FALSE );
		//dlg->SetWindowTitle(_T("������Ŀ��󾮻�����Ϣ:"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KeyParamCacl()
{
    //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      KeyParamDialog* dlg = new KeyParamDialog( FALSE );
		//dlg->SetWindowTitle(_T("��ɹؼ�������������"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP1()
{
    //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      DifficultEvalDialog* dlg = new DifficultEvalDialog( FALSE );
		//dlg->SetWindowTitle(_T("ú����������׳̶�����"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP2()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      MineGasReservesPredictDialog* dlg = new MineGasReservesPredictDialog( FALSE );
		//dlg->SetWindowTitle(_T("��ú�����������ɳ���Ԥ��"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP3()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      MineGasFlowPredictDialog* dlg = new MineGasFlowPredictDialog( FALSE );
		//dlg->SetWindowTitle(_T("����˹ӿ����Ԥ��"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP4()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      TwsGasFlowPredictDialog* dlg = new TwsGasFlowPredictDialog( FALSE );
		//dlg->SetWindowTitle(_T("�����������˹ӿ����Ԥ��"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP5()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      WsGasFlowPredictDialog* dlg = new WsGasFlowPredictDialog( FALSE );
		//dlg->SetWindowTitle(_T("�زɹ�������˹ӿ����Ԥ��"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP6()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      HighDrillingTunnelDialog* dlg = new HighDrillingTunnelDialog( FALSE );
		//dlg->SetWindowTitle(_T("�߳���������λ����"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP7()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      HighDrillingDesignDialog* dlg = new HighDrillingDesignDialog( FALSE );
		//dlg->SetWindowTitle(_T("��λ��������Ч���跶Χ����"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP8()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      DrillingRadiusDesignDialog* dlg = new DrillingRadiusDesignDialog( FALSE );
		//dlg->SetWindowTitle(_T("ú����˹��ɰ뾶����"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP9()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      PoreSizeDialog* dlg = new PoreSizeDialog( FALSE );
		//dlg->SetWindowTitle(_T("��ɹܾ���С��������"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP10()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      PoreFlowDialog* dlg = new PoreFlowDialog( FALSE );
		//dlg->SetWindowTitle(_T("�װ���������"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::KP11()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      //CAcModuleResourceOverride myResources;

  //      //PoreFlowDialog* dlg = new PoreFlowDialog( FALSE );
		////dlg->SetWindowTitle(_T("���۵�Ԫ���ּ���"));
  //      ////��ѯ�˻������Ŀ�
  //      //MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      //dlg->mine_id = mine->getID();
  //      //dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::GasDesign()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      GasDesignDialog* dlg = new GasDesignDialog( FALSE );
		//dlg->SetWindowTitle(_T("���¹�ģ�����ú���������������"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::PolicyHelp()
{
 //   CAcModuleResourceOverride myResources;

 //   PolicyDialog* dlg = new PolicyDialog( FALSE );
	//dlg->SetWindowTitle(_T("�鿴ú���������ر�׼���淶������"));
 //   dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
}

static void test_ucs()
{
    AcGePoint3d pt( 100, 20, 0 );
    ArxUcsSwitch ucs_switch( pt, AcGeVector3d( 1, 1, 0 ), AcGeVector3d( -1, 1, 0 ) );

    AcDbObjectIdArray ents;
    //AcGePoint3d spt(0, 0, 0), ept(100,100,0);
    //spt = ArxUcsHelper::ucsToWcs(spt);
    //ept = ArxUcsHelper::ucsToWcs(ept);
    ents.append( ArxDrawHelper::DrawLine( AcGePoint3d( 0, 0, 0 ), AcGePoint3d( 100, 100, 0 ) ) );
    ents.append( ArxDrawHelper::DrawLine( AcGePoint3d( 100, 100, 0 ), AcGePoint3d( 100, 0, 0 ) ) );
    ents.append( ArxDrawHelper::DrawLine( AcGePoint3d( 100, 0, 0 ), AcGePoint3d( 0, 100, 0 ) ) );

    ArxUcsHelper::ucsToWcs( ents );
}

void UIHelper::Main()
{
  //  //���ҹ���Ա�ʻ�
  //  AccountPtr admin = FIND_ONE( Account, FIELD( username ), _T( "admin" ) );
  //  if( admin == 0 ) return;

  //  int account_id = DaoHelper::GetOnlineAccountId();
  //  if( account_id == 0 )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "���¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else if( account_id == admin->getID() )
  //  {
  //      SMessageBox( acedGetAcadFrame()->GetSafeHwnd(), _T( "��ע�����Էǹ���Ա�˺ŵ�¼!" ), _T( "������ʾ" ), MB_OK );
  //      //���õ�¼����
  //      UIHelper::Login();
  //  }
  //  else
  //  {
  //      CAcModuleResourceOverride myResources;

  //      MainDialog* dlg = new MainDialog( FALSE );
		//dlg->SetWindowTitle(_T("����ú������ģ����ɼ�����������"));
  //      //��ѯ�˻������Ŀ�
  //      MinePtr mine = FIND_ONE( Mine, FKEY( Account ), Utils::int_to_cstring( account_id ) );
  //      dlg->mine_id = mine->getID();
  //      dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
  //  }
}

void UIHelper::xxx()
{
	std::string json_data = CbmClientHelper::GetJsonDatasFromCAD(1);
	//int ret = CbmClientHelper::VerifyMineAccount("dlj", "123");
	CbmClientHelper::SendCommandToCAD("regen");
	//acutPrintf(_T("\n��֤���:%d"), ret);
}

void UIHelper::PostJsonDatasToRpc()
{
	int data_type = 0;
	if(acedGetInt(_T("\n�������������������(>0):"), &data_type) != RTNORM) return;
	if(data_type < 1) return;
	// ��ȡ��Կ
	TCHAR str[MAX_PATH];
	if(acedGetString(0, _T("��������Կ:"), str) != RTNORM) return;

	CString secret_key = str;
	secret_key.Trim();
	acutPrintf(_T("\n��Կ����:"), secret_key.GetLength());
	//if(secret_key.GetLength() != 36) return;

	// �ռ�����
	bool ret = true;
	switch(data_type)
	{
	case 1:
		//
		break;
	case 2:
		//
		break;
	default:
		ret = false;
		break;
	}
	if(ret)
	{
		//��rpc����
		CbmClientHelper::PostJsonDatasFromCAD(data_type, W2C((LPCTSTR)secret_key), "{'name':'dlj'}");
	}
	else
	{
		CbmClientHelper::PostJsonDatasFromCAD(data_type, W2C((LPCTSTR)secret_key), "{}");
	}
}
