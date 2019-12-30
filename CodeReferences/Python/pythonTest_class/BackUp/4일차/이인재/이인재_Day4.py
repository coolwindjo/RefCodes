from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sqlite3
import sys

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('result.ui')
        self.dlg.pushButton1.clicked.connect(self.btnClick1)
        self.dlg.pushButton.clicked.connect(self.btnClick2)
        self.dlg.show()

    def addTableData(self,name,age,date):
        n= self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount( n+1 )
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name) )
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)) )
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(date) )

    def saveDB(self,name,age,date):
        try:
            sql = 'create table if not exists person(name varchar(20), age int, birth date)'
            db = sqlite3.connect('personal_info.db')
            db.execute(sql)
            print("db create success")
        except Exception as err:
            print("에러", err)
        try:
            sql = "insert into person(name,age,birth) values(?,?,?)"
            db.execute(sql, (name,age,date))
            db.commit()
            db.close()
            print("db insert success")
        except Exception as err:
            print("에러", err)

    def btnClick1(self):
        name = self.dlg.lineEdit.text()
        age = self.dlg.spinNum.value()
        date = QDate.currentDate()
        
#       self.saveDB(('홍길동',20,'1999-10-12'))
        self.saveDB((name,age,date))


    def btnClick2(self):
        self.dlg.tableWidget.setRowCount(0)
        self.addTableData('홍길동',20,'1999-10-12')


app = QApplication( sys.argv )
dlg = MyDlg()
app.exec()