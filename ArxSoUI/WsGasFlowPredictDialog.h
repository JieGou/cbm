#pragma once
#include "AcadSouiDialog.h"

class WsGasFlowPredictDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    WsGasFlowPredictDialog( BOOL bModal = FALSE );
    ~WsGasFlowPredictDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnQr1CaclButtonClick();
    void OnQr2CaclButtonClick();
    void OnSaveButtonClick();
    void OnWsComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnQrCaclButtonClick();
    void OnRadioGroup1Switch( int nID );

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
    EVENT_NAME_COMMAND( _T( "qr1_cacl" ), OnQr1CaclButtonClick )
    EVENT_NAME_COMMAND( _T( "qr2_cacl" ), OnQr2CaclButtonClick )
    EVENT_NAME_COMMAND( _T( "save" ), OnSaveButtonClick )
    EVENT_NAME_HANDLER( _T( "ws" ), EVT_CB_SELCHANGE, OnWsComboxSelChanged )
    EVENT_NAME_COMMAND( _T( "qr_cacl" ), OnQrCaclButtonClick )
    EVENT_ID_COMMAND_RANGE( 100, 101, OnRadioGroup1Switch )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( WsGasFlowPredictDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SEdit* m_Qr1Edit;
    SEdit* m_Qr2Edit;
    SEdit* m_QrEdit;
    SRadioBox* m_MethodThinRadio;
    SRadioBox* m_MethodThickRadio;
    SComboBox* m_WsCombox;
    SEdit* m_ThickEdit;
    SEdit* m_HwEdit;
    SEdit* m_LEdit;
    SEdit* m_WsThickEdit;

public:
    int mine_id;

protected:
    virtual void OnDestroyWindow();

private:
    void initWsDatas();
    void fillWsCombox();
    cbm::WorkSurfPtr getCurSelWs();
};
