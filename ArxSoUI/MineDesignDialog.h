#pragma once
#include "AcadSouiDialog.h"

class MineDesignDialog : public AcadSouiDialog
{

	/** 构造和析构函数 */
public:
	MineDesignDialog(BOOL bModal = FALSE);
	~MineDesignDialog(void);

	/** 控件消息处理 */
protected:
	void OnDelCoalButtonClick();
	void OnAddCoalButtonClick();
	void OnCoalComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnWorkAreaComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnDelWorkAreaButtonClick();
	void OnAddWorkAreaButtonClick();
	void OnWsComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnTwsComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnDelWsButtonClick();
	void OnAddWsButtonClick();
	void OnDelTwsButtonClick();
	void OnAddTwsButtonClick();
	void OnSaveButtonClick();

	/** 菜单消息 */
protected:
	//处理菜单消息(菜单在一个单独的xml文件中描述，每个菜单项都有一个id号)
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	/** 窗口消息 */
protected:
	//对话框初始化过程
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	//控件消息映射表
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(_T("del_coal"), OnDelCoalButtonClick)
		EVENT_NAME_COMMAND(_T("add_coal"), OnAddCoalButtonClick)
		EVENT_NAME_HANDLER(_T("coal"), EVT_CB_SELCHANGE, OnCoalComboxSelChanged)
		EVENT_NAME_HANDLER(_T("work_area"), EVT_CB_SELCHANGE, OnWorkAreaComboxSelChanged)
		EVENT_NAME_COMMAND(_T("del_work_area"), OnDelWorkAreaButtonClick)
		EVENT_NAME_COMMAND(_T("add_work_area"), OnAddWorkAreaButtonClick)
		EVENT_NAME_HANDLER(_T("ws"), EVT_CB_SELCHANGE, OnWsComboxSelChanged)
		EVENT_NAME_HANDLER(_T("tws"), EVT_CB_SELCHANGE, OnTwsComboxSelChanged)
		EVENT_NAME_COMMAND(_T("del_ws"), OnDelWsButtonClick)
		EVENT_NAME_COMMAND(_T("add_ws"), OnAddWsButtonClick)
		EVENT_NAME_COMMAND(_T("del_tws"), OnDelTwsButtonClick)
		EVENT_NAME_COMMAND(_T("add_tws"), OnAddTwsButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST消息(WINDOWS消息)映射表
	BEGIN_MSG_MAP_EX(MineDesignDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_NameEdit;
	SComboBox* m_CoalCombox;
	SComboBox* m_WorkAreaCombox;
	SComboBox* m_WsCombox;
	SComboBox* m_TwsCombox;

public:
	int mine_id;

protected:
	virtual void OnDestroyWindow();

private:
	void initMineDatas();
	void fillCoalCombox();

	cbm::CoalPtr getCurSelCoal();
	cbm::WorkAreaPtr getCurSelWorkArea();
	cbm::WorkSurfPtr getCurSelWs();
	cbm::DrillingSurfPtr getCurSelTws();
};
