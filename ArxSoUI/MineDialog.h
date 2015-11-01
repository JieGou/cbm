#pragma once
#include "AcadSouiDialog.h"

class MineDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    MineDialog( BOOL bModal = FALSE );
    ~MineDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnNextButtonClick();
    void OnCancelButtonClick();
    void OnRegionComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnBaseComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnSaveButtonClick();
    void OnTopoGeoComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnHydrGeoComboxSelChanged( SOUI::EventArgs* pEvt );

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
    EVENT_NAME_COMMAND( _T( "next" ), OnNextButtonClick )
    EVENT_NAME_COMMAND( _T( "cancel" ), OnCancelButtonClick )
    EVENT_NAME_HANDLER( _T( "mine_region" ), EVT_CB_SELCHANGE, OnRegionComboxSelChanged )
    EVENT_NAME_HANDLER( _T( "base" ), EVT_CB_SELCHANGE, OnBaseComboxSelChanged )
    EVENT_NAME_COMMAND( _T( "save" ), OnSaveButtonClick )
    EVENT_NAME_HANDLER( _T( "topo_geo" ), EVT_CB_SELCHANGE, OnTopoGeoComboxSelChanged )
    EVENT_NAME_HANDLER( _T( "hydr_geo" ), EVT_CB_SELCHANGE, OnHydrGeoComboxSelChanged )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( MineDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SEdit* m_NameEdit;
    SEdit* m_CapacityEdit;
    SComboBox* m_RegionCombox;
    SComboBox* m_BaseCombox;
    SEdit* m_ProvinceEdit;
    SEdit* m_CityEdit;
    SComboBox* m_TopoGeoCombox;
    SCheckBox* m_GroundCondCheck;
    SComboBox* m_HydrGeoCombox;

public:
    int mine_id;

private:
    void fillBaseCombox();
    void fillRegionCombox( const CString& base );
    void fillMineDatas();
    void clearBaseCombox();
    void clearRegionCombox();
};
