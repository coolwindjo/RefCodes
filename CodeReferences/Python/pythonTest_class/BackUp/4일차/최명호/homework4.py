import sqlite3
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys

def createTable():
    try:
        sql = 'create table if not exists student(name varchar(20), age int, birth date)'
        db = sqlite3.connect('test.db')
        db.execute(sql)
        db.close()
        print('create table success')
    except Exception as err:
        print('createTable() 에러발생', err)

def insertTable(name, age, date):
    try:
        sql = "insert into student(name, age, birth) values(?, ?, ?)"
        db = sqlite3.connect('test.db')
        db.execute(sql, (name,age,date))
        db.commit()
        db.close()
        print('insert table success')

    except Exception as err:
        print('insertTable() 에러발생', err)

def selectTable():
    try:
        sql="select * from student"
        db = sqlite3.connect('test.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data

    except Exception as err:
        print("selectTable() 에러발생",err)
        return None

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('test.ui')
        self.dlg.pushButton.clicked.connect( self.btnClick )
        self.dlg.pushButton_2.clicked.connect( self.btnClick_2 )
        self.dlg.show()
        createTable()

    def addTableData(self,name,age,birth):
        n = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(n+1)
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(str(birth)))

    def btnClick(self):
        input_name = self.dlg.lineEdit.text()
        input_age = int(self.dlg.spinBox.value())
        dt = self.dlg.dateEdit.date()
        input_date = '%d-%d-%d'%(dt.year(),dt.month(),dt.day())
        insertTable(input_name, input_age, input_date)

    def btnClick_2(self):
        self.dlg.tableWidget.setRowCount(0)
        rd = selectTable()
        for name,age,birth in rd:
            self.addTableData(name,age,birth)

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec()

