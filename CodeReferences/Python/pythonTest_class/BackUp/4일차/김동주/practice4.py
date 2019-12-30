from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from db_handle import *
import sys

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('practice4.ui')
        self.dlg.pushButton.clicked.connect(self.input)
        self.dlg.pushButton_2.clicked.connect(self.output)
        self.dlg.pushButton_3.clicked.connect(self.clear)
        self.dlg.show()


    def clear(self):
        clearTable()
        self.dlg.tableWidget.setRowCount(0)


    def input(self):
        n = self.dlg.lineEdit.text()
        a = self.dlg.spinBox.value()
        b = self.dlg.dateEdit.date()
        y = b.year()
        m = b.month()
        d = b.day()
        birth = "-".join([str(y), str(m), str(d)])
        insertTable(n, int(a), birth)

    def addTableData(self, name, age, birth):
            n = self.dlg.tableWidget.rowCount()
            self.dlg.tableWidget.setRowCount(n+1)

            self.dlg.tableWidget.setItem(n, 0, QTableWidgetItem(name))
            self.dlg.tableWidget.setItem(n, 1, QTableWidgetItem(str(age)))
            self.dlg.tableWidget.setItem(n, 2, QTableWidgetItem(birth))

    def output(self):
        self.dlg.tableWidget.setRowCount(0)
        data = selectTable()
        for n in data:
            self.addTableData(*n)


app = QApplication(sys.argv)
createTable()
dlg = MyDlg()
app.exec()

