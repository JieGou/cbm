#pragma once

using namespace SOUI;

#include "Singleton.h"

//�ο�demo�����е�main����soui���ع���
//�������ʽ���з�װ,��ͼ�򻯴���~
class SoUILoader : public Singleton<SoUILoader>
{
public:
	SoUILoader(HINSTANCE _hInstance);
	virtual ~SoUILoader();
	bool init();
	SApplication* getApp();
	CString getResName() const;

protected:
	//����uires�ļ��е�����·��
	virtual LPCTSTR getSkinDir() const;
	virtual bool initRender();
	virtual bool initApp();
	virtual bool initResource();
	virtual bool initScripts();
	virtual bool initExtendControls();
	virtual bool initSysResource();
	virtual bool initRealWnd();
	virtual bool initGlobalStyle();
	SComMgr* getComMrg();
protected:
	HINSTANCE hInstance;                                //��ǰģ��(exe��dll�ľ��)
	SComMgr comMgrObj;                                  // ������ع�����
	CAutoRefPtr<IImgDecoderFactory> pImgDecoderFactory; //ͼƬ������
	CAutoRefPtr<IRenderFactory> pRenderFactory;         //UI��Ⱦģ��,��render-gdi.dll��render-skia.dll�ṩ
	//CAutoRefPtr<ITranslatorMgr> trans;                //�����Է���ģ��,��translator.dll�ṩ
	CAutoRefPtr<IScriptFactory> pScriptLua;             //lua�ű�ģ��,��scriptmodule-lua.dll�ṩ
	SApplication* pSouiApp;
};
