/****************************************************************************
*  功    能：使用SOUI自主设计音乐播放器                                     *
*  作    者：小可                                                           *
*  添加时间：2015.01.09 17：00                                              *
*  版本类型：初始版本                                                       *
*  联系方式：QQ-1035144170                                                  *
****************************************************************************/

// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"



/****************************************************************************
*  函 数 名：GetAudioAllPath                                          
*  功能描述: 回调回去拖拽进列表的所有音频路径                                         
*  输入参数：std::vector<CString> vInfo      [IN] :单个或多个音频文件路径 
*            void *pUser                     [IN] :主窗口的指针
*  输出参数: 无
*  返 回 值：TRUE  执行成功
* 		     FALSE 执行失败
*  抛出异常：无
****************************************************************************/
BOOL __stdcall GetAudioAllPath(vector<CString> vInfo, void *pUser)
{
	if (NULL != pUser)
	{
		int i=0;
		//CString str;
		//str.Format("Dll回调的值： %d\n",lpMyStruct);
		CMainDlg *pThis = (CMainDlg *)pUser;
		pThis->InsertTreeBox(vInfo);
		//测试：播放音乐
		pThis->bPlayFlag=false;
		pThis->OnButPlay();
	}
	return TRUE;
}

//测试数据
TCHAR szLrc[][24]={L"歌名:伤心城市 演唱:雷婷",L"作词:陈炜 作曲:陈炜 LRC制作:@小可",L"关于你们之间的故事",L"你总有牵强的解释",L"我不再想听你的毒誓",L"因为这已不是第一次",
L"你把谎言精心的编织",L"我不想再被你伤一次",L"早已听惯了你的滥调陈词",L"现在回头算不算太迟",L"知道他在你心里的位置",L"你在梦里喊着他的名字",L"把我变成了寂寞的影子",
L"所有一切往事都将随风远逝",L"我想忘掉过去的山盟海誓",L"试着习惯没有你的日子",L"就要告别这个伤心的城市",L"所有一切都将都将重新开始",L"谢谢！@小可 1035144170 谢谢观赏"};

BOOL __stdcall SetLrcStyle(void *pUser)
{
	if (NULL != pUser)
	{
		CMainDlg *pThis = (CMainDlg *)pUser;
		pThis->ChangeLrcFont();
	}
	return TRUE;
}

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
,nSelenum(0)
,nNum(4)
,bTurnFlag(true)
{
    m_bCut=false;
	m_3DType=false;
	m_bLayoutInited=FALSE;

	bPlayFlag=false;
	m_pMuOPreat=NULL;
} 

CMainDlg::~CMainDlg()
{
	shellNotifyIcon.Hide();	
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 		MARGINS mar = {5,5,30,5};
	// 		DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	shellNotifyIcon.Create(m_hWnd,GETRESPROVIDER->LoadIcon(_T("ICON_LOGO"),16));
	shellNotifyIcon.Show();
	//InitListCtrl();

	//拖拽功能
	SWindow *pListBox = FindChildByName(L"music_lbe");
	if(pListBox)
	{
		HRESULT hr=::RegisterDragDrop(m_hWnd,GetDropTarget());
		CTestDropTarget1 *pDrop=new CTestDropTarget1(pListBox);
		RegisterDragDrop(pListBox->GetSwnd(),pDrop);
		pDrop->GetDragData(GetAudioAllPath,this);
	}
    
	//初始化音频操作类
	m_pMuOPreat=new CMusicOpreat(m_hWnd);
	m_pMuOPreat->InitDatas();

	//找到列表控件
	SScrollLrc *pTreeBox=FindChildByName2<SScrollLrc>(L"music_lrc");
	if(pTreeBox)
	{
		SStringT m_sTemp;
		STreeItem *pItem;
		HSTREEITEM rootItem;

		for (int i=0;i<20;i++)
		{
			m_sTemp.Format(L"<item><text pos=\"10,0,-5,-0\" name=\"数据_%d\" valign=\"middle\" align=\"left\" colorText=\"#ff0000\" align=\"center\" font=\"face:微软雅黑,adding:5\">%s</text></item>",i,szLrc[i]);
			//m_sTemp=_T(,strTemp); 
			pItem=pTreeBox->InsertItem((LPCWSTR )m_sTemp,(DWORD)rootItem,STVI_ROOT,STVI_LAST,FALSE);
			m_TreItemInfo.insert(std::make_pair(i,pItem));
		}
		pTreeBox->GetSetLrcFun(SetLrcStyle,this);
		pTreeBox->StarsRollLrc();
	}

	return 0;
}


