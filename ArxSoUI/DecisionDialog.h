#pragma once
#include "AcadSouiDialog.h"

class DecisionDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    DecisionDialog( BOOL bModal = FALSE );
    ~DecisionDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnGraphButtonClick();
    void OnTechnologyButtonClick();

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
    EVENT_NAME_COMMAND( _T( "graph" ), OnGraphButtonClick )
    EVENT_NAME_COMMAND( _T( "technology" ), OnTechnologyButtonClick )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( DecisionDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SStatic* m_TechModeLabel;

public:
    int mine_id; // �ⲿ����(��id)

private:
	bool getPoint( AcGePoint3d& pt );
};
