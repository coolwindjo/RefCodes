
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
import sqlite3
from PyQt5.QtCore import *

def createDB():
    try:
        sql = "create table if not exists address(name varchar(20), age int, birth date)"
        db = sqlite3.connect('address.db')
        db.execute(sql)
        db.close()
        print('created address db')
    except Exception as err:
        print('error', err)

def insertTable(name, age, b_year, b_month, b_day):
    try:
        sql = "insert into address(name, age, birth) values(?,?,?)"
        db = sqlite3.connect('address.db')
        db.execute(sql,(name,int(age),'{}-{}-{}'.format(b_year,b_month,b_day)))
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("error", err)

def readTable():
    try:
        sql = "select * from address"
        db = sqlite3.connect('address.db')

        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()

        db.commit()
        db.close()

        return data

    except Exception as err:
        print("error", err)

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('e.ui')
        self.dlg.pushButton.clicked.connect(self.btnclick_input)
        self.dlg.pushButton_2.clicked.connect(self.btnclick_output)
        self.dlg.show()

    def btnclick_input(self):
        name = self.dlg.lineEdit.text()
        age = self.dlg.spinBox.value()
        birth = self.dlg.dateEdit.date()

        insertTable(name,age,birth.year(),birth.month(),birth.day())

    def btnclick_output(self):
        self.data = readTable()
        self.show_data(self.data)

    def show_data(self, data):
        self.dlg.tableWidget.setRowCount(0)
        for p_data in data:
            n = self.dlg.tableWidget.rowCount()
            self.dlg.tableWidget.setRowCount(n+1)
            self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(p_data[0]))
            self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(p_data[1])))
            self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(p_data[2]))



##### main #####

createDB()

app = QApplication(sys.argv)

dlg = MyDlg()

app.exec()
print('Bye~')