//TODO:消息映射
void CMainDlg::OnClose()
{
	PostMessage(WM_QUIT);
	
}

void CMainDlg::OnMaximize()
{
	//SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	if (!m_bCut)
	{
		STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
		if(pTab)
		{
			pTab->SetCurSel(_T("在线音乐"));
			m_bCut=true;
		}
		
	}else
	{
		STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
		if(pTab)
		{
			pTab->SetCurSel(_T("我的音乐"));
			m_bCut=false;
		}
	}

}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

#include <helper/smenu.h>
LRESULT CMainDlg::OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/)
{
	switch (lParam)
	{
	case  WM_RBUTTONDOWN:
	{
	    SetForegroundWindow(m_hWnd);
            //显示右键菜单
            SMenu menu;
            menu.LoadMenu(_T("menu_tray"),_T("smenu"));
            POINT pt;
            GetCursorPos(&pt);
            menu.TrackPopupMenu(0,pt.x,pt.y,m_hWnd);
	}break;
	case WM_LBUTTONDOWN:
	{
		//显示/隐藏主界面
		if (IsIconic())
		   ShowWindow(SW_SHOWNORMAL);
		else
		   ShowWindow(SW_MINIMIZE);
	}break;
	default:
		break;
	}
	return S_OK;
}

//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (uNotifyCode == 0)
	{
		switch (nID)
		{
		case 6:
			PostMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}
}


BOOL CMainDlg::OnTurn3D( EventArgs *pEvt )
{
	EventTurn3d *pEvt3dTurn = (EventTurn3d*)pEvt;
	STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_3d");
	if(pEvt3dTurn->bTurn2Front_)
	{
		pTab->SetCurSel(_T("musiclist"));
		
	}else
	{
		pTab->SetCurSel(_T("lrc"));
	}
	return TRUE;
}

void CMainDlg::OnTurn3DBut()
{
	if (!m_3DType)
	{
		STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_3d");
		if(pTab)
		{
			STurn3dView * pTurn3d = FindChildByName2<STurn3dView>(L"turn3d");
			if(pTurn3d)
			{
				pTurn3d->Turn(pTab->GetPage(_T("musiclist")),pTab->GetPage(_T("lrc")),FALSE);
				m_3DType=true;
			}
		}
	}else
	{
		STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_3d");
		if(pTab)
		{
			STurn3dView * pTurn3d = FindChildByName2<STurn3dView>(L"turn3d");
			if(pTurn3d)
			{
				pTurn3d->Turn(pTab->GetPage(_T("lrc")),pTab->GetPage(_T("musiclist")),TRUE);
				m_3DType=false;
			}
		}

	}
	
}

void CMainDlg::OnBtnMyMusic()
{
	STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
	if(pTab)
	{
		pTab->SetCurSel(_T("我的音乐"));
	}

}

void CMainDlg::OnBtnOnlineMusic()
{
	STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
	if(pTab)
	{
		pTab->SetCurSel(_T("在线音乐"));
	}

}

void CMainDlg::OnBtnMyDevice()
{
	STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
	if(pTab)
	{
		pTab->SetCurSel(_T("我的设备"));
	}

}

