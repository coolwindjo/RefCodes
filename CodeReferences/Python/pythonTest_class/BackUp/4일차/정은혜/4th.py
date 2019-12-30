from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sqlite3
import sys

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('e.ui')
        self.dlg.pushButtonSave.clicked.connect( self.btnClickSave )
        self.dlg.pushButtonShow.clicked.connect( self.btnClickShow )
        self.dlg.show()

    def createTable(self):
        try:
            sql='create table if not exists myDB(name varchar(20),age int, birth int)'
            db = sqlite3.connect('myDB.db')
            db.execute(sql)
            db.close()
            print("create success")
        except Exception as err:
            print("에러",err)
    def insertTable( self, name, age, birth ):
        try:
            sql="insert into myDB(name,age,birth) values(?,?,?)"
            db = sqlite3.connect('myDB.db')
            db.execute(sql, (name,age,birth) )
            db.commit()
            db.close()
            print("insert success")
        except Exception as err:
            print("에러",err)
    def btnClickSave(self): #DB에 저장하기
        self.createTable()
        # self.insertTable('홍길동',20,'2000-01-20' )
        self.name = self.dlg.lineEdit.Text()

        self.age = self.dlg.spinBox.value()
        dt = self.dlg.dateTimeEdit.date()
        self.birth = '%d년%d월%d일'%(dt.year(),dt.month(),dt.day())
        self.insertTable(self.name,self.age,self.birth )


    def addTableData(self,name,age,birth):
        n= self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount( n+1 )
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name) )
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)) )
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(birth) )

    def btnClickShow(self):
        #테이블에 보여주기
        self.addTableData()
        self.addTableDate(self.name , self.age, self.birth)



app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)
