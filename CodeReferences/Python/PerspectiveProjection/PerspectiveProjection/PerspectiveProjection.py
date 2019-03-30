# -*- coding: utf-8 -*-
## @package Perspective Projection

import sys

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QApplication, QWidget, QLCDNumber, QSlider, QVBoxLayout)
from PyQt5.QtWidgets import QMainWindow
from PyQt5 import uic

##################
# Configurations #
##################
UI_FILE = "main_window.ui"
# Get the x, y limits
IMAGE_WIDTH = 1280
IMAGE_HEIGHT = 720
# Implementation
form_class = uic.loadUiType(UI_FILE)[0]

class TuningPanel(QWidget):
    def __init__(self, **kwargs):
        super(TuningPanel, self).__init__(**kwargs)
        self.initUI()

    def initUI(self):

        self.get_input_and_parameters()
        lcd = QLCDNumber(self)
        self.sld = QSlider(Qt.Horizontal, self)

        vbox = QVBoxLayout()
        vbox.addWidget(lcd)
        vbox.addWidget(self.sld)

        self.setLayout(vbox)
        self.sld.valueChanged.connect(lcd.display)
        self.sld.valueChanged.connect(self.draw_forward_scene)
        
        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Signal & slot')
        self.show()

        return
 
    def btn_clicked(self):
        return

    def get_input_and_parameters(self):
        import fileinput

        try:
            fi = fileinput.FileInput()
            (self.linesX, self.linesY, self.linesZ, 
                self.rectsX, self.rectsY, self.rectsZ) = fi.read_world_model_from_txt("world_model_x+5.txt")
            self.calibration_parameters, self.front_axis_height = fi.read_input_parameters_from_xml("Calibration.xml")

        except :
            print("[Error] Unexpected error at get_input_and_parameters().", sys.exc_info()[0])

        return

    def draw_forward_scene(self, d_roll):
        import homography
        import matplotlib.pyplot    as plt

        try:
            hm = homography.Homography()
            self.calibration_parameters.rotation.roll = d_roll
            H = hm.generate_3x4_homography_matrix(self.front_axis_height, self.calibration_parameters)
            
            for i in range(0, 10):
                (   lineX_computed, 
                    lineY_computed) = hm.compute_line_with_points_in_ICS_using_homography(
                                    H, self.linesX[i], self.linesY[i], self.linesZ[i])
                plt.plot(lineX_computed, lineY_computed, 'k-', lw=2)
            for i in range(0, 8):
                (   linesX_computed, 
                    linesY_computed)= hm.compute_rectangle_with_points_in_ICS_using_homography(
                                    H, self.rectsX[i], self.rectsY[i], self.rectsZ[i])
                for j in range(0, 4):
                    plt.plot(linesX_computed[j], linesY_computed[j], 'k-', lw=2)

            # Set the y limits making the maximum 5% greater
            plt.xlim(0, IMAGE_WIDTH)
            plt.ylim(0, IMAGE_HEIGHT)
            ax = plt.gca()
            ax.invert_yaxis()
            plt.draw()
            plt.show()
        except :
            print("[Error] Unexpected error at draw_forward_scene().", sys.exc_info()[0])
            print("len(H) = " + str(len(H)))

        return


if __name__ == '__main__':
    app = QApplication(sys.argv)
    t_panel = TuningPanel()
    t_panel.show()
    app.exec_()