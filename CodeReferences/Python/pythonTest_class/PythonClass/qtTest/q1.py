from PyQt5.QtWidgets import *
import sys
def btnClick():
    print("click...")
app = QApplication( sys.argv )

dlg = QDialog()
dlg.setWindowTitle('타이틀')
dlg.setGeometry(50,50,300,500)
vbox = QVBoxLayout()
btn = QPushButton('클릭')
# btn.clicked.connect( btnClick )
btn.clicked.connect( lambda v:print('hello') )

edit = QLineEdit()
vbox.addWidget(btn)
vbox.addWidget(edit)
dlg.setLayout(vbox)

dlg.show()

app.exec() #무한loop 큐메모리 감시(윈도우종료시)
print('bye!')

