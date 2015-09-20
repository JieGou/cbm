#pragma once
#include "AcadSouiDialog.h"

class DifficultEvalDialog : public AcadSouiDialog
{

    /** ������������� */
public:
    DifficultEvalDialog( BOOL bModal = FALSE );
    ~DifficultEvalDialog( void );

    /** �ؼ���Ϣ���� */
protected:
    void OnCancelButtonClick();
    void OnEvalButtonClick();
    void OnEvalProofButtonClick();
    void OnEvalDifficultComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnCoalComboxSelChanged( SOUI::EventArgs* pEvt );
    void OnPermeabilityKEditSetFocus( SOUI::EventArgs* pEvt );
    void OnPermeabilityLambdaEditSetFocus( SOUI::EventArgs* pEvt );

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
    EVENT_NAME_COMMAND( _T( "cancel" ), OnCancelButtonClick )
    EVENT_NAME_COMMAND( _T( "eval" ), OnEvalButtonClick )
    EVENT_NAME_COMMAND( _T( "eval_proof" ), OnEvalProofButtonClick )
    EVENT_NAME_HANDLER( _T( "eval_difficult" ), EVT_CB_SELCHANGE, OnEvalDifficultComboxSelChanged )
    EVENT_NAME_HANDLER( _T( "coal" ), EVT_CB_SELCHANGE, OnCoalComboxSelChanged )
    EVENT_NAME_HANDLER( _T( "permeability_k" ), EVT_SETFOCUS, OnPermeabilityKEditSetFocus )
    EVENT_NAME_HANDLER( _T( "permeability_lambda" ), EVT_SETFOCUS, OnPermeabilityLambdaEditSetFocus )
    CHAIN_EVENT_MAP( AcadSouiDialog )
    EVENT_MAP_END()

//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
    BEGIN_MSG_MAP_EX( DifficultEvalDialog )
    MSG_WM_INITDIALOG( OnInitDialog )
    MSG_WM_COMMAND( OnCommand )
    CHAIN_MSG_MAP( AcadSouiDialog )
    REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()

protected:
    SEdit* m_PermeabilityKEdit;
    SEdit* m_DecayAlphaEdit;
    SEdit* m_PermeabilityLambdaEdit;
    SComboBox* m_EvalDifficultCombox;
    SComboBox* m_CoalCombox;

public:
    int mine_id;

protected:
    virtual void OnDestroyWindow();

private:
    void fillCoalCombox();
    void initCoalDatas();
};
