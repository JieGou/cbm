#pragma once
#include "AcadSouiDialog.h"

class WsGasFlowPredictAdjDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    WsGasFlowPredictAdjDialog( BOOL bModal = FALSE );
    ~WsGasFlowPredictAdjDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnSaveButtonClick();
    void OnAdjLayerComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnDelAdjLayerButtonClick();
    void OnAddAdjLayerButtonClick();
    void OnEtaCaclButtonClick();

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
    EVENT_NAME_COMMAND( _T( "save" ), OnSaveButtonClick )
    EVENT_NAME_HANDLER( _T( "adj_layer" ), EVT_CB_SELCHANGE, OnAdjLayerComboxSelChanged )
    EVENT_NAME_COMMAND( _T( "del_adj_layer" ), OnDelAdjLayerButtonClick )
    EVENT_NAME_COMMAND( _T( "add_adj_layer" ), OnAddAdjLayerButtonClick )
    EVENT_NAME_COMMAND( _T( "eta_cacl" ), OnEtaCaclButtonClick )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

    //HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( WsGasFlowPredictAdjDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SEdit* m_GasW0Edit;
    SEdit* m_ThickEdit;
    SEdit* m_GasEtaEdit;
    SEdit* m_GasWc2Edit;
    SComboBox* m_AdjLayerCombox;
    SEdit* m_HEdit;
    SEdit* m_HpEdit;
    SCheckBox* m_InCzCheck;

public:
    int ws_id; // �ⲿ����(������id)

protected:
    virtual void OnDestroyWindow();

private:
    void initAdjLayerDatas();
    void fillAdjLayerCombox();
    cbm::AdjLayerPtr getCurSelAdjLayer();
};
