# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'uifiles\gas_design_p2_3_dlg.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_gas_design_p2_3_dlg(object):
    def setupUi(self, gas_design_p2_3_dlg):
        gas_design_p2_3_dlg.setObjectName(_fromUtf8("gas_design_p2_3_dlg"))
        gas_design_p2_3_dlg.resize(444, 371)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8(":/images/cbm.ico")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        gas_design_p2_3_dlg.setWindowIcon(icon)
        self.dip_graph = QtGui.QPushButton(gas_design_p2_3_dlg)
        self.dip_graph.setGeometry(QtCore.QRect(320, 200, 101, 51))
        self.dip_graph.setObjectName(_fromUtf8("dip_graph"))
        self.save = QtGui.QPushButton(gas_design_p2_3_dlg)
        self.save.setGeometry(QtCore.QRect(320, 280, 101, 51))
        self.save.setObjectName(_fromUtf8("save"))
        self.head_graph = QtGui.QPushButton(gas_design_p2_3_dlg)
        self.head_graph.setGeometry(QtCore.QRect(320, 120, 101, 51))
        self.head_graph.setObjectName(_fromUtf8("head_graph"))
        self.groupBox = QtGui.QGroupBox(gas_design_p2_3_dlg)
        self.groupBox.setGeometry(QtCore.QRect(10, 10, 281, 51))
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.dip_angle = QtGui.QLineEdit(self.groupBox)
        self.dip_angle.setGeometry(QtCore.QRect(200, 20, 41, 20))
        self.dip_angle.setObjectName(_fromUtf8("dip_angle"))
        self.label_10 = QtGui.QLabel(self.groupBox)
        self.label_10.setGeometry(QtCore.QRect(140, 20, 51, 21))
        self.label_10.setObjectName(_fromUtf8("label_10"))
        self.thick = QtGui.QLineEdit(self.groupBox)
        self.thick.setGeometry(QtCore.QRect(70, 20, 41, 20))
        self.thick.setObjectName(_fromUtf8("thick"))
        self.label_7 = QtGui.QLabel(self.groupBox)
        self.label_7.setGeometry(QtCore.QRect(120, 20, 16, 16))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.label_9 = QtGui.QLabel(self.groupBox)
        self.label_9.setGeometry(QtCore.QRect(250, 20, 12, 14))
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.label_6 = QtGui.QLabel(self.groupBox)
        self.label_6.setGeometry(QtCore.QRect(10, 20, 51, 21))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.plane_graph = QtGui.QPushButton(gas_design_p2_3_dlg)
        self.plane_graph.setGeometry(QtCore.QRect(320, 40, 101, 51))
        self.plane_graph.setObjectName(_fromUtf8("plane_graph"))
        self.groupBox_2 = QtGui.QGroupBox(gas_design_p2_3_dlg)
        self.groupBox_2.setGeometry(QtCore.QRect(10, 80, 281, 81))
        self.groupBox_2.setObjectName(_fromUtf8("groupBox_2"))
        self.L2 = QtGui.QLineEdit(self.groupBox_2)
        self.L2.setGeometry(QtCore.QRect(210, 20, 41, 20))
        self.L2.setObjectName(_fromUtf8("L2"))
        self.label_11 = QtGui.QLabel(self.groupBox_2)
        self.label_11.setGeometry(QtCore.QRect(140, 20, 61, 21))
        self.label_11.setObjectName(_fromUtf8("label_11"))
        self.L1 = QtGui.QLineEdit(self.groupBox_2)
        self.L1.setGeometry(QtCore.QRect(70, 20, 41, 20))
        self.L1.setObjectName(_fromUtf8("L1"))
        self.label_13 = QtGui.QLabel(self.groupBox_2)
        self.label_13.setGeometry(QtCore.QRect(10, 20, 51, 21))
        self.label_13.setObjectName(_fromUtf8("label_13"))
        self.h = QtGui.QLineEdit(self.groupBox_2)
        self.h.setGeometry(QtCore.QRect(210, 50, 41, 20))
        self.h.setObjectName(_fromUtf8("h"))
        self.label_14 = QtGui.QLabel(self.groupBox_2)
        self.label_14.setGeometry(QtCore.QRect(10, 50, 51, 21))
        self.label_14.setObjectName(_fromUtf8("label_14"))
        self.label_12 = QtGui.QLabel(self.groupBox_2)
        self.label_12.setGeometry(QtCore.QRect(140, 50, 61, 21))
        self.label_12.setObjectName(_fromUtf8("label_12"))
        self.w = QtGui.QLineEdit(self.groupBox_2)
        self.w.setGeometry(QtCore.QRect(70, 50, 41, 20))
        self.w.setObjectName(_fromUtf8("w"))
        self.groupBox_3 = QtGui.QGroupBox(gas_design_p2_3_dlg)
        self.groupBox_3.setGeometry(QtCore.QRect(10, 180, 281, 81))
        self.groupBox_3.setObjectName(_fromUtf8("groupBox_3"))
        self.pore_gap = QtGui.QLineEdit(self.groupBox_3)
        self.pore_gap.setGeometry(QtCore.QRect(80, 50, 51, 20))
        self.pore_gap.setObjectName(_fromUtf8("pore_gap"))
        self.label_15 = QtGui.QLabel(self.groupBox_3)
        self.label_15.setGeometry(QtCore.QRect(20, 50, 61, 21))
        self.label_15.setObjectName(_fromUtf8("label_15"))
        self.Dp = QtGui.QLineEdit(self.groupBox_3)
        self.Dp.setGeometry(QtCore.QRect(80, 20, 51, 20))
        self.Dp.setObjectName(_fromUtf8("Dp"))
        self.label_17 = QtGui.QLabel(self.groupBox_3)
        self.label_17.setGeometry(QtCore.QRect(20, 20, 51, 21))
        self.label_17.setObjectName(_fromUtf8("label_17"))
        self.label_21 = QtGui.QLabel(self.groupBox_3)
        self.label_21.setGeometry(QtCore.QRect(140, 50, 81, 21))
        self.label_21.setObjectName(_fromUtf8("label_21"))
        self.pore_angle = QtGui.QLineEdit(self.groupBox_3)
        self.pore_angle.setGeometry(QtCore.QRect(220, 50, 51, 20))
        self.pore_angle.setObjectName(_fromUtf8("pore_angle"))
        self.label_22 = QtGui.QLabel(self.groupBox_3)
        self.label_22.setGeometry(QtCore.QRect(140, 20, 81, 21))
        self.label_22.setObjectName(_fromUtf8("label_22"))
        self.pore_stubble = QtGui.QLineEdit(self.groupBox_3)
        self.pore_stubble.setGeometry(QtCore.QRect(220, 20, 51, 20))
        self.pore_stubble.setObjectName(_fromUtf8("pore_stubble"))
        self.groupBox_4 = QtGui.QGroupBox(gas_design_p2_3_dlg)
        self.groupBox_4.setGeometry(QtCore.QRect(10, 280, 281, 81))
        self.groupBox_4.setObjectName(_fromUtf8("groupBox_4"))
        self.pore_type_4 = QtGui.QRadioButton(self.groupBox_4)
        self.pore_type_4.setGeometry(QtCore.QRect(160, 50, 89, 16))
        self.pore_type_4.setObjectName(_fromUtf8("pore_type_4"))
        self.pore_type_1 = QtGui.QRadioButton(self.groupBox_4)
        self.pore_type_1.setGeometry(QtCore.QRect(20, 20, 89, 16))
        self.pore_type_1.setChecked(True)
        self.pore_type_1.setObjectName(_fromUtf8("pore_type_1"))
        self.pore_type_3 = QtGui.QRadioButton(self.groupBox_4)
        self.pore_type_3.setGeometry(QtCore.QRect(20, 50, 89, 16))
        self.pore_type_3.setObjectName(_fromUtf8("pore_type_3"))
        self.pore_type_2 = QtGui.QRadioButton(self.groupBox_4)
        self.pore_type_2.setGeometry(QtCore.QRect(160, 20, 89, 16))
        self.pore_type_2.setObjectName(_fromUtf8("pore_type_2"))

        self.retranslateUi(gas_design_p2_3_dlg)
        QtCore.QMetaObject.connectSlotsByName(gas_design_p2_3_dlg)
        gas_design_p2_3_dlg.setTabOrder(self.thick, self.dip_angle)
        gas_design_p2_3_dlg.setTabOrder(self.dip_angle, self.L1)
        gas_design_p2_3_dlg.setTabOrder(self.L1, self.L2)
        gas_design_p2_3_dlg.setTabOrder(self.L2, self.w)
        gas_design_p2_3_dlg.setTabOrder(self.w, self.h)
        gas_design_p2_3_dlg.setTabOrder(self.h, self.Dp)
        gas_design_p2_3_dlg.setTabOrder(self.Dp, self.pore_stubble)
        gas_design_p2_3_dlg.setTabOrder(self.pore_stubble, self.pore_gap)
        gas_design_p2_3_dlg.setTabOrder(self.pore_gap, self.pore_angle)
        gas_design_p2_3_dlg.setTabOrder(self.pore_angle, self.pore_type_1)
        gas_design_p2_3_dlg.setTabOrder(self.pore_type_1, self.pore_type_2)
        gas_design_p2_3_dlg.setTabOrder(self.pore_type_2, self.pore_type_3)
        gas_design_p2_3_dlg.setTabOrder(self.pore_type_3, self.pore_type_4)
        gas_design_p2_3_dlg.setTabOrder(self.pore_type_4, self.plane_graph)
        gas_design_p2_3_dlg.setTabOrder(self.plane_graph, self.head_graph)
        gas_design_p2_3_dlg.setTabOrder(self.head_graph, self.dip_graph)
        gas_design_p2_3_dlg.setTabOrder(self.dip_graph, self.save)

    def retranslateUi(self, gas_design_p2_3_dlg):
        gas_design_p2_3_dlg.setWindowTitle(_translate("gas_design_p2_3_dlg", "顺层平行钻孔抽采工作面瓦斯", None))
        self.dip_graph.setText(_translate("gas_design_p2_3_dlg", "倾 向 剖 面 图", None))
        self.save.setText(_translate("gas_design_p2_3_dlg", "保 存", None))
        self.head_graph.setText(_translate("gas_design_p2_3_dlg", "走 向 剖 面 图", None))
        self.groupBox.setTitle(_translate("gas_design_p2_3_dlg", ">> 煤层参数", None))
        self.label_10.setText(_translate("gas_design_p2_3_dlg", "煤层倾角", None))
        self.label_7.setText(_translate("gas_design_p2_3_dlg", "<html><head/><body><p>m</p></body></html>", None))
        self.label_9.setText(_translate("gas_design_p2_3_dlg", "<html><head/><body><p>°</p></body></html>", None))
        self.label_6.setText(_translate("gas_design_p2_3_dlg", "煤层厚度", None))
        self.plane_graph.setText(_translate("gas_design_p2_3_dlg", "平 面 图", None))
        self.groupBox_2.setTitle(_translate("gas_design_p2_3_dlg", ">> 工作面参数", None))
        self.label_11.setText(_translate("gas_design_p2_3_dlg", "工作面长度", None))
        self.label_13.setText(_translate("gas_design_p2_3_dlg", "顺槽长度", None))
        self.label_14.setText(_translate("gas_design_p2_3_dlg", "巷道宽度", None))
        self.label_12.setText(_translate("gas_design_p2_3_dlg", "巷道高度", None))
        self.groupBox_3.setTitle(_translate("gas_design_p2_3_dlg", ">> 钻孔参数", None))
        self.label_15.setText(_translate("gas_design_p2_3_dlg", "钻孔间距", None))
        self.label_17.setText(_translate("gas_design_p2_3_dlg", "钻孔直径", None))
        self.label_21.setText(_translate("gas_design_p2_3_dlg", "斜交钻孔角度", None))
        self.label_22.setText(_translate("gas_design_p2_3_dlg", "钻孔压茬长度", None))
        self.groupBox_4.setTitle(_translate("gas_design_p2_3_dlg", ">> 钻孔类型", None))
        self.pore_type_4.setText(_translate("gas_design_p2_3_dlg", "交叉钻孔", None))
        self.pore_type_1.setText(_translate("gas_design_p2_3_dlg", "平行钻孔", None))
        self.pore_type_3.setText(_translate("gas_design_p2_3_dlg", "扇形钻孔", None))
        self.pore_type_2.setText(_translate("gas_design_p2_3_dlg", "斜交钻孔", None))

import usecad_rc
