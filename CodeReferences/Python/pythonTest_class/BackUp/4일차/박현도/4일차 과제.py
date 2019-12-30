from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sqlite3
import sys
#MVC


def createable():
    try:
        sql='create table if not exists ' \
            'student(name varchar(20), age varchar(20), birth varchar(20))'
        db = sqlite3.connect('test.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)

def insertTable(name,age,birth):
    print("insert start")
    try:
        sql="insert into student(name, age,birth) values(?,?,?)"
        db = sqlite3.connect('test.db')
        db.execute(sql, (name,age,birth) )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)


class MyDlg:
    def __init__(self):
        self.dlg=loadUi('e.ui')
        self.dlg.pushButton.clicked.connect(self.btnClick)
        self.dlg.pushButton_2.clicked.connect(self.showItem)
        self.dlg.show()
        createable()
    def selectTable(self):
        try:
            sql="select * from student"
            db = sqlite3.connect('test.db')
            cur = db.cursor()
            cur.execute(sql)
            data = cur.fetchall()
            for n,a,b in data:
                self.addTableData(n,a,b)
            db.commit()
            db.close()
            return data
        except Exception as err:
            print("에러",err)
            return None
    def addTableData(self,name,age,birth):
        n=self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(n+1)
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(birth))

    def btnClick(self):
       name_=self.dlg.lineEdit.text()
       age_=self.dlg.spinBox.text()
       dt=self.dlg.dateEdit.date()
       birth_='%d년 %d월 %d일'%(dt.year(),dt.month(),dt.day())
       # self.addTableData(name_,age_,birth_)
       self.addItem(name_,age_,birth_)

    def addItem(self,name,age,birth):
        pass
        insertTable(name,age,birth)
    def showItem(self):
        self.selectTable()

app=QApplication(sys.argv)
dlg=MyDlg()

app.exec()  #무한 Loop 큐메모리 감시(윈도우 종료시)

