from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
import sqlite3

def createTable():
    try:
        sql='create table if not exists ' \
            'grade(name varchar(20),age int,birth date)'
        db = sqlite3.connect('person.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)
def insertTable( name, age, birth ):
    try:
        sql="insert into grade(name,age,birth)" \
            " values(?,?,?)"
        db = sqlite3.connect('person.db')
        db.execute(sql, (name,age,birth) )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)

def selectTable():
    try:
        sql="select * from grade"
        db = sqlite3.connect('person.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러",err)
        return None

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('e.ui')
        self.dlg.pushButtonInput.clicked.connect( self.inputBtnClick )
        self.dlg.pushButtonShow.clicked.connect( self.showBtnClick )
        self.dlg.show()
        createTable()

    def inputBtnClick(self):
        print("inputBtnClick1")
        # DB생성, 저장
        n = self.dlg.lineEdit.text()
        a = int(self.dlg.spinBox.value())
        d = self.dlg.dateEdit.date()
        s = '%d-%d-%d'%(d.year(), d.month(),d.day())

        insertTable(n,a,s)

    def addTableData(self, name, age, birth):
        n = self.dlg.tableWidgetResult.rowCount()
        self.dlg.tableWidgetResult.setRowCount(n+1)
        self.dlg.tableWidgetResult.setItem(n,0,QTableWidgetItem(name))
        self.dlg.tableWidgetResult.setItem(n,1,QTableWidgetItem(str(age)))
        self.dlg.tableWidgetResult.setItem(n,2,QTableWidgetItem(str(birth)))

    def showBtnClick(self):
        sData = selectTable()
        for a,b,c in sData:
            print(a,b,c)
            self.addTableData(a,b,c)

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec()
