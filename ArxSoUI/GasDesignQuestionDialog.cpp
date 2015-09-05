#include "stdafx.h"
#include "GasDesignQuestionDialog.h"
#include "SouiListHelper.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

GasDesignQuestionDialog::GasDesignQuestionDialog(BOOL bModal) : AcadSouiDialog(_T("layout:gas_design_question"), bModal)
{
	region = 0;
	tech = 0;
}

GasDesignQuestionDialog::~GasDesignQuestionDialog()
{
}

void GasDesignQuestionDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT GasDesignQuestionDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_TechnologyListbox = FindChildByName2<SListBox>(L"technology");

	m_TechnologyListbox->DeleteAll();
	//���������
	if(region == 1)
	{
		m_TechnologyListbox->AddString(_T("�װ������ܼ�������׳��ú��������˹"));
		m_TechnologyListbox->AddString(_T("˳����������ڻ���������ɷ�"));
		m_TechnologyListbox->AddString(_T("���˫������ѭ������ʽ��ɼ���"));
	}
	//�ز��������
	else if(region == 2)
	{
		m_TechnologyListbox->AddString(_T("�װ���������������׳�ɹ�������˹"));
		m_TechnologyListbox->AddString(_T("˳����׵ݽ�ʽ�ڻ���ɹ�������˹��"));
		m_TechnologyListbox->AddString(_T("˳��ƽ����׳�ɹ�������˹"));
		m_TechnologyListbox->AddString(_T("˳�㽻����׳�ɹ�������˹"));
		m_TechnologyListbox->AddString(_T("ǧ�����������׳�ɷ�"));

	}
	//�ɿ���������
	else
	{
		m_TechnologyListbox->AddString(_T("�߳���жѹ��˹��ɷ�"));
		m_TechnologyListbox->AddString(_T("�����λ���������˹��ɷ�"));
		m_TechnologyListbox->AddString(_T("�ؿ����ﴩ����׳��"));
		m_TechnologyListbox->AddString(_T("�ɿ��������˹��ɷ���"));
	}
	m_TechnologyListbox->SetCurSel(0);

	return 0;
}


void GasDesignQuestionDialog::OnTechnologyListboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventLBSelChanged* pEvtOfLB = (EventLBSelChanged*)pEvt;
	if(pEvtOfLB == 0) return;
	int nCurSel = pEvtOfLB->nNewSel;
	if(nCurSel == -1) return;

	// do something
}

void GasDesignQuestionDialog::OnGoButtonClick()
{
	if(m_TechnologyListbox->GetCurSel() == -1)
	{
		SMessageBox( GetSafeHwnd(), _T( "��ѡ��һ���ɼ����������!" ), _T( "������ʾ" ), MB_OK );
	}
	else
	{
		//�����û�ѡ��
		tech = m_TechnologyListbox->GetCurSel()+1;
		AcadSouiDialog::OnOK();
	}
}
