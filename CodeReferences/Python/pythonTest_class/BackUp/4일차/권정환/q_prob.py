#install pyqt5, pyqt5-tools

import sqlite3
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys


def createTable():
    try:
        sql = 'create table if not exists student(name varchar(20), age int, birthday date)'
        db = sqlite3.connect('day4_prob.db')
        db.execute(sql)
        db.close()
        print("create succeed")
    except Exception as err:
        print("에러 :", err)

def insertTable(n, k, e):
    try:
        sql = "insert into student(name, age, birthday) values(?, ?, ?)"
        db = sqlite3.connect('day4_prob.db')
        db.execute(sql, (n, k, e))
        db.commit() # 명령 확정을 해야함!
        db.close()
        print("Insert succeed")
    except Exception as err:
        print("에러 :", err)

class MyDlg:

    def __init__(self):
        self.dlg = loadUi('prob.ui')
        self.dlg.pushButton.clicked.connect(self.btn_click)
        self.dlg.pushButton_2.clicked.connect(self.btn_click_2)
        self.dlg.show()

    def addTableDate(self, name, age, birth):
        n = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(1) # 첫번째에만 나타나고자 할 때
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(str(birth)))
        # self.dlg.tableWidget.setRowCount(n+1) # 추가로 계속 프린트하고자 할 때
        # self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name))
        # self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)))
        # self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(str(birth)))

    def get_data(self):
        self.name = self.dlg.lineEdit.text()
        self.age = self.dlg.spinBox.value()
        self.birth = self.dlg.dateEdit.date()
        self.birthday = '%d-%d-%d'%(self.birth.year(),self.birth.month(),self.birth.day())

    def btn_click(self):
        self.get_data()
        insertTable(self.name , self.age, self.birthday)

    def btn_click_2(self):
        self.get_data()
        self.addTableDate(self.name , self.age, self.birthday)

app = QApplication (sys.argv)
createTable()
dlg = MyDlg()
app.exec() # 무한루프 큐메모리 감시 (윈도 종료 시 종료가 됨.)
print('hello')
