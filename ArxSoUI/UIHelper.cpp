#include "StdAfx.h"
#include "UIHelper.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"
#include "../Util/HelperClass.h"

#include "MySoUiLoader.h"
#include "LoginDlg.h"

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

	LOG_TRACE(_T("�����µ�soui��ģ̬�Ի���"));
	LoginDlg* dlg = new LoginDlg(FALSE);
	dlg->Run(acedGetAcadFrame()->GetSafeHwnd());
}

void UIHelper::ShowSoUIDlg2()
{
	CAcModuleResourceOverride myResources;

	LOG_TRACE(_T("�����µ�souiģ̬�Ի���"));
	LoginDlg dlg(TRUE);
	dlg.Run(acedGetAcadFrame()->GetSafeHwnd());
}