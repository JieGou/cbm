#pragma once
#include "AcadSouiDialog.h"

class MineGasReservesPredictInputDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    MineGasReservesPredictInputDialog( BOOL bModal = FALSE );
    ~MineGasReservesPredictInputDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnCoalComboxSelChanged( SOUI::EventArgs* pEvt );
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
    EVENT_NAME_COMMAND( _T( "save" ), OnSaveButtonClick )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( MineGasReservesPredictInputDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

public:
    int mine_id;

protected:
    SEdit* m_ResA1Edit;
    SEdit* m_GasX1Edit;
    SComboBox* m_CoalCombox;

public:
    int type; // �Ƿ�ɲ�ú��(Ĭ��Ϊ1-�ɲ�)

protected:
    virtual void OnDestroyWindow();

private:
    void fillCoalCombox();
    void initCoalDatas();
    cbm::CoalPtr getCurSelCoal();
};
