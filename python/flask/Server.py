#-*- coding:utf-8 -*-
#!/usr/bin/env python

import sys, glob
sys.path.append('gen-py')
# sys.path.insert(0, glob.glob('../../lib/py/build/lib.*')[0])

import logging

import ControlServiceHelper
import CbmServiceHelper
import ServerHelper

if __name__ == '__main__':
    # ����logĬ�ϵĻ�������
    logging.basicConfig()

    # ����control������
    ctrlHandler, ctrlServer = ControlServiceHelper.create_server('localhost', 9090)

    # ����service������
    handler, server = CbmServiceHelper.create_server('localhost', 9100)

    # ע��service�����������Ʒ���ӿ�
    ctrlHandler.register(server)

    # ����һ���̸߳�service��������
    print '����service������(�˿�:9100)...'
    t1 = ServerHelper.run_rpc_server(server, runThread=True)

    # �������Ʒ�����,����shutdown��Ϣ(���������߳�)
    print '����control������(�˿�:9090)...'
    ServerHelper.run_rpc_server(ctrlServer, runThread=False)
    