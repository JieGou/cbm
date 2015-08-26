#pragma once
#include "AcadSouiDialog.h"

class SampleManageDialog : public AcadSouiDialog
{

	/** ������������� */
public:
	SampleManageDialog(BOOL bModal = FALSE);
	~SampleManageDialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnRegionComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnTopoGeoComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnHydrGeoComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnRankComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnConstComplexityComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnResAbundanceComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnStabilityComboxSelChanged(SOUI::EventArgs *pEvt);
	void OnSaveButtonClick();
	void OnTechModeButtonClick();
	void OnTechnologyButtonClick();

	/** �˵���Ϣ */
protected:
	//����˵���Ϣ(�˵���һ��������xml�ļ���������ÿ���˵����һ��id��)
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	/** ������Ϣ */
protected:
	//�Ի����ʼ������
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	//�ؼ���Ϣӳ���
	EVENT_MAP_BEGIN()
		EVENT_NAME_HANDLER(_T("region"), EVT_CB_SELCHANGE, OnRegionComboxSelChanged)
		EVENT_NAME_HANDLER(_T("topo_geo"), EVT_CB_SELCHANGE, OnTopoGeoComboxSelChanged)
		EVENT_NAME_HANDLER(_T("hydr_geo"), EVT_CB_SELCHANGE, OnHydrGeoComboxSelChanged)
		EVENT_NAME_HANDLER(_T("rank"), EVT_CB_SELCHANGE, OnRankComboxSelChanged)
		EVENT_NAME_HANDLER(_T("const_complexity"), EVT_CB_SELCHANGE, OnConstComplexityComboxSelChanged)
		EVENT_NAME_HANDLER(_T("res_abundance"), EVT_CB_SELCHANGE, OnResAbundanceComboxSelChanged)
		EVENT_NAME_HANDLER(_T("stability"), EVT_CB_SELCHANGE, OnStabilityComboxSelChanged)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_NAME_COMMAND(_T("tech_mode"), OnTechModeButtonClick)
		EVENT_NAME_COMMAND(_T("technology"), OnTechnologyButtonClick)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(SampleManageDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SComboBox* m_RegionCombox;
	SComboBox* m_TopoGeoCombox;
	SCheckBox* m_GroundCondCheck;
	SComboBox* m_HydrGeoCombox;
	SEdit* m_FValueEdit;
	SEdit* m_ThickEdit;
	SComboBox* m_RankCombox;
	SEdit* m_PressureEdit;
	SEdit* m_GasContentEdit;
	SEdit* m_GasPenetrationEdit;
	SComboBox* m_ConstComplexityCombox;
	SEdit* m_VarCoeffEdit;
	SEdit* m_DipAngleEdit;
	SEdit* m_CavingZoneHeightEdit;
	SComboBox* m_ResAbundanceCombox;
	SEdit* m_LayerGapEdit;
	SEdit* m_InfluenceFactorEdit;
	SEdit* m_MineIndexEdit;
	SComboBox* m_StabilityCombox;
	SCheckBox* m_MinableCheck;

protected:
	virtual void OnDestroyWindow();

private:
	void initMineDatas();
	void initCoalDatas();
};
