#pragma once
#include "AcadSouiDialog.h"

class MainDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    MainDialog( BOOL bModal = FALSE );
    ~MainDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnF1ButtonClick();
    void OnF2ButtonClick();
    void OnF3ButtonClick();
    void OnF0ButtonClick();
    void OnF4ButtonClick();

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
    EVENT_NAME_COMMAND( _T( "f1" ), OnF1ButtonClick )
    EVENT_NAME_COMMAND( _T( "f2" ), OnF2ButtonClick )
    EVENT_NAME_COMMAND( _T( "f3" ), OnF3ButtonClick )
    EVENT_NAME_COMMAND( _T( "f0" ), OnF0ButtonClick )
    EVENT_NAME_COMMAND( _T( "f4" ), OnF4ButtonClick )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( MainDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

public:
    int mine_id;
};
