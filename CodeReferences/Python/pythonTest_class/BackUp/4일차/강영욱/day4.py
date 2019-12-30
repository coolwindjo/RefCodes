from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
import sqlite3

s = None

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('day4.ui')
        self.dlg.pushButtonInput.clicked.connect( self.pushButtonInput )
        self.dlg.pushButtonView.clicked.connect( self.pushButtonView )
        self.dlg.show()

        try:
            sql='create table if not exists ' \
                'student(name varchar(20),age int,birth varchar(20))'
            db = sqlite3.connect('day4.db')
            db.execute(sql)
            db.close()
            print("create success")
        except Exception as err:
            print("에러",err)

    def addDb(self,n,a,b):
        try:
            sql="insert into student(name,age,birth)" \
                " values(?,?,?)"
            db = sqlite3.connect('day4.db')
            db.execute(sql, (n,a,b) )
            db.commit()
            db.close()
            print("insert success")
        except Exception as err:
            print("에러",err)

    def pushButtonInput(self):
        name = self.dlg.lineEdit.text()
        age = self.dlg.spinBox.value()
        birth = self.dlg.dateEdit.date()
        s = '%d년%d월%d일'%(birth.year(),birth.month(),birth.day())
        self.addDb(name,age,s)

    def pushButtonView(self):
        try:
            sql="select * from student"
            db = sqlite3.connect('day4.db')
            cur = db.cursor()
            cur.execute(sql)
            data = cur.fetchall()
            db.commit()
            db.close()
            print("SELECT success")
        except Exception as err:
            print("에러",err)
            return None

        for n in data:
            print(n[0],n[1],n[2])
            k = self.dlg.tableWidget.rowCount()
            self.dlg.tableWidget.setRowCount(k+1)
            self.dlg.tableWidget.setItem(k,0,QTableWidgetItem(n[0]))
            self.dlg.tableWidget.setItem(k,1,QTableWidgetItem(str(n[1])))
            self.dlg.tableWidget.setItem(k,2,QTableWidgetItem(n[2]))



app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)







