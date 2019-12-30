from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
import h4_db

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('h4.ui')
        self.dlg.inputBtn.clicked.connect(self.inputBtnClick)
        self.dlg.displayBtn.clicked.connect(self.displayBtnClick)
        self.dlg.show()
        h4_db.createTable()

    def displayData(self, name, age, birth):
        n = self.dlg.listTable.rowCount()
        self.dlg.listTable.setRowCount(n+1)

        self.dlg.listTable.setItem(n,0,QTableWidgetItem(name))
        self.dlg.listTable.setItem(n,1,QTableWidgetItem(str(age)))
        self.dlg.listTable.setItem(n,2,QTableWidgetItem(birth))

    def inputBtnClick(self):
        name = self.dlg.nameEdit.text()
        age = int(self.dlg.ageBox.value())
        dt = self.dlg.birthDate.date()
        birth = '%d년%d월%d일'%(dt.year(), dt.month(),dt.day())

        # self.addTableData(name, age, birth)
        h4_db.insertTable(name, age, birth)

    def displayBtnClick(self):
        print ('displayBtnClick')
        data_list = h4_db.selectTable()

        for name, age, birth in data_list:
            self.displayData(name, int(age), birth)



app = QApplication( sys.argv )
dlg = MyDlg()
app.exec()

print ('hello')

