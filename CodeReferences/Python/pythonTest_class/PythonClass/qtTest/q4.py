from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('qtTest/b.ui')
        self.dlg.pushButton.clicked.connect( self.btnClick )
        self.dlg.show()

    def btnClick(self):
        n1 = self.dlg.spinNum1.value()
        n2 = self.dlg.spinNum2.value()
        self.dlg.lineEditResult.setText( "합:%d"%(n1+n2) )

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)
print('bye!')

