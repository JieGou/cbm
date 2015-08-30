#include "StdAfx.h"
#include "ReactorHelper.h"

#include "LinkedGEEditorReactor.h"
#include "MineGETooltipMonitor.h"
#include "MineGEDatabaseReactor.h"

/*
 * ���ڼ�¼��Document��ص�reactor
 * ����AcDbDataBaseReactor��AcEdInputPointMonitor�ȶ������ĵ���ص�
 * һ���ĵ������Ӧһ��reactor�����Կ�����"�ֲ���"
 * ��AcEditorReactor����AcEditor�����Կ�����"ȫ�ֵ�"
 * ��arx����Ϣ���̿��Կ�������kLoadAppMsg()��AcEditor��Ч��
 * �������������ĵ�����(AcApDocument)�����ݿ����(AcDbDatabase)������Ч��
 * ֻ����kLoadDwgMsg()�е��ĵ������ݿ����ſ�ʼ��Ч
 */
#include <map>
struct MineGE_DocumentReactor
{
    MineGE_DocumentReactor() : pTooltipMonitor( 0 ), pDbReactor( 0 ) {}
    MineGETooltipMonitor* pTooltipMonitor;
    MineGEDatabaseReactor* pDbReactor;
    // ��������������� AcDbDatabaseReactor��
    // AcEdInputPointMonitor������ApApDocument����reactor
    // ...
    // ������һ����ڹ���Ҳ����˶��ĵ�������
    // 1) �½��ĵ�������kLoadDwgMsg��Ϣ
    // 2) �����ĵ�������arx����Ҳ�������е��ĵ�����kLoadDwgMsg��Ϣ
    // 3) �ر��ĵ��� ����kUnloadDwgMsg��Ϣ
    // 4) ж��arx����Ҳ�������е��ĵ�����kUnloadDwgMsg��Ϣ
};

/*
 * long���ͱ�ʾAcApDocument*��ָ���ַ
 */
typedef std::map<long, MineGE_DocumentReactor> DocumentReactorMap;

LinkedGEEditorReactor* pEdgeEdReactor = 0;
DocumentReactorMap* pDocumentReactorMap_MineGE = 0;

void ReactorHelper::CreateLinkedGE_EditorReactor()
{
    if( pEdgeEdReactor == 0 )
    {
        pEdgeEdReactor = new LinkedGEEditorReactor( true );
    }
}

void ReactorHelper::RemoveLinkedGE_EditorReactor()
{
    delete pEdgeEdReactor;
    pEdgeEdReactor = 0;
}

void ReactorHelper::CreateDocumentReactorMap()
{
    if( pDocumentReactorMap_MineGE == 0 )
    {
        pDocumentReactorMap_MineGE = new DocumentReactorMap();
    }
}

void ReactorHelper::RemoveDocumentReactorMap()
{
    delete pDocumentReactorMap_MineGE;
    pDocumentReactorMap_MineGE = 0;
}

void ReactorHelper::AddDocumentReactor( AcApDocument* pDoc )
{
    if( pDoc == 0 ) return;
    if( pDocumentReactorMap_MineGE == 0 ) return;
    long id = ( long )pDoc;
    DocumentReactorMap::iterator itr = pDocumentReactorMap_MineGE->find( id );
    if( itr != pDocumentReactorMap_MineGE->end() ) return;

    MineGE_DocumentReactor dr;
    //dr.pTooltipMonitor = new MineGETooltipMonitor(pDoc);
    dr.pDbReactor = new MineGEDatabaseReactor( pDoc->database() );

    pDocumentReactorMap_MineGE->insert( DocumentReactorMap::value_type( id, dr ) );
}

void ReactorHelper::RemoveDocumentReactor( AcApDocument* pDoc )
{
    if( pDoc == 0 ) return;
    if( pDocumentReactorMap_MineGE == 0 ) return;
    long id = ( long )pDoc;
    DocumentReactorMap::iterator itr = pDocumentReactorMap_MineGE->find( id );
    if( itr == pDocumentReactorMap_MineGE->end() ) return;

    // �����
    MineGE_DocumentReactor dr = itr->second;
    delete dr.pDbReactor;
    //delete dr.pTooltipMonitor;

    pDocumentReactorMap_MineGE->erase( id );
}