from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys
class SubDlg:
    def __init__(self):
        self.dlg = loadUi('qtTest/dlg.ui')
        self.dlg.pushButton.clicked.connect(self.closeFn)
        # self.dlg.show() #modaless
        self.dlg.exec() # modal

    def closeFn(self):
        self.dlg.close()

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('qtTest/e.ui')
        self.dlg.actiondialog.triggered.connect(self.dlgClick)
        self.dlg.show()

    def dlgClick(self):
        sub = SubDlg()
        s = sub.dlg.lineEdit.text()
        self.dlg.lineEditMain.setText( s )

        print("end....")

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)
print('bye!')

