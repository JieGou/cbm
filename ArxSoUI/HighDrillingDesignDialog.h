#pragma once
#include "AcadSouiDialog.h"

class HighDrillingDesignDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    HighDrillingDesignDialog( BOOL bModal = FALSE );
    ~HighDrillingDesignDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnWsComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnDrillSiteButtonClick();
    void OnDrillPoreButtonClick();
    void OnSaveButtonClick();

    /** �˵���Ϣ */
protected:
    //����˵���Ϣ(�˵���һ��������xml�ļ���������ÿ���˵����һ��id��)
    void OnCommand( UINT uNotifyCode, int nID, HWND wndCtl );

    /** ������Ϣ */
protected:
    //�Ի����ʼ������
    LRESULT OnInitDialog( HWND hWnd, LPARAM lParam );

    //�ؼ���Ϣӳ���
    EVENT_MAP_BEGIN()
    EVENT_NAME_HANDLER( _T( "ws" ), EVT_CB_SELCHANGE, OnWsComboxSelChanged )
    EVENT_NAME_COMMAND( _T( "drill_site" ), OnDrillSiteButtonClick )
    EVENT_NAME_COMMAND( _T( "drill_pore" ), OnDrillPoreButtonClick )
    EVENT_NAME_COMMAND( _T( "save" ), OnSaveButtonClick )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( HighDrillingDesignDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SEdit* m_L1Edit;
    SEdit* m_L2Edit;
    SEdit* m_LgEdit;
    SComboBox* m_WsCombox;
    SListCtrl* m_AbcListctrl;
    SListCtrl* m_BcdListctrl;

public:
    int mine_id;

protected:
    virtual void OnDestroyWindow();

private:
    void initDatas();
    void fillWsCombox();
    cbm::WorkSurfPtr getCurSelWs();
};
