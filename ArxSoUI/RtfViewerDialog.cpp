#include "stdafx.h"
#include "RtfViewerDialog.h"

#include <ArxHelper/HelperClass.h>
#include <Dao/DaoHelper.h>
#include <Dao/Entity.h>
using namespace orm;
using namespace cbm;

#include <controls.extend/reole/richeditole.h>

RtfViewerDialog::RtfViewerDialog(BOOL bModal) : AcadSouiDialog(_T("layout:rtf_viewer"), bModal)
{
	m_use_res = true;
}

RtfViewerDialog::~RtfViewerDialog()
{
}

void RtfViewerDialog::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
	if(uNotifyCode==0)
	{
		//if(nID==6)
		//{
		//}
	}
}

//class CSmileySource2 : public CSmileySource
//{
//public:
//	CSmileySource2(){}
//
//protected:
//	//���ID��Ӧ��ͼƬ·��
//	virtual SStringW ImageID2Path(UINT nID)
//	{
//		return SStringW().Format(L"./gif/%d.gif",nID);
//	}
//};

//ole��Դ(����ͼƬ�����excel��ppt��)�ص�������
ISmileySource * CreateSource2()
{
	//��ͨ��rtf֧�ֵ�ole����
	return  new CSmileySource();
	//CSmileySource2����֧�ֱ������(΢�š�QQ�����õ�����)
	//return  new CSmileySource2();
}

LRESULT RtfViewerDialog::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	AcadSouiDialog::OnInitDialog(hWnd, lParam);
	//do something
	m_RtfViewerRichedit = FindChildByName2<SRichEdit>(L"rtf_viewer");
	if(m_RtfViewerRichedit != 0)
	{
		//����Ҫ����ole�ص�,����rtf�ļ���ͼƬ�����������޷���ʾ
		SetSRicheditOleCallback(m_RtfViewerRichedit,CreateSource2);

		if(this->m_use_res)
		{
			//�޸�richedit��rtf����
			CString rtf;
			rtf.Format(_T("rtf:%s"), this->m_rtf_res);
			m_RtfViewerRichedit->SetAttribute(L"rtf", (LPCTSTR)rtf);
		}
		else
		{
			m_RtfViewerRichedit->LoadRtf(m_rtf_file);
		}
	}
	return 0;
}

void RtfViewerDialog::setRtfRes(const CString& rtf_res)
{
	m_rtf_res = rtf_res;
	m_use_res = true;
}

void RtfViewerDialog::setRtfFile(const CString& rtf_file)
{
	m_rtf_file = rtf_file;
	m_use_res = false;
}
