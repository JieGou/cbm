#coding:utf-8

from BaseDialog import *
from uipy.ui_pore_flow_K_dlg import *

class PoreFlowKDlg(BaseDialog):
	def __init__(self,parent=None):
		super(PoreFlowKDlg, self).__init__(parent)
		self.ui = Ui_pore_flow_K_dlg()
		self.ui.setupUi(self)
		self.initUi(self.ui) # ����ui
		self.setTitle(u"ʵ�ʿװ���������ϵ������")
		self.setFixedSize(self.width(), self.height())
		self.ui.save.clicked.connect(self.onSave)

	def onSave(self):
		#���������
		self.accept()
