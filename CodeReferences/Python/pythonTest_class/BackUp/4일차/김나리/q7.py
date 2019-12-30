from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
from dbHandle import *

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('quiz.ui')
        self.dlg.inputButton.clicked.connect(self.inputbtnClick)
        self.dlg.printButton.clicked.connect(self.printbtnClick)
        self.dlg.show()

    def addTableData(self,name,age,birth):
        n = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(n+1)
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(birth))

    def inputbtnClick(self):
        name = self.dlg.lineEditName.text()
        age = self.dlg.spinBoxAge.value()
        birth = self.dlg.dateEditBirth.date()
        data = (name,age,"%d년 %d월 %d일"%(birth.year(),birth.month(),birth.day()))
        insertTable(data)

    # 여기 db검색하는 부분 dbHandle로 해보기
    def printbtnClick(self):
        self.dlg.tableWidget.setRowCount(0)
        try:
            sql = "select * from person"
            db = sqlite3.connect('personal_info.db')
            cur = db.cursor()
            cur.execute(sql)
            for a,b,c in cur:
                self.addTableData(a,b,c)
            db.close()
        except Exception as err:
            print("에러",err)

createTable()
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()


