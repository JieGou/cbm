#-*- coding:utf-8 -*-
#!/usr/bin/env python

from cbm.ttypes import *
from cbm import CbmService
from ctrl import ControlService
from RpcClient import *

import CbmUtil
import SQLClientHelper
import CbmClientHelper

'''
����SQLClientHelperģ��
'''
def main():
    print SQLClientHelper.GetMineBaseNames()