# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'uifiles\gas_design_p1_2_dlg.ui'
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

class Ui_gas_design_p1_2_dlg(object):
    def setupUi(self, gas_design_p1_2_dlg):
        gas_design_p1_2_dlg.setObjectName(_fromUtf8("gas_design_p1_2_dlg"))
        gas_design_p1_2_dlg.resize(601, 511)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8(":/images/cbm.ico")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        gas_design_p1_2_dlg.setWindowIcon(icon)
        self.widget_main = QtGui.QWidget(gas_design_p1_2_dlg)
        self.widget_main.setGeometry(QtCore.QRect(0, 30, 601, 481))
        self.widget_main.setObjectName(_fromUtf8("widget_main"))
        self.groupBox = QtGui.QGroupBox(self.widget_main)
        self.groupBox.setGeometry(QtCore.QRect(20, 20, 411, 71))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.groupBox.setFont(font)
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.dip_angle = QtGui.QLineEdit(self.groupBox)
        self.dip_angle.setGeometry(QtCore.QRect(290, 30, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.dip_angle.setFont(font)
        self.dip_angle.setObjectName(_fromUtf8("dip_angle"))
        self.label_10 = QtGui.QLabel(self.groupBox)
        self.label_10.setGeometry(QtCore.QRect(210, 30, 71, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_10.setFont(font)
        self.label_10.setObjectName(_fromUtf8("label_10"))
        self.thick = QtGui.QLineEdit(self.groupBox)
        self.thick.setGeometry(QtCore.QRect(100, 30, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.thick.setFont(font)
        self.thick.setObjectName(_fromUtf8("thick"))
        self.label_7 = QtGui.QLabel(self.groupBox)
        self.label_7.setGeometry(QtCore.QRect(170, 30, 31, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_7.setFont(font)
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.label_9 = QtGui.QLabel(self.groupBox)
        self.label_9.setGeometry(QtCore.QRect(360, 30, 41, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_9.setFont(font)
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.label_6 = QtGui.QLabel(self.groupBox)
        self.label_6.setGeometry(QtCore.QRect(20, 30, 71, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_6.setFont(font)
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.groupBox_3 = QtGui.QGroupBox(self.widget_main)
        self.groupBox_3.setGeometry(QtCore.QRect(20, 330, 411, 131))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.groupBox_3.setFont(font)
        self.groupBox_3.setObjectName(_fromUtf8("groupBox_3"))
        self.gbp = QtGui.QLineEdit(self.groupBox_3)
        self.gbp.setGeometry(QtCore.QRect(310, 30, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.gbp.setFont(font)
        self.gbp.setObjectName(_fromUtf8("gbp"))
        self.label_15 = QtGui.QLabel(self.groupBox_3)
        self.label_15.setGeometry(QtCore.QRect(210, 30, 91, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_15.setFont(font)
        self.label_15.setObjectName(_fromUtf8("label_15"))
        self.dp = QtGui.QLineEdit(self.groupBox_3)
        self.dp.setGeometry(QtCore.QRect(100, 30, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.dp.setFont(font)
        self.dp.setObjectName(_fromUtf8("dp"))
        self.label_17 = QtGui.QLabel(self.groupBox_3)
        self.label_17.setGeometry(QtCore.QRect(20, 30, 81, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_17.setFont(font)
        self.label_17.setObjectName(_fromUtf8("label_17"))
        self.label_21 = QtGui.QLabel(self.groupBox_3)
        self.label_21.setGeometry(QtCore.QRect(20, 90, 111, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_21.setFont(font)
        self.label_21.setObjectName(_fromUtf8("label_21"))
        self.l_stripe = QtGui.QLineEdit(self.groupBox_3)
        self.l_stripe.setGeometry(QtCore.QRect(150, 90, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.l_stripe.setFont(font)
        self.l_stripe.setObjectName(_fromUtf8("l_stripe"))
        self.label_22 = QtGui.QLabel(self.groupBox_3)
        self.label_22.setGeometry(QtCore.QRect(20, 60, 101, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_22.setFont(font)
        self.label_22.setObjectName(_fromUtf8("label_22"))
        self.leading_dist = QtGui.QLineEdit(self.groupBox_3)
        self.leading_dist.setGeometry(QtCore.QRect(120, 60, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.leading_dist.setFont(font)
        self.leading_dist.setObjectName(_fromUtf8("leading_dist"))
        self.label_4 = QtGui.QLabel(self.groupBox_3)
        self.label_4.setGeometry(QtCore.QRect(170, 30, 31, 25))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.label_5 = QtGui.QLabel(self.groupBox_3)
        self.label_5.setGeometry(QtCore.QRect(380, 30, 31, 25))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_8 = QtGui.QLabel(self.groupBox_3)
        self.label_8.setGeometry(QtCore.QRect(190, 60, 31, 25))
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.label_11 = QtGui.QLabel(self.groupBox_3)
        self.label_11.setGeometry(QtCore.QRect(220, 90, 31, 25))
        self.label_11.setObjectName(_fromUtf8("label_11"))
        self.groupBox_4 = QtGui.QGroupBox(self.widget_main)
        self.groupBox_4.setGeometry(QtCore.QRect(20, 210, 411, 101))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.groupBox_4.setFont(font)
        self.groupBox_4.setObjectName(_fromUtf8("groupBox_4"))
        self.bottom = QtGui.QLineEdit(self.groupBox_4)
        self.bottom.setGeometry(QtCore.QRect(210, 30, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.bottom.setFont(font)
        self.bottom.setObjectName(_fromUtf8("bottom"))
        self.label_16 = QtGui.QLabel(self.groupBox_4)
        self.label_16.setGeometry(QtCore.QRect(160, 30, 41, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_16.setFont(font)
        self.label_16.setObjectName(_fromUtf8("label_16"))
        self.top = QtGui.QLineEdit(self.groupBox_4)
        self.top.setGeometry(QtCore.QRect(70, 30, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.top.setFont(font)
        self.top.setObjectName(_fromUtf8("top"))
        self.label_18 = QtGui.QLabel(self.groupBox_4)
        self.label_18.setGeometry(QtCore.QRect(20, 30, 51, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_18.setFont(font)
        self.label_18.setObjectName(_fromUtf8("label_18"))
        self.right = QtGui.QLineEdit(self.groupBox_4)
        self.right.setGeometry(QtCore.QRect(210, 60, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.right.setFont(font)
        self.right.setObjectName(_fromUtf8("right"))
        self.label_19 = QtGui.QLabel(self.groupBox_4)
        self.label_19.setGeometry(QtCore.QRect(20, 60, 51, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_19.setFont(font)
        self.label_19.setObjectName(_fromUtf8("label_19"))
        self.label_20 = QtGui.QLabel(self.groupBox_4)
        self.label_20.setGeometry(QtCore.QRect(160, 60, 41, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_20.setFont(font)
        self.label_20.setObjectName(_fromUtf8("label_20"))
        self.left = QtGui.QLineEdit(self.groupBox_4)
        self.left.setGeometry(QtCore.QRect(70, 60, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.left.setFont(font)
        self.left.setObjectName(_fromUtf8("left"))
        self.help = QtGui.QPushButton(self.groupBox_4)
        self.help.setGeometry(QtCore.QRect(300, 30, 81, 51))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.help.setFont(font)
        self.help.setObjectName(_fromUtf8("help"))
        self.save = QtGui.QPushButton(self.widget_main)
        self.save.setGeometry(QtCore.QRect(450, 34, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.save.setFont(font)
        self.save.setObjectName(_fromUtf8("save"))
        self.plane_graph = QtGui.QPushButton(self.widget_main)
        self.plane_graph.setGeometry(QtCore.QRect(450, 117, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.plane_graph.setFont(font)
        self.plane_graph.setObjectName(_fromUtf8("plane_graph"))
        self.dip_graph = QtGui.QPushButton(self.widget_main)
        self.dip_graph.setGeometry(QtCore.QRect(450, 300, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.dip_graph.setFont(font)
        self.dip_graph.setObjectName(_fromUtf8("dip_graph"))
        self.groupBox_2 = QtGui.QGroupBox(self.widget_main)
        self.groupBox_2.setGeometry(QtCore.QRect(20, 100, 411, 101))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.groupBox_2.setFont(font)
        self.groupBox_2.setObjectName(_fromUtf8("groupBox_2"))
        self.lm = QtGui.QLineEdit(self.groupBox_2)
        self.lm.setGeometry(QtCore.QRect(100, 30, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.lm.setFont(font)
        self.lm.setObjectName(_fromUtf8("lm"))
        self.label_13 = QtGui.QLabel(self.groupBox_2)
        self.label_13.setGeometry(QtCore.QRect(20, 30, 71, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_13.setFont(font)
        self.label_13.setObjectName(_fromUtf8("label_13"))
        self.h = QtGui.QLineEdit(self.groupBox_2)
        self.h.setGeometry(QtCore.QRect(290, 60, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.h.setFont(font)
        self.h.setObjectName(_fromUtf8("h"))
        self.label_14 = QtGui.QLabel(self.groupBox_2)
        self.label_14.setGeometry(QtCore.QRect(20, 60, 81, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_14.setFont(font)
        self.label_14.setObjectName(_fromUtf8("label_14"))
        self.label_12 = QtGui.QLabel(self.groupBox_2)
        self.label_12.setGeometry(QtCore.QRect(210, 60, 71, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label_12.setFont(font)
        self.label_12.setObjectName(_fromUtf8("label_12"))
        self.w = QtGui.QLineEdit(self.groupBox_2)
        self.w.setGeometry(QtCore.QRect(100, 60, 61, 25))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.w.setFont(font)
        self.w.setObjectName(_fromUtf8("w"))
        self.label = QtGui.QLabel(self.groupBox_2)
        self.label.setGeometry(QtCore.QRect(170, 30, 54, 25))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(self.groupBox_2)
        self.label_2.setGeometry(QtCore.QRect(170, 60, 54, 25))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.label_3 = QtGui.QLabel(self.groupBox_2)
        self.label_3.setGeometry(QtCore.QRect(360, 60, 41, 25))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.head_graph = QtGui.QPushButton(self.widget_main)
        self.head_graph.setGeometry(QtCore.QRect(450, 210, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.head_graph.setFont(font)
        self.head_graph.setObjectName(_fromUtf8("head_graph"))
        self.creat_report = QtGui.QPushButton(self.widget_main)
        self.creat_report.setGeometry(QtCore.QRect(450, 390, 130, 51))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.creat_report.setFont(font)
        self.creat_report.setObjectName(_fromUtf8("creat_report"))
        self.widget_title = QtGui.QWidget(gas_design_p1_2_dlg)
        self.widget_title.setGeometry(QtCore.QRect(0, 0, 601, 31))
        self.widget_title.setObjectName(_fromUtf8("widget_title"))
        self.lab_Ico = QtGui.QLabel(self.widget_title)
        self.lab_Ico.setGeometry(QtCore.QRect(0, 0, 31, 31))
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lab_Ico.sizePolicy().hasHeightForWidth())
        self.lab_Ico.setSizePolicy(sizePolicy)
        self.lab_Ico.setMinimumSize(QtCore.QSize(30, 0))
        self.lab_Ico.setAlignment(QtCore.Qt.AlignCenter)
        self.lab_Ico.setObjectName(_fromUtf8("lab_Ico"))
        self.lab_Title = QtGui.QLabel(self.widget_title)
        self.lab_Title.setGeometry(QtCore.QRect(40, 0, 511, 31))
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lab_Title.sizePolicy().hasHeightForWidth())
        self.lab_Title.setSizePolicy(sizePolicy)
        self.lab_Title.setStyleSheet(_fromUtf8("font: 10pt \"微软雅黑\";"))
        self.lab_Title.setText(_fromUtf8(""))
        self.lab_Title.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.lab_Title.setObjectName(_fromUtf8("lab_Title"))
        self.btnMenu_Close = QtGui.QPushButton(self.widget_title)
        self.btnMenu_Close.setGeometry(QtCore.QRect(560, 0, 41, 31))
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btnMenu_Close.sizePolicy().hasHeightForWidth())
        self.btnMenu_Close.setSizePolicy(sizePolicy)
        self.btnMenu_Close.setMinimumSize(QtCore.QSize(40, 0))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.btnMenu_Close.setFont(font)
        self.btnMenu_Close.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.btnMenu_Close.setFocusPolicy(QtCore.Qt.NoFocus)
        self.btnMenu_Close.setText(_fromUtf8(""))
        self.btnMenu_Close.setIconSize(QtCore.QSize(32, 32))
        self.btnMenu_Close.setFlat(True)
        self.btnMenu_Close.setObjectName(_fromUtf8("btnMenu_Close"))

        self.retranslateUi(gas_design_p1_2_dlg)
        QtCore.QMetaObject.connectSlotsByName(gas_design_p1_2_dlg)
        gas_design_p1_2_dlg.setTabOrder(self.thick, self.dip_angle)
        gas_design_p1_2_dlg.setTabOrder(self.dip_angle, self.lm)
        gas_design_p1_2_dlg.setTabOrder(self.lm, self.w)
        gas_design_p1_2_dlg.setTabOrder(self.w, self.h)
        gas_design_p1_2_dlg.setTabOrder(self.h, self.top)
        gas_design_p1_2_dlg.setTabOrder(self.top, self.bottom)
        gas_design_p1_2_dlg.setTabOrder(self.bottom, self.left)
        gas_design_p1_2_dlg.setTabOrder(self.left, self.right)
        gas_design_p1_2_dlg.setTabOrder(self.right, self.help)
        gas_design_p1_2_dlg.setTabOrder(self.help, self.dp)
        gas_design_p1_2_dlg.setTabOrder(self.dp, self.gbp)
        gas_design_p1_2_dlg.setTabOrder(self.gbp, self.leading_dist)
        gas_design_p1_2_dlg.setTabOrder(self.leading_dist, self.l_stripe)
        gas_design_p1_2_dlg.setTabOrder(self.l_stripe, self.plane_graph)
        gas_design_p1_2_dlg.setTabOrder(self.plane_graph, self.head_graph)
        gas_design_p1_2_dlg.setTabOrder(self.head_graph, self.dip_graph)
        gas_design_p1_2_dlg.setTabOrder(self.dip_graph, self.save)

    def retranslateUi(self, gas_design_p1_2_dlg):
        gas_design_p1_2_dlg.setWindowTitle(_translate("gas_design_p1_2_dlg", "顺层钻孔条带掩护巷道掘进抽采法", None))
        self.groupBox.setTitle(_translate("gas_design_p1_2_dlg", "煤层参数", None))
        self.label_10.setText(_translate("gas_design_p1_2_dlg", "煤层倾角", None))
        self.label_7.setText(_translate("gas_design_p1_2_dlg", "<html><head/><body><p>(m)</p></body></html>", None))
        self.label_9.setText(_translate("gas_design_p1_2_dlg", "<html><head/><body><p>(°)</p></body></html>", None))
        self.label_6.setText(_translate("gas_design_p1_2_dlg", "煤层厚度", None))
        self.groupBox_3.setTitle(_translate("gas_design_p1_2_dlg", "钻孔参数", None))
        self.label_15.setText(_translate("gas_design_p1_2_dlg", "钻孔底间距", None))
        self.label_17.setText(_translate("gas_design_p1_2_dlg", "钻孔直径", None))
        self.label_21.setText(_translate("gas_design_p1_2_dlg", "钻孔控制的条带长度", None))
        self.label_22.setText(_translate("gas_design_p1_2_dlg", "钻孔超前距", None))
        self.label_4.setText(_translate("gas_design_p1_2_dlg", "(m)", None))
        self.label_5.setText(_translate("gas_design_p1_2_dlg", "(m)", None))
        self.label_8.setText(_translate("gas_design_p1_2_dlg", "(m)", None))
        self.label_11.setText(_translate("gas_design_p1_2_dlg", "(m)", None))
        self.groupBox_4.setTitle(_translate("gas_design_p1_2_dlg", "回采巷道控制范围", None))
        self.label_16.setText(_translate("gas_design_p1_2_dlg", "下帮", None))
        self.label_18.setText(_translate("gas_design_p1_2_dlg", "上帮", None))
        self.label_19.setText(_translate("gas_design_p1_2_dlg", "左帮", None))
        self.label_20.setText(_translate("gas_design_p1_2_dlg", "右帮", None))
        self.help.setText(_translate("gas_design_p1_2_dlg", "参考取值", None))
        self.save.setText(_translate("gas_design_p1_2_dlg", "保 存", None))
        self.plane_graph.setText(_translate("gas_design_p1_2_dlg", "平 面 图", None))
        self.dip_graph.setText(_translate("gas_design_p1_2_dlg", "倾 向 剖 面 图", None))
        self.groupBox_2.setTitle(_translate("gas_design_p1_2_dlg", "掘进巷道参数", None))
        self.label_13.setText(_translate("gas_design_p1_2_dlg", "掘进长度", None))
        self.label_14.setText(_translate("gas_design_p1_2_dlg", "巷道宽度", None))
        self.label_12.setText(_translate("gas_design_p1_2_dlg", "巷道高度", None))
        self.label.setText(_translate("gas_design_p1_2_dlg", "(m)", None))
        self.label_2.setText(_translate("gas_design_p1_2_dlg", "(m)", None))
        self.label_3.setText(_translate("gas_design_p1_2_dlg", "(m)", None))
        self.head_graph.setText(_translate("gas_design_p1_2_dlg", "走 向 剖 面 图", None))
        self.creat_report.setText(_translate("gas_design_p1_2_dlg", "生成钻孔及报单", None))
        self.lab_Ico.setText(_translate("gas_design_p1_2_dlg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'SimSun\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", None))

import usecad_rc
