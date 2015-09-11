#include "stdafx.h"
#include "MineDialog.h"
#include "CoalDialog.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>

using namespace orm;
using namespace cbm;

MineDialog::MineDialog( BOOL bModal ) : AcadSouiDialog( _T( "layout:mine" ), bModal )
{
    mine_id = 0;
}

MineDialog::~MineDialog()
{
}

void MineDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT MineDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    AcadSouiDialog::OnInitDialog( hWnd, lParam );
    //do something
    m_NameEdit = FindChildByName2<SEdit>( L"name" );
    m_CapacityEdit = FindChildByName2<SEdit>( L"capacity" );
    m_RegionCombox = FindChildByName2<SComboBox>( L"region" );
    m_BaseCombox = FindChildByName2<SComboBox>( L"base" );
    m_ProvinceEdit = FindChildByName2<SEdit>( L"province" );
    m_CityEdit = FindChildByName2<SEdit>( L"city" );
    m_TopoGeoCombox = FindChildByName2<SComboBox>( L"topo_geo" );
    m_GroundCondCheck = FindChildByName2<SCheckBox>( L"ground_cond" );
    m_HydrGeoCombox = FindChildByName2<SComboBox>( L"hydr_geo" );

    fillBaseCombox();
    fillMineDatas();

    return 0;
}


void MineDialog::OnNextButtonClick()
{
    AcadSouiDialog::OnOK();

    CoalDialog* dlg = new CoalDialog( FALSE );
    dlg->mine_id = mine_id;
    dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
}

void MineDialog::OnCancelButtonClick()
{
    AcadSouiDialog::OnCancel();
}

void MineDialog::OnRegionComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void MineDialog::OnBaseComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
    //���ҵ�ǰú̿���ض�Ӧ���еĿ���
    CString base = m_BaseCombox->GetLBText( pEvtOfCB->nCurSel );
    fillRegionCombox( base );
}

void MineDialog::OnSaveButtonClick()
{
    CString regionName = m_RegionCombox->GetWindowText();

    //���ݵ�ǰ�˻��Ŀ�
    MinePtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    mine->name = m_NameEdit->GetWindowText();
    mine->province = m_ProvinceEdit->GetWindowText();
    mine->city = m_CityEdit->GetWindowText();
    Utils::cstring_to_double( ( LPCTSTR )m_CapacityEdit->GetWindowText(), mine->capacity );
    mine->topo_geo = m_TopoGeoCombox->GetCurSel() + 1;
    mine->hydr_geo = m_HydrGeoCombox->GetCurSel() + 1;
    mine->ground_condition = m_GroundCondCheck->IsChecked();
    //���¿���������
    mine->region = FIND_ONE( Region, FIELD( name ), regionName );

    //���ӵ����ݿⲢ���������е�idֵ
    if( mine->save() )
    {
        CString msg;
        msg.Format( _T( "���¿�%s���ݳɹ�!" ), mine->name );
        SMessageBox( GetSafeHwnd(), msg, _T( "������ʾ" ), MB_OK );
    }
    else
    {
        CString msg;
        msg.Format( _T( "���¿�%s����ʧ��!" ), mine->name );
        SMessageBox( GetSafeHwnd(), msg, _T( "������ʾ" ), MB_OK );
    }
}

void MineDialog::OnTopoGeoComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void MineDialog::OnHydrGeoComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void MineDialog::fillBaseCombox()
{
    //�������е�ú̿����
    StringArray bases;
    DaoHelper::GetAllMineBases( bases );

    //������е�ú̿�����б�
    clearBaseCombox();
    for( int i = 0; i < bases.size(); i++ )
    {
        m_BaseCombox->InsertItem( i, bases[i], 0, 0 );
    }
    //SetCurSel�ᴥ��EVT_CB_SELCHANGE��Ϣ
    m_BaseCombox->SetCurSel( 0 );
}

void MineDialog::fillRegionCombox( const CString& base )
{
    StringArray regions;
    DaoHelper::GetAllMineRegions( base, regions );

    //��տ��������б�
    clearRegionCombox();
    for( int i = 0; i < regions.size(); i++ )
    {
        m_RegionCombox->InsertItem( i, regions[i], 0, 0 );
    }
    m_RegionCombox->SetCurSel( 0 );
}

void MineDialog::fillMineDatas()
{
    MinePtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    //�������
    m_NameEdit->SetWindowText( mine->name );
    m_CapacityEdit->SetWindowText( Utils::double_to_cstring( mine->capacity ) );

    //���ݿ����������
    CString regionName = mine->region->get( FIELD( name ) );
    CString baseName = DaoHelper::GetBaeByRegion( regionName );
    m_BaseCombox->SetCurSel( m_BaseCombox->FindString( baseName ) );
    m_RegionCombox->SetCurSel( m_RegionCombox->FindString( regionName ) );

    m_ProvinceEdit->SetWindowText( mine->province );
    m_CityEdit->SetWindowText( mine->city );
    m_TopoGeoCombox->SetCurSel( mine->topo_geo - 1 );
    m_HydrGeoCombox->SetCurSel( mine->hydr_geo - 1 );
    m_GroundCondCheck->SetCheck( BOOL_2_INT( mine->ground_condition != 0 ) );
}

void MineDialog::clearBaseCombox()
{
    m_BaseCombox->ResetContent();
}

void MineDialog::clearRegionCombox()
{
    m_RegionCombox->ResetContent();
}
