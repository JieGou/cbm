#include "stdafx.h"
#include "MineDesignDialog.h"
#include "SouiListHelper.h"
#include "NameDialog.h"

#include <ArxHelper/HelperClass.h>
#include <ArxDao/DaoHelper.h>
#include <ArxDao/Entity.h>
using namespace orm;
using namespace cbm;

MineDesignDialog::MineDesignDialog(BOOL bModal) : AcadSouiDialog(_T("layout:mine_design"), bModal)
{
	mine_id = 0;
}

MineDesignDialog::~MineDesignDialog()
{
}

void MineDesignDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

LRESULT MineDesignDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_NameEdit = FindChildByName2<SEdit>(L"name");
	m_CoalCombox = FindChildByName2<SComboBox>(L"coal");
	m_WorkAreaCombox = FindChildByName2<SComboBox>(L"work_area");
	m_WsCombox = FindChildByName2<SComboBox>(L"ws");
	m_TwsCombox = FindChildByName2<SComboBox>(L"tws");

	initMineDatas();
	fillCoalCombox();

	return 0;
}

void MineDesignDialog::OnDelCoalButtonClick()
{
	CoalPtr coal = getCurSelCoal();
	if(coal == 0) return;

	//��ɾ������
	if(coal->remove())
	{
		//�Ӳ����б���ɾ��
		SComboBoxHelper::DeleteCurSel(m_CoalCombox);
		SComboBoxHelper::Select(m_CoalCombox, 0);
		SMessageBox(GetSafeHwnd(),_T("ɾ��ú��ɹ�"),_T("������ʾ"),MB_OK);
	}
	else
	{
		SMessageBox(GetSafeHwnd(),_T("ɾ��ú��ʧ��"),_T("������ʾ"),MB_OK);
	}
}

void MineDesignDialog::OnAddCoalButtonClick()
{
	MinePtr mine = FIND_BY_ID(Mine, mine_id);
	if(mine == 0) return;

	NameDialog dlg(TRUE);
	dlg.SetWindowTitle(_T("����ú��"));
	if(IDOK != dlg.Run(GetSafeHwnd())) return;

	CString name = dlg.name;
	if(name.IsEmpty()) return;

	if(m_CoalCombox->FindString(name) != -1)
	{
		CString msg;
		msg.Format(_T("ú��%s�Ѵ���!"), name);
		SMessageBox(GetSafeHwnd(),msg,_T("������ʾ"),MB_OK);
	}
	else
	{
		//�ύ�����ݿ�
		CoalPtr coal(new Coal);
		coal->name = name;
		coal->mine = mine;
		if(coal->save())
		{
			//���뵽ú���б��б�
			int nItem = SComboBoxHelper::Add(m_CoalCombox, coal->name, coal->getID());
			SComboBoxHelper::Select(m_CoalCombox, nItem);
			SMessageBox(GetSafeHwnd(),_T("����ú��ɹ�"),_T("������ʾ"),MB_OK);
		}
		else
		{
			SMessageBox(GetSafeHwnd(),_T("����ú��ʧ��"),_T("������ʾ"),MB_OK);
		}
	}
}

void MineDesignDialog::OnCoalComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	//SComboBoxHelper::Clear(m_CoalCombox);
	SComboBoxHelper::Clear(m_WorkAreaCombox);
	//SComboBoxHelper::Clear(m_WsCombox);
	//SComboBoxHelper::Clear(m_TwsCombox);

	CoalPtr coal = getCurSelCoal();
	if(coal == 0) return;

	//�������б�
	RecordPtrListPtr lists = FIND_MANY(WorkArea, FKEY(Coal), coal->getStringID());
	if(lists != 0)
	{
		for(int i=0;i<lists->size();i++)
		{
			WorkAreaPtr work_area = DYNAMIC_POINTER_CAST(WorkArea, lists->at(i));
			SComboBoxHelper::Add(m_WorkAreaCombox, work_area->name, work_area->getID());
		}
		SComboBoxHelper::Select(m_WorkAreaCombox, 0);
	}
}

void MineDesignDialog::OnWorkAreaComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	//SComboBoxHelper::Clear(m_CoalCombox);
	//SComboBoxHelper::Clear(m_WorkAreaCombox);
	SComboBoxHelper::Clear(m_WsCombox);
	SComboBoxHelper::Clear(m_TwsCombox);

	// do something
	WorkAreaPtr work_area = getCurSelWorkArea();
	if(work_area == 0) return;

	//���زɹ������б�
	RecordPtrListPtr ws_lists = FIND_MANY(WorkSurf, FKEY(WorkArea), work_area->getStringID());
	if(ws_lists != 0)
	{
		for(int i=0;i<ws_lists->size();i++)
		{
			WorkSurfPtr work_surf = DYNAMIC_POINTER_CAST(WorkSurf, ws_lists->at(i));
			SComboBoxHelper::Add(m_WsCombox, work_surf->name, work_surf->getID());
		}
		SComboBoxHelper::Select(m_WsCombox, 0);
	}

	//������������б�
	RecordPtrListPtr tws_lists = FIND_MANY(DrillingSurf, FKEY(WorkArea), work_area->getStringID());
	if(tws_lists != 0)
	{
		for(int i=0;i<tws_lists->size();i++)
		{
			DrillingSurfPtr drilling_surf = DYNAMIC_POINTER_CAST(DrillingSurf, tws_lists->at(i));
			SComboBoxHelper::Add(m_TwsCombox, drilling_surf->name, drilling_surf->getID());
		}
		SComboBoxHelper::Select(m_TwsCombox, 0);
	}	
}

