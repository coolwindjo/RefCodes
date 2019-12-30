from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('qtTest/c.ui')
        self.dlg.pushButton.clicked.connect( self.btnClick )
        self.dlg.show()

    def btnClick(self):
        # q =QDateTime(2019,5,10,12,13,14)
        q = QDateTime.currentDateTime()
        self.dlg.dateTimeEdit.setDateTime( q  )
        dt = self.dlg.dateTimeEdit.date()
        tm = self.dlg.dateTimeEdit.time()
        s = '%d년%d월%d일'%(dt.year(),dt.month(),dt.day())
        #s ='%d:%d:%d'%(tm.hour(),tm.minute(),tm.second())
        self.dlg.lineEdit.setText(s)

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)
print('bye!')
