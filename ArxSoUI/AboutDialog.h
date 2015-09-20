#pragma once
#include "AcadSouiDialog.h"

class AboutDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    AboutDialog( BOOL bModal = FALSE );
    ~AboutDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnCombox71SelChanged( SOUI::EventArgs* pEvt );

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
    EVENT_NAME_HANDLER( _T( "combobox71" ), EVT_CB_SELCHANGE, OnCombox71SelChanged )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( AboutDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SComboBox* m_Combox71;
    SLink* m_Link73;
    SRadioBox* m_Radio75;
};