void MineDesignDialog::OnDelWorkAreaButtonClick()
{
	WorkAreaPtr work_area = getCurSelWorkArea();
	if(work_area == 0) return;

	//��ɾ������
	if(work_area->remove())
	{
		//�Ӳ����б���ɾ��
		SComboBoxHelper::DeleteCurSel(m_WorkAreaCombox);
		SComboBoxHelper::Select(m_WorkAreaCombox, 0);
		SMessageBox(GetSafeHwnd(),_T("ɾ�������ɹ�"),_T("������ʾ"),MB_OK);
	}
	else
	{
		SMessageBox(GetSafeHwnd(),_T("ɾ������ʧ��"),_T("������ʾ"),MB_OK);
	}
}

void MineDesignDialog::OnAddWorkAreaButtonClick()
{
	CoalPtr coal = getCurSelCoal();
	if(coal == 0) return;

	NameDialog dlg(TRUE);
	dlg.SetWindowTitle(_T("��������"));
	if(IDOK != dlg.Run(GetSafeHwnd())) return;

	CString name = dlg.name;
	if(name.IsEmpty()) return;

	if(m_WorkAreaCombox->FindString(name) != -1)
	{
		CString msg;
		msg.Format(_T("��������%s�Ѵ���!"), name);
		SMessageBox(GetSafeHwnd(),msg,_T("������ʾ"),MB_OK);
	}
	else
	{
		//�ύ�����ݿ�
		WorkAreaPtr work_area(new WorkArea);
		work_area->name = name;
		work_area->coal = coal;
		if(work_area->save())
		{
			//���뵽�����б�
			int nItem = SComboBoxHelper::Add(m_WorkAreaCombox, work_area->name, work_area->getID());
			SComboBoxHelper::Select(m_WorkAreaCombox, nItem);
			SMessageBox(GetSafeHwnd(),_T("���������ɹ�"),_T("������ʾ"),MB_OK);
		}
		else
		{
			SMessageBox(GetSafeHwnd(),_T("��������ʧ��"),_T("������ʾ"),MB_OK);
		}
	}
}

void MineDesignDialog::OnWsComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void MineDesignDialog::OnTwsComboxSelChanged(SOUI::EventArgs *pEvt)
{
	if(!isLayoutInited()) return;
	EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;
	if(pEvtOfCB == 0) return;
	int nCurSel = pEvtOfCB->nCurSel;
	if(nCurSel == -1) return;

	// do something
}

void MineDesignDialog::OnDelWsButtonClick()
{
	WorkSurfPtr work_surf = getCurSelWs();
	if(work_surf == 0) return;

	//��ɾ������
	if(work_surf->remove())
	{
		//�Ӳ����б���ɾ��
		SComboBoxHelper::DeleteCurSel(m_WsCombox);
		SComboBoxHelper::Select(m_WsCombox, 0);
		SMessageBox(GetSafeHwnd(),_T("ɾ���زɹ�����ɹ�"),_T("������ʾ"),MB_OK);
	}
	else
	{
		SMessageBox(GetSafeHwnd(),_T("ɾ���زɹ�����ʧ��"),_T("������ʾ"),MB_OK);
	}
}

void MineDesignDialog::OnAddWsButtonClick()
{
	WorkAreaPtr work_area = getCurSelWorkArea();
	if(work_area == 0) return;

	NameDialog dlg(TRUE);
	dlg.SetWindowTitle(_T("����������"));
	if(IDOK != dlg.Run(GetSafeHwnd())) return;

	CString name = dlg.name;
	if(name.IsEmpty()) return;

	if(m_WsCombox->FindString(name) != -1)
	{
		CString msg;
		msg.Format(_T("�زɹ�����%s�Ѵ���!"), name);
		SMessageBox(GetSafeHwnd(),msg,_T("������ʾ"),MB_OK);
	}
	else
	{
		//�ύ�����ݿ�
		WorkSurfPtr work_surf(new WorkSurf);
		work_surf->name = name;
		work_surf->work_area = work_area;
		if(work_surf->save())
		{
			//���뵽�������б�
			int nItem = SComboBoxHelper::Add(m_WsCombox, work_surf->name, work_surf->getID());
			SComboBoxHelper::Select(m_WsCombox, nItem);
			SMessageBox(GetSafeHwnd(),_T("����������ɹ�"),_T("������ʾ"),MB_OK);
		}
		else
		{
			SMessageBox(GetSafeHwnd(),_T("����������ʧ��"),_T("������ʾ"),MB_OK);
		}
	}
}