void CMainDlg::OnButPrev()         // 上一曲
{
	m_pMuOPreat->OnButPrev();
	if (m_pMuOPreat->m_MusicManager.empty())
	{
		return;
	}
	DrawMusicInfo();

	//同步进度条
	OnSetProgress();

	SListBoxEx *pMusicLbe=FindChildByName2<SListBoxEx>(L"music_lbe");
	if(pMusicLbe)
	{
		pMusicLbe->SetCurSel(m_pMuOPreat->nIndex);
		//对应滚动滑块
		CPoint ptNew;
		CSize size=pMusicLbe->GetViewSize();
		ptNew.x=size.cx;
		ptNew.y=size.cy/m_pMuOPreat->m_MusicManager.size()*(m_pMuOPreat->nIndex-2);//最好根据当前插入项数、宽度和能显示的来计算
		pMusicLbe->SetViewOrigin(ptNew);
	}

	/*---------------------------------------------- listboxex选择上一 beg -----------------------------------------------------*/
	//SListBoxEx *pMusicLbe=FindChildByName2<SListBoxEx>(L"music_lbe");
	//if(pMusicLbe)
	//{
	//	int count=pMusicLbe->GetItemCount();

	//	if (pMusicLbe->GetCurSel()!=-1)
	//	{
	//		nSelenum=pMusicLbe->GetCurSel();
	//		nSelenum--;
	//		if (nSelenum<0)
	//		{
	//			nSelenum=count-1;
	//		}
	//	}else
	//	{
	//		nSelenum=count-1;
	//	}
	//	pMusicLbe->SetCurSel(nSelenum);
	//	//STRACE(_T("选择的歌曲是:列表第%d首歌曲"),nSelenum+1);
	//	std::map <int, tagMusicInfo>::iterator iter=m_SeleInfoMap.begin();
	//	for (; iter != m_SeleInfoMap.end(); iter++)
	//	{
	//		if (nSelenum==(int)iter->first)
	//		{
	//			STRACE(_T("选择的歌曲是:列表第%d首歌曲"),(int)iter->first);
	//		}	
	//	}

	//	//对应滚动滑块
	//	CPoint ptNew;
	//	CSize size=pMusicLbe->GetViewSize();
	//	ptNew.x=size.cx;
	//	ptNew.y=size.cy/20*(nSelenum-2);//最好根据当前插入项数、宽度和能显示的来计算
	//	pMusicLbe->SetViewOrigin(ptNew);
	//}
	/*---------------------------------------------- listboxex选择上一 end -----------------------------------------------------*/
}

void CMainDlg::OnButPlay()         // 播放
{
	if (!bPlayFlag)
	{
		m_pMuOPreat->OnButPlay();
		bPlayFlag=true;

	}else
	{
		m_pMuOPreat->OnButPause();
		bPlayFlag=false;
	}
	if (m_pMuOPreat->m_MusicManager.empty())
	{
		return;
	}
	DrawMusicInfo();

	//同步进度条
	OnSetProgress();

	//测试：播放音乐
	//if (hStream)
	//{
	//	BASS_ChannelStop(hStream);
	//	hStream=NULL;
	//}
	//CString lpszFileName="C:/Users/Administrator/Desktop/Music/BEYOND - 不再犹豫.mp3";
	//hStream=BASS_StreamCreateFile(FALSE, lpszFileName.GetBuffer(),0,0,BASS_SAMPLE_MONO);
	//if (hStream)
	//{
	//	//开始播放
	//	BOOL bResult = BASS_ChannelPlay(hStream, FALSE);
	//	if (bResult)
	//	{
	//		int i=0;
	//	}
	//}
}

void CMainDlg::OnButPause()        // 暂停
{
	m_pMuOPreat->OnButPause();
}

void CMainDlg::OnButPlayNext()     // 下一曲
{
	m_pMuOPreat->OnButPlayNext();
	if (m_pMuOPreat->m_MusicManager.empty())
	{
		return;
	}
	DrawMusicInfo();

	//同步进度条
	OnSetProgress();

	SListBoxEx *pMusicLbe=FindChildByName2<SListBoxEx>(L"music_lbe");
	if(pMusicLbe)
	{
		pMusicLbe->SetCurSel(m_pMuOPreat->nIndex);
		//对应滚动滑块
		CPoint ptNew;
		CSize size=pMusicLbe->GetViewSize();
		ptNew.x=size.cx;
		ptNew.y=size.cy/m_pMuOPreat->m_MusicManager.size()*(m_pMuOPreat->nIndex-2);//最好根据当前插入项数、宽度和能显示的来计算
		pMusicLbe->SetViewOrigin(ptNew);
	}

	/*---------------------------------------------- listboxex选择下一 beg -----------------------------------------------------*/
	//SListBoxEx *pMusicLbe=FindChildByName2<SListBoxEx>(L"music_lbe");
	//if(pMusicLbe)
	//{
	//	int count=pMusicLbe->GetItemCount();

	//	if (pMusicLbe->GetCurSel()!=-1)
	//	{
	//		nSelenum=pMusicLbe->GetCurSel();
	//		nSelenum++;
	//		if (nSelenum>=count)
	//		{
	//			nSelenum=0;
	//		}
	//	}else
	//	{
	//		nSelenum=0;
	//	}
	//	pMusicLbe->SetCurSel(nSelenum);
	//	//STRACE(_T("选择的歌曲是:列表第%d首歌曲"),nSelenum+1);
	//	std::map <int, tagMusicInfo>::iterator iter=m_SeleInfoMap.begin();
	//	for (; iter != m_SeleInfoMap.end(); iter++)
	//	{
	//		if (nSelenum==(int)iter->first)
	//		{
	//			STRACE(_T("选择的歌曲是:列表第%d首歌曲"),(int)iter->first);
	//		}	
	//	}

	//	//对应滚动滑块
	//	CPoint ptNew;
	//	CSize size=pMusicLbe->GetViewSize();
	//	ptNew.x=size.cx;
	//	ptNew.y=size.cy/20*(nSelenum-2);//最好根据当前插入项数、宽度和能显示的来计算
	//	pMusicLbe->SetViewOrigin(ptNew);
	//}
	/*---------------------------------------------- listboxex选择下一 end -----------------------------------------------------*/
}

