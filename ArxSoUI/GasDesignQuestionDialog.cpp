#include "stdafx.h"
#include "GasDesignQuestionDialog.h"
#include "SouiListHelper.h"
#include "NameDialog.h"
#include "GasDesignP11Dialog.h"
#include "GasDesignP12Dialog.h"
#include "GasDesignP21Dialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

static int CreateNewTech(int region, const DesignTechnologyPtr& tech, const CString& name)
{
	int id  = -1;

	if(region == 1)
	{
		DesignDrillingSurfTechnologyPtr tws_tech(new DesignDrillingSurfTechnology);
		tws_tech->design_technology = tech;
		tws_tech->name = name;
		if( tws_tech->save() )
		{
			id = tws_tech->getID();
		}
	}
	else if(region == 2)
	{
		DesignWorkSurfTechnologyPtr ws_tech(new DesignWorkSurfTechnology);
		ws_tech->design_technology = tech;
		ws_tech->name = name;
		if( ws_tech->save() )
		{
			id = ws_tech->getID();
		}
	}
	else
	{
		DesignGoafTechnologyPtr goaf_tech(new DesignGoafTechnology);
		goaf_tech->design_technology = tech;
		goaf_tech->name = name;
		if( goaf_tech->save() )
		{
			id = goaf_tech->getID();
		}
	}
	return id;
}

static void RunGasDesignDlg(int coal_id, int region, int whick_tech, int tech_id)
{
	if(region == 0 || tech_id == 0) return;
	if(region == 1)
	{
		if(whick_tech == 1)
		{
			GasDesignP11Dialog* dlg = new GasDesignP11Dialog( FALSE );
			dlg->coal_id = coal_id;
			dlg->tech_id = tech_id;
			dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
		}
		else if(whick_tech == 2)
		{
			GasDesignP12Dialog* dlg = new GasDesignP12Dialog( FALSE );
			dlg->coal_id = coal_id;
			dlg->tech_id = tech_id;
			dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
		}
		else if(whick_tech == 3)
		{

		}
	}
	else if(region == 2)
	{
		if(whick_tech == 1)
		{
			GasDesignP21Dialog* dlg = new GasDesignP21Dialog( FALSE );
			dlg->coal_id = coal_id;
			dlg->tech_id = tech_id;
			dlg->Run( acedGetAcadFrame()->GetSafeHwnd() );
		}
		else if(whick_tech == 2)
		{

		}
		else if(whick_tech == 3)
		{

		}
		else if(whick_tech == 4)
		{
		}
		else if(whick_tech == 5)
		{

		}
	}
	else if(region == 3)
	{
		if(whick_tech == 1)
		{

		}
		else if(whick_tech == 2)
		{

		}
		else if(whick_tech == 3)
		{

		}
		else if(whick_tech == 4)
		{
		}
	}
}

static void GetTechnologies(int region, AcStringArray& techs)
{
	if(region == 1)
	{
		techs.append(_T("�װ������ܼ�������׳��ú��������˹"));
		techs.append(_T("˳����������ڻ���������ɷ�"));
		techs.append(_T("���˫������ѭ������ʽ��ɼ���"));
	}
	//�ز��������
	else if(region == 2)
	{
		techs.append(_T("�װ���������������׳�ɹ�������˹"));
		techs.append(_T("˳����׵ݽ�ʽ�ڻ���ɹ�������˹��"));
		techs.append(_T("˳��ƽ����׳�ɹ�������˹"));
		techs.append(_T("˳�㽻����׳�ɹ�������˹"));
		techs.append(_T("ǧ�����������׳�ɷ�"));

	}
	//�ɿ���������
	else
	{
		techs.append(_T("�߳���жѹ��˹��ɷ�"));
		techs.append(_T("�����λ���������˹��ɷ�"));
		techs.append(_T("�ؿ����ﴩ����׳��"));
		techs.append(_T("�ɿ��������˹��ɷ���"));
	}
}

static RecordPtrListPtr Select(int region, const CString& id)
{
	if(region == 1)
	{
		return FIND_MANY( DesignDrillingSurfTechnology, FKEY(DesignTechnology), id );
	}
	else if(region == 2)
	{
		return FIND_MANY( DesignWorkSurfTechnology, FKEY(DesignTechnology), id );
	}
	else if(region == 3)
	{
		return FIND_MANY( DesignGoafTechnology, FKEY(DesignTechnology), id );
	}
	else
	{
		return RecordPtrListPtr();
	}
}

GasDesignQuestionDialog::GasDesignQuestionDialog(BOOL bModal) : AcadSouiDialog(_T("layout:gas_design_question"), bModal)
{
	coal_id = 0;
	region = 0;
	tech_id = 0;
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
	m_DesignCombox = FindChildByName2<SComboBox>(L"design");

	fillDatas();

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
	else if(m_DesignCombox->GetCurSel() == -1)
	{
		SMessageBox( GetSafeHwnd(), _T( "���½�һ����Ʒ���!" ), _T( "������ʾ" ), MB_OK );
	}
	else
	{
		this->tech_id = SComboBoxHelper::GetCurSelItemID(m_DesignCombox);
		int tech_kind = m_TechnologyListbox->GetCurSel()+1;
		AcadSouiDialog::OnOK();

		//���ø���ϸ����ƶԻ���
		RunGasDesignDlg(this->coal_id, this->region, tech_kind, this->tech_id);
	}
}

