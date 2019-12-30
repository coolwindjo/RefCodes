from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
import sqlite3

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('day4_hw.ui')
        self.dlg.insertPushButton.clicked.connect(self.btnClick)
        self.dlg.showPushButton.clicked.connect(self.showBtnClick)
        self.dlg.show()

    def btnClick(self):
        name = self.dlg.lineEdit.text()
        print("1", name)
        age = self.dlg.spinBox.value()
        print("2", age)
        date = self.dlg.dateEdit.date()
        birth = "%d년 %d월 %d일"%(date.year(), date.month(), date.day())
        # # s="%d년 %d월 %d일"%(date.year(), date.month(), date.day())
        print("3", birth)
        self.insertTable(str(name), int(age), str(birth))

    def addTableData(self, name, age, birth):
        n = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(n + 1)
        self.dlg.tableWidget.setItem(n, 0, QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(n, 1, QTableWidgetItem(age))
        self.dlg.tableWidget.setItem(n, 2, QTableWidgetItem(birth))

    def showBtnClick(self):
        self.dlg.tableWidget.setRowCount(0)
        try:
            sql = "select * from person"
            db = sqlite3.connect('name.db')
            cur = db.cursor()
            cur.execute(sql)
            for c in cur:
                self.addTableData(c[0], c[1], c[2])
            db.commit()
            db.close()
        except Exception as err:
            print("error", err)

    def insertTable(self, name, age, birth):
        print("insert ", name, ", ", age, ", ", birth)
        try:
            sql = "insert into person(name,age,birth) values(?,?,?)"
            db = sqlite3.connect('name.db')
            db.execute(sql, (name, age, birth))
            db.commit()
            db.close()
            print("insert success")
        except Exception as err:
            print("에러", err)


def createTable():
    try:
        sql = 'create table if not exists ' \
            'person(name varchar(20),age int,birth varchar(20))'
        db = sqlite3.connect('name.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)


createTable()
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()      # 무한 Loop (Hold)
