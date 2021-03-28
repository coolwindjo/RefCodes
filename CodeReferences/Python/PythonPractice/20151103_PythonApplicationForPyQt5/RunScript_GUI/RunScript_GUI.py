# -*- coding: utf-8 -*-
##  @package Run script GUI
# Documentation for RunScript_GUI
#
# More details.

##################
# Configurations #
##################
UI_FILE = "RunScript_GUI.ui"
SCRIPT_FILE = "script.bat"

import os
import sys
import subprocess

from PyQt5.QtWidgets import *
from PyQt5 import uic

form_class = uic.loadUiType(UI_FILE)[0]

def invoke_cmd(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE,
       stderr=subprocess.PIPE)
    out, err = p.communicate()    
    if p.returncode != 0:
        print ("Failed to execute cmd" + cmd)
        print (err)        
        sys.exit(p.returncode)
    else :
        return out       

def run_script():
    
    try:
        cmd = [SCRIPT_FILE]
        out = invoke_cmd(cmd)
    except:
        print("[Error] Unexpected error at run_script().", sys.exc_info()[0])

    return out

class MyWindow(QMainWindow, form_class):
    def __init__(self):
        super(MyWindow, self).__init__()
        self.setupUi(self)
        self.pushButtonRunScript.clicked.connect(self.btn_clicked)

    def btn_clicked(self):
        run_script()
        QMessageBox.about(self, "message", "Running...")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()