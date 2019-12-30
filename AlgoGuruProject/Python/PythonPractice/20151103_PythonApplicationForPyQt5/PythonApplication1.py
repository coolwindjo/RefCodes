# -*- coding: utf-8 -*- 
 
import sys #system module을 사용한다.
from PyQt5 import QtWidgets
from PyQt5 import uic

class Form(QtWidgets.QDialog):
    def __init__(self, parent=None):
        QtWidgets.QDialog.__init__(self, parent)
        self.ui = uic.loadUi("form.ui")
        self.ui.show()
        return 

# main function
def main():
    app = QtWidgets.QApplication(sys.argv)
    w = Form()
    sys.exit(app.exec())

    return

if __name__ == "__main__":
    main()