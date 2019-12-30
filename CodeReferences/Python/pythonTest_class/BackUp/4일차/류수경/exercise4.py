from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
import dbmanager as db


class MyDlg:
    def __init__(self):
        self.dlg = loadUi('people.ui')
        self.dlg.inputButton.clicked.connect( self.inputBtnClick )
        self.dlg.viewButton.clicked.connect( self.viewBtnClick )
        self.dlg.show()

    def inputBtnClick(self):
        name = self.dlg.nameEdit.text()
        age = self.dlg.spinBox.value()
        date = self.dlg.dateEdit.date()
        birth = '%d년%d월%d일'%(date.year(),date.month(),date.day())
        db.createTable()
        db.insertTable(name,age,birth)

    def viewBtnClick(self):
        totaltable = db.selectTable()
        self.dlg.tableWidget.setRowCount(0)
        for name,age,birth in totaltable:
            n= self.dlg.tableWidget.rowCount()
            self.dlg.tableWidget.setRowCount( n+1 )
            self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name) )
            self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)) )
            self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(birth) )

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec()







