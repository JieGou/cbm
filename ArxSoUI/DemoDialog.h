#pragma once
#include "AcadSouiDialog.h"

class DemoDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    DemoDialog( BOOL bModal = FALSE );
    ~DemoDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnButton12Click();
    void OnButton13Click();
    void OnButton32Click();
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
    EVENT_NAME_COMMAND( _T( "button12" ), OnButton12Click )
    EVENT_NAME_COMMAND( _T( "button13" ), OnButton13Click )
    EVENT_NAME_COMMAND( _T( "button32" ), OnButton32Click )
    EVENT_NAME_HANDLER( _T( "combobox71" ), EVT_CB_SELCHANGE, OnCombox71SelChanged )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( DemoDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SEdit* m_UserEdit;
    SEdit* m_Edit11;
    SImageWnd* m_Img17;
    SListBox* m_Listbox29;
    SRichEdit* m_Richedit30;
    SRichEdit* m_Richedit31;
    SListCtrl* m_Listctrl45;
    STabCtrl* m_Tabctrl48;
    STabCtrl* m_Tabctrl49;
    STreeCtrl* m_Tree1Treectrl;
    SComboBox* m_Combox71;
    SLink* m_Link73;
    SRadioBox* m_Radio75;
};
