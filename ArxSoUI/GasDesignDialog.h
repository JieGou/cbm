#pragma once
#include "AcadSouiDialog.h"

class GasDesignDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    GasDesignDialog( BOOL bModal = FALSE );
    ~GasDesignDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnCoalComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnTwsDesignButtonClick();
    void OnWsDesignButtonClick();
    void OnGoafDesignButtonClick();
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
    EVENT_NAME_HANDLER( _T( "coal" ), EVT_CB_SELCHANGE, OnCoalComboxSelChanged )
    EVENT_NAME_COMMAND( _T( "tws_design" ), OnTwsDesignButtonClick )
    EVENT_NAME_COMMAND( _T( "ws_design" ), OnWsDesignButtonClick )
    EVENT_NAME_COMMAND( _T( "goaf_design" ), OnGoafDesignButtonClick )
    EVENT_NAME_COMMAND( _T( "save" ), OnSaveButtonClick )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( GasDesignDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SComboBox* m_CoalCombox;
    SEdit* m_ThickEdit;
    SEdit* m_DipAngleEdit;

public:
    int mine_id;

protected:
    virtual void OnDestroyWindow();

private:
    void fillCoalCombox();
};
