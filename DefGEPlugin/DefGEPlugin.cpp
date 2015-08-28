#include "StdAfx.h"
#include "DefGEPlugin.h"

// ˫�����
#include "DoubleTunnelDraw.h"
// ����߼�ͷ
#include "PolyLineDirectionDraw.h"
//���
#include "SimplePoreDraw.h"
//�곡
#include "SimpleDrillSiteDraw.h"
//ú����
#include "SimpleCoalSurfaceDraw.h"

void DefGEPlugin::initialize( MineGEDrawManager* pGEDrawManager )
{
    BEGIN_REGISTER_MINEGE_DRAW( MineGEDrawManager, pGEDrawManager )
    // ���
    REGISTER_MINEGE_DRAW( Tunnel, DoubleTunnelDraw )
    //��������
    REGISTER_MINEGE_DRAW( WindDirection, PolyLineDirectionDraw )
    //���
    REGISTER_MINEGE_DRAW( Pore, SimplePoreDraw );
    //�곡
    REGISTER_MINEGE_DRAW( DrillSite, SimpleDrillSiteDraw );
    //ú����
    REGISTER_MINEGE_DRAW( CoalSurface, SimpleCoalSurfaceDraw );
    END_REGISTER_MINEGE_DRAW
}

void DefGEPlugin::unInitialize( MineGEDrawManager* pGEDrawManager )
{
    BEGIN_UNREGISTER_MINEGE_DRAW( MineGEDrawManager, pGEDrawManager )
    // ���
    UNREGISTER_MINEGE_DRAW( Tunnel, DoubleTunnelDraw )
    // ��������
    UNREGISTER_MINEGE_DRAW( WindDirection, PolyLineDirectionDraw )
    //���
    UNREGISTER_MINEGE_DRAW( Pore, SimplePoreDraw );
    //�곡
    UNREGISTER_MINEGE_DRAW( DrillSite, SimpleDrillSiteDraw );
    //ú����
    UNREGISTER_MINEGE_DRAW( CoalSurface, SimpleCoalSurfaceDraw );
    END_UNREGISTER_MINEGE_DRAW
}

// ���������������ʵ�ֲ�����
MINEGE_PLUGIN_CREATE_FUNC_IMPL( DefGEPlugin )
