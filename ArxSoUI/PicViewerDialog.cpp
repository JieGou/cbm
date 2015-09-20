#include "stdafx.h"
#include "PicViewerDialog.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>
#include <Dao/Entity.h>
using namespace orm;
using namespace cbm;

PicViewerDialog::PicViewerDialog( BOOL bModal ) : AcadSouiDialog( _T( "layout:pic_viewer" ), bModal )
{
    m_use_res = true;
}

PicViewerDialog::~PicViewerDialog()
{
}

void PicViewerDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT PicViewerDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    AcadSouiDialog::OnInitDialog( hWnd, lParam );
    //do something
    m_PicImg = FindChildByName2<SImageWnd>( L"pic" );
    ISkinObj* skin = GETSKIN( ( LPCTSTR )m_pic_skin );
    if( skin != 0 )
    {
        //����ͼƬ
        m_PicImg->SetSkin( skin );
        //��ȡƤ����Դ�Ĵ�С
        SIZE size = skin->GetSkinSize();

        //����Ĵ�����Ч,��������SetAttribute()������Move()
        //����Ӧ�������ڴ�С
        SOUI::CRect rect1;
        SWindow::GetWindowRect( &rect1 );
        rect1.right += size.cx - rect1.Width();
        rect1.bottom += size.cy - rect1.Height();
        this->MoveWindow( &rect1 );

        //����Ӧ����ͼƬ���С
        SOUI::CRect rect2;
        m_PicImg->GetClientRect( &rect2 );
        rect2.right += size.cx - rect2.Width() + 5;
        rect2.bottom += size.cy - rect2.Height() + 5;
        m_PicImg->Move( &rect2 );
    }
    return 0;
}

void PicViewerDialog::setPicSkin( const CString& pic_skin )
{
    this->m_pic_skin = pic_skin;
    this->m_use_res = true;
}

void PicViewerDialog::setPicFile( const CString& pic_file )
{
    this->m_pic_file = pic_file;
    this->m_use_res = false;
}

