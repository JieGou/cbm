#-*- coding:utf-8 -*-
#!/usr/bin/env python

# 导入sqlalchemy模块
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm.exc import NoResultFound
from sqlalchemy.orm.exc import MultipleResultsFound
# from sqlalchemy.ext.declarative import declarative_base

from cbm import CbmService
from cbm.ttypes import *

import sql
import CbmUtil
import ServerHelper
import SQLServiceHelper

#初始化sqlalchemy，连接mysql数据库
def init_sqlalchemy():
    #连接mysql数据并创建session会话
    # engine = create_engine("mysql+pymysql:# root:@localhost/cbm?charset=utf-8")
    #echo开关用于调试!!!
    engine = create_engine("mysql+pymysql://root:@localhost/cbm",echo=True)
    Session = sessionmaker()
    Session.configure(bind=engine)
    return Session

# 参考:处理多个service(http:# blog.csdn.net/hivon/article/details/11681977)
# sqlalchemy的两种方法详解(http:# www.it165.net/database/html/201404/6034.html)
# service接口处理类
class CbmServiceHandler(SQLServiceHelper.SQLServiceHandler):
    def __init__(self, Session):
        self.session = Session()
        # 解决mysql中文乱码问题
        self.session.execute("set names 'gbk'")
        # 调用基类的初始化方法
        super(CbmServiceHandler, self).__init__(self.session)

    def InitSampleMine(self, region_id, account_id, name):
        query = self.session.query(sql.Mine).filter(sql.Mine.mine_region_id==region_id, sql.Mine.account_id==account_id).first()
        if query is None:
            mine = sql.Mine()
            mine.name = '示范矿区矿井-%s' % name
            mine.mine_region_id = region_id
            mine.account_id = account_id
            self.session.add(mine)
            self.session.flush()
            self.session.commit()

    def InitSampleRegion(self):
        try:
            # 查找管理员帐户
            admin = self.session.query(sql.Account).filter(sql.Account.username=='adminx').first()
            if admin is None:
                admin = sql.Account()
                admin.username = 'adminx'
                admin.password = '123'
                admin.comment = '超级管理员'
                self.session.add(admin)
                self.session.flush()
                self.session.commit()
                print admin.id
            # 查找三个示范矿区
            jincheng = self.session.query(sql.MineRegion).filter(sql.MineRegion.name=='晋城').one()
            lianghuai = self.session.query(sql.MineRegion).filter(sql.MineRegion.name=='两淮').one()
            songzao = self.session.query(sql.MineRegion).filter(sql.MineRegion.name=='松藻').one()
            # 根据id依次初始化示范矿区的数据
            self.InitSampleMine(jincheng.id, admin.id, "晋城")
            self.InitSampleMine(lianghuai.id, admin.id, "两淮")
            self.InitSampleMine(songzao.id, admin.id, "松藻")
        except Exception, e:
            print e
    
    def GetOnlineAccountId(self):
        query = self.session.query(sql.Account).join(sql.SysInfo).first()
        if query is None:
            return -1
        else:
            return query.id

    def GetOnlineMine(self):
        mine = Mine()
        mine.id = -1

        account_id = self.GetOnlineAccountId()
        if account_id > -1:
            try:
                query = self.session.query(sql.Mine).filter(sql.Mine.account_id==account_id).one()
                CbmUtil.CopyAttribs(query, mine)
            except Exception, e:
                mine.id = -1
                print e
        return mine

    def VerifyMineAccount(self, username, pwd):
        print '. VerifyMineAccount'
        query = self.session.query(sql.Account).filter(sql.Account.username==username)
        if query.count() == 0:
            return 0  # 用户名不存在
        elif query.count() > 1:
            return -2 # 内部错误(用户名不唯一)
        else:
            accout = query.one()
            if accout.password != pwd:
                return -1  # 密码错误
            else:
                return 1  # 用户名和密码均匹配

    def GetAllMineBases(self):
        mine_bases = []
        query = self.session.query(sql.MineBase.name).all()
        mine_bases = [mine_base.name for mine_base in query]
        return mine_bases

    def GetAllMineRegions(self, baseName):
        mine_regions = []
        query = self.session.query(sql.MineRegion).join(sql.MineBase).filter(sql.MineBase.name==baseName).all()
        mine_regions = [region.name for region in query]
        return mine_regions

    def GetBaseByRegion(self, regionName):
        baseName = ''
        try:
            query = self.session.query(sql.MineBase).join(sql.MineRegion).filter(sql.MineRegion.name==regionName).one()
            baseName = query.name
        except Exception, e:
            baseName = ''
            print e
        return baseName

    def GetSampleMine(self, regionName):
        sample_mine = Mine()
        sample_mine.id = -1
        try:
            query = self.session.query(sql.Mine).join(sql.MineRegion).filter(sql.MineRegion.name==regionName).one()
            # 通用复制函数
            CbmUtil.CopyAttribs(query, sample_mine)
        except Exception, e:
            sample_mine.id = -1
            print e
        return sample_mine

    def GetSampleCoal(self, regionName):
        sample_coal = Coal()
        sample_coal.id = -1
        
        sample_mine = self.GetSampleMine(regionName)
        if sample_mine.id > -1:
            try:
                query = self.session.query(sql.Coal).filter(sql.Coal.mine_id==sample_mine.id).one()
                # 通用复制函数
                CbmUtil.CopyAttribs(query, sample_coal)
            except Exception, e:
                sample_coal.id = -1
                print e
        return sample_coal

    def GetCoalNames(self, mine_id):
        query = self.session.query(sql.Coal).filter(sql.Coal.mine_id==mine_id).all()
        return [coal.name for coal in query]

    def GetCoalIds(self, mine_id):
        query = self.session.query(sql.Coal).filter(sql.Coal.mine_id==mine_id).all()
        return [coal.id for coal in query]

    def GetWorkAreas(self, mine_id):
        coal_ids = self.GetCoalIds(mine_id)
        if len(coal_ids) == 0:
            return []

        query = self.session.query(sql.WorkArea).filter(sql.WorkArea.coal_id.in_(coal_ids)).all()
        if len(query) == 0:
            return []

        n = len(query)
        work_areas = [WorkArea() for i in range(n)]
        for i in range(n):
            work_areas[i].id = -1
            CbmUtil.CopyAttribs(query[i], work_areas[i])
        return work_areas

    def GetWorkSurfs(self, mine_id):
        work_area_ids = self.GetWorkAreaIds(mine_id)
        if len(work_area_ids) == 0:
            return []

        query = self.session.query(sql.WorkSurf).filter(sql.WorkSurf.work_area_id.in_(work_area_ids)).all()
        if len(query) == 0:
            return []

        n = len(query)
        work_surfs = [WorkSurf() for i in range(n)]
        for i in range(n):
            work_surfs[i].id = -1
            CbmUtil.CopyAttribs(query[i], work_surfs[i])
        return work_surfs

    def GetDrillingSurfs(self, mine_id):
        work_area_ids = self.GetWorkAreaIds(mine_id)
        if len(work_area_ids) == 0:
            return []

        query = self.session.query(sql.DrillingSurf).filter(sql.DrillingSurf.work_area_id.in_(work_area_ids)).all()
        if len(query) == 0:
            return []
        
        n = len(query)
        drilling_surfs = [DrillingSurf() for i in range(n)]
        for i in range(n):
            drilling_surfs[i].id = -1
            CbmUtil.CopyAttribs(query[i], drilling_surfs[i])
        return drilling_surfs

    def GetWorkAreaIds(self, mine_id):
        coal_ids = self.GetCoalIds(mine_id)
        if len(coal_ids) == 0:
            return []
        query = self.session.query(sql.WorkArea).filter(sql.WorkArea.coal_id.in_(coal_ids)).all()
        return [work_area.id for work_area in query]

    def GetWorkSurfIds(self, mine_id):
        work_area_ids = self.GetWorkAreaIds(mine_id)
        if len(work_area_ids) == 0:
            return []
        query = self.session.query(sql.WorkSurf).filter(sql.WorkSurf.work_area_id.in_(work_area_ids)).all()
        return [work_surf.id for work_surf in query]

    def GetDrillingSurfIds(self, mine_id):
        work_area_ids = self.GetWorkAreaIds(mine_id)
        if len(work_area_ids) == 0:
            return []
        query = self.session.query(sql.DrillingSurf).filter(sql.DrillingSurf.work_area_id.in_(work_area_ids)).all()
        return [drilling_surf.id for drilling_surf in query]

    def DifficultEval(self, coal):
        # 根据钻孔流量衰减系数 和 煤层透气性系数进行评价
        k1 = CbmUtil.DifficultEval1(coal.decay_alpha)
        k2 = CbmUtil.DifficultEval2(coal.permeability_lambda)
        return CbmUtil.DifficultEvalHelper(k1, k2)

    def DifficultEvalString(self, coal):
        s1 = PermeabilityString(coal.permeability_k)
        s2 = EvalDifficultString(coal.eval_difficult)
        return "该煤层属于:%s\\n瓦斯抽采难易程度:%s" % (s1, s2)

    def MineGasReservesW1(self, mine_id):
       query = self.session.query(sql.Coal).filter(sql.Coal.mine_id==mine_id, sql.Coal.minable==1).all()
       return sum([coal.res_a1*coal.gas_x1 for coal in query])
    
    def MineGasReservesW2(self, mine_id):
        query = self.session.query(sql.Coal).filter(sql.Coal.mine_id==mine_id, sql.Coal.minable==0).all()
        if len(query) == 0:
            return 0
        else:
            return sum([coal.res_a1*coal.gas_x1 for coal in query])

    def WorkAreaGasFlow(self, work_area, K1):
        query = self.session.query(sql.WorkSurf).filter(sql.WorkSurf.work_area_id==work_area.id).all()
        S1 = sum([ws.qr*ws.a for ws in query])
        query = self.session.query(sql.DrillingSurf).filter(sql.DrillingSurf.work_area_id==work_area.id).all()
        S2 = sum([tws.qa for tws in query])
        if work_area.a <= 0:
            return -1
        else:
            return K1*(S1+S2)/work_area.a

    def MineGasFlow(self, mine):
        work_areas = self.GetWorkAreas(mine.id)
        if len(work_areas) == 0:
            return 0.0

        S1 = sum([work_area.qr*work_area.a for work_area in query])
        S2 = sum([work_area.a for work_area in query])
        if S2 <= 0:
            return -1
        else:
            K2 = mine.gas_k2
            return K2*S1/S2

    def WorkSurfGasFlow1(self, coal, work_area, work_surf):
        K1 = work_surf.k1
        K2 = work_surf.k2
        K3 = work_surf.k3
        kf = work_surf.kf
        # 开采层厚度(????分层如何考虑???)
        m = coal.thick
        # 工作面采高
        M = coal.hw
        W0 = coal.gas_w0
        Wc = coal.gas_wc2

        # 计算开采层相对瓦斯涌出量q1
        if work_surf.layerable == 0:
            return K1 * K2 * K3 * ( W0 - Wc ) * m / M
        else:
            return K1 * K2 * K3 * ( W0 - Wc ) * kf

    def WorkSurfGasFlow2(self, coal, work_area, work_surf):
        query = self.session.query(sql.AdjLayer).filter(sql.AdjLayer.work_surf_id==work_surf.id).all()
        if len(query) == 0:
            return 0.0
        f = lambda adj_coal:(adj_coal.gas_w0-adj_coal.gas_wc2)*adj_coal.thick*adj_coal.gas_eta
        S = sum([f(adj_layer.coal) for adj_layer in query])
        M = coal.hw
        return S / M

    def DrillingSurfGasFlow(self, coal, drilling_surf, tunnel):
        # 计算q0
        Vr = coal.vr
        W0 = coal.gas_w0
        D = tunnel.d
        v = tunnel.v
        L = tunnel.l
        S = tunnel.s
        r = coal.rho
        Wc = coal.gas_wc2
        q0 = ( 0.0004 * pow( Vr, 2 ) + 0.16 ) * 0.026 * W0
        q3 = D * v * q0 * ( 2 * sqrt( L / v ) - 1 )
        q4 = S * v * r * ( W0 - Wc )
        qa = q3 + q4 #  掘进面瓦斯涌出量

        # 计算结果保存到参数结构体
        ret = DrillingSurfGasFlowResult()
        ret.q0 = q0
        ret.q3 = q3
        ret.q4 = q4
        ret.qa = qa
        return ret

# 创建服务器
def create_server(host, port):
     # sqlalchemy连接mysql数据库
    Session = init_sqlalchemy()
    # 构造rpc消息处理接口
    handler = CbmServiceHandler(Session)
    processor = CbmService.Processor(handler)
    # 创建thrift rpc服务器
    server = ServerHelper.make_rpc_server(processor, host=host, port=port)
    return handler, server