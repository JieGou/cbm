#include "StdAfx.h"
#include "UIHelper.h"

#include <ArxHelper/HelperClass.h>
#include <MineGE/HelperClass.h>
#include <Util/HelperClass.h>

#include "MySoUiLoader.h"
#include "DemoDialog.h"
#include "LoginDialog.h"
#include "MineDialog.h"
#include "KeyParamDialog.h"
#include "SampleManageDialog.h"

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

void UIHelper::ShowModelessDemo()
{
	// �л���Դ
	CAcModuleResourceOverride myResources;

	LOG_TRACE(_T("����soui��ģ̬�Ի���"));
	DemoDialog* dlg = new DemoDialog(FALSE);
	dlg->Run(acedGetAcadFrame()->GetSafeHwnd());
}

void UIHelper::ShowModalDemo()
{
	CAcModuleResourceOverride myResources;

	LOG_TRACE(_T("����souiģ̬�Ի���"));
	DemoDialog dlg(TRUE);
	dlg.Run(acedGetAcadFrame()->GetSafeHwnd());
}

void UIHelper::Login()
{
	CAcModuleResourceOverride myResources;

	LoginDialog dlg(TRUE);
	dlg.Run(acedGetAcadFrame()->GetSafeHwnd());
}

void UIHelper::Mine()
{
	CAcModuleResourceOverride myResources;

	MineDialog dlg(TRUE);
	dlg.Run(acedGetAcadFrame()->GetSafeHwnd());
}

void UIHelper::KPC()
{
	CAcModuleResourceOverride myResources;

	KeyParamDialog dlg(TRUE);
	dlg.Run(acedGetAcadFrame()->GetSafeHwnd());
}

void UIHelper::SampleManage()
{
	CAcModuleResourceOverride myResources;

	SampleManageDialog* dlg = new SampleManageDialog(FALSE);
	dlg->Run(acedGetAcadFrame()->GetSafeHwnd());
}
