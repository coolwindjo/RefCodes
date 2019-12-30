from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sqlite3
import sys

def create():
    try:
        sql = 'create table if not exists student(name varchar(20), age int, birth date)'
        db= sqlite3.connect('test.db') #있으면 접속, 없으면 생성
        db.execute(sql)

        db.close()
    except Exception as err:
        print("error",err)

def saveData(name, age, addr):
    try:
        sql = "insert into student(name, age, birth) values(?,?,?)"
        db = sqlite3.connect('test.db')  # 있으면 접속, 없으면 생성

        db.execute(sql, (name, age, '%d-%d-%d'%(addr.year(),addr.month(),addr.day())))
        db.commit()
        db.close()
    except Exception as err:
        print("error", err)

def getData():
    try:
        sql = "select * from student"
        db = sqlite3.connect('test.db')  # 있으면 접속, 없으면 생성
        cur = db.cursor()
        cur.execute(sql)
        list = []
        for c in cur:
            list.append(c)
            # addTableData(c[0],c[1],c[2])
        db.commit()
        db.close()
        return list
    except Exception as err:
        print("error", err)

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('e.ui')
        self.dlg.inputBtn.clicked.connect(self.inputBtnClick)
        self.dlg.showBtn.clicked.connect(self.showBtnClick)
        self.dlg.show()

    def inputBtnClick(self):
        saveData(self.dlg.lineEdit.text(), self.dlg.spinBox.value(), self.dlg.dateEdit.date())

    def showBtnClick(self):
        self.dlg.tableWidget.setRowCount(0)
        for name, age, birth in getData():
            self.addTableData(name, age, birth)

    def addTableData(self, name, age, birth):
        n = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(n+1)
        self.dlg.tableWidget.setItem(n, 0, QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(n, 1, QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(n, 2, QTableWidgetItem(birth))

create()
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