void GasDesignQuestionDialog::OnDesignComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void GasDesignQuestionDialog::OnNewDesignButtonClick()
{
	NameDialog dlg( TRUE );
	dlg.SetWindowTitle( _T( "��������������" ) );
	if( IDOK != dlg.Run( GetSafeHwnd() ) ) return;
	CString name = dlg.name;
	if( name.IsEmpty() ) return;

	if( m_DesignCombox->FindString( name ) != -1 )
	{
		CString msg;
		msg.Format( _T( "������ݡ�%s���Ѵ���!" ), name );
		SMessageBox( GetSafeHwnd(), msg, _T( "������ʾ" ), MB_OK );
	}
	else
	{
		CoalPtr coal = FIND_BY_ID( Coal, this->coal_id );
		if( coal == 0 ) return;

		DesignTechnologyPtr tech = FIND_ONE2( DesignTechnology, FKEY( Coal ), coal->getStringID(), FIELD(region), Utils::int_to_cstring(this->region) );
		if( tech == 0 )
		{
			tech.reset( new DesignTechnology );
			tech->region = this->region;
			tech->coal = coal;
			//���浽���ݿ�
			if( !tech->save() )
			{
				SMessageBox( GetSafeHwnd(), _T("�����������ʧ��!"), _T( "������ʾ" ), MB_OK );
				return;
			}
		}

		//����������ݲ����浽���ݿ�
		int id = CreateNewTech(this->region, tech, name);
		if(id != -1)
		{
			//���뵽ú���б��б�
			int nItem = SComboBoxHelper::Add( m_DesignCombox, name, id );
			SComboBoxHelper::Select( m_DesignCombox, nItem );
			SMessageBox( GetSafeHwnd(), _T( "����������ݳɹ�" ), _T( "������ʾ" ), MB_OK );
		}
		else
		{
			SMessageBox( GetSafeHwnd(), _T( "�����������ʧ��" ), _T( "������ʾ" ), MB_OK );
		}
	}
}

void GasDesignQuestionDialog::fillDatas()
{
	m_TechnologyListbox->DeleteAll();
	AcStringArray techs;
	GetTechnologies(this->region, techs);
	for(int i=0;i<techs.length();i++)
	{
		m_TechnologyListbox->AddString(techs[i].kACharPtr());
	}
	m_TechnologyListbox->SetCurSel(0);

	//�����Ʒ����б�
	SComboBoxHelper::Clear(m_DesignCombox);

	CoalPtr coal = FIND_BY_ID( Coal, this->coal_id );
	if( coal == 0 ) return;

	DesignTechnologyPtr tech = FIND_ONE2( DesignTechnology, FKEY( Coal ), coal->getStringID(), FIELD(region), Utils::int_to_cstring(this->region) );
	if( tech == 0 )
	{
		tech.reset( new DesignTechnology );
		tech->region = this->region;
		tech->coal = coal;
		//���浽���ݿ�
		if( !tech->save() ) return;
	}
	else
	{
		RecordPtrListPtr tech_list = Select(this->region, tech->getStringID());
		if( tech_list != 0 )
		{
			for(int i=0;i<tech_list->size();i++)
			{
				RecordPtr ptr = tech_list->at(i);
				CString name = ptr->get(FIELD(name));
				int id = ptr->getID();
				SComboBoxHelper::Add(m_DesignCombox, name, id);
			}
			SComboBoxHelper::Select(m_DesignCombox, 0);
		}
	}
}

void GasDesignQuestionDialog::OnDelDesignButtonClick()
{
	int tech_id = SComboBoxHelper::GetCurSelItemID(m_DesignCombox);
	bool ret = false;
	if(region == 1)
	{
		DesignDrillingSurfTechnologyPtr tws_tech = FIND_BY_ID(DesignDrillingSurfTechnology, tech_id);
		ret = (tws_tech != 0 && tws_tech->remove());
	}
	else if(region == 2)
	{
		DesignWorkSurfTechnologyPtr ws_tech = FIND_BY_ID(DesignWorkSurfTechnology, tech_id);
		ret = (ws_tech != 0 && ws_tech->remove());
	}
	else
	{
		DesignGoafTechnologyPtr goaf_tech = FIND_BY_ID(DesignGoafTechnology, tech_id);
		ret = (goaf_tech != 0 && goaf_tech->remove());
	}

	if(ret)
	{
		SComboBoxHelper::DeleteCurSel(m_DesignCombox);
		SComboBoxHelper::Select(m_DesignCombox, 0);
		SMessageBox( GetSafeHwnd(), _T( "ɾ����Ʒ����ɹ�!" ), _T( "������ʾ" ), MB_OK );
	}
	else
	{
		SMessageBox( GetSafeHwnd(), _T( "ɾ����Ʒ���ʧ��!" ), _T( "������ʾ" ), MB_OK );
	}
}

void GasDesignQuestionDialog::OnDestroyWindow()
{
	SListBoxHelper::Clear(m_TechnologyListbox);
	SComboBoxHelper::Clear(m_DesignCombox);
}
