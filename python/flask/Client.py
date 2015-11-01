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

from cbm import CbmService, ControlService
from cbm.ttypes import *

#�ͻ��˷�װ��
class RpcClient:
  def __init__(self, Service, host='localhost', port=9090):
    self.protocol = None
    self.transport = None
    self.client = None
    self.host = host
    self.port = port
    self.Service = Service
  
  def start(self):
    # Make socket
    self.transport = TSocket.TSocket(self.host, self.port)
    # Buffering is critical. Raw sockets are very slow
    self.transport = TTransport.TBufferedTransport(self.transport)
    # Wrap in a protocol
    self.protocol = TBinaryProtocol.TBinaryProtocol(self.transport)
    # ����ͻ��˶���
    self.client = self.Service.Client(self.protocol)
    # Connect!
    self.transport.open()

  def get(self):
      return self.client

  def close(self):
    if self.transport is not None:
      self.transport.close()

#����1
def QuitServer():
  ctrl_client = RpcClient(ControlService, port=9090)
  ctrl_client.start()
  ctrl_client.get().shutdown()
  ctrl_client.close()

#����2
def VerifyMineAccount(client):
  usename, pwd = 'dlj', '123'
  ret = client.VerifyMineAccount(usename, pwd)
  print '==>�û���:%s ����:%s ��֤���%d' % (usename, pwd, ret)

#����3
def GetAllMineBases(client):
  mine_bases = client.GetAllMineBases()
  print 'ú̿�����б�:',mine_bases[1]

# ע�����еĲ��Ժ���
all_cmds = {
  '1': VerifyMineAccount,
  '2': GetAllMineBases,
  'q': QuitServer
}

def main():
  try:
    
    cbm_client = RpcClient(CbmService, port=9100)
    cbm_client.start()

    while True:
      cmd = raw_input('������һ������:')
      if cmd == 'q' or cmd == 'Q':
        break
      if cmd in all_cmds:
        all_cmds[cmd](cbm_client.get())
        print '\n'
      else:
        print '����%sδʵ��!!!' % cmd
    cbm_client.close()

    # �ر�rpc������
    QuitServer()

  except Thrift.TException, tx:
    print '%s' % (tx.message)

if __name__ == '__main__':
  main()