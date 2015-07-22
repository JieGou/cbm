#include "StdAfx.h"
#include "UIHelper.h"

#include "SoUILoader.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"
#include "../Util/HelperClass.h"

#include <controls.extend/SListCtrl2.h>
#include <controls.extend/SVscrollbar.h>
#include <controls.extend/SIPAddressCtrl.h>
#include <controls.extend/SChatEdit.h>
#include <controls.extend/SScrollText.h>
#include <controls.extend/SListCtrlEx.h>
#include <controls.extend/gif/SGifPlayer.h>
#include <controls.extend/gif/SSkinGif.h>

using namespace SOUI;

class MySoUiLoader4 : public SoUILoader
{
public:
	MySoUiLoader4(HINSTANCE hInstance) : SoUILoader(hInstance)
	{

	}

	~MySoUiLoader4() 
	{
		//�˳�GDI+����
		SSkinGif::Gdiplus_Shutdown();
	}

	virtual LPCTSTR getSkinDir() const
	{
		return _T("\\..\\..\\Skin\\demo4");
	}

	virtual bool initExtendControls()
	{
		pSouiApp->RegisterWndFactory(TplSWindowFactory<SGifPlayer>());//ע��GIFPlayer
		pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinGif>());//ע��SkinGif
		//pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinAPNG>());//ע��SSkinAPNG
		pSouiApp->RegisterSkinFactory(TplSkinFactory<SSkinVScrollbar>());//ע�����������Ƥ��

		pSouiApp->RegisterWndFactory(TplSWindowFactory<SIPAddressCtrl>());//ע��IP�ؼ�
		pSouiApp->RegisterWndFactory(TplSWindowFactory<SChatEdit>());//ע��ChatEdit
		pSouiApp->RegisterWndFactory(TplSWindowFactory<SScrollText>());//ע��SScrollText
		pSouiApp->RegisterWndFactory(TplSWindowFactory<SListCtrlEx>());//ע��SListCtrlEx
		pSouiApp->RegisterWndFactory(TplSWindowFactory<SListCtrl2>()); //ע��SListCtrl2
		//if(SUCCEEDED(CUiAnimation::Init()))
		//{
		//	pSouiApp->RegisterWndFactory(TplSWindowFactory<SUiAnimationWnd>());//ע�ᶯ���ؼ�
		//}
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SFlyWnd>());//ע����ж����ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SFadeFrame>());//ע�ὥ���������ؼ�
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SRadioBox2>());//ע��RadioBox2
		//pSouiApp->RegisterWndFactory(TplSWindowFactory<SCalendar2>());//ע��SCalendar2

		//��ʼ��GDI+����
		SSkinGif::Gdiplus_Startup();
		return true;
	}

	virtual bool initRealWnd()
	{
		//�����洰�ڴ���ӿ�
		//CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
		//pSouiApp->SetRealWndHandler(pRealWndHandler);
		//pRealWndHandler->Release();

		return SoUILoader::initRealWnd();
	}

	virtual bool initGlobalStyle()
	{
		//����ȫ����Դ����XML
		//��ʼ��SOUIȫ����Դ
		return (TRUE == pSouiApp->Init(_T("xml_init"), _T("uidef"))); 
	}
};

#include "LoginDlg.h"
#include "TestDlg.h"
void UIHelper::ShowSoUIDlg4()
{
	// �л���Դ
	CAcModuleResourceOverride myResources;

	LOG_TRACE(_T("�����µ�soui����"));

	//����soui��ص��齨����Դ
	MySoUiLoader4 suLoader(_hdllInstance);
	if(!suLoader.init()) return;

	//��������ʾʹ��SOUI����Ӧ�ó��򴰿�
	//LoginDlg dlg;
	//dlg.Create(GetActiveWindow(),0,0,0,0);
	//dlg.GetNative()->SendMessage(WM_INITDIALOG);
	//dlg.CenterWindow();
	//dlg.ShowWindow(SW_SHOWNORMAL);
	TestDlg dlg;
	dlg.DoModal();
	//suLoader.getApp()->Run(dlg.m_hWnd);
	//suLoader.getApp()->Run(GetActiveWindow());
}