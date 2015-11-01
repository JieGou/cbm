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

#��ʼ��sqlalchemy������mysql���ݿ�
def init_sqlalchemy():
    #����mysql���ݲ�����session�Ự
    # engine = create_engine("mysql+pymysql://root:@localhost/cbm?charset=utf-8")
    engine = create_engine("mysql+pymysql://root:@localhost/cbm")
    Session = sessionmaker()
    Session.configure(bind=engine)
    return Session

# �ο�:������service(http://blog.csdn.net/hivon/article/details/11681977)
# service�ӿڴ�����
class CbmServiceHandler:
  def __init__(self, Session):
    self.session = Session()
    # ���mysql������������
    self.session.execute("set names 'gbk';")

  def VerifyMineAccount(self, username, pwd):
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
    try:
        query = self.session.query(sql.MineBase.name).all()
        mine_bases = [mine_base.name for mine_base in query]
    except NoResultFound, e:
        mine_bases = []
    return mine_bases

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