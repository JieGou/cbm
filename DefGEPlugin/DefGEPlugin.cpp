#include "StdAfx.h"
#include "DefGEPlugin.h"

//���
#include "TunnelDraw.h"
//���
#include "DrillPoreDraw.h"
//�곡
#include "DrillSiteDraw.h"
//ú����
#include "CoalSurfaceDraw.h"

void DefGEPlugin::initialize( MineGEDrawManager* pGEDrawManager )
{
    BEGIN_REGISTER_MINEGE_DRAW( MineGEDrawManager, pGEDrawManager )
    // ���
    REGISTER_MINEGE_DRAW( Tunnel, TunnelDraw )
    //���
    REGISTER_MINEGE_DRAW( Pore, DrillPoreDraw );
    //�곡
    REGISTER_MINEGE_DRAW( DrillSite, DrillSiteDraw );
    //ú����
    REGISTER_MINEGE_DRAW( CoalSurface, CoalSurfaceDraw );
    END_REGISTER_MINEGE_DRAW
}

void DefGEPlugin::unInitialize( MineGEDrawManager* pGEDrawManager )
{
    BEGIN_UNREGISTER_MINEGE_DRAW( MineGEDrawManager, pGEDrawManager )
    // ���
    UNREGISTER_MINEGE_DRAW( Tunnel, TunnelDraw )
    //���
    UNREGISTER_MINEGE_DRAW( Pore, DrillPoreDraw );
    //�곡
    UNREGISTER_MINEGE_DRAW( DrillSite, DrillSiteDraw );
    //ú����
    UNREGISTER_MINEGE_DRAW( CoalSurface, CoalSurfaceDraw );
    END_UNREGISTER_MINEGE_DRAW
}

// ���������������ʵ�ֲ�����
MINEGE_PLUGIN_CREATE_FUNC_IMPL( DefGEPlugin )
