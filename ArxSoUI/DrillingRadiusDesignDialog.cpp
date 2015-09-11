#include "stdafx.h"
#include "DrillingRadiusDesignDialog.h"
#include "SouiListHelper.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>

using namespace orm;
using namespace cbm;

DrillingRadiusDesignDialog::DrillingRadiusDesignDialog( BOOL bModal ) : AcadSouiDialog( _T( "layout:drilling_radius_design" ), bModal )
{
    mine_id = 0;
}

DrillingRadiusDesignDialog::~DrillingRadiusDesignDialog()
{
}

void DrillingRadiusDesignDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT DrillingRadiusDesignDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    AcadSouiDialog::OnInitDialog( hWnd, lParam );
    //do something
    m_K1Edit = FindChildByName2<SEdit>( L"K1" );
    m_RhoEdit = FindChildByName2<SEdit>( L"rho" );
    m_AEdit = FindChildByName2<SEdit>( L"a" );
    m_TEdit = FindChildByName2<SEdit>( L"t" );
    m_LEdit = FindChildByName2<SEdit>( L"L" );
    m_Q0Edit = FindChildByName2<SEdit>( L"q0" );
    m_REdit = FindChildByName2<SEdit>( L"R" );
    m_QmEdit = FindChildByName2<SEdit>( L"Qm" );
    m_GasW0Edit = FindChildByName2<SEdit>( L"gas_W0" );
    m_QSumEdit = FindChildByName2<SEdit>( L"QSum" );
    m_EtaEdit = FindChildByName2<SEdit>( L"eta" );
    m_GasWc3Edit = FindChildByName2<SEdit>( L"gas_Wc3" );
    m_HwEdit = FindChildByName2<SEdit>( L"hw" );
    m_CoalCombox = FindChildByName2<SComboBox>( L"coal" );

    initCoalDatas();
    initDrillingRadiusDatas();

    return 0;
}


void DrillingRadiusDesignDialog::OnCaclButtonClick()
{
    //��ȡ��������
    double R = 0, L = 0, K1 = 0, rho = 0, q0 = 0, a = 0, t = 0, h = 0, W = 0, Q = 0;
    Utils::cstring_to_double( ( LPCTSTR )m_REdit->GetWindowText(), R );
    Utils::cstring_to_double( ( LPCTSTR )m_LEdit->GetWindowText(), L );
    Utils::cstring_to_double( ( LPCTSTR )m_K1Edit->GetWindowText(), K1 );
    Utils::cstring_to_double( ( LPCTSTR )m_RhoEdit->GetWindowText(), rho );
    Utils::cstring_to_double( ( LPCTSTR )m_Q0Edit->GetWindowText(), q0 );
    Utils::cstring_to_double( ( LPCTSTR )m_AEdit->GetWindowText(), a );
    Utils::cstring_to_double( ( LPCTSTR )m_TEdit->GetWindowText(), t );
    Utils::cstring_to_double( ( LPCTSTR )m_HwEdit->GetWindowText(), h );
    Utils::cstring_to_double( ( LPCTSTR )m_GasW0Edit->GetWindowText(), W );
    Utils::cstring_to_double( ( LPCTSTR )m_QSumEdit->GetWindowText(), Q );
    if( R == 0 || h == 0 || W == 0 || L == 0 )
    {
        SMessageBox( GetSafeHwnd(), _T( "��Ч����,���ܳ��ֵ���0�����!" ), _T( "������ʾ" ), MB_OK );
        return;
    }

    //����Qm
    double Qm = 0;
    if( 2 * R < h || fabs( 2 * R - h ) < 1e-3 ) // 2R<=h
    {
        double S = PI * R * R;
        Qm = 1440 * K1 * q0 * ( 1 - exp( -1 * a * t ) ) / ( rho * a * S * ( R + L ) );
    }
    else
    {
        double S = 2 * R * R * asin( 0.5 * h / R ) + h * sqrt( R * R - 0.25 * h * h );
        Qm = 1440 * K1 * q0 * ( 1 - exp( -1 * a * t ) ) / ( rho * a * S * ( R + L ) );
    }

    //����eta��Wc,���չ�ʽҪ��eta>=0.3, Wc<=8
    double eta = Qm / W; //
    double Wc = W - Q;
    //���µ�����
    m_EtaEdit->SetWindowText( Utils::double_to_cstring( eta ) );
    m_GasWc3Edit->SetWindowText( Utils::double_to_cstring( Wc ) );

    //��ӡ��ʾ
    CString msg;
    msg.Format( _T( "���ݹ涨Ҫ��:\\n" ) );
    msg.AppendFormat( _T( "    ����ʦ�=%.2fӦ���ڵ���0.3" ), eta );
    msg.AppendFormat( _T( "    ��ɺ�ú��д���˹����Wc=%.3fӦС�ڵ���8" ), Wc );
    SMessageBox( GetSafeHwnd(), msg, _T( "������ʾ" ), MB_OK );
}

