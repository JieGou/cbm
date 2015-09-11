#include "stdafx.h"
#include "MineGasFlowPredictDialog.h"
#include "MineGasFlowPredictDesignDialog.h"
#include "NameDialog.h"
#include "SouiListHelper.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>

using namespace orm;
using namespace cbm;

MineGasFlowPredictDialog::MineGasFlowPredictDialog( BOOL bModal ) : AcadSouiDialog( _T( "layout:mine_gas_flow_predict" ), bModal )
{
    mine_id = 0;
}

MineGasFlowPredictDialog::~MineGasFlowPredictDialog()
{
}

void MineGasFlowPredictDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT MineGasFlowPredictDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    AcadSouiDialog::OnInitDialog( hWnd, lParam );
    //do something
    m_WorkAreaAEdit = FindChildByName2<SEdit>( L"work_area_A" );
    m_K1GasEdit = FindChildByName2<SEdit>( L"K1_gas" );
    m_QrEdit = FindChildByName2<SEdit>( L"qr" );
    m_K2GasEdit = FindChildByName2<SEdit>( L"K2_gas" );
    m_WorkAreaCombox = FindChildByName2<SComboBox>( L"work_area" );
    m_WorkAreaQrEdit = FindChildByName2<SEdit>( L"work_area_qr" );
    m_CoalCombox = FindChildByName2<SComboBox>( L"coal" );

    initMineDatas();
    initWorkAreaDatas();
    fillCoalCombox();
    fillWorkAreadCombox();
    return 0;
}


void MineGasFlowPredictDialog::OnK1HelpButtonClick()
{
    SMessageBox( GetSafeHwnd(), _T( "K1����(��δʵ��,����������!!!" ), _T( "������ʾ" ), MB_OK );
}

void MineGasFlowPredictDialog::OnSaveButtonClick()
{
    //���浱ǰ����������
    WorkAreaPtr work_area = getCurSelWorkArea();
    if( work_area == 0 ) return;

    Utils::cstring_to_double( ( LPCTSTR )m_WorkAreaAEdit->GetWindowText(), work_area->a );
    Utils::cstring_to_double( ( LPCTSTR )m_WorkAreaQrEdit->GetWindowText(), work_area->qr );
    work_area->coal = getCurSelCoal();
    //���µ����ݿ�
    if( !work_area->save() ) return;

    //����󾮵�����
    MinePtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    Utils::cstring_to_double( ( LPCTSTR )m_K1GasEdit->GetWindowText(), mine->gas_k1 );
    Utils::cstring_to_double( ( LPCTSTR )m_K2GasEdit->GetWindowText(), mine->gas_k2 );
    Utils::cstring_to_double( ( LPCTSTR )m_QrEdit->GetWindowText(), mine->qr );
    //���µ����ݿ�
    if( !mine->save() ) return;
}

void MineGasFlowPredictDialog::OnK2HelpButtonClick()
{
    SMessageBox( GetSafeHwnd(), _T( "K2����(��δʵ��,����������!!!" ), _T( "������ʾ" ), MB_OK );
}

void MineGasFlowPredictDialog::OnWorkAreaComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    //��յ�ǰ����������
    initWorkAreaDatas();

    //����ǰ������id
    int work_area_id =  SComboBoxHelper::GetItemID( m_WorkAreaCombox, nCurSel );
    if( work_area_id == 0 ) return;
    //����id���Ҳ���
    WorkAreaPtr work_area = FIND_BY_ID( WorkArea, work_area_id );
    if( work_area == 0 ) return;

    //���½����ϵĲ�������
    m_WorkAreaAEdit->SetWindowText( Utils::double_to_cstring( work_area->a ) );
    m_WorkAreaQrEdit->SetWindowText( Utils::double_to_cstring( work_area->qr ) );

    //���²������ڵ�ú��
    if( work_area->coal == 0 )
    {
        m_CoalCombox->SetCurSel( -1 );
    }
    else
    {
        SComboBoxHelper::SetCurSelByString( m_CoalCombox, work_area->coal->get( FIELD( name ) ) );
    }
}

void MineGasFlowPredictDialog::OnWorkAreaCaclButtonClick()
{
    //��ǰ����
    WorkAreaPtr work_area = getCurSelWorkArea();
    if( work_area == 0 ) return;

    //�������еĻزɹ�����
    double S1 = 0;
    RecordPtrListPtr ws_lists = FIND_MANY( WorkSurf, FKEY( WorkArea ), work_area->getStringID() );
    if( ws_lists != 0 )
    {
        for( int i = 0; i < ws_lists->size(); i++ )
        {
            WorkSurfPtr ws = DYNAMIC_POINTER_CAST( WorkSurf, ws_lists->at( i ) );
            if( ws == 0 ) continue;

            double qr = ws->qr;
            double A = ws->a;
            S1 += A * qr;
        }
    }

    //�������еľ����
    double S2 = 0;
    RecordPtrListPtr tws_lists = FIND_MANY( DrillingSurf, FKEY( WorkArea ), work_area->getStringID() );
    if( tws_lists != 0 )
    {
        for( int i = 0; i < tws_lists->size(); i++ )
        {
            DrillingSurfPtr tws = DYNAMIC_POINTER_CAST( DrillingSurf, tws_lists->at( i ) );
            if( tws == 0 ) continue;

            double qr = tws->qa;
            S2 += qr;
        }
    }

    //�����������˹ӿ����
    double K1 = 0;
    Utils::cstring_to_double( ( LPCTSTR )m_K1GasEdit->GetWindowText(), K1 );
    double A0 = 0;
    Utils::cstring_to_double( ( LPCTSTR )m_WorkAreaAEdit->GetWindowText(), A0 );
    if( A0 <= 0 )
    {
        SMessageBox( GetSafeHwnd(), _T( "�������ղ���A�������0!!!" ), _T( "������ʾ" ), MB_OK );
    }
    else
    {
        work_area->a = A0;
        work_area->qr = K1 * ( S1 + S2 ) / A0;
        work_area->coal = getCurSelCoal();
        if( work_area->save() )
        {
            //��������˹ӿ�������������µ�����
            m_WorkAreaQrEdit->SetWindowText( Utils::double_to_cstring( work_area->qr ) );
        }
    }
}

