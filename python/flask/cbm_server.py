#-*- coding:utf-8 -*-
#!/usr/bin/env python

import sys, glob
sys.path.append('gen-py')
# sys.path.insert(0, glob.glob('../../lib/py/build/lib.*')[0])

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

from cbm import CbmService, ServerControl
from cbm.ttypes import *

# ����sqlalchemyģ��
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
# from sqlalchemy.ext.declarative import declarative_base
import sql

import threading

#���������ƽӿڴ�����
class ServerControlHandler:
    def __init__(self):
        self.server_list = []
    def register(self, server):
        self.server_list.append(server)
    def shutdown(self):
        print '����������:',len(self.server_list)
        for server in self.server_list:
            print '�رշ�����(��δʵ��,ֱ��ǿ���˳�����)...'
            # python��thrift���û��ʵ��stop()����
            # server.stop()
            #ֱ��ǿ���˳�
            sys.exit()

#service�ӿڴ�����
class CbmServiceHandler:
  def __init__(self, Session):
    self.session = Session()

  def VerifyMineAccount(self, username, pwd):
    print '��֤�û���:%s   ����:%s�Ƿ�ƥ��' % (username, pwd)
    query = self.session.query(sql.Account)
    # print query.statement # ͬ��
    return 0

  def GetAllMineBases(self):
    print '��ȡ���е�ú̿��������,����һ���б�'
    return []

#��ʼ��sqlalchemy������mysql���ݿ�
def init_sqlalchemy():
    #����mysql���ݲ�����session�Ự
    engine = create_engine("mysql+pymysql://root:@localhost/cbm?charset=utf8")
    Session = sessionmaker()
    Session.configure(bind=engine)
    return Session

def make_rpc_server(processor, host='localhost', port=9090):
    transport = TSocket.TServerSocket(host=host, port=port)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()
    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)
    
    # You could do one of these for a multithreaded server
    # server = TServer.TThreadedServer(processor, transport, tfactory, pfactory)
    
    # server = TServer.TThreadPoolServer(processor, transport, tfactory, pfactory)
    # server.daemon = True #enable ctrl+c to exit the server
    # server.setNumThreads(10);
    return server

def run_rpc_server(server):
    print '����rpc������(python)...\n'
    server.serve()

# �رշ�������˼·:
# http://grokbase.com/t/thrift/user/11541vwzj4/stop-the-thrift-server
if __name__ == '__main__':
    # ������������Ϣ����ӿ�
    ctrlHandler = ServerControlHandler()
    # �������Ʒ�����
    ctrlServer = make_rpc_server(ServerControl.Processor(ctrlHandler), port=9090)
    # ע������������Ʒ���ӿ�
    ctrlHandler.register(ctrlServer)

    # sqlalchemy����mysql���ݿ�
    Session = init_sqlalchemy()
    # ����rpc��Ϣ����ӿ�
    handler = CbmServiceHandler(Session)
    processor = CbmService.Processor(handler)
    # ����thrift rpc������
    server = make_rpc_server(processor, port=9100)

    # ע������������Ʒ���ӿ�
    ctrlHandler.register(server)

    # �����̣߳����߳�����rpc����
    t1 = threading.Thread(target=run_rpc_server,args=(server,))
    t1.setDaemon(True)
    t1.start()

    # �������Ʒ�����(���������߳�)
    run_rpc_server(ctrlServer)
    