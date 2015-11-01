#-*- coding:utf-8 -*-
#!/usr/bin/env python

import sys
import ServerHelper
from cbm import ControlService

# �رշ�������˼·:
# http://grokbase.com/t/thrift/user/11541vwzj4/stop-the-thrift-server

#���������ƽӿڴ�����
class ControlServiceHandler:
    def __init__(self):
        self.server_list = []
    def register(self, server):
        self.server_list.append(server)
    def shutdown(self):
        print '����������:',len(self.server_list)
        for server in self.server_list:
            print '�رշ�����(��δʵ��,ֱ��ǿ���˳�����)...'
            # python��thrift���û��ʵ��stop()����
            # ���,ֱ��ǿ���˳�(sys.eixt())
            # server.stop()
            sys.exit()

def create_server(host, port):
     # ������������Ϣ����ӿ�
    ctrlHandler = ControlServiceHandler()
    # �������Ʒ�����
    ctrlServer = ServerHelper.make_rpc_server(ControlService.Processor(ctrlHandler), host = host, port=port)
    # ע������������Ʒ���ӿ�
    ctrlHandler.register(ctrlServer)
    return ctrlHandler, ctrlServer