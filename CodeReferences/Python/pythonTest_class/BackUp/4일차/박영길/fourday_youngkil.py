import sys

import sqlite3

from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi

def createTable():
    try:
        sql='create table if not exists ' \
            'grade(name archar(20), age int, birthday int)'
        db = sqlite3.connect('home4.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)

def insertTable( name, age, birthday ):
    try:
        sql="insert into grade(name,age,birthday)" \
            " values(?,?,?)"
        db = sqlite3.connect('home4.db')
        db.execute(sql, (name, age, birthday) )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)


def selectTable():
    try:
        sql="select * from grade"
        db = sqlite3.connect('home4.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러",err)
        return None





class MyDlg :
    def __init__(self):

        self.dlg = loadUi('home4.ui')   #xml 정보를 기준으로 객체로 변경해 주는 것을 말함. diolog 객체의 참조를 반환한다.
        self.dlg.pushButton.clicked.connect(self.btnclick)
        self.dlg.pushButtonOut.clicked.connect(self.btnclickout)
        self.dlg.show()

    def btnclickout (self) :

        for name, age, day in selectTable() :
            print(name,age,day)
            self.addTableData(name, age, day)


    def btnclick (self) :
        name = self.dlg.lineEdit.text()
        # print(name)
        age = self.dlg.spinBox.value()
        # print(age)

        dt = self.dlg.dateTimeEdit.date()
        s  = '%d년%d월%d일'%(dt.year(), dt.month(), dt.day())
        # print(s)
        insertTable( name, age, s )

        # yn = input("계속입력(y/n):")
        # print(self.dlg.pushButtonOut.isChecked())
        # sys.exit()

        if self.dlg.pushButtonOut.isChecked() :
            self.btnclickout()
        # if yn =='n':
        #     for name, age, day in selectTable() :
        #         print(name,age,day)
        #         self.addTableData(name, age, day)



    def addTableData(self,name, age, day):
        n = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount( n + 1)
        self.dlg.tableWidget.setItem(n,0,  QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(n,1,  QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(n,2,  QTableWidgetItem(day))


    def btnclick_backup2(self) : #함수 이름이 주소이다.
        self.addTableData('홍길동',20,'서울시')








createTable()

app = QApplication ( sys.argv )
dlg = MyDlg()






# end sandwitch code part
app.exec() # 무한 loop 큐메모리 감시(윈도우 종료시 while loop를 빠져나감.

print('hello')
