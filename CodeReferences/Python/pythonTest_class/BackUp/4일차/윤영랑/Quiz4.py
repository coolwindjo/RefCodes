from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import QDateTime
import sys
import sqlite3

class MyDlg:
    def __init__(self):
        MemberDatabase.create()

        self.dlg = loadUi('Quiz4.ui')
        self.dlg.insertBtn.clicked.connect( self.insertBtnClick )
        self.dlg.showBtn.clicked.connect( self.showBtnClick )
        self.dlg.show()

    def insertBtnClick(self):
        name = self.dlg.nameEdit.text()
        age = self.dlg.ageEdit.value()
        birth = self.dlg.birthEdit.date()
        birth_str = '%d-%d-%d'%(birth.year(), birth.month(), birth.day())
        MemberDatabase.insert(name, age, birth_str)
        self.showBtnClick()


    def showBtnClick(self):
        self.dlg.tableWidget.clearContents()
        self.dlg.tableWidget.setRowCount(0)
        MemberDatabase.select(MyDlg.addTableData, self.dlg.tableWidget)

    @staticmethod
    def addTableData(tableWidget, name, age, birth):
        n = tableWidget.rowCount()
        tableWidget.setRowCount(n+1)
        tableWidget.setItem (n,0, QTableWidgetItem(name))
        tableWidget.setItem (n,1, QTableWidgetItem(str(age)))
        tableWidget.setItem (n,2, QTableWidgetItem(birth))


class MemberDatabase:
    @classmethod
    def create(cls):
        try:
            sql='create table if not exists ' \
                'members(name varchar(20), age int, birth date)'
            db = sqlite3.connect('Quiz4.db')
            db.execute(sql)
            db.close()
        except Exception as err:
            print("에러",err)

    @classmethod
    def insert(cls, name, age, birth):
        try:
            sql="insert into members(name, age, birth)" \
                " values(?,?,?)"
            db = sqlite3.connect('Quiz4.db')
            db.execute(sql, (name, age, birth) )
            db.commit()
            db.close()
        except Exception as err:
            print("에러",err)

    @classmethod
    def select(cls, callback, tableWidget):
        try:
            sql="select * from members"
            db = sqlite3.connect('Quiz4.db')
            cur = db.cursor()
            cur.execute(sql)
            for c in cur:
                if callback:
                    callback(tableWidget, *c)
            db.close()
        except Exception as err:
            print("에러",err)


app = QApplication( sys.argv )
dlg = MyDlg()
app.exec()







