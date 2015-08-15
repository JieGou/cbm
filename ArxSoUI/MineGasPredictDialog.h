#pragma once
#include "AcadSouiDialog.h"

class MineGasPredictDialog : public AcadSouiDialog
{

	/** 构造和析构函数 */
public:
	MineGasPredictDialog(BOOL bModal = FALSE);
	~MineGasPredictDialog(void);

	/** 控件消息处理 */
protected:
	void OnK1HelpButtonClick();
	void OnSaveButtonClick();
	void OnK2HelpButtonClick();
	void OnWorkAreaComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnInputButtonClick();

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
		EVENT_NAME_COMMAND(_T("k1_help"), OnK1HelpButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_NAME_COMMAND(_T("k2_help"), OnK2HelpButtonClick)
		EVENT_NAME_HANDLER(_T("work_area"), EVT_CB_SELCHANGE, OnWorkAreaComboxSelChanged)
		EVENT_NAME_COMMAND(_T("input"), OnInputButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST消息(WINDOWS消息)映射表
	BEGIN_MSG_MAP_EX(MineGasPredictDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_WorkAreaAEdit;
	SEdit* m_K1GasEdit;
	SEdit* m_QrEdit;
	SEdit* m_K2GasEdit;
	SComboBox* m_WorkAreaCombox;
	SEdit* m_WorkAreaQrEdit;
};
