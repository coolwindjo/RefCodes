from PyQt5.QtWidgets import *
import sys
import sqlite3
from PyQt5.uic import loadUi
#MVC

#Make database
try:
    sql='create table if not exists tables(name varchar(20), year int, birth varchar(20))'
    db = sqlite3.connect('hw.db')
    db.execute(sql)
    db.close()
    print("create success")
except Exception as err:
    print("에러",err)

def add(name, kor, eng):
    try:
        sql = "insert into tables(name, year, birth) values(?, ?, ?)"
        db = sqlite3.connect('hw.db')
        db.execute(sql, (name, int(kor), eng))
        db.commit()
        db.close()
        print('insert success')
    except Exception as err:
        print("에러",err)

def selectTable():
    try:
        sql="select * from tables"
        db = sqlite3.connect('hw.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러",err)

def deleteTable():
    try:
        # sql="delete from student where name='이이'"
        sql="delete from tables"
        db = sqlite3.connect('hw.db')
        db.execute(sql)
        db.commit()
        db.close()
        print("delete success")
    except Exception as err:
        print("에러",err)

class Mydlg:
    def __init__(self):
        self.dlg = loadUi('e.ui')
        self.dlg.pushButton.clicked.connect(self.addTabel)
        self.dlg.pushButton2.clicked.connect(self.click)
        self.dlg.show()
    def addTabel(self):
        a = self.dlg.lineEdit_3.text()
        b = self.dlg.spinBox.value()
        dt = self.dlg.dateEdit.date()
        s = '%d년%d월%d일'%(dt.year(),dt.month(),dt.day())
        add(a, b, s)
        #print(a)
        #print(b)
        #print(s)

    def click(self):
        self.dlg.tableWidget.setRowCount(0)
        data = selectTable()
        for a,b,c in data:
            n = self.dlg.tableWidget.rowCount()
            self.dlg.tableWidget.setRowCount(n+1)
            self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(a))
            self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(b)))
            self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(c))

app = QApplication(sys.argv)
dlg = Mydlg()
app.exec()
deleteTable()
