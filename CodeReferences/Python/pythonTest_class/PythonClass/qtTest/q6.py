from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('qtTest/d.ui')
        self.dlg.pushButton.clicked.connect( self.btnClick )
        self.dlg.show()

    def addTableData(self,name,age,addr):
        n= self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount( n+1 )
        self.dlg.tableWidget.setItem(n,0,QTableWidgetItem(name) )
        self.dlg.tableWidget.setItem(n,1,QTableWidgetItem(str(age)) )
        self.dlg.tableWidget.setItem(n,2,QTableWidgetItem(addr) )

    def btnClick(self):
        self.addTableData('홍길동',20,'서울시' )
        self.dlg.tableWidget.setRowCount(2)
        self.dlg.tableWidget.setItem(0,0,QTableWidgetItem('홍길동'))
        self.dlg.tableWidget.setItem(0,1,QTableWidgetItem('20'))
        self.dlg.tableWidget.setItem(0,2,QTableWidgetItem('서울시'))
        
        self.dlg.tableWidget.setItem(1,0,QTableWidgetItem('이순신'))
        self.dlg.tableWidget.setItem(1,1,QTableWidgetItem('30'))
        self.dlg.tableWidget.setItem(1,2,QTableWidgetItem('부산시'))


app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)
print('bye!')
