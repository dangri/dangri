# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'essai.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 800)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.frame = QtWidgets.QFrame(self.centralwidget)
        self.frame.setGeometry(QtCore.QRect(1, 1, 399, 799))
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.verticalLayoutWidget = QtWidgets.QWidget(self.frame)
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(0, 0, 401, 65))
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.groupBox_2 = QtWidgets.QGroupBox(self.verticalLayoutWidget)
        self.groupBox_2.setTitle("")
        self.groupBox_2.setObjectName("groupBox_2")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.groupBox_2)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_3 = QtWidgets.QLabel(self.groupBox_2)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_3.addWidget(self.label_3)
        self.LHeure = QtWidgets.QLabel(self.groupBox_2)
        self.LHeure.setObjectName("LHeure")
        self.horizontalLayout_3.addWidget(self.LHeure)
        self.PBSave = QtWidgets.QPushButton(self.groupBox_2)
        self.PBSave.setObjectName("PBSave")
        self.horizontalLayout_3.addWidget(self.PBSave)
        self.verticalLayout.addWidget(self.groupBox_2)
        self.tableWidget = QtWidgets.QTableWidget(self.frame)
        self.tableWidget.setGeometry(QtCore.QRect(0, 60, 391, 551))
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setRowCount(0)
        self.frame_2 = QtWidgets.QFrame(self.centralwidget)
        self.frame_2.setGeometry(QtCore.QRect(400, 70, 398, 799))
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.frame_3 = QtWidgets.QFrame(self.frame_2)
        self.frame_3.setGeometry(QtCore.QRect(0, 0, 391, 250))
        self.frame_3.setFrameShape(QtWidgets.QFrame.Box)
        self.frame_3.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_3.setLineWidth(2)
        self.frame_3.setObjectName("frame_3")
        self.gridLayoutWidget = QtWidgets.QWidget(self.frame_3)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(10, 10, 406, 221))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.groupBox_3 = QtWidgets.QGroupBox(self.gridLayoutWidget)
        self.groupBox_3.setMaximumSize(QtCore.QSize(240, 16777215))
        self.groupBox_3.setTitle("")
        self.groupBox_3.setObjectName("groupBox_3")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout(self.groupBox_3)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_2 = QtWidgets.QLabel(self.groupBox_3)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_4.addWidget(self.label_2)
        self.comboBox_3 = QtWidgets.QComboBox(self.groupBox_3)
        self.comboBox_3.setObjectName("comboBox_3")
        self.horizontalLayout_4.addWidget(self.comboBox_3)
        self.LH = QtWidgets.QLabel(self.groupBox_3)
        self.LH.setMaximumSize(QtCore.QSize(20, 16777215))
        self.LH.setObjectName("LH")
        self.horizontalLayout_4.addWidget(self.LH)
        self.comboBox = QtWidgets.QComboBox(self.groupBox_3)
        self.comboBox.setMaximumSize(QtCore.QSize(50, 16777215))
        self.comboBox.setObjectName("comboBox")
        self.horizontalLayout_4.addWidget(self.comboBox)
        self.comboBox_2 = QtWidgets.QComboBox(self.groupBox_3)
        self.comboBox_2.setMaximumSize(QtCore.QSize(50, 16777215))
        self.comboBox_2.setObjectName("comboBox_2")
        self.horizontalLayout_4.addWidget(self.comboBox_2)
        self.LH_2 = QtWidgets.QLabel(self.groupBox_3)
        self.LH_2.setMaximumSize(QtCore.QSize(20, 16777215))
        self.LH_2.setObjectName("LH_2")
        self.horizontalLayout_4.addWidget(self.LH_2)
        self.gridLayout.addWidget(self.groupBox_3, 1, 1, 1, 2)
        self.groupBox_4 = QtWidgets.QGroupBox(self.gridLayoutWidget)
        self.groupBox_4.setTitle("")
        self.groupBox_4.setObjectName("groupBox_4")
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout(self.groupBox_4)
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.PBChaOn = QtWidgets.QPushButton(self.groupBox_4)
        self.PBChaOn.setMaximumSize(QtCore.QSize(60, 30))
        self.PBChaOn.setObjectName("PBChaOn")
        self.horizontalLayout_5.addWidget(self.PBChaOn)
        self.PBChaOff = QtWidgets.QPushButton(self.groupBox_4)
        self.PBChaOff.setMaximumSize(QtCore.QSize(60, 30))
        self.PBChaOff.setObjectName("PBChaOff")
        self.horizontalLayout_5.addWidget(self.PBChaOff)
        self.gridLayout.addWidget(self.groupBox_4, 0, 1, 1, 1)
        self.LHeureDpt = QtWidgets.QLabel(self.gridLayoutWidget)
        self.LHeureDpt.setObjectName("LHeureDpt")
        self.gridLayout.addWidget(self.LHeureDpt, 1, 0, 1, 1)
        self.LChargt = QtWidgets.QLabel(self.gridLayoutWidget)
        self.LChargt.setObjectName("LChargt")
        self.gridLayout.addWidget(self.LChargt, 0, 0, 1, 1)
        self.lineEdit = QtWidgets.QLineEdit(self.gridLayoutWidget)
        self.lineEdit.setMaximumSize(QtCore.QSize(230, 16777215))
        self.lineEdit.setObjectName("lineEdit")
        self.gridLayout.addWidget(self.lineEdit, 3, 1, 1, 1)
        self.LChaMaxPosVal = QtWidgets.QLabel(self.gridLayoutWidget)
        self.LChaMaxPosVal.setObjectName("LChaMaxPosVal")
        self.gridLayout.addWidget(self.LChaMaxPosVal, 2, 1, 1, 1, QtCore.Qt.AlignHCenter)
        self.label = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 3, 0, 1, 1)
        self.label_5 = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_5.setMaximumSize(QtCore.QSize(120, 30))
        self.label_5.setObjectName("label_5")
        self.gridLayout.addWidget(self.label_5, 2, 0, 1, 1)
        self.frame_4 = QtWidgets.QFrame(self.frame_2)
        self.frame_4.setGeometry(QtCore.QRect(10, 260, 381, 281))
        self.frame_4.setStyleSheet("border-color: rgb(0, 0, 0);")
        self.frame_4.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_4.setObjectName("frame_4")
        self.verticalLayoutWidget_3 = QtWidgets.QWidget(self.frame_4)
        self.verticalLayoutWidget_3.setGeometry(QtCore.QRect(0, 0, 381, 281))
        self.verticalLayoutWidget_3.setObjectName("verticalLayoutWidget_3")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.verticalLayoutWidget_3)
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.label_6 = QtWidgets.QLabel(self.verticalLayoutWidget_3)
        self.label_6.setObjectName("label_6")
        self.verticalLayout_3.addWidget(self.label_6)
        self.tableWidget_2 = QtWidgets.QTableWidget(self.verticalLayoutWidget_3)
        self.tableWidget_2.setObjectName("tableWidget_2")
        self.tableWidget_2.setColumnCount(0)
        self.tableWidget_2.setRowCount(0)
        self.verticalLayout_3.addWidget(self.tableWidget_2)
        self.frame_5 = QtWidgets.QFrame(self.frame_2)
        self.frame_5.setGeometry(QtCore.QRect(0, 0, 404, 43))
        self.frame_5.setFrameShape(QtWidgets.QFrame.Box)
        self.frame_5.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_5.setLineWidth(3)
        self.frame_5.setObjectName("frame_5")
        self.formLayoutWidget = QtWidgets.QWidget(self.frame_5)
        self.formLayoutWidget.setGeometry(QtCore.QRect(0, 10, 381, 24))
        self.formLayoutWidget.setObjectName("formLayoutWidget")
        self.formLayout = QtWidgets.QFormLayout(self.formLayoutWidget)
        self.formLayout.setContentsMargins(0, 0, 0, 0)
        self.formLayout.setVerticalSpacing(4)
        self.formLayout.setObjectName("formLayout")
        self.label_4 = QtWidgets.QLabel(self.formLayoutWidget)
        self.label_4.setObjectName("label_4")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label_4)
        self.comboBox_4 = QtWidgets.QComboBox(self.formLayoutWidget)
        self.comboBox_4.setObjectName("comboBox_4")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.comboBox_4)
        self.verticalLayoutWidget_2 = QtWidgets.QWidget(self.centralwidget)
        self.verticalLayoutWidget_2.setGeometry(QtCore.QRect(400, 0, 434, 72))
        self.verticalLayoutWidget_2.setObjectName("verticalLayoutWidget_2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.verticalLayoutWidget_2)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.groupBox = QtWidgets.QGroupBox(self.verticalLayoutWidget_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(4)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy)
        self.groupBox.setObjectName("groupBox")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.groupBox)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.checkBox_4 = QtWidgets.QCheckBox(self.groupBox)
        self.checkBox_4.setObjectName("checkBox_4")
        self.horizontalLayout_2.addWidget(self.checkBox_4)
        self.checkBox_5 = QtWidgets.QCheckBox(self.groupBox)
        self.checkBox_5.setObjectName("checkBox_5")
        self.horizontalLayout_2.addWidget(self.checkBox_5)
        self.checkBox_3 = QtWidgets.QCheckBox(self.groupBox)
        self.checkBox_3.setObjectName("checkBox_3")
        self.horizontalLayout_2.addWidget(self.checkBox_3)
        self.checkBox_2 = QtWidgets.QCheckBox(self.groupBox)
        self.checkBox_2.setObjectName("checkBox_2")
        self.horizontalLayout_2.addWidget(self.checkBox_2)
        self.checkBox = QtWidgets.QCheckBox(self.groupBox)
        self.checkBox.setObjectName("checkBox")
        self.horizontalLayout_2.addWidget(self.checkBox)
        self.horizontalLayout.addLayout(self.horizontalLayout_2)
        self.verticalLayout_2.addWidget(self.groupBox)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 19))
        self.menubar.setObjectName("menubar")
        self.menumesures = QtWidgets.QMenu(self.menubar)
        self.menumesures.setObjectName("menumesures")
        self.menumaj_grandeurs = QtWidgets.QMenu(self.menubar)
        self.menumaj_grandeurs.setObjectName("menumaj_grandeurs")
        self.menuarr_ter = QtWidgets.QMenu(self.menubar)
        self.menuarr_ter.setObjectName("menuarr_ter")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionafficher = QtWidgets.QAction(MainWindow)
        self.actionafficher.setObjectName("actionafficher")
        self.actionafficher_cycliquement = QtWidgets.QAction(MainWindow)
        self.actionafficher_cycliquement.setObjectName("actionafficher_cycliquement")
        self.actionmise_jour = QtWidgets.QAction(MainWindow)
        self.actionmise_jour.setObjectName("actionmise_jour")
        self.actionforcer = QtWidgets.QAction(MainWindow)
        self.actionforcer.setObjectName("actionforcer")
        self.actionarr_ter = QtWidgets.QAction(MainWindow)
        self.actionarr_ter.setObjectName("actionarr_ter")
        self.actioneloigner_EV = QtWidgets.QAction(MainWindow)
        self.actioneloigner_EV.setObjectName("actioneloigner_EV")
        self.actionAfficheVarsBorne = QtWidgets.QAction(MainWindow)
        self.actionAfficheVarsBorne.setObjectName("actionAfficheVarsBorne")
        self.actionAfficherVarsBorneCycliquement = QtWidgets.QAction(MainWindow)
        self.actionAfficherVarsBorneCycliquement.setObjectName("actionAfficherVarsBorneCycliquement")
        self.menumesures.addAction(self.actionafficher)
        self.menumesures.addSeparator()
        self.menumesures.addAction(self.actionafficher_cycliquement)
        self.menumesures.addSeparator()
        self.menumesures.addAction(self.actionAfficheVarsBorne)
        self.menumesures.addSeparator()
        self.menumesures.addAction(self.actionAfficherVarsBorneCycliquement)
        self.menumaj_grandeurs.addAction(self.actionmise_jour)
        self.menumaj_grandeurs.addSeparator()
        self.menuarr_ter.addAction(self.actionarr_ter)
        self.menuarr_ter.addAction(self.actioneloigner_EV)
        self.menubar.addAction(self.menumesures.menuAction())
        self.menubar.addAction(self.menumaj_grandeurs.menuAction())
        self.menubar.addAction(self.menuarr_ter.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Electric Vehicle"))
        self.label_3.setText(_translate("MainWindow", "TextLabel"))
        self.LHeure.setText(_translate("MainWindow", "Heure Affichage"))
        self.PBSave.setText(_translate("MainWindow", "sauvegarder"))
        self.frame_2.setAccessibleDescription(_translate("MainWindow", "0"))
        self.label_2.setText(_translate("MainWindow", "CC"))
        self.LH.setText(_translate("MainWindow", "H:"))
        self.LH_2.setText(_translate("MainWindow", "MN:"))
        self.PBChaOn.setText(_translate("MainWindow", "marche"))
        self.PBChaOff.setText(_translate("MainWindow", "arret"))
        self.LHeureDpt.setText(_translate("MainWindow", "heure départ"))
        self.LChargt.setText(_translate("MainWindow", "Chargement du véhicule"))
        self.LChaMaxPosVal.setText(_translate("MainWindow", "0.0"))
        self.label.setText(_translate("MainWindow", "SoC demandé"))
        self.label_5.setText(_translate("MainWindow", "Energie à transfèrer"))
        self.label_6.setText(_translate("MainWindow", "variables de la borne"))
        self.label_4.setText(_translate("MainWindow", "  type de connexion"))
        self.groupBox.setTitle(_translate("MainWindow", "Vehicule Automobile"))
        self.checkBox_4.setText(_translate("MainWindow", "wifi"))
        self.checkBox_5.setText(_translate("MainWindow", "simu"))
        self.checkBox_3.setText(_translate("MainWindow", "connecter"))
        self.checkBox_2.setText(_translate("MainWindow", "charger"))
        self.checkBox.setText(_translate("MainWindow", "décharger"))
        self.menumesures.setTitle(_translate("MainWindow", "affichage grandeurs"))
        self.menumaj_grandeurs.setTitle(_translate("MainWindow", "maj grandeurs"))
        self.menuarr_ter.setTitle(_translate("MainWindow", "general"))
        self.actionafficher.setText(_translate("MainWindow", "afficherVarsEV"))
        self.actionafficher_cycliquement.setText(_translate("MainWindow", "afficher VarsEVcycliquement"))
        self.actionmise_jour.setText(_translate("MainWindow", "mise à jour"))
        self.actionforcer.setText(_translate("MainWindow", "forcer"))
        self.actionarr_ter.setText(_translate("MainWindow", "arrêter"))
        self.actioneloigner_EV.setText(_translate("MainWindow", "eloigner EV"))
        self.actionAfficheVarsBorne.setText(_translate("MainWindow", "afficherVarsBorne"))
        self.actionAfficherVarsBorneCycliquement.setText(_translate("MainWindow", "afficherVarsBorneCycliquement"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
