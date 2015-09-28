#include "stdafx.h"
#include "SampleManageDialog.h"
#include "TechModeDialog.h"
#include "TechnologyDialog.h"
#include "SouiListHelper.h"
#include "NameDialog.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>

using namespace orm;
using namespace cbm;

SampleManageDialog::SampleManageDialog( BOOL bModal ) : AcadSouiDialog( _T( "layout:sample_manage" ), bModal )
{
}

SampleManageDialog::~SampleManageDialog()
{
}

void SampleManageDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT SampleManageDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    AcadSouiDialog::OnInitDialog( hWnd, lParam );

    //do something
    m_RegionCombox = FindChildByName2<SComboBox>( L"region" );
    m_TopoGeoCombox = FindChildByName2<SComboBox>( L"topo_geo" );
    m_GroundCondCheck = FindChildByName2<SCheckBox>( L"ground_cond" );
    m_HydrGeoCombox = FindChildByName2<SComboBox>( L"hydr_geo" );
    m_FValueEdit = FindChildByName2<SEdit>( L"f_value" );
    m_ThickEdit = FindChildByName2<SEdit>( L"thick" );
    m_RankCombox = FindChildByName2<SComboBox>( L"rank" );
    m_PressureEdit = FindChildByName2<SEdit>( L"pressure" );
    m_GasContentEdit = FindChildByName2<SEdit>( L"gas_content" );
    m_GasPenetrationEdit = FindChildByName2<SEdit>( L"gas_penetration" );
    m_ConstComplexityCombox = FindChildByName2<SComboBox>( L"const_complexity" );
    m_VarCoeffEdit = FindChildByName2<SEdit>( L"var_coeff" );
    m_DipAngleEdit = FindChildByName2<SEdit>( L"dip_angle" );
    m_CavingZoneHeightEdit = FindChildByName2<SEdit>( L"caving_zone_height" );
    m_ResAbundanceCombox = FindChildByName2<SComboBox>( L"res_abundance" );
    m_LayerGapEdit = FindChildByName2<SEdit>( L"layer_gap" );
    m_InfluenceFactorEdit = FindChildByName2<SEdit>( L"influence_factor" );
    m_MineIndexEdit = FindChildByName2<SEdit>( L"mine_index" );
    m_StabilityCombox = FindChildByName2<SComboBox>( L"stability" );
    m_MinableCheck = FindChildByName2<SCheckBox>( L"minable" );

    //��OnInitDialog��ֱ�ӵ���SetCurSel��Ч!!!(ԭ��δ֪)
    //m_RegionCombox->SetCurSel(0);
    EventCBSelChange evtCBSelChange( m_RegionCombox, 0 );
    FireEvent( evtCBSelChange );

    return 0;
}

void SampleManageDialog::OnRegionComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;

    //��ʼ��ú����Ϣ�ֶ�
    initMineDatas();
    initCoalDatas();

    //�õ�ʾ�������������
    CString regionName = m_RegionCombox->GetLBText( pEvtOfCB->nCurSel );
    MinePtr mine = DaoHelper::GetSampleMine( regionName );
    if( mine == 0 ) return;

    CoalPtr coal = DaoHelper::GetSampleCoal( regionName );
    if( coal == 0 ) return;

    //���󾮿�������
    m_TopoGeoCombox->SetCurSel( mine->topo_geo - 1 );
    m_HydrGeoCombox->SetCurSel( mine->hydr_geo - 1 );
    m_GroundCondCheck->SetCheck( mine->ground_condition != 0 ? TRUE : FALSE );

    //���ú���б�����
    m_ThickEdit->SetWindowText( Utils::double_to_cstring( coal->thick ) );
    m_RankCombox->SetCurSel( coal->rank - 1 );
    m_PressureEdit->SetWindowText( Utils::double_to_cstring( coal->pressure ) );
    m_GasContentEdit->SetWindowText( Utils::double_to_cstring( coal->gas_content ) );
    m_GasPenetrationEdit->SetWindowText( Utils::double_to_cstring( coal->gas_penetration ) );
    m_FValueEdit->SetWindowText( Utils::double_to_cstring( coal->f_value ) );
    m_ResAbundanceCombox->SetCurSel( coal->res_abundance - 1 );
    m_ConstComplexityCombox->SetCurSel( coal->complexity - 1 );
    m_MineIndexEdit->SetWindowText( Utils::double_to_cstring( coal->mine_index ) );
    m_VarCoeffEdit->SetWindowText( Utils::double_to_cstring( coal->var_coeff ) );
    m_StabilityCombox->SetCurSel( coal->stability - 1 );
    m_DipAngleEdit->SetWindowText( Utils::double_to_cstring( coal->dip_angle ) );
    m_CavingZoneHeightEdit->SetWindowText( Utils::double_to_cstring( coal->czh ) );
    m_MinableCheck->SetCheck( BOOL_2_INT( coal->minable != 0 ) );
}

