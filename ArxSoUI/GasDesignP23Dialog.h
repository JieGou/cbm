#pragma once
#include "AcadSouiDialog.h"

class GasDesignP23Dialog : public AcadSouiDialog
{

	/** ������������� */
public:
	GasDesignP23Dialog(BOOL bModal = FALSE);
	~GasDesignP23Dialog(void);

	/** �ؼ���Ϣ���� */
protected:
	void OnHeadGraphButtonClick();
	void OnDipGraphButtonClick();
	void OnPlaneGraphButtonClick();
	void OnSaveButtonClick();
	void OnRadioGroup1Switch(int nID);

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
		EVENT_NAME_COMMAND(_T("head_graph"), OnHeadGraphButtonClick)
		EVENT_NAME_COMMAND(_T("dip_graph"), OnDipGraphButtonClick)
		EVENT_NAME_COMMAND(_T("plane_graph"), OnPlaneGraphButtonClick)
		EVENT_NAME_COMMAND(_T("save"), OnSaveButtonClick)
		EVENT_ID_COMMAND_RANGE(120, 122, OnRadioGroup1Switch)
		CHAIN_EVENT_MAP(AcadSouiDialog)
	EVENT_MAP_END()
	
//HOST��Ϣ(WINDOWS��Ϣ)ӳ���
	BEGIN_MSG_MAP_EX(GasDesignP23Dialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(AcadSouiDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	SEdit* m_ThickEdit;
	SEdit* m_DipAngleEdit;
	SEdit* m_L1Edit;
	SEdit* m_L2Edit;
	SEdit* m_WEdit;
	SEdit* m_HEdit;
	SEdit* m_DpEdit;
	SEdit* m_PoreGapEdit;
	SEdit* m_PoreStubbleEdit;
	SRadioBox* m_PoreType1Radio;
	SRadioBox* m_PoreType2Radio;
	SRadioBox* m_PoreType3Radio;
	SEdit* m_PoreAngleEdit;

public:
	int coal_id; // �ⲿ����
	int tech_id;  // �ⲿ����

private:
	void initDatas();
	bool getPoint(AcGePoint3d& pt);

};
