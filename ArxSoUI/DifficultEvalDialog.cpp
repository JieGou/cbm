#include "stdafx.h"
#include "DifficultEvalDialog.h"
#include "SouiListHelper.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>

using namespace orm;
using namespace cbm;

DifficultEvalDialog::DifficultEvalDialog( BOOL bModal ) : AcadSouiDialog( _T( "layout:difficult_eval" ), bModal )
{
    mine_id = 0;
}

DifficultEvalDialog::~DifficultEvalDialog()
{
}

void DifficultEvalDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if( uNotifyCode == 0 )
    {
        //if(nID==6)
        //{
        //}
    }
}

LRESULT DifficultEvalDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    AcadSouiDialog::OnInitDialog( hWnd, lParam );
    //do something
    m_PermeabilityKEdit = FindChildByName2<SEdit>( L"permeability_k" );
    m_DecayAlphaEdit = FindChildByName2<SEdit>( L"decay_alpha" );
    m_PermeabilityLambdaEdit = FindChildByName2<SEdit>( L"permeability_lambda" );
    m_EvalDifficultCombox = FindChildByName2<SComboBox>( L"eval_difficult" );
    m_CoalCombox = FindChildByName2<SComboBox>( L"coal" );

    initCoalDatas();
    fillCoalCombox();

    return 0;
}


void DifficultEvalDialog::OnCancelButtonClick()
{
    AcadSouiDialog::OnCancel();
}

void DifficultEvalDialog::OnEvalButtonClick()
{
    ItemData* pData = ( ItemData* )m_CoalCombox->GetItemData( m_CoalCombox->GetCurSel() );
    if( pData == 0 ) return;
    CoalPtr coal = FIND_BY_ID( Coal, pData->id );
    if( coal == 0 ) return;

    //�ӽ�����ȡ����
    Utils::cstring_to_double( ( LPCTSTR )m_PermeabilityKEdit->GetWindowText(), coal->permeability_k );
    Utils::cstring_to_double( ( LPCTSTR )m_PermeabilityLambdaEdit->GetWindowText(), coal->permeability_lambda );
    Utils::cstring_to_double( ( LPCTSTR )m_DecayAlphaEdit->GetWindowText(), coal->decay_alpha );

    //�����������˥��ϵ�� �� ú��͸����ϵ����������
    coal->eval_difficult = DaoHelper::DifficultEval( coal );

    if( coal->eval_difficult != 0 )
    {
        //���浽���ݿ�
        coal->eval_difficult = m_EvalDifficultCombox->GetCurSel() + 1;
        if( coal->save() )
        {
            SMessageBox( GetSafeHwnd(), DaoHelper::DifficultEvalString( coal ), _T( "������ʾ" ), MB_OK );
        }
    }
    //�������۽��۵�����
    m_EvalDifficultCombox->SetCurSel( coal->eval_difficult - 1 );
}

void DifficultEvalDialog::OnEvalProofButtonClick()
{

}

void DifficultEvalDialog::OnEvalDifficultComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
}

void DifficultEvalDialog::OnCoalComboxSelChanged( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;
    EventCBSelChange* pEvtOfCB = ( EventCBSelChange* )pEvt;
    if( pEvtOfCB == 0 ) return;
    int nCurSel = pEvtOfCB->nCurSel;
    if( nCurSel == -1 ) return;

    // do something
    initCoalDatas();
    int coal_id = SComboBoxHelper::GetItemID( m_CoalCombox, nCurSel );
    if( coal_id == 0 ) return;
    CoalPtr coal = FIND_BY_ID( Coal, coal_id );
    if( coal == 0 ) return;

    m_DecayAlphaEdit->SetWindowText( Utils::double_to_cstring( coal->decay_alpha ) );
    m_PermeabilityLambdaEdit->SetWindowText( Utils::double_to_cstring( coal->permeability_lambda ) );
    m_PermeabilityKEdit->SetWindowText( Utils::double_to_cstring( coal->permeability_k ) );
    m_EvalDifficultCombox->SetCurSel( coal->eval_difficult - 1 );
}

void DifficultEvalDialog::OnPermeabilityKEditSetFocus( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;

    //�ӽ�����ȡ"͸����ϵ��"
    double permeability_k = 0;
    double permeability_lambda = 0;
    Utils::cstring_to_double( ( LPCTSTR )m_PermeabilityLambdaEdit->GetWindowText(), permeability_lambda );
    permeability_k = 0.025 * permeability_lambda;
    //���µ�����
    m_PermeabilityKEdit->SetWindowText( Utils::double_to_cstring( permeability_k, 3 ) );
}

void DifficultEvalDialog::OnPermeabilityLambdaEditSetFocus( SOUI::EventArgs* pEvt )
{
    if( !isLayoutInited() ) return;

    //�ӽ�����ȡ"��͸��"
    double permeability_k = 0;
    double permeability_lambda = 0;
    Utils::cstring_to_double( ( LPCTSTR )m_PermeabilityKEdit->GetWindowText(), permeability_k );
    permeability_lambda = permeability_k / 0.025;
    //���µ�����
    m_PermeabilityLambdaEdit->SetWindowText( Utils::double_to_cstring( permeability_lambda ) );
}

void DifficultEvalDialog::OnDestroyWindow()
{
    //ɾ�����еĸ�������
    SComboBoxHelper::Clear( m_CoalCombox );
    AcadSouiDialog::OnDestroyWindow();
}

void DifficultEvalDialog::initCoalDatas()
{
    m_DecayAlphaEdit->SetWindowText( NULL );
    m_PermeabilityKEdit->SetWindowText( NULL );
    m_PermeabilityLambdaEdit->SetWindowText( NULL );
    m_EvalDifficultCombox->SetCurSel( -1 );
}

void DifficultEvalDialog::fillCoalCombox()
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