from PyQt5.QtWidgets import *
import sys
from PyQt5.uic import loadUi
import sqlite3


class MyDlg:
    def __init__(self):
        self.dlg = loadUi('t.ui') #xml 기준으로 object로 변환
        self.dlg.pushButton.clicked.connect(self.inputclick)
        self.dlg.pushButton_2.clicked.connect(self.resultclick)
        self.dlg.show()
    def addTableData(self, name, age, addr):
        n = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(n+1)
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem( name ))
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem( str(age)))
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem( addr))

    def inputclick(self):
        name = self.dlg.lineEdit.text()
        age = self.dlg.spinBox.value()
        t_date = self.dlg.dateEdit.date()
        date =t_date.toPyDate()
        print(name, age, date)
        self.insertTable1(name, age, date)

    def resultclick(self):
        self.selectTable()

    def insertTable1(self,name,age,birth):
        try:
            sql = "insert into student(name, age, birth)" \
                    " values(?,?,?)"
            db = sqlite3.connect('test2.db')
            db.execute(sql, (name, age, birth))
            db.commit()
            db.close()
            print("insert success")
        except Exception as err:
            print("error", err)

    def selectTable(self):
        try:
            sql = "select * from student"
            db = sqlite3.connect('test2.db')
            cur = db.cursor()
            cur.execute(sql)
            data = cur.fetchall()
            db.commit()
            db.close()
            print(data)
            for n in data:
                self.addTableData(n[0], n[1], n[2])
        except Exception as err:
            print("에러", err)




def createTable():
    try:
        sql = 'create table if not exists ' \
                'student(name varchar(20), age int, birth data)'
        db =  sqlite3.connect('test2.db')
        db.execute(sql)
        db.close()
        print('create success')
    except Exception as err:
        print('error ',err)


app = QApplication (sys.argv)
createTable()
dlg = MyDlg()
app.exec()

