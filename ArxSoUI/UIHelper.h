#pragma once

class UIHelper
{
public:
    static void InitAllData();
    static void InitSouiEnviroment();
    static void UnInitSouiEnviroment();
    static void ShowModelessDemo();
    static void ShowModalDemo();
    static void TestRtfViewer();
    static void TestPicViewer();
    static void ShowImgView( const CString& bstrFileName );

    //��¼
    static void Login();
    //ע��
    static void RegMine();
    //ע��
    static void Logout();
    //ʾ���������������
    static void SampleManage();
    //��������
    static void GasTechModeDecision();
    //�����
    static void MineDesign();
    //�ؼ������������
    static void KeyParamCacl();
    //�����ĵ����
    static void PolicyHelp();
    //������(������)
    static void Main();
    //�ؼ���������-ú����������׳̶�����
    static void KP1();
    //�ؼ���������-��ú�����������ɳ���Ԥ��
    static void KP2();
    //�ؼ���������-����˹ӿ����Ԥ��
    static void KP3();
    //�ؼ���������-�����������˹ӿ����Ԥ��
    static void KP4();
    //�ؼ���������-�زɹ�������˹ӿ����Ԥ��
    static void KP5();
    //�ؼ���������-�߳���������λ����
    static void KP6();
    //�ؼ���������-��λ��������Ч���跶Χ����
    static void KP7();
    //�ؼ���������-ú����˹��ɰ뾶����
    static void KP8();
    //�ؼ���������-��ɹܾ���С��������
    static void KP9();
    //�ؼ���������-�װ���������
    static void KP10();
    //�ؼ���������-���۵�Ԫ���ּ���
    static void KP11();

    //ú����������
    static void GasDesign();
};