void SampleManageDialog::OnTopoGeoComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void SampleManageDialog::OnHydrGeoComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void SampleManageDialog::OnRankComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void SampleManageDialog::OnConstComplexityComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void SampleManageDialog::OnResAbundanceComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void SampleManageDialog::OnStabilityComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void SampleManageDialog::OnSaveButtonClick()
{
    CString regionName = m_RegionCombox->GetLBText( m_RegionCombox->GetCurSel() );
    MinePtr mine = DaoHelper::GetSampleMine( regionName );
    if( mine == 0 ) return;

    CoalPtr coal = DaoHelper::GetSampleCoal( regionName );
    if( coal == 0 ) return;

    mine->topo_geo = m_TopoGeoCombox->GetCurSel() + 1;
    mine->hydr_geo = m_HydrGeoCombox->GetCurSel() + 1;
    mine->ground_condition = m_GroundCondCheck->IsChecked();
    if( !mine->save() ) return;

    Utils::cstring_to_double( ( LPCTSTR )m_ThickEdit->GetWindowText(), coal->thick ); // ú��
    coal->rank = m_RankCombox->GetCurSel() + 1; // ú��
    Utils::cstring_to_double( ( LPCTSTR )m_PressureEdit->GetWindowText(), coal->pressure ); // ����ѹ��
    Utils::cstring_to_double( ( LPCTSTR )m_GasContentEdit->GetWindowText(), coal->gas_content ); // ������
    Utils::cstring_to_double( ( LPCTSTR )m_GasPenetrationEdit->GetWindowText(), coal->gas_penetration ); // ��͸��
    Utils::cstring_to_double( ( LPCTSTR )m_FValueEdit->GetWindowText(), coal->f_value ); // fֵ
    coal->res_abundance = m_ResAbundanceCombox->GetCurSel() + 1; // ú�����������
    coal->complexity = m_ConstComplexityCombox->GetCurSel() + 1; // ���츴�ӳ̶�
    Utils::cstring_to_double( ( LPCTSTR )m_MineIndexEdit->GetWindowText(), coal->mine_index ); // �ɲ���ָ��
    Utils::cstring_to_double( ( LPCTSTR )m_VarCoeffEdit->GetWindowText(), coal->var_coeff ); // ����ϵ��
    coal->stability = m_StabilityCombox->GetCurSel() + 1; // ú���ȶ���
    Utils::cstring_to_double( ( LPCTSTR )m_DipAngleEdit->GetWindowText(), coal->dip_angle ); // ú�����
    Utils::cstring_to_double( ( LPCTSTR )m_CavingZoneHeightEdit->GetWindowText(), coal->czh ); // ð����߶�
    coal->minable = m_MinableCheck->IsChecked(); // �Ƿ�ɲ�ú��
    if( !coal->save() ) return;

    SMessageBox( GetSafeHwnd(), _T( "���³ɹ�!" ), _T( "������ʾ" ), MB_OK );
}

void SampleManageDialog::OnTechModeButtonClick()
{
    CString regionName = m_RegionCombox->GetLBText( m_RegionCombox->GetCurSel() );
    TechModeDialog dlg( TRUE );
	dlg.SetWindowTitle(_T("ú��������˹����ɼ���ģʽ�����趨"));
    dlg.regionName = regionName; // ����ʾ������������
    dlg.Run( GetSafeHwnd() );
}

void SampleManageDialog::OnTechnologyButtonClick()
{
    CString regionName = SComboBoxHelper::GetCurSelString( m_RegionCombox );
    TechnologyDialog dlg( TRUE );
	dlg.SetWindowTitle(_T("�Ƽ�ú��������˹����ɼ���"));
    dlg.regionName = regionName; // ����ʾ������������
    dlg.Run( GetSafeHwnd() );
}

void SampleManageDialog::OnDestroyWindow()
{
    //ɾ�����еĸ�������
    AcadSouiDialog::OnDestroyWindow();
}

void SampleManageDialog::initMineDatas()
{
    m_HydrGeoCombox->SetCurSel( -1 );
    m_TopoGeoCombox->SetCurSel( -1 );
    m_GroundCondCheck->SetCheck( FALSE );
}

void SampleManageDialog::initCoalDatas()
{
    m_ThickEdit->SetWindowText( NULL );
    m_RankCombox->SetCurSel( -1 );
    m_PressureEdit->SetWindowText( NULL );
    m_GasContentEdit->SetWindowText( NULL );
    m_GasPenetrationEdit->SetWindowText( NULL );
    m_FValueEdit->SetWindowText( NULL );
    m_ResAbundanceCombox->SetCurSel( -1 );
    m_ConstComplexityCombox->SetCurSel( -1 );
    m_MineIndexEdit->SetWindowText( NULL );
    m_VarCoeffEdit->SetWindowText( NULL );
    m_StabilityCombox->SetCurSel( -1 );
    m_DipAngleEdit->SetWindowText( NULL );
    m_CavingZoneHeightEdit->SetWindowText( NULL );
    m_MinableCheck->SetCheck( FALSE );
}