void CMainDlg::OnButLyric()        // 歌词面板
{

	STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_3d");
	if(pTab&&!m_3DType)
	{
		STurn3dView * pTurn3d = FindChildByName2<STurn3dView>(L"turn3d");
		if(pTurn3d)
		{
			pTurn3d->Turn(pTab->GetPage(_T("musiclist")),pTab->GetPage(_T("lrc")),FALSE);
		}
		m_3DType=true;
	}
}

void CMainDlg::OnButMusicList()    // 歌词列表
{

	STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_3d");
	if(pTab&&m_3DType)
	{
		STurn3dView * pTurn3d = FindChildByName2<STurn3dView>(L"turn3d");
		if(pTurn3d)
		{
			pTurn3d->Turn(pTab->GetPage(_T("lrc")),pTab->GetPage(_T("musiclist")),TRUE);
		}
		m_3DType=false;
	}
}

void CMainDlg::OnFlywndState( EventArgs *pEvt )
{
    FlyStateEvent *pEvtFlywnd = (FlyStateEvent*)pEvt;
    if(pEvtFlywnd->nPercent == SAnimator::PER_END)
    {
        //测试：隐藏音乐频谱 (可以用定时器判断分层窗口的收缩状态来控制)

        SWindow *pSpectrum = FindChildByName2<SWindow>("spectrum");
        if(pSpectrum) pSpectrum->SetVisible(pEvtFlywnd->bEndPos,TRUE);        
//         if (!m_bCut)
//         {
//             m_bCut=true;
//         }else
//         {
//             SWindow *pSpectrum = FindChildByName2<SWindow>("spectrum");
//             if(pSpectrum) pSpectrum->SetVisible(FALSE,TRUE);
//             m_bCut=false;
//         }        
    }
}

void CMainDlg::InsertTreeBox(vector<CString> vInfo)
{
	//找到列表控件,先清干净列表
	SListBoxEx *pMusicLbe=FindChildByName2<SListBoxEx>(L"music_lbe");
	if(pMusicLbe)
	{
		pMusicLbe->DeleteAllItems();
	}

	for (int i=0;i<vInfo.size();++i)
	{
		tagMusicInfo pMusicInfo;
		m_pMuOPreat->InsertMapInfo(i,vInfo[i],pMusicInfo);

		//往ListBox中添加新数据
		InsertSingleInfo(pMusicInfo,i);
	}
	pMusicLbe->SetCurSel(0);//设置第一项为选中

}