void MineDesignDialog::OnDelTwsButtonClick()
{
	DrillingSurfPtr drilling_surf = getCurSelTws();
	if(drilling_surf == 0) return;

	//��ɾ������
	if(drilling_surf->remove())
	{
		//�Ӳ����б���ɾ��
		SComboBoxHelper::DeleteCurSel(m_TwsCombox);
		SComboBoxHelper::Select(m_TwsCombox, 0);
		SMessageBox(GetSafeHwnd(),_T("ɾ�������ɹ�"),_T("������ʾ"),MB_OK);
	}
	else
	{
		SMessageBox(GetSafeHwnd(),_T("ɾ�������ʧ��"),_T("������ʾ"),MB_OK);
	}
}

void MineDesignDialog::OnAddTwsButtonClick()
{
	WorkAreaPtr work_area = getCurSelWorkArea();
	if(work_area == 0) return;

	NameDialog dlg(TRUE);
	dlg.SetWindowTitle(_T("���������"));
	if(IDOK != dlg.Run(GetSafeHwnd())) return;

	CString name = dlg.name;
	if(name.IsEmpty()) return;
	if(m_TwsCombox->FindString(name) != -1)
	{
		CString msg;
		msg.Format(_T("���������%s�Ѵ���!"), name);
		SMessageBox(GetSafeHwnd(),msg,_T("������ʾ"),MB_OK);
	}
	else
	{
		//�ύ�����ݿ�
		DrillingSurfPtr drilling_surf(new DrillingSurf);
		drilling_surf->name = name;
		drilling_surf->work_area = work_area;
		if(drilling_surf->save())
		{
			//���뵽�����б�
			int nItem = SComboBoxHelper::Add(m_TwsCombox, drilling_surf->name, drilling_surf->getID());
			SComboBoxHelper::Select(m_TwsCombox, nItem);
			SMessageBox(GetSafeHwnd(),_T("���������ɹ�"),_T("������ʾ"),MB_OK);
		}
		else
		{
			SMessageBox(GetSafeHwnd(),_T("���������ʧ��"),_T("������ʾ"),MB_OK);
		}
	}
}

void MineDesignDialog::OnSaveButtonClick()
{
}

void MineDesignDialog::OnDestroyWindow()
{
	//ɾ�����еĸ�������
	SComboBoxHelper::Clear(m_WorkAreaCombox);
	SComboBoxHelper::Clear(m_WsCombox);
	SComboBoxHelper::Clear(m_TwsCombox);
	SComboBoxHelper::Clear(m_CoalCombox);
	AcadSouiDialog::OnDestroyWindow();
}

void MineDesignDialog::initMineDatas()
{
	MinePtr mine = FIND_BY_ID(Mine, mine_id);
	if(mine == 0) return;

	m_NameEdit->SetWindowText(mine->name);
}

void MineDesignDialog::fillCoalCombox()
{
	SComboBoxHelper::Clear(m_CoalCombox);

	MinePtr mine = FIND_BY_ID(Mine, mine_id);
	if(mine == 0) return;

	StringArray coal_names;
	IntArray coal_ids;
	DaoHelper::GetCoalIds(mine->getID(), coal_ids);
	DaoHelper::GetCoalNames(mine->getID(), coal_names);

	SComboBoxHelper::Clear(m_CoalCombox);
	SComboBoxHelper::Append(m_CoalCombox, coal_names, coal_ids);
	SComboBoxHelper::Select(m_CoalCombox, 0);
}

CoalPtr MineDesignDialog::getCurSelCoal()
{
	int coal_id = SComboBoxHelper::GetCurSelItemID(m_CoalCombox);
	if(coal_id == 0) return CoalPtr();
	return FIND_BY_ID(Coal, coal_id);
}

WorkAreaPtr MineDesignDialog::getCurSelWorkArea()
{
	int work_area_id = SComboBoxHelper::GetCurSelItemID(m_WorkAreaCombox);
	if(work_area_id == 0) return WorkAreaPtr();
	return FIND_BY_ID(WorkArea, work_area_id);
}

DrillingSurfPtr MineDesignDialog::getCurSelTws()
{
	int tws_id = SComboBoxHelper::GetCurSelItemID(m_TwsCombox);
	if(tws_id == 0) return DrillingSurfPtr();
	return FIND_BY_ID(DrillingSurf, tws_id);
}

WorkSurfPtr MineDesignDialog::getCurSelWs()
{
	int ws_id = SComboBoxHelper::GetCurSelItemID(m_WsCombox);
	if(ws_id == 0) return WorkSurfPtr();
	return FIND_BY_ID(WorkSurf, ws_id);
}
