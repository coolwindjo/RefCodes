from PyQt5.QtWidgets import *
import sys
class MyDlg:
    def __init__(self):
        self.dlg = QDialog()
        self.dlg.setWindowTitle('타이틀')
        self.dlg.setGeometry(50,50,300,500)
        self.vbox = QVBoxLayout()
        self.btn = QPushButton('클릭')
        self.btn.clicked.connect( self.btnClick )

        self.edit = QLineEdit()
        self.vbox.addWidget(self.btn)
        self.vbox.addWidget(self.edit)
        self.dlg.setLayout(self.vbox)

        self.dlg.show()
        
    def btnClick(self):
        print("click...")

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)
print('bye!')

