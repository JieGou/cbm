#pragma  once

#define ISNULL _T("**")

//��ʼ��ȫ�ֱ���(new������󣬲���ʼ��com)
extern bool initword();
//ж��ȫ�ֱ���(�ͷ��ڴ棬�ͷ�com)
extern void uninitword();
//���ɱ���
extern bool CreatReport(const CString& savePath,const AcDbObjectId& drill_site);
//��word�ĵ�
extern void OpenWordDocument( const CString& filePath );
