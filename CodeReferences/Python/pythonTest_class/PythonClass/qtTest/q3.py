from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
#MVC
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('qtTest/a.ui')
        self.dlg.pushButton.clicked.connect( self.btnClick )
        self.dlg.show()

    def btnClick(self):
        self.dlg.spinBox.setValue(50)
        self.dlg.lineEdit.setText('대한민국')
        s = self.dlg.lineEdit.text()
        print(s)

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)
print('bye!')
