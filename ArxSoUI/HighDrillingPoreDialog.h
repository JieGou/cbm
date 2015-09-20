#pragma once
#include "AcadSouiDialog.h"

class HighDrillingPoreDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    HighDrillingPoreDialog( BOOL bModal = FALSE );
    ~HighDrillingPoreDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnSaveButtonClick();
    void OnCaclButtonClick();

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
    EVENT_NAME_COMMAND( _T( "cacl" ), OnCaclButtonClick )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( HighDrillingPoreDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SEdit* m_LkEdit;
    SEdit* m_LcEdit;
    SEdit* m_LwEdit;
    SEdit* m_N2Edit;
    SEdit* m_BetaEdit;
    SEdit* m_LdEdit;
    SEdit* m_N1Edit;

public:
    double Lg;
    int ws_id; // ������id(�ⲿ����)

private:
    void initDatas();
    void fillDatas();
};
