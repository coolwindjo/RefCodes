# -*- coding: utf-8 -*-
##  @package Run script GUI
# Documentation for RunScript_GUI
#
# More details.

import sys
import subprocess

from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMessageBox
from PyQt5 import uic

##################
# Configurations #
##################
UI_FILE = "main_window.ui"
YUV_SCRIPT          = '''cmd /c echo y | PSTools\plink.exe -pw root root@192.168.0.16 "cd /opt/bin/; sh dispmodsel.sh color"'''
SGM_SCRIPT          = '''cmd /c echo y | PSTools\plink.exe -pw root root@192.168.0.16 "cd /opt/bin/; sh dispmodsel.sh sgm"'''
OPTICAL_FLOW_SCRIPT = '''cmd /c echo y | PSTools\plink.exe -pw root root@192.168.0.16 "cd /opt/bin/; sh dispmodsel.sh of"'''

# Implementation
form_class = uic.loadUiType(UI_FILE)[0]

def invoke_cmd(cmd):
    try:
        p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()    
        if p.returncode != 0:
            p.stderr.close()
            out = err
        else:
            pass
    except:
        print("[Error] Unexpected error at invoke_cmd().", sys.exc_info()[0])
    return out

def select_yuv_channel():
    
    try:
        cmd = YUV_SCRIPT
        out = invoke_cmd(cmd)
    except:
        print("[Error] Unexpected error at select_yuv_channel().", sys.exc_info()[0])

    return out       

def select_sgm_channel():
    
    try:
        cmd = SGM_SCRIPT
        out = invoke_cmd(cmd)
    except:
        print("[Error] Unexpected error at select_sgm_channel().", sys.exc_info()[0])

    return out       

def select_optical_flow_channel():
    
    try:
        cmd = OPTICAL_FLOW_SCRIPT
        out = invoke_cmd(cmd)
    except:
        print("[Error] Unexpected error at select_optical_flow_channel().", sys.exc_info()[0])

    return out       


class MyWindow(QMainWindow, form_class):
    def __init__(self):
        super(MyWindow, self).__init__()
        self.setupUi(self)
        self.pushButtonYUV.clicked.connect(self.yuv_btn_clicked)
        self.pushButtonSGM.clicked.connect(self.sgm_btn_clicked)
        self.pushButtonOpticalFlow.clicked.connect(self.optical_flow_btn_clicked)

    def yuv_btn_clicked(self):
        out_message = select_yuv_channel()
        if out_message.lower().find("error",0,15) != -1:
            QMessageBox.about(self, "message", out_message)
        else:
            pass
        return


    def sgm_btn_clicked(self):
        out_message = select_sgm_channel()
        if out_message.lower().find("error",0,15) != -1:
            QMessageBox.about(self, "message", out_message)
        else:
            pass
        return

    def optical_flow_btn_clicked(self):
        out_message = select_optical_flow_channel()
        if out_message.lower().find("error",0,15) != -1:
            QMessageBox.about(self, "message", out_message)
        else:
            pass
        return


if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()