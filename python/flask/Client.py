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

from cbm import CbmService
from cbm.ttypes import *
from ctrl import ControlService

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
  username = raw_input('�������û���:')
  pwd = raw_input('����������:')
  ret = client.VerifyMineAccount(username, pwd)
  if ret == 0:
    print '�û���������'
  elif ret == -1:
    print '�������'
  elif ret == 1:
    print '�û�����������ȷ'
  else:
    print 'δ֪����'

#����3
def GetAllMineBases(client):
  mine_bases = client.GetAllMineBases()
  print 'ú̿�����б�:'
  for base in mine_bases:
    print '\t',base

def GetAllMineRegions(client):
  baseName = raw_input('������ú̿��������:')
  mine_regions = client.GetAllMineRegions(baseName)
  print '%s�Ŀ���:' % (baseName)
  for region in mine_regions:
    print '\t',region

def GetBaseByRegion(client):
  regionName = raw_input('���������������:')
  baseName = client.GetBaseByRegion(regionName)
  print '%s�Ļ���:%s' % (regionName, baseName)

def GetSampleMine(client):
  regionName = raw_input('���������������:')
  mine = client.GetSampleMine(regionName)
  print 'ʾ������:%s�������:%s' % (regionName, mine)

def GetSampleCoal(client):
  regionName = raw_input('���������������:')
  coal = client.GetSampleCoal(regionName)
  print 'ʾ������:%s������ú��:%s' % (regionName, coal)

def GetCoalNames(client):
  mine_id = int(input('�������id:'))
  coal_names = client.GetCoalNames(mine_id)
  print '��id=%d��ú���б�:' % mine_id
  for name in coal_names:
    print name

def GetCoalIds(client):
  mine_id = int(input('�������id:'))
  coal_ids = client.GetCoalIds(mine_id)
  print '��id=%d��ú���б�:' % mine_id
  for coal_id in coal_ids:
    print coal_id

def GetOnlineAccountId(client):
  account_id = client.GetOnlineAccountId()
  print '��ǰ��¼�û���id:%d' % account_id

def GetOnlineMine(client):
  mine = client.GetOnlineMine()
  print '��ǰ��¼�û���Ӧ�Ŀ�:',mine

def GetWorkAreas(client):
  mine_id = int(input('�������id:'))
  work_areas = client.GetWorkAreas(mine_id)
  print '��id=%d�Ĳ����б�:' % mine_id
  for work_area in work_areas:
    print work_area.id, work_area.name

def GetWorkSurfs(client):
  mine_id = int(input('�������id:'))
  work_surfs = client.GetWorkSurfs(mine_id)
  print '��id=%d�Ļزɹ������б�:' % mine_id
  for work_surf in work_surfs:
    print work_surf.id, work_surf.name

def GetDrillingSurfs(client):
  mine_id = int(input('�������id:'))
  drilling_surfs = client.GetDrillingSurfs(mine_id)
  print '��id=%d�ľ���������б�:' % mine_id
  for drilling_surf in drilling_surfs:
    print drilling_surf.id, drilling_surf.name

def InitSampleRegion(client):
  print '������������Ա�˻�������'
  client.InitSampleRegion()

# ע�����еĲ��Ժ���
all_cmds = {
  '1': VerifyMineAccount,
  '2': GetAllMineBases,
  '3': GetAllMineRegions,
  '4': GetBaseByRegion,
  '5': GetSampleMine,
  '6': GetSampleCoal,
  '7': GetCoalNames,
  '8': GetCoalIds,
  '9': GetOnlineAccountId,
  '10': GetOnlineMine,
  '11': GetWorkAreas,
  '12': GetWorkSurfs,
  '13': GetDrillingSurfs,
  '14': InitSampleRegion,
  'q': QuitServer
}

def main():
  try:
    
    service_client = RpcClient(CbmService, port=9100)
    service_client.start()

    while True:
      cmd = raw_input('����������:')
      if cmd == 'q' or cmd == 'Q':
        break
      if cmd in all_cmds:
        all_cmds[cmd](service_client.get())
        print '\n'
      else:
        print '����%sδʵ��!!!' % cmd
    service_client.close()

    # �ر�rpc������
    QuitServer()

  except Thrift.TException, tx:
    print '%s' % (tx.message)

if __name__ == '__main__':
  main()