void CMainDlg::InsertSingleInfo(tagMusicInfo pMusicInfo, int nNum)
{
	/*---------------------------------------------- listboxex动态插入 beg -----------------------------------------------------*/
	//m_SeleInfoMap.clear();
	SListBoxEx *pMusicLbe=FindChildByName2<SListBoxEx>(L"music_lbe");
	if(pMusicLbe)
	{
		SStringW m_sTemp;     //信息
		SStringW StrTotleTime;//时间
		DWORD dwTotleTime = pMusicInfo.dwTime;
		StrTotleTime.Format(L"%u:%02u",dwTotleTime/60,dwTotleTime%60);
		if (nNum%2)
		{
			m_sTemp.Format(L"<item>\
							  <img skin=\"_skin.logo.skin\" pos=\"5,5,55,55\" />\
							  <text pos=\"70,5\"  valign=\"middle\" align=\"left\" colorText=\"#CDD7E1\" >歌曲：%s </text>\
							  <text pos=\"70,20\" valign=\"middle\" align=\"left\" colorText=\"#CDD7E1\" >歌手：%s </text>\
							  <text pos=\"70,35\" valign=\"middle\" align=\"left\" colorText=\"#CDD7E1\" >时长：%s 交流群:229313785 </text>\
							 </item>",pMusicInfo.szTitle,pMusicInfo.szArtist,StrTotleTime);	
		}else
		{
			m_sTemp.Format(L"<item>\
							  <img skin=\"_skin.spectrum\" pos=\"5,5,55,55\" />\
							  <text pos=\"70,5\"  valign=\"middle\" align=\"left\" colorText=\"#CDD7E1\" >歌曲：%s </text>\
							  <text pos=\"70,20\" valign=\"middle\" align=\"left\" colorText=\"#CDD7E1\" >歌手：%s </text>\
							  <text pos=\"70,35\" valign=\"middle\" align=\"left\" colorText=\"#CDD7E1\" >时长：%s 小可QQ:1035144170 </text>\
							</item>",pMusicInfo.szTitle,pMusicInfo.szArtist,StrTotleTime);
		}
		pMusicLbe->InsertItem(nNum,m_sTemp);
		m_SeleInfoMap.insert(pair<int, tagMusicInfo>(nNum, pMusicInfo));
	
	}
	/*---------------------------------------------- listboxex动态插入 end -----------------------------------------------------*/
}

void CMainDlg::OnMusicLbeEvent( EventArgs *pEvt )
{
	/*该如何响应当前 双击的选项播放音乐*/
	EventOfPanel *pEvtOfPanel = (EventOfPanel*)pEvt;

	/*---------------------------------------------- listboxex响应双击 beg -----------------------------------------------------*/
	if(pEvtOfPanel->pOrgEvt->GetID() >= EVT_ITEMPANEL_DBCLICK && pEvtOfPanel->pOrgEvt->GetID() <= EVT_ITEMPANEL_RCLICK)
	{
		HSTREEITEM hItem = (HSTREEITEM)pEvtOfPanel->pPanel->GetItemIndex();

		std::map <int, tagMusicInfo>::iterator iter=m_SeleInfoMap.begin();
		for (; iter != m_SeleInfoMap.end(); iter++)
		{
			if((HSTREEITEM)iter->first==hItem)
			{
				m_pMuOPreat->nIndex=iter->first;
				m_pMuOPreat->OnButPlay();
				ReDraw(0,0,0,0);
				STRACE(_T("你要播放歌曲是:列表第%d首歌曲"),hItem);
			}
		}
	}
	/*---------------------------------------------- listboxex响应双击 end -----------------------------------------------------*/
}

void CMainDlg::DrawMusicInfo()
{
	CString m_sTemp;
	tagMusicInfo pMusicInfo;
	pMusicInfo=*(m_pMuOPreat->m_MusicManager[m_pMuOPreat->nIndex]);
	DWORD dwTotleTime = pMusicInfo.dwTime;
	StrTotleTime.Format(TEXT("%u:%02u"),dwTotleTime/60,dwTotleTime%60);

	//找到列表控件
	SWindow *pText=FindChildByName2<SWindow>(L"play_title");
	if (pText)
	{
		m_sTemp.Format(_T("当前播放:%s 总长:%s"),pMusicInfo.szTitle,StrTotleTime);
		pText->SetWindowText(m_sTemp);
	}
}
LRESULT CMainDlg::ReDraw(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/)
{
	DrawMusicInfo();

	//同步进度条
	OnSetProgress();

	SListBoxEx *pMusicLbe=FindChildByName2<SListBoxEx>(L"music_lbe");
	if(pMusicLbe)
	{
		pMusicLbe->SetCurSel(m_pMuOPreat->nIndex);
		//对应滚动滑块
		CPoint ptNew;
		CSize size=pMusicLbe->GetViewSize();
		ptNew.x=size.cx;
		ptNew.y=size.cy/m_pMuOPreat->m_MusicManager.size()*(m_pMuOPreat->nIndex-2);//最好根据当前插入项数、宽度和能显示的来计算
		pMusicLbe->SetViewOrigin(ptNew);
	}

	return 0;
}
void CMainDlg::OnSetProgress()
{
	//设置滑块控件的长度，同时启动计时器，计算当前播放进度
	SSliderBar *pSlid=FindChildByName2<SSliderBar>(L"slider_test");
	if(pSlid)
	{
		pSlid->SetRange(0,m_pMuOPreat->m_MusicManager[m_pMuOPreat->nIndex]->dwTime);
		pSlid->SetValue(0);
	}
	//定时器控制滑块
	::KillTimer(this->m_hWnd,1);
	::SetTimer(this->m_hWnd,1,500,NULL);
	
}

