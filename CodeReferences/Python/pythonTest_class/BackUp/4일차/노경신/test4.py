from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
from test4DB import *

class MyDlg:
    def __init__(self):
        createTable()
        self.dlg = loadUi('e.ui')
        self.dlg.pushBtn1.clicked.connect(self.btnClick)
        self.dlg.pushBtn2.clicked.connect(self.btnClick2)
        self.dlg.show()

    #입력
    def btnClick(self):
        name = self.dlg.lineEdit.text()
        age = self.dlg.spinBox.value()
        birth = self.dlg.dateEdit.date()
        s = '%d년 %d월 %d일' % (birth.year(), birth.month(), birth.day())
        insertTable(name, age, s)

    #출력
    def btnClick2(self):
        cnt = 0
        data = selectTable()
        for n in data:
            print(n[2])
            self.dlg.tableWidget.setRowCount(cnt+1)
            self.dlg.tableWidget.setItem(cnt, 0, QTableWidgetItem(n[0]))
            self.dlg.tableWidget.setItem(cnt, 1, QTableWidgetItem(n[1]))
            self.dlg.tableWidget.setItem(cnt, 2, QTableWidgetItem(n[2]))
            cnt += 1

        # self.dlg.tableWidget.setRowCount(2)
        # self.dlg.tableWidget.setItem(0, 0, QTableWidgetItem('홍길동'))


app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
# print('hello')
