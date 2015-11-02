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

import CbmUtil

#客户端封装类
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
    # 构造客户端对象
    self.client = self.Service.Client(self.protocol)
    # Connect!
    self.transport.open()

  def get(self):
      return self.client

  def close(self):
    if self.transport is not None:
      self.transport.close()

#测试1
def QuitServer():
  ctrl_client = RpcClient(ControlService, port=9090)
  ctrl_client.start()
  ctrl_client.get().shutdown()
  ctrl_client.close()

#测试2
def VerifyMineAccount(client):
  username = raw_input('请输入用户名:')
  pwd = raw_input('请输入密码:')
  ret = client.VerifyMineAccount(username, pwd)
  if ret == 0:
    print '用户名不存在'
  elif ret == -1:
    print '密码错误'
  elif ret == 1:
    print '用户名和密码正确'
  else:
    print '未知错误'

#测试3
def GetMineBaseNames(client):
  mine_bases = client.GetMineBaseNames()
  print '煤炭基地列表:'
  for base in mine_bases:
    print '\t',base

def GetMineRegionsOfBase(client):
  baseName = raw_input('请输入煤炭基地名称:')
  mine_regions = client.GetMineRegionsOfBase(baseName)
  print '%s的矿区:' % (baseName)
  for region in mine_regions:
    print '\t',region

def GetBaseByRegion(client):
  regionName = raw_input('请输入矿区的名称:')
  baseName = client.GetBaseByRegion(regionName)
  print '%s的基地:%s' % (regionName, baseName)

def GetSampleMineOfRegion(client):
  regionName = raw_input('请输入矿区的名称:')
  mine = client.GetSampleMineOfRegion(regionName)
  print '示范矿区:%s的虚拟矿井:%s' % (regionName, mine)

def GetSampleCoalOfRegion(client):
  regionName = raw_input('请输入矿区的名称:')
  coal = client.GetSampleCoalOfRegion(regionName)
  print '示范矿区:%s的虚拟煤层:%s' % (regionName, coal)

def GetCoalNames(client):
  mine_id = int(input('请输入矿井id:'))
  coal_names = client.GetCoalNames(mine_id)
  print '矿井id=%d的煤层列表:' % mine_id
  for name in coal_names:
    print name

def GetCoalIds(client):
  mine_id = int(input('请输入矿井id:'))
  coal_ids = client.GetCoalIds(mine_id)
  print '矿井id=%d的煤层列表:' % mine_id
  for coal_id in coal_ids:
    print coal_id

def GetOnlineAccountId(client):
  account_id = client.GetOnlineAccountId()
  print '当前登录用户的id:%d' % account_id

def GetOnlineMine(client):
  mine = client.GetOnlineMine()
  print '当前登录用户对应的矿井:',mine

def GetWorkAreasOfMine(client):
  mine_id = int(input('请输入矿井id:'))
  work_areas = client.GetWorkAreasOfMine(mine_id)
  print '矿井id=%d的采区列表:' % mine_id
  for work_area in work_areas:
    print work_area.id, work_area.name

def GetWorkSurfsOfMine(client):
  mine_id = int(input('请输入矿井id:'))
  work_surfs = client.GetWorkSurfsOfMine(mine_id)
  print '矿井id=%d的回采工作面列表:' % mine_id
  for work_surf in work_surfs:
    print work_surf.id, work_surf.name

def GetDrillingSurfsOfMine(client):
  mine_id = int(input('请输入矿井id:'))
  drilling_surfs = client.GetDrillingSurfsOfMine(mine_id)
  print '矿井id=%d的掘进工作面列表:' % mine_id
  for drilling_surf in drilling_surfs:
    print drilling_surf.id, drilling_surf.name

def InitSampleRegion(client):
  print '创建超级管理员账户和密码'
  client.InitSampleRegion()

def DifficultEval(client):
  # CbmUtil.CopyAttribs
  pass

def DifficultEvalString(client):
  mine_id = int(input('请输入矿井id:'))
  coal_ids = client.GetCoalIdsOfMine(mine_id)
  if len(coal_ids) == 0:
    print '该矿井没有煤层'
  else:
    print '该矿井的煤层列表:', '  '.join([str(i) for i in coal_ids])
    coal_id = int(input('请选择一个煤层:'))

def MineGasReservesW1(client):
  pass

def MineGasReservesW2(client):
  pass

def WorkAreaGasFlow(client):
  pass

def MineGasFlow(client):
  pass

def WorkSurfGasFlow1(client):
  pass

def WorkSurfGasFlow2(client):
  pass

def DrillingSurfGasFlow(client):
  pass

def GetAccount(client):
  account_id = int(input('请输入账户id:'))
  # account = client.GetAccount(account_id)
  #account = client.GetAccountByFields1('id', '1')
  account = client.GetAccountByFields1('username', 'dlj')
  if account.id < 0:
    print '查询错误'
  else:
    print '账户id=%d 名称:%s' % (account.id, account.username)

def GetMine(client):
  mine = client.GetMineByForeignKey('account_id', 2)
  if mine.id < 0:
    print '查询错误'
  else:
    print '矿井id=%d 名称:%s' % (mine.id, mine.name)

def AddAccount(client):
  account = Account()
  account.username = raw_input('新建用户:')
  account.password = raw_input('密码:')

  account_id = client.AddAccount(account)
  print '新建用户的id=%d' % account_id

def DeleteAccount(client):
  pass

# 注册所有的测试函数
all_cmds = {
  '1': VerifyMineAccount,
  '2': GetMineBaseNames,
  '3': GetMineRegionsOfBase,
  '4': GetBaseByRegion,
  '5': GetSampleMineOfRegion,
  '6': GetSampleCoalOfRegion,
  '7': GetCoalNames,
  '8': GetCoalIds,
  '9': GetOnlineAccountId,
  '10': GetOnlineMine,
  '11': GetWorkAreasOfMine,
  '12': GetWorkSurfsOfMine,
  '13': GetDrillingSurfsOfMine,
  '14': InitSampleRegion,
  '15': DifficultEval,
  '16': DifficultEvalString,
  '17': MineGasReservesW1,
  '18': MineGasReservesW2,
  '19': WorkAreaGasFlow,
  '20': MineGasFlow,
  '21': WorkSurfGasFlow1,
  '22': WorkSurfGasFlow2,
  '23': DrillingSurfGasFlow,
  '24': GetAccount,
  '25': AddAccount,
  '26': GetMine,
  'q': QuitServer
}

def main():
  try:
    
    service_client = RpcClient(CbmService, port=9100)
    service_client.start()

    goto_quit = False
    while True:
      cmd = raw_input('请输入命令:')
      if cmd == 'q' or cmd == 'Q':
        goto_quit = True
        break
      elif cmd == 'c' or cmd == 'C':
        break
      if cmd in all_cmds:
        all_cmds[cmd](service_client.get())
        print '\n'
      else:
        print '命令%s未实现!!!' % cmd
    service_client.close()

    if goto_quit:
      # 关闭rpc服务器
      QuitServer()

  except Thrift.TException, tx:
    print '%s' % (tx.message)

if __name__ == '__main__':
  main()