void DrillingRadiusDesignDialog::OnSaveButtonClick()
{
    int coal_id = SComboBoxHelper::GetCurSelItemID( m_CoalCombox );
    if( coal_id == 0 ) return;
    CoalPtr coal = FIND_BY_ID( Coal, coal_id );
    if( coal == 0 ) return;

    //����ú������
    Utils::cstring_to_double( ( LPCTSTR )m_HwEdit->GetWindowText(), coal->hw );
    Utils::cstring_to_double( ( LPCTSTR )m_GasW0Edit->GetWindowText(), coal->gas_w0 );
    Utils::cstring_to_double( ( LPCTSTR )m_GasWc3Edit->GetWindowText(), coal->gas_wc3 );

    //��˹�뾶����
    DrillingRadiusParamPtr drp = FIND_ONE( DrillingRadiusParam, FKEY( Coal ), coal->getStringID() );
    if( drp == 0 )
    {
        drp.reset( new DrillingRadiusParam );
    }
    Utils::cstring_to_double( ( LPCTSTR )m_RhoEdit->GetWindowText(), drp->rho );
    Utils::cstring_to_double( ( LPCTSTR )m_AEdit->GetWindowText(), drp->a );
    Utils::cstring_to_double( ( LPCTSTR )m_TEdit->GetWindowText(), drp->t );
    Utils::cstring_to_double( ( LPCTSTR )m_LEdit->GetWindowText(), drp->l );
    Utils::cstring_to_double( ( LPCTSTR )m_Q0Edit->GetWindowText(), drp->q0 );
    Utils::cstring_to_double( ( LPCTSTR )m_REdit->GetWindowText(), drp->r );
    Utils::cstring_to_double( ( LPCTSTR )m_QmEdit->GetWindowText(), drp->qm );
    Utils::cstring_to_double( ( LPCTSTR )m_QSumEdit->GetWindowText(), drp->qsum );
    Utils::cstring_to_double( ( LPCTSTR )m_EtaEdit->GetWindowText(), drp->eta );
    Utils::cstring_to_double( ( LPCTSTR )m_K1Edit->GetWindowText(), drp->k1 );
    //���浽���ݿ�
    if( !drp->save() )
    {
        SMessageBox( GetSafeHwnd(), _T( "��������ʧ��!" ), _T( "������ʾ" ), MB_OK );
    }
    else
    {
        SMessageBox( GetSafeHwnd(), _T( "�������ݳɹ�!" ), _T( "������ʾ" ), MB_OK );
    }
}

void DrillingRadiusDesignDialog::OnCoalComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
    initCoalDatas();
    initDrillingRadiusDatas();

    int coal_id = SComboBoxHelper::GetItemID( m_CoalCombox, nCurSel );
    if( coal_id == 0 ) return;
    CoalPtr coal = FIND_BY_ID( Coal, coal_id );
    if( coal == 0 ) return;
    //ú������
    m_HwEdit->SetWindowText( Utils::double_to_cstring( coal->hw ) );
    m_GasW0Edit->SetWindowText( Utils::double_to_cstring( coal->gas_w0 ) );
    m_GasWc3Edit->SetWindowText( Utils::double_to_cstring( coal->gas_wc3 ) );
    //���浽���ݿ�
    if( !coal->save() ) return;

    //��˹�뾶����
    DrillingRadiusParamPtr drp = FIND_ONE( DrillingRadiusParam, FKEY( Coal ), coal->getStringID() );
    if( drp != 0 )
    {
        m_RhoEdit->SetWindowText( Utils::double_to_cstring( drp->rho ) );
        m_AEdit->SetWindowText( Utils::double_to_cstring( drp->a ) );
        m_TEdit->SetWindowText( Utils::double_to_cstring( drp->t ) );
        m_LEdit->SetWindowText( Utils::double_to_cstring( drp->l ) );
        m_Q0Edit->SetWindowText( Utils::double_to_cstring( drp->q0 ) );
        m_REdit->SetWindowText( Utils::double_to_cstring( drp->r ) );
        m_QmEdit->SetWindowText( Utils::double_to_cstring( drp->qm ) );
        m_QSumEdit->SetWindowText( Utils::double_to_cstring( drp->qsum ) );
        m_EtaEdit->SetWindowText( Utils::double_to_cstring( drp->eta ) );
        m_K1Edit->SetWindowText( Utils::double_to_cstring( drp->k1 ) );
    }
}

void DrillingRadiusDesignDialog::OnDestroyWindow()
{
    //ɾ�����еĸ�������
    SComboBoxHelper::Clear( m_CoalCombox );
    AcadSouiDialog::OnDestroyWindow();
}

void DrillingRadiusDesignDialog::fillCoalCombox()
{
    MinePtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    StringArray coal_names;
    IntArray coal_ids;
    DaoHelper::GetCoalIds( mine->getID(), coal_ids );
    DaoHelper::GetCoalNames( mine->getID(), coal_names );

    SComboBoxHelper::Clear( m_CoalCombox );
    SComboBoxHelper::Append( m_CoalCombox, coal_names, coal_ids );
    SComboBoxHelper::Select( m_CoalCombox, 0 );
}

void DrillingRadiusDesignDialog::initCoalDatas()
{
    m_HwEdit->SetWindowText( NULL );
    m_GasW0Edit->SetWindowText( NULL );
    m_GasWc3Edit->SetWindowText( NULL );
    //m_CoalCombox->SetCurSel(-1);
}

void DrillingRadiusDesignDialog::initDrillingRadiusDatas()
{
    m_RhoEdit->SetWindowText( NULL );
    m_AEdit->SetWindowText( NULL );
    m_TEdit->SetWindowText( NULL );
    m_LEdit->SetWindowText( NULL );
    m_Q0Edit->SetWindowText( NULL );
    m_REdit->SetWindowText( NULL );
    m_QmEdit->SetWindowText( NULL );
    m_QSumEdit->SetWindowText( NULL );
    m_EtaEdit->SetWindowText( NULL );
    m_K1Edit->SetWindowText( _T( "1.2" ) );
}
