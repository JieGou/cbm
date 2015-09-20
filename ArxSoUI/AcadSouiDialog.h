#pragma once

#include "SouiDialog.h"

//��չ��arxʹ�õ�soui�Ի������
class AcadSouiDialog : public SouiDialog
{
public:
    AcadSouiDialog( LPCTSTR pszXmlName, BOOL bModal = FALSE );
    ~AcadSouiDialog( void );

    /** CAD������Ϣ */
protected:
    //CAD������Ϣ����
    LRESULT OnAcadKeepFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

    /** �ؼ���Ϣӳ��� */
    EVENT_MAP_BEGIN()
    CHAIN_EVENT_MAP( SouiDialog )
    EVENT_MAP_END()

    /** ������Ϣӳ��� */
    BEGIN_MSG_MAP_EX( AcadSouiDialog )
    MESSAGE_HANDLER( WM_ACAD_KEEPFOCUS, OnAcadKeepFocus )
    CHAIN_MSG_MAP( SouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
};
