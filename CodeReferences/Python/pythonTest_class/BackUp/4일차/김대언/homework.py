import sqlite3
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('e.ui')
        self.dlg.btnInsert.clicked.connect(self.clickInsert)
        self.dlg.btnView.clicked.connect(self.clickView)
        self.dlg.show()
    def clickInsert(self):
        name = self.dlg.editName.text()
        age = str(self.dlg.sbAge.value())
        dt = self.dlg.dateBirth.date()
        birth = '%d-%d-%d'%(dt.year(), dt.month(), dt.day())
        insertTable((name, age, birth))
    def clickView(self):
        data = selectTable()
        self.dlg.tableWidget.setRowCount(0)
        for n, a, b in data:
            print(n, a, b)
            cnt = self.dlg.tableWidget.rowCount()
            self.dlg.tableWidget.setRowCount(cnt+1)
            self.dlg.tableWidget.setItem(cnt, 0, QTableWidgetItem(n))
            self.dlg.tableWidget.setItem(cnt, 1, QTableWidgetItem(str(a)))
            self.dlg.tableWidget.setItem(cnt, 2, QTableWidgetItem(b))

def createTable():
    try:
        sql = 'create table if not exists people(name varchar(20), age int, birth date)'
        db = sqlite3.connect('test.db')
        db.execute(sql)
        db.close()
    except Exception as err:
        print("에러", err)

def insertTable(data):
    try:
        sql = "insert into people(name, age, birth) values(?,?,?)"
        db = sqlite3.connect('test.db')
        print(data)
        db.execute(sql, data)
        db.commit()
        db.close()
    except Exception as err:
        print("에러", err)

def selectTable():
    try:
        sql = "select * from people"
        db = sqlite3.connect('test.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러", err)

createTable()
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
print('exit')
