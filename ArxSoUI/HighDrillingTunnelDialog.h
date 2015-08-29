#pragma once
#include "AcadSouiDialog.h"

class HighDrillingTunnelDialog : public AcadSouiDialog
{

	/** 构造和析构函数 */
public:
	HighDrillingTunnelDialog(BOOL bModal = FALSE);
	~HighDrillingTunnelDialog(void);

	/** 控件消息处理 */
protected:
	void OnRockComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnSaveButtonClick();
	void OnWsComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnCaclButtonClick();

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
		EVENT_NAME_HANDLER(_T("rock"), EVT_CB_SELCHANGE, OnRockComboxSelChanged)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_NAME_HANDLER(_T("ws"), EVT_CB_SELCHANGE, OnWsComboxSelChanged)
		EVENT_NAME_COMMAND(_T("cacl"), OnCaclButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST消息(WINDOWS消息)映射表
	BEGIN_MSG_MAP_EX(HighDrillingTunnelDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_HwEdit;
	SEdit* m_CzkEdit;
	SEdit* m_DipAngleEdit;
	SComboBox* m_RockCombox;
	SEdit* m_HzMinEdit;
	SEdit* m_HzMaxEdit;
	SComboBox* m_WsCombox;

public:
	int mine_id;

protected:
	virtual void OnDestroyWindow();

private:
	void initWsDatas();
	void fillWsCombox();
	cbm::WorkSurfPtr getCurSelWs();
};
