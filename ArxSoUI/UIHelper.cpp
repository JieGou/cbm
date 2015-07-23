#include "StdAfx.h"
#include "UIHelper.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"
#include "../Util/HelperClass.h"

#include "MySoUiLoader.h"
#include "LoginDlg.h"
#include "ModalLoginDlg.h"
#include "EmbedSouiDlg.h"

//TestDockBarDlg* pTestDockBarDlg = 0;
//EmbedSouiDlg* globalEmbedSouiDlg = 0;

void UIHelper::InitSouiEnviroment()
{
	LOG_TRACE( _T( "��ʼ��soui����..." ) );
	new MySoUiLoader(_hdllInstance);
	SoUILoader::getSingletonPtr()->init();
}

void UIHelper::UnInitSouiEnviroment()
{
	LOG_TRACE( _T( "�˳�soui����..." ) );
	delete SoUILoader::getSingletonPtr();
}

void UIHelper::ShowSoUIDlg1()
{
	// �л���Դ
	CAcModuleResourceOverride myResources;

	LOG_TRACE(_T("�����µ�soui����"));

	//��������ʾʹ��SOUI����Ӧ�ó��򴰿�
	EmbedSouiDlg* dlg = new EmbedSouiDlg();
	dlg->Create(IDD_SOUI_EMBED_DLG, acedGetAcadFrame());
	dlg->ShowWindow(SW_SHOWNORMAL);
	//LoginDlg dlg;
	////dlg.DoModal();
	//dlg.Create(acedGetAcadFrame()->GetSafeHwnd(),0,0,0,0);
	//dlg.SendMessage(WM_INITDIALOG);
	//dlg.CenterWindow();
	//dlg.ShowWindow(SW_SHOWNORMAL);
	//SoUILoader::getSingletonPtr()->getApp()->Run(dlg.m_hWnd);
}

void UIHelper::ShowSoUIDlg2()
{
	CAcModuleResourceOverride myResources;

	ModalLoginDlg dlg;
	dlg.DoModal(acedGetAcadFrame()->GetSafeHwnd());
}