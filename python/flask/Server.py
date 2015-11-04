#-*- coding:utf-8 -*-
#!/usr/bin/env python

import sys, glob
sys.path.append('gen-py')
# sys.path.insert(0, glob.glob('../../lib/py/build/lib.*')[0])

import logging

import ControlServerHelper
import CbmServerHelper
import ThriftServerHelper
from RpcClient import *

if __name__ == '__main__':
    # ����logĬ�ϵĻ�������
    logging.basicConfig()
    
    # ����control������
    ctrlHandler, ctrlServer = ControlServerHelper.create_server(HOST, PORT1)

    # ����service������
    handler, server = CbmServerHelper.create_server(HOST, PORT2)

    # ע��service�����������Ʒ���ӿ�
    ctrlHandler.register(server)

    # ����һ���̸߳�service��������
    print '����service������(�˿�:9100)...'
    t1 = ThriftServerHelper.run_rpc_server(server, runThread=True)

    # �������Ʒ�����,����shutdown��Ϣ(���������߳�)
    print '����control������(�˿�:9090)...'
    ThriftServerHelper.run_rpc_server(ctrlServer, runThread=False)
    