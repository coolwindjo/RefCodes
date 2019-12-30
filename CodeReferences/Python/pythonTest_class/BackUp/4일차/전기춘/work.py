from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *
import sys, sqlite3

dbName = 'student.db'
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('work.ui')
        self.dlg.inputButton.clicked.connect(self.inputBtnClick)
        self.dlg.showButton.clicked.connect(self.showBtnClick)
        self.dlg.show()

        try:
            sql = 'create table if not exists ' \
                    'student(name varchar(20), age int, birth date)'
            db = sqlite3.connect(dbName)
            db.execute(sql)
            db.close()
            print("create success")
        except Exception as err:
            print("Error", err)


    def insertTable(self, data):
        try:
            sql = "insert into student(name, age, birth)" \
                    "values(?, ?, ?)"
            db = sqlite3.connect(dbName)
            db.executemany(sql, data)
            db.commit()
            db.close()
            print("create success")
        except Exception as err:
            print("Error", err)


    def selectTable(self):
        try:
            sql="select * from student"
            db = sqlite3.connect(dbName)
            cur = db.cursor()
            cur.execute(sql)
            data = cur.fetchall()
            db.commit()
            db.close()

            return data
        except Exception as err:
            print("Error", err)
            return False


    def inputBtnClick(self):
        name = self.dlg.lineEdit.text()
        age = self.dlg.spinBox.value()
        date = self.dlg.dateEdit.date().toString("yyyy.MM.dd")

        self.insertTable([(name, age, date)])

        self.dlg.lineEdit.setText('')

    def showBtnClick(self):
        data = self.selectTable()

        self.dlg.tableWidget.setRowCount(len(data))

        index = 0
        for name, age, birth in data:
            self.dlg.tableWidget.setItem(index,0,
                                QTableWidgetItem(name))
            self.dlg.tableWidget.setItem(index,1,
                                QTableWidgetItem(str(age)))
            self.dlg.tableWidget.setItem(index,2,
                                QTableWidgetItem(birth))
            index += 1

app = QApplication( sys.argv )
dlg = MyDlg()
app.exec() #무한loop 큐메모리 감시(윈도우종료시)







