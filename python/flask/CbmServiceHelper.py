#-*- coding:utf-8 -*-
#!/usr/bin/env python

# ����sqlalchemyģ��
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm.exc import NoResultFound
from sqlalchemy.orm.exc import MultipleResultsFound
# from sqlalchemy.ext.declarative import declarative_base

from cbm import CbmService
from cbm.ttypes import *

import sql
import ServerHelper
import CbmMath

#��ʼ��sqlalchemy������mysql���ݿ�
def init_sqlalchemy():
    #����mysql���ݲ�����session�Ự
    # engine = create_engine("mysql+pymysql://root:@localhost/cbm?charset=utf-8")
    engine = create_engine("mysql+pymysql://root:@localhost/cbm")
    Session = sessionmaker()
    Session.configure(bind=engine)
    return Session

import types
# ��¼���������Ƶ���������
obj_types_set = set([types.IntType, types.FloatType, types.StringType, types.LongType])
def obj_copy(obj1, obj2):
    for name in dir(obj1):
        if not hasattr(obj2, name):continue
        if name.startswith('__'):continue
        a = getattr(obj1, name)
        if type(a) in obj_types_set:
            setattr(obj2, name, a)

# �ο�:������service(http://blog.csdn.net/hivon/article/details/11681977)
# sqlalchemy�����ַ������(http://www.it165.net/database/html/201404/6034.html)
# service�ӿڴ�����
class CbmServiceHandler:
    def __init__(self, Session):
        self.session = Session()
        # ���mysql������������
        self.session.execute("set names 'gbk';")

    def InitSampleMine(self, region_id, account_id, name):
        query = self.session.query(sql.Mine).filter(sql.Mine.mine_region_id==region_id, sql.Mine.account_id==account_id).first()
        if query is None:
            mine = sql.Mine()
            mine.name = 'ʾ��������-%s' % name
            mine.mine_region_id = region_id
            mine.account_id = account_id
            self.session.add(mine)
            self.session.flush()
            self.session.commit()

    def InitSampleRegion(self):
        try:
            # ���ҹ���Ա�ʻ�
            admin = self.session.query(sql.Account).filter(sql.Account.username=='adminx').first()
            if admin is None:
                admin = sql.Account()
                admin.username = 'adminx'
                admin.password = '123'
                admin.comment = '��������Ա'
                self.session.add(admin)
                self.session.flush()
                self.session.commit()
                print admin.id
            # ��������ʾ������
            jincheng = self.session.query(sql.MineRegion).filter(sql.MineRegion.name=='����').one()
            lianghuai = self.session.query(sql.MineRegion).filter(sql.MineRegion.name=='����').one()
            songzao = self.session.query(sql.MineRegion).filter(sql.MineRegion.name=='����').one()
            # ����id���γ�ʼ��ʾ������������
            self.InitSampleMine(jincheng.id, admin.id, "����");
            self.InitSampleMine(lianghuai.id, admin.id, "����");
            self.InitSampleMine(songzao.id, admin.id, "����");
        except Exception, e:
            print e
    
    def GetOnlineAccountId(self):
        account_id = -1
        try:
            query = self.session.query(sql.Account).join(sql.SysInfo).first()
            account_id = query.id
        except Exception, e:
            account_id = -1
            print e
        return account_id

    def GetOnlineMine(self):
        mine = Mine()
        mine.id = -1

        account_id = self.GetOnlineAccountId()
        if account_id > -1:
            try:
                query = self.session.query(sql.Mine).filter(sql.Mine.account_id==account_id).one()
                obj_copy(query, mine)
            except Exception, e:
                mine.id = -1
                print e
        return mine

    def VerifyMineAccount(self, username, pwd):
        print '-> VerifyMineAccount'
        query = self.session.query(sql.Account).filter(sql.Account.username==username)
        if query.count() == 0:
            return 0  # �û���������
        elif query.count() > 1:
            return -2 # �ڲ�����(�û�����Ψһ)
        else:
            accout = query.one()
            if accout.password != pwd:
                return -1  # �������
            else:
                return 1  # �û����������ƥ��

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
            # ͨ�ø��ƺ���
            obj_copy(query, sample_mine)
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
                # ͨ�ø��ƺ���
                obj_copy(query, sample_coal)
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
            obj_copy(query[i], work_areas[i])
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
            obj_copy(query[i], work_surfs[i])
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
            obj_copy(query[i], drilling_surfs[i])
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
        # �����������˥��ϵ�� �� ú��͸����ϵ����������
        k1 = CbmMath.DifficultEval1(coal.decay_alpha);
        k2 = CbmMath.DifficultEval2(coal.permeability_lambda);
        return CbmMath.DifficultEvalHelper(k1, k2);

    def DifficultEvalString(self, coal):
        return ''

    def MineGasReservesW1(self, mine_id):
        return 0.0

    def MineGasReservesW2(self, mine_id):
        return 0.0

    def WorkAreaGasFlow(self, work_area, K1):
        return 0.0

    def MineGasFlow(self, mine):
        return 0.0

    def WorkSurfGasFlow1(self, coal, work_area, work_surf):
        return 0.0

    def WorkSurfGasFlow2(self, coal, work_area, work_surf):
        return 0.0

    def DrillingSurfGasFlow(self, coal, drilling_surf, tunnel):
        return 0.0

# ����������
def create_server(host, port):
     # sqlalchemy����mysql���ݿ�
    Session = init_sqlalchemy()
    # ����rpc��Ϣ����ӿ�
    handler = CbmServiceHandler(Session)
    processor = CbmService.Processor(handler)
    # ����thrift rpc������
    server = ServerHelper.make_rpc_server(processor, host=host, port=port)
    return handler, server