void CMainDlg::OnTimer(UINT_PTR cTimerID)
{
	//定时器修改
	if (1==cTimerID)
	{
		SSliderBar *pSlid=FindChildByName2<SSliderBar>(L"slider_test");
		SStatic *pText=FindChildByName2<SStatic>(L"text_time");
		if(pSlid&&m_pMuOPreat->hStream)
		{
			pSlid->SetValue((int)BASS_ChannelBytes2Seconds(m_pMuOPreat->hStream,BASS_ChannelGetPosition(m_pMuOPreat->hStream,BASS_POS_BYTE)));

			CString strTime,m_sTemp;
			DWORD dwTime = (DWORD)BASS_ChannelBytes2Seconds(m_pMuOPreat->hStream,BASS_ChannelGetPosition(m_pMuOPreat->hStream,BASS_POS_BYTE));
			strTime.Format(TEXT("%u:%02u"),dwTime/60,dwTime%60);
			m_sTemp.Format(_T("%s/%s"),strTime,StrTotleTime);
			if (pText)
			{
				pText->SetWindowText(m_sTemp);
			}
		}

	}else
	{
		__super::OnTimer(cTimerID);
	}
}

void CMainDlg::ChangeLrcFont()
{
	//这里用保存的STreeItem来简单实现,也可通过遍历树实现
	SStringW strTemp;
	std::map<DWORD, STreeItem *>::iterator itr_data;

	for (itr_data=m_TreItemInfo.begin();itr_data!=m_TreItemInfo.end();itr_data++)
	{
		if (bTurnFlag)
		{
			if (nNum-1>=0)
			{
				if (nNum-1==itr_data->first)
				{
					//上一项恢复原样
					strTemp.Format(L"数据_%d",nNum-1);
					itr_data->second->FindChildByName(strTemp)->SetWindowText(szLrc[nNum-1]);
					itr_data->second->FindChildByName(strTemp)->SetAttribute(L"colorText",L"#ff0000");
					itr_data->second->FindChildByName(strTemp)->SetAttribute(L"font",L"face:微软雅黑,adding:5");
				}
			}
		}else
		{
			if (nNum+1<=15)
			{
				if (nNum+1==itr_data->first)
				{
					//上一项恢复原样
					strTemp.Format(L"数据_%d",nNum+1);
					itr_data->second->FindChildByName(strTemp)->SetWindowText(szLrc[nNum+1]);
					itr_data->second->FindChildByName(strTemp)->SetAttribute(L"colorText",L"#ff0000");
					itr_data->second->FindChildByName(strTemp)->SetAttribute(L"font",L"face:微软雅黑,adding:5");
				}
			}

		}

		//改变下一项
		if (nNum==itr_data->first)
		{
			strTemp.Format(L"数据_%d",nNum);
			itr_data->second->FindChildByName(strTemp)->SetWindowText(szLrc[nNum]);
			itr_data->second->FindChildByName(strTemp)->SetAttribute(L"colorText",L"#96D00D");
			itr_data->second->FindChildByName(strTemp)->SetAttribute(L"font",L"face:华文行楷,adding:18");
		}

	}
	if (bTurnFlag)
	{		
		nNum++;
	}else
	{		
		nNum--;
	}
	if(nNum>16)
	{
		nNum=15;
		bTurnFlag=false;
	}
	if (nNum<4)
	{
		nNum=4;
		bTurnFlag=true;
	}

}