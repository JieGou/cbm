// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� RPCDAO_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// RPCDAO_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef RPCDAO_EXPORTS
#define RPCDAO_API __declspec(dllexport)
#else
#define RPCDAO_API __declspec(dllimport)
#endif

// �����Ǵ� RpcDao.dll ������
class RPCDAO_API CRpcDao {
public:
	CRpcDao(void);
	// TODO: �ڴ�������ķ�����
};

extern RPCDAO_API int nRpcDao;

RPCDAO_API int fnRpcDao(void);
