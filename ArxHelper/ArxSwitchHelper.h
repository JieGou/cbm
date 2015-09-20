#pragma once

#include "dlimexp.h"

// ϵͳ����������
// ���ڵ����ꡢ����������ж�
class ARXHELPER_DLLIMPEXP ArxTolSetter
{
public:
    ArxTolSetter( double eq )
    {
        m_originEq = AcGeContext::gTol.equalPoint();
        setEq( eq );
    }

    void setEq( double eq )
    {
        AcGeContext::gTol.setEqualPoint( eq );
    }

    ~ArxTolSetter()
    {
        AcGeContext::gTol.setEqualPoint( m_originEq );
    }

private:
    double m_originEq;
};

/*
ʹ�÷���:
ArxTolSetter ts(0.001); // ����������ʱ���Զ���ԭϵͳ���

�ȼ���:
// ����ϵͳ���
double ep = AcGeContext::gTol.equalPoint();
// �������
AcGeContext::gTol.setEqualPoint(0.001); // 10-3

// do something
// ...

// ��ԭϵͳ���
AcGeContext::gTol.setEqualPoint(ep);
*/

//��ģ̬���ĵ������л�
class ArxDocLockSwitch
{
public:
    ArxDocLockSwitch()
    {
        acDocManager->lockDocument( curDoc() );
    }
    ~ArxDocLockSwitch()
    {
        acDocManager->unlockDocument( curDoc() );
    }
};

//�л�controlbar��ʾ
class ArxCtrlBarShowSwitch
{
public:
    //���캯������controlbar
    ArxCtrlBarShowSwitch( CWnd* _dlg ) : dlg( _dlg )
    {
        ShowParentControlBar( dlg, FALSE );
    }
    //����������ʾcontrolbar
    ~ArxCtrlBarShowSwitch()
    {
        ShowParentControlBar( dlg, TRUE );
    }

private:
    static void ShowParentControlBar( CWnd* pWnd, BOOL bShow )
    {
        CAcModuleResourceOverride myResources;
        CControlBar* pBar = reinterpret_cast<CControlBar*>( pWnd->GetParent() );
        if( pBar == 0 ) return;

        CMDIFrameWnd* pAcadFrame = acedGetAcadFrame();
        if( pAcadFrame == 0 ) return;

        pAcadFrame->ShowControlBar( pBar, bShow, FALSE );
    }
    CWnd* dlg;
};

//�л�������ʾ/����
class ArxDialogShowSwitch
{
public:
    //���캯������
    ArxDialogShowSwitch( CWnd* _dlg ) : dlg( _dlg )
    {
        dlg->ShowWindow( SW_HIDE );
        ////������֮������CAD����ʧȥ����
        //dlg->SetFocus();
    }
    //����������ʾ
    ~ArxDialogShowSwitch()
    {
        dlg->ShowWindow( SW_SHOW );
    }
    CWnd* dlg;
};