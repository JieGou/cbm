# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'uifiles\sample_manage.ui'
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

class Ui_sample_manage(object):
    def setupUi(self, sample_manage):
        sample_manage.setObjectName(_fromUtf8("sample_manage"))
        sample_manage.setEnabled(True)
        sample_manage.resize(490, 566)
        sample_manage.setMaximumSize(QtCore.QSize(490, 566))
        sample_manage.setSizeIncrement(QtCore.QSize(490, 566))
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8(":/images/cbm.ico")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        sample_manage.setWindowIcon(icon)
        self.label = QtGui.QLabel(sample_manage)
        self.label.setGeometry(QtCore.QRect(10, 10, 111, 21))
        self.label.setObjectName(_fromUtf8("label"))
        self.regionComBox = QtGui.QComboBox(sample_manage)
        self.regionComBox.setGeometry(QtCore.QRect(130, 10, 141, 22))
        self.regionComBox.setObjectName(_fromUtf8("regionComBox"))
        self.save = QtGui.QPushButton(sample_manage)
        self.save.setGeometry(QtCore.QRect(400, 10, 75, 23))
        self.save.setObjectName(_fromUtf8("save"))
        self.groupBox = QtGui.QGroupBox(sample_manage)
        self.groupBox.setGeometry(QtCore.QRect(10, 60, 471, 101))
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.label_3 = QtGui.QLabel(self.groupBox)
        self.label_3.setGeometry(QtCore.QRect(10, 30, 71, 21))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.topo_geo = QtGui.QComboBox(self.groupBox)
        self.topo_geo.setGeometry(QtCore.QRect(90, 30, 101, 20))
        self.topo_geo.setObjectName(_fromUtf8("topo_geo"))
        self.topo_geo.addItem(_fromUtf8(""))
        self.topo_geo.addItem(_fromUtf8(""))
        self.topo_geo.addItem(_fromUtf8(""))
        self.label_4 = QtGui.QLabel(self.groupBox)
        self.label_4.setGeometry(QtCore.QRect(270, 30, 81, 21))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.hydr_geo = QtGui.QComboBox(self.groupBox)
        self.hydr_geo.setGeometry(QtCore.QRect(350, 30, 111, 20))
        self.hydr_geo.setObjectName(_fromUtf8("hydr_geo"))
        self.hydr_geo.addItem(_fromUtf8(""))
        self.hydr_geo.addItem(_fromUtf8(""))
        self.hydr_geo.addItem(_fromUtf8(""))
        self.hydr_geo.addItem(_fromUtf8(""))
        self.ground_cond = QtGui.QCheckBox(self.groupBox)
        self.ground_cond.setGeometry(QtCore.QRect(10, 70, 161, 16))
        self.ground_cond.setObjectName(_fromUtf8("ground_cond"))
        self.label_2 = QtGui.QLabel(sample_manage)
        self.label_2.setGeometry(QtCore.QRect(20, 40, 461, 16))
        font = QtGui.QFont()
        font.setPointSize(14)
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.groupBox_2 = QtGui.QGroupBox(sample_manage)
        self.groupBox_2.setGeometry(QtCore.QRect(10, 180, 471, 301))
        self.groupBox_2.setObjectName(_fromUtf8("groupBox_2"))
        self.label_5 = QtGui.QLabel(self.groupBox_2)
        self.label_5.setGeometry(QtCore.QRect(10, 30, 51, 21))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.coal = QtGui.QComboBox(self.groupBox_2)
        self.coal.setGeometry(QtCore.QRect(70, 30, 91, 22))
        self.coal.setObjectName(_fromUtf8("coal"))
        self.minable = QtGui.QCheckBox(self.groupBox_2)
        self.minable.setGeometry(QtCore.QRect(390, 30, 71, 21))
        self.minable.setObjectName(_fromUtf8("minable"))
        self.label_6 = QtGui.QLabel(self.groupBox_2)
        self.label_6.setGeometry(QtCore.QRect(240, 70, 51, 21))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.thick = QtGui.QLineEdit(self.groupBox_2)
        self.thick.setGeometry(QtCore.QRect(300, 70, 41, 20))
        self.thick.setObjectName(_fromUtf8("thick"))
        self.label_7 = QtGui.QLabel(self.groupBox_2)
        self.label_7.setGeometry(QtCore.QRect(350, 70, 16, 16))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.label_8 = QtGui.QLabel(self.groupBox_2)
        self.label_8.setGeometry(QtCore.QRect(370, 70, 21, 16))
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.f_value = QtGui.QLineEdit(self.groupBox_2)
        self.f_value.setGeometry(QtCore.QRect(400, 70, 61, 20))
        self.f_value.setObjectName(_fromUtf8("f_value"))
        self.dip_angle = QtGui.QLineEdit(self.groupBox_2)
        self.dip_angle.setGeometry(QtCore.QRect(70, 70, 41, 20))
        self.dip_angle.setObjectName(_fromUtf8("dip_angle"))
        self.label_9 = QtGui.QLabel(self.groupBox_2)
        self.label_9.setGeometry(QtCore.QRect(120, 70, 12, 14))
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.label_10 = QtGui.QLabel(self.groupBox_2)
        self.label_10.setGeometry(QtCore.QRect(10, 70, 51, 21))
        self.label_10.setObjectName(_fromUtf8("label_10"))
        self.hw = QtGui.QLineEdit(self.groupBox_2)
        self.hw.setGeometry(QtCore.QRect(170, 70, 41, 20))
        self.hw.setObjectName(_fromUtf8("hw"))
        self.label_11 = QtGui.QLabel(self.groupBox_2)
        self.label_11.setGeometry(QtCore.QRect(140, 70, 31, 21))
        self.label_11.setObjectName(_fromUtf8("label_11"))
        self.label_12 = QtGui.QLabel(self.groupBox_2)
        self.label_12.setGeometry(QtCore.QRect(220, 70, 12, 14))
        self.label_12.setObjectName(_fromUtf8("label_12"))
        self.rank = QtGui.QComboBox(self.groupBox_2)
        self.rank.setGeometry(QtCore.QRect(260, 30, 71, 22))
        self.rank.setObjectName(_fromUtf8("rank"))
        self.rank.addItem(_fromUtf8(""))
        self.rank.addItem(_fromUtf8(""))
        self.rank.addItem(_fromUtf8(""))
        self.label_13 = QtGui.QLabel(self.groupBox_2)
        self.label_13.setGeometry(QtCore.QRect(220, 30, 31, 21))
        self.label_13.setObjectName(_fromUtf8("label_13"))
        self.gas_penetration = QtGui.QLineEdit(self.groupBox_2)
        self.gas_penetration.setGeometry(QtCore.QRect(390, 110, 71, 20))
        self.gas_penetration.setObjectName(_fromUtf8("gas_penetration"))
        self.label_14 = QtGui.QLabel(self.groupBox_2)
        self.label_14.setGeometry(QtCore.QRect(340, 110, 41, 16))
        self.label_14.setObjectName(_fromUtf8("label_14"))
        self.pressure = QtGui.QLineEdit(self.groupBox_2)
        self.pressure.setGeometry(QtCore.QRect(70, 110, 61, 20))
        self.pressure.setObjectName(_fromUtf8("pressure"))
        self.gas_content = QtGui.QLineEdit(self.groupBox_2)
        self.gas_content.setGeometry(QtCore.QRect(240, 110, 51, 20))
        self.gas_content.setObjectName(_fromUtf8("gas_content"))
        self.label_16 = QtGui.QLabel(self.groupBox_2)
        self.label_16.setGeometry(QtCore.QRect(190, 110, 41, 21))
        self.label_16.setObjectName(_fromUtf8("label_16"))
        self.label_17 = QtGui.QLabel(self.groupBox_2)
        self.label_17.setGeometry(QtCore.QRect(10, 110, 51, 21))
        self.label_17.setObjectName(_fromUtf8("label_17"))
        self.label_18 = QtGui.QLabel(self.groupBox_2)
        self.label_18.setGeometry(QtCore.QRect(140, 110, 12, 14))
        self.label_18.setObjectName(_fromUtf8("label_18"))
        self.label_15 = QtGui.QLabel(self.groupBox_2)
        self.label_15.setGeometry(QtCore.QRect(300, 110, 12, 14))
        self.label_15.setObjectName(_fromUtf8("label_15"))
        self.res_abundance = QtGui.QComboBox(self.groupBox_2)
        self.res_abundance.setGeometry(QtCore.QRect(110, 150, 111, 22))
        self.res_abundance.setObjectName(_fromUtf8("res_abundance"))
        self.res_abundance.addItem(_fromUtf8(""))
        self.res_abundance.addItem(_fromUtf8(""))
        self.res_abundance.addItem(_fromUtf8(""))
        self.label_33 = QtGui.QLabel(self.groupBox_2)
        self.label_33.setGeometry(QtCore.QRect(10, 150, 91, 21))
        self.label_33.setObjectName(_fromUtf8("label_33"))
        self.const_complexity = QtGui.QComboBox(self.groupBox_2)
        self.const_complexity.setGeometry(QtCore.QRect(350, 150, 111, 22))
        self.const_complexity.setObjectName(_fromUtf8("const_complexity"))
        self.const_complexity.addItem(_fromUtf8(""))
        self.const_complexity.addItem(_fromUtf8(""))
        self.const_complexity.addItem(_fromUtf8(""))
        self.const_complexity.addItem(_fromUtf8(""))
        self.label_34 = QtGui.QLabel(self.groupBox_2)
        self.label_34.setGeometry(QtCore.QRect(270, 150, 71, 21))
        self.label_34.setObjectName(_fromUtf8("label_34"))
        self.mine_index = QtGui.QLineEdit(self.groupBox_2)
        self.mine_index.setGeometry(QtCore.QRect(80, 190, 51, 20))
        self.mine_index.setObjectName(_fromUtf8("mine_index"))
        self.label_35 = QtGui.QLabel(self.groupBox_2)
        self.label_35.setGeometry(QtCore.QRect(10, 190, 61, 21))
        self.label_35.setObjectName(_fromUtf8("label_35"))
        self.mine_index_cacl = QtGui.QPushButton(self.groupBox_2)
        self.mine_index_cacl.setGeometry(QtCore.QRect(140, 190, 61, 23))
        self.mine_index_cacl.setObjectName(_fromUtf8("mine_index_cacl"))
        self.label_36 = QtGui.QLabel(self.groupBox_2)
        self.label_36.setGeometry(QtCore.QRect(260, 190, 71, 21))
        self.label_36.setObjectName(_fromUtf8("label_36"))
        self.var_coeff_cacl = QtGui.QPushButton(self.groupBox_2)
        self.var_coeff_cacl.setGeometry(QtCore.QRect(400, 190, 61, 23))
        self.var_coeff_cacl.setObjectName(_fromUtf8("var_coeff_cacl"))
        self.var_coeff = QtGui.QLineEdit(self.groupBox_2)
        self.var_coeff.setGeometry(QtCore.QRect(340, 190, 51, 20))
        self.var_coeff.setObjectName(_fromUtf8("var_coeff"))
        self.label_37 = QtGui.QLabel(self.groupBox_2)
        self.label_37.setGeometry(QtCore.QRect(10, 230, 61, 21))
        self.label_37.setObjectName(_fromUtf8("label_37"))
        self.czh_cacl = QtGui.QPushButton(self.groupBox_2)
        self.czh_cacl.setGeometry(QtCore.QRect(140, 230, 61, 23))
        self.czh_cacl.setObjectName(_fromUtf8("czh_cacl"))
        self.stability_cacl = QtGui.QPushButton(self.groupBox_2)
        self.stability_cacl.setGeometry(QtCore.QRect(400, 230, 61, 23))
        self.stability_cacl.setObjectName(_fromUtf8("stability_cacl"))
        self.caving_zone_height = QtGui.QLineEdit(self.groupBox_2)
        self.caving_zone_height.setGeometry(QtCore.QRect(80, 230, 41, 20))
        self.caving_zone_height.setObjectName(_fromUtf8("caving_zone_height"))
        self.label_38 = QtGui.QLabel(self.groupBox_2)
        self.label_38.setGeometry(QtCore.QRect(230, 230, 61, 21))
        self.label_38.setObjectName(_fromUtf8("label_38"))
        self.stability = QtGui.QComboBox(self.groupBox_2)
        self.stability.setGeometry(QtCore.QRect(298, 230, 91, 22))
        self.stability.setObjectName(_fromUtf8("stability"))
        self.stability.addItem(_fromUtf8(""))
        self.stability.setItemText(0, _fromUtf8(""))
        self.stability.addItem(_fromUtf8(""))
        self.stability.addItem(_fromUtf8(""))
        self.stability.addItem(_fromUtf8(""))
        self.stability.addItem(_fromUtf8(""))
        self.label_39 = QtGui.QLabel(self.groupBox_2)
        self.label_39.setGeometry(QtCore.QRect(130, 230, 12, 14))
        self.label_39.setObjectName(_fromUtf8("label_39"))
        self.label_40 = QtGui.QLabel(self.groupBox_2)
        self.label_40.setGeometry(QtCore.QRect(10, 270, 101, 21))
        self.label_40.setObjectName(_fromUtf8("label_40"))
        self.influence_factor = QtGui.QLineEdit(self.groupBox_2)
        self.influence_factor.setEnabled(True)
        self.influence_factor.setGeometry(QtCore.QRect(340, 270, 51, 20))
        self.influence_factor.setObjectName(_fromUtf8("influence_factor"))
        self.influence_factor_cacl = QtGui.QPushButton(self.groupBox_2)
        self.influence_factor_cacl.setGeometry(QtCore.QRect(400, 270, 61, 23))
        self.influence_factor_cacl.setObjectName(_fromUtf8("influence_factor_cacl"))
        self.layer_gap = QtGui.QLineEdit(self.groupBox_2)
        self.layer_gap.setGeometry(QtCore.QRect(120, 270, 51, 20))
        self.layer_gap.setObjectName(_fromUtf8("layer_gap"))
        self.label_41 = QtGui.QLabel(self.groupBox_2)
        self.label_41.setGeometry(QtCore.QRect(260, 270, 71, 21))
        self.label_41.setObjectName(_fromUtf8("label_41"))
        self.label_42 = QtGui.QLabel(self.groupBox_2)
        self.label_42.setGeometry(QtCore.QRect(180, 270, 12, 14))
        self.label_42.setObjectName(_fromUtf8("label_42"))
        self.groupBox_3 = QtGui.QGroupBox(sample_manage)
        self.groupBox_3.setGeometry(QtCore.QRect(10, 490, 471, 71))
        self.groupBox_3.setObjectName(_fromUtf8("groupBox_3"))
        self.tech_mode = QtGui.QPushButton(self.groupBox_3)
        self.tech_mode.setGeometry(QtCore.QRect(40, 20, 131, 41))
        self.tech_mode.setObjectName(_fromUtf8("tech_mode"))
        self.technology = QtGui.QPushButton(self.groupBox_3)
        self.technology.setGeometry(QtCore.QRect(280, 20, 131, 41))
        self.technology.setObjectName(_fromUtf8("technology"))

        self.retranslateUi(sample_manage)
        QtCore.QMetaObject.connectSlotsByName(sample_manage)

    def retranslateUi(self, sample_manage):
        sample_manage.setWindowTitle(_translate("sample_manage", "示范矿区技术库管理", None))
        self.label.setText(_translate("sample_manage", "示范矿区技术库管理:", None))
        self.save.setText(_translate("sample_manage", "保存", None))
        self.groupBox.setTitle(_translate("sample_manage", ">> 基础参数", None))
        self.label_3.setText(_translate("sample_manage", "地形地貌特征", None))
        self.topo_geo.setItemText(0, _translate("sample_manage", "复杂", None))
        self.topo_geo.setItemText(1, _translate("sample_manage", "中等", None))
        self.topo_geo.setItemText(2, _translate("sample_manage", "简单", None))
        self.label_4.setText(_translate("sample_manage", "水文地质条件", None))
        self.hydr_geo.setItemText(0, _translate("sample_manage", "复杂", None))
        self.hydr_geo.setItemText(1, _translate("sample_manage", "极复杂", None))
        self.hydr_geo.setItemText(2, _translate("sample_manage", "中等", None))
        self.hydr_geo.setItemText(3, _translate("sample_manage", "简单", None))
        self.ground_cond.setText(_translate("sample_manage", "是否具备地面井开发条件", None))
        self.label_2.setText(_translate("sample_manage", "------------------------------------------------------------------------------------------", None))
        self.groupBox_2.setTitle(_translate("sample_manage", ">> 煤层参数", None))
        self.label_5.setText(_translate("sample_manage", "煤层列表", None))
        self.minable.setText(_translate("sample_manage", "可采煤层", None))
        self.label_6.setText(_translate("sample_manage", "煤层厚度", None))
        self.label_7.setText(_translate("sample_manage", "<html><head/><body><p>m</p></body></html>", None))
        self.label_8.setText(_translate("sample_manage", "<html><head/><body><p>f值</p></body></html>", None))
        self.label_9.setText(_translate("sample_manage", "<html><head/><body><p>°</p></body></html>", None))
        self.label_10.setText(_translate("sample_manage", "煤层倾角", None))
        self.label_11.setText(_translate("sample_manage", "采高", None))
        self.label_12.setText(_translate("sample_manage", "<html><head/><body><p>m</p></body></html>", None))
        self.rank.setItemText(0, _translate("sample_manage", "烟煤", None))
        self.rank.setItemText(1, _translate("sample_manage", "褐煤", None))
        self.rank.setItemText(2, _translate("sample_manage", "无烟煤", None))
        self.label_13.setText(_translate("sample_manage", "煤阶", None))
        self.label_14.setText(_translate("sample_manage", "<html><head/><body><p>渗透率</p></body></html>", None))
        self.label_16.setText(_translate("sample_manage", "气含量", None))
        self.label_17.setText(_translate("sample_manage", "储层压力", None))
        self.label_18.setText(_translate("sample_manage", "<html><head/><body><p>Pa</p></body></html>", None))
        self.label_15.setText(_translate("sample_manage", "<html><head/><body><p>%</p></body></html>", None))
        self.res_abundance.setItemText(0, _translate("sample_manage", "中(0.5~3.0)", None))
        self.res_abundance.setItemText(1, _translate("sample_manage", "高(>3.0)", None))
        self.res_abundance.setItemText(2, _translate("sample_manage", "低(<3.0)", None))
        self.label_33.setText(_translate("sample_manage", "煤层气储量丰度", None))
        self.const_complexity.setItemText(0, _translate("sample_manage", "复杂", None))
        self.const_complexity.setItemText(1, _translate("sample_manage", "极复杂", None))
        self.const_complexity.setItemText(2, _translate("sample_manage", "中等", None))
        self.const_complexity.setItemText(3, _translate("sample_manage", "简单", None))
        self.label_34.setText(_translate("sample_manage", "构造复杂程度", None))
        self.label_35.setText(_translate("sample_manage", "可采性指数", None))
        self.mine_index_cacl.setText(_translate("sample_manage", "计算", None))
        self.label_36.setText(_translate("sample_manage", "煤厚变异系数", None))
        self.var_coeff_cacl.setText(_translate("sample_manage", "计算", None))
        self.label_37.setText(_translate("sample_manage", "冒落带高度", None))
        self.czh_cacl.setText(_translate("sample_manage", "计算", None))
        self.stability_cacl.setText(_translate("sample_manage", "计算", None))
        self.label_38.setText(_translate("sample_manage", "煤层稳定性", None))
        self.stability.setItemText(1, _translate("sample_manage", "稳定煤层", None))
        self.stability.setItemText(2, _translate("sample_manage", "较稳定煤层", None))
        self.stability.setItemText(3, _translate("sample_manage", "不稳定煤层", None))
        self.stability.setItemText(4, _translate("sample_manage", "极不稳定煤层", None))
        self.label_39.setText(_translate("sample_manage", "<html><head/><body><p>m</p></body></html>", None))
        self.label_40.setText(_translate("sample_manage", "与上覆煤层层间距", None))
        self.influence_factor_cacl.setText(_translate("sample_manage", "计算", None))
        self.label_41.setText(_translate("sample_manage", "采动影响倍数", None))
        self.label_42.setText(_translate("sample_manage", "<html><head/><body><p>m</p></body></html>", None))
        self.groupBox_3.setTitle(_translate("sample_manage", ">> 抽采技术参数", None))
        self.tech_mode.setText(_translate("sample_manage", "抽采技术模式参数", None))
        self.technology.setText(_translate("sample_manage", "推荐抽采技术参数", None))

import usecad_rc
