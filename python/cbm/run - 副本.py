#-*- coding:utf-8 -*-
#!flask/bin/python

import subprocess

def main():
	global rpc_process
	try:
		# ����һ����������rpc������
		rpc_process = subprocess.Popen(["python","rpc_server.py"])
		if rpc_process is None:
			raise
		else:
			print("����rpc��̨����")
			# ����flask������
			from app import app
			app.run(debug=False)
	except Exception, e:
		print e
	finally:
		# ����ӽ���״̬
		if rpc_process.poll() is not None:
			# �ر�rpc������
			from rpc import CtrlClientHelper
			CtrlClientHelper.QuitServer()

			# ɱ��rpc����	
			rpc_process.kill()

if __name__ == '__main__':
	main()