#include "stdafx.h"
#include "AcadSouiDialog.h"

AcadSouiDialog::AcadSouiDialog( LPCTSTR pszXmlName, BOOL bModal )
    : SouiDialog( pszXmlName, bModal )
{
}

AcadSouiDialog::~AcadSouiDialog( void )
{
}

//- Needed for modeless dialogs to keep focus.
//- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT AcadSouiDialog::OnAcadKeepFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    //��ģ̬������,�������ڴ�����(m_mouseInWindow=TRUE),����Ϊ����Ӧ�û�ȡ����
    SetMsgHandled( TRUE );
    return SouiDialog::keepFocus();
}

