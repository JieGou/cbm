#include "stdafx.h"
#include "TechnologyDialog.h"
#include "SouiListHelper.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>

using namespace orm;
using namespace cbm;

TechnologyDialog::TechnologyDialog( BOOL bModal ) : AcadSouiDialog( _T( "layout:technology" ), bModal )
{
}

TechnologyDialog::~TechnologyDialog()
{
}

void TechnologyDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT TechnologyDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    AcadSouiDialog::OnInitDialog( hWnd, lParam );
    //do something
    m_TechnologyListbox = FindChildByName2<SListBox>( L"technology" );
    m_IsKeyCheck = FindChildByName2<SCheckBox>( L"is_key" );
    m_DocEdit = FindChildByName2<SEdit>( L"doc" );
    m_VideoEdit = FindChildByName2<SEdit>( L"video" );
    m_RegionLabel = FindChildByName2<SStatic>( L"mine_region" );

    CString msg;
    msg.Format( _T( ">>%s�����Ƽ���ɼ���" ), regionName );
    m_RegionLabel->SetWindowText( ( LPCTSTR )msg );
    fillTechnologyListBox();

    return 0;
}


void TechnologyDialog::OnTechnologyListboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventLBSelChanged* pEvtOfLB = ( EventLBSelChanged* )pEvt;
    if( pEvtOfLB == 0 ) return;
    int nCurSel = pEvtOfLB->nNewSel;
    if( nCurSel == -1 ) return;

    // do something
    //���ݼ���ģʽ��id������ز���
    int technology_id = SListBoxHelper::GetItemID( m_TechnologyListbox, nCurSel );
    if( technology_id == 0 ) return;
    TechnologyPtr technology = FIND_BY_ID( Technology, technology_id );
    if( technology == 0 ) return;

    m_DocEdit->SetWindowText( technology->doc );
    m_VideoEdit->SetWindowText( technology->video );
    m_IsKeyCheck->SetCheck( BOOL_2_INT( technology->iskey != 0 ) );
}

void TechnologyDialog::OnDocReadButtonClick()
{
    SMessageBox( GetSafeHwnd(), _T( "�����ĵ��Ķ���(��δʵ��!!)" ), _T( "������ʾ" ), MB_OK );
}

void TechnologyDialog::OnVideoPlayButtonClick()
{
    SMessageBox( GetSafeHwnd(), _T( "����������(��δʵ��!!)" ), _T( "������ʾ" ), MB_OK );
}

void TechnologyDialog::OnDocSelectButtonClick()
{
    SMessageBox( GetSafeHwnd(), _T( "ѡ���ĵ�(��δʵ��!!)" ), _T( "������ʾ" ), MB_OK );
}

void TechnologyDialog::OnVideoSelectButtonClick()
{
    SMessageBox( GetSafeHwnd(), _T( "ѡ����Ƶ(��δʵ��!!)" ), _T( "������ʾ" ), MB_OK );
}

void TechnologyDialog::OnSaveButtonClick()
{
    int technology_id = SListBoxHelper::GetCurSelItemID( m_TechnologyListbox );
    if( technology_id == 0 ) return;
    TechnologyPtr technology = FIND_BY_ID( Technology, technology_id );
    if( technology == 0 ) return;

    //���³�ɼ���������
    technology->iskey = m_IsKeyCheck->IsChecked();
    technology->doc = m_DocEdit->GetWindowText();
    technology->video = m_VideoEdit->GetWindowText();

    //���浽���ݿ�
    if( technology->save() )
    {
        SMessageBox( GetSafeHwnd(), _T( "���³�ɼ������ݳɹ�!!" ), _T( "������ʾ" ), MB_OK );
    }
}

void TechnologyDialog::OnDestroyWindow()
{
    //ɾ�����еĸ������ݲ����
    SListBoxHelper::Clear( m_TechnologyListbox );
    AcadSouiDialog::OnDestroyWindow();
}

void TechnologyDialog::fillTechnologyListBox()
{
    MineRegionPtr mine_region = FIND_ONE( MineRegion, FIELD( name ), regionName );
    if( mine_region == 0 ) return;

    RecordPtrListPtr lists = FIND_MANY( Technology, FKEY( MineRegion ), mine_region->getStringID() );
    if( lists == 0 ) return;

    SListBoxHelper::Clear( m_TechnologyListbox );
    for( int i = 0; i < lists->size(); i++ )
    {
        TechnologyPtr technology = DYNAMIC_POINTER_CAST( Technology, lists->at( i ) );
        SListBoxHelper::Add( m_TechnologyListbox, technology->name, technology->getID() );
    }
    SListBoxHelper::Select( m_TechnologyListbox, 0 );
}