void MineGasFlowPredictDialog::OnCaclButtonClick()
{
    MinePtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    //���Ҹÿ����еĲ���
    RecordPtrListPtr lists = DaoHelper::GetWorkAreas( mine->getID() );
    if( lists == 0 ) return;

    double S1 = 0, S2 = 0;
    for( int i = 0; i < lists->size(); i++ )
    {
        WorkAreaPtr work_area = DYNAMIC_POINTER_CAST( WorkArea, lists->at( i ) );
        double qr = work_area->qr;
        double A0 = work_area->a;
        S1 += qr * A0;
        S2 += A0;
    }
    if( S2 <= 0 )
    {
        SMessageBox( GetSafeHwnd(), _T( "����:�������ղ���֮�͵���0!!!" ), _T( "������ʾ" ), MB_OK );
    }
    else
    {
        double K2 = 0;
        Utils::cstring_to_double( ( LPCTSTR )m_K2GasEdit->GetWindowText(), K2 );
        //���㲢���¿󾮵���˹ӿ����
        mine->qr = K2 * S1 / S2;
        //���浽���ݿ�
        if( mine->save() )
        {
            //���µ�����
            m_QrEdit->SetWindowText( Utils::double_to_cstring( mine->qr ) );
        }
    }
}

void MineGasFlowPredictDialog::OnCoalComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void MineGasFlowPredictDialog::OnAssignButtonClick()
{
    //��ȡ��ǰú��
    CoalPtr coal = getCurSelCoal();
    if( coal == 0 ) return;

    //��ȡ��ǰ����
    WorkAreaPtr work_area = getCurSelWorkArea();
    if( work_area == 0 ) return;

    //�����������µ�ú��
    work_area->coal = coal;
    //���浽���ݿ�
    if( work_area->save() )
    {
        CString msg;
        msg.Format( _T( "����%s�ɹ�������ú��%s" ), work_area->name, coal->name );
        SMessageBox( GetSafeHwnd(), msg, _T( "������ʾ" ), MB_OK );
    }
}

void MineGasFlowPredictDialog::OnDesignWorkAreaButtonClick()
{
    WorkAreaPtr work_area = getCurSelWorkArea();
    if( work_area == 0 ) return;

    //���öԻ���
    //������;�������˹ӿ������ز��������
    MineGasFlowPredictDesignDialog dlg( TRUE );
    dlg.work_area_id = work_area->getID(); // �������id���
    dlg.Run( GetSafeHwnd() );
}

void MineGasFlowPredictDialog::OnDestroyWindow()
{
    //ɾ�����еĸ�������
    SComboBoxHelper::Clear( m_CoalCombox );
    SComboBoxHelper::Clear( m_WorkAreaCombox );
    AcadSouiDialog::OnDestroyWindow();
}

void MineGasFlowPredictDialog::fillCoalCombox()
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

void MineGasFlowPredictDialog::initMineDatas()
{
    m_WorkAreaCombox->SetCurSel( -1 );
    m_CoalCombox->SetCurSel( -1 );
    m_WorkAreaAEdit->SetWindowText( NULL );
    m_WorkAreaQrEdit->SetWindowText( NULL );
}

void MineGasFlowPredictDialog::initWorkAreaDatas()
{
    m_K1GasEdit->SetWindowText( NULL );
    m_K2GasEdit->SetWindowText( NULL );
    m_QrEdit->SetWindowText( NULL );
}

void MineGasFlowPredictDialog::fillWorkAreadCombox()
{
    SComboBoxHelper::Clear( m_WorkAreaCombox );

    //��ǰ�����û���ú��
    MinePtr mine = FIND_BY_ID( Mine, mine_id );
    if( mine == 0 ) return;

    //���Ҹÿ����еĲ���
    RecordPtrListPtr lists = DaoHelper::GetWorkAreas( mine->getID() );
    if( lists == 0 ) return;

    for( int i = 0; i < lists->size(); i++ )
    {
        WorkAreaPtr work_area = DYNAMIC_POINTER_CAST( WorkArea, lists->at( i ) );
        SComboBoxHelper::Add( m_WorkAreaCombox, work_area->name, work_area->getID() );
    }
    SComboBoxHelper::Select( m_WorkAreaCombox, 0 );
}

CoalPtr MineGasFlowPredictDialog::getCurSelCoal()
{
    int coal_id = SComboBoxHelper::GetCurSelItemID( m_CoalCombox );
    if( coal_id == 0 ) return CoalPtr();
    return FIND_BY_ID( Coal, coal_id );
}

WorkAreaPtr MineGasFlowPredictDialog::getCurSelWorkArea()
{
    int work_area_id = SComboBoxHelper::GetCurSelItemID( m_WorkAreaCombox );
    if( work_area_id == 0 ) return WorkAreaPtr();
    return FIND_BY_ID( WorkArea, work_area_id );
}