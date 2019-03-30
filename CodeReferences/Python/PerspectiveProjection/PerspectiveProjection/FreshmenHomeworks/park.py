#https://docs.python.org/2/library/x#ml.etree.elementtree.html
import xml.etree.ElementTree as ET

#http://matplotlib.org/users/pyplot_tutorial.html
import matplotlib.pyplot as plt

import sys
import re
import numpy as np
import math

#https://docs.scipy.org/doc/numpy/reference/generated/numpy.linalg.inv.html
from numpy.linalg import inv


import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class Vehicle:
    fWheelbase = 0
    fTireRadius = 0

class Camera:
    x = 0
    y = 0
    z = 0
    roll = 0
    pitch = 0
    yaw = 0
    focal_U = 0
    focal_V = 0
    CenterU = 0
    CenterV = 0

class Point:
    def __init__(self, p):
        self.x = p[0]
        self.y = p[1]
        self.z = p[2]

class Line:
    def __init__(self, pts):
        #self.p1 = [int(pts[0]), int(pts[1]),int(pts[2])]
        #self.p2 = [int(pts[3]), int(pts[4]),int(pts[5])]
        self.p1 = Point([int(pts[0]), int(pts[1]),int(pts[2])])
        self.p2 = Point([int(pts[3]), int(pts[4]),int(pts[5])])



FLAG_LINE = 1
FLAG_RECT = 2
LineList=[]
cam = Camera()
veh = Vehicle()

def main():
    ReadWorldModel()
    ReadCameraParameter()
    ReadVehicleParameter()
    DrawImage()
    

def DrawImage():
    P = np.array([  [0, -1,  0, 0],\
                    [0,  0, -1, 0],\
                    [1,  0,  0, 0],\
                    [0,  0,  0, 1]])

    Kn = np.array([[cam.focal_U, 0,             cam.CenterU, 0],\
                    [0,          cam.focal_V,   cam.CenterV, 0],\
                    [0,          0,             1, 0]])
    

    R = makeMatrixV2C(veh.fWheelbase+cam.x, cam.y, veh.fTireRadius+cam.z, 3, cam.pitch, 0)

    PRT = np.dot(P, R)
    KPRT = np.dot(Kn, PRT)
    
    
    fig2 = plt.figure(2)
    ax = fig2.add_subplot(111, projection='3d')
    for i in LineList:
        ax.plot([i.p1.x, i.p2.x], [i.p1.y, i.p2.y], zs=[i.p1.z, i.p2.z])           
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    plt.gca().invert_xaxis()
    plt.gca().invert_yaxis()
    mngr = plt.get_current_fig_manager()
    mngr.window.setGeometry(50,50,640, 545)

    fig3 = plt.figure(3)
    for i in LineList:
        t1 = np.dot(KPRT, np.array([i.p1.x, i.p1.y, i.p1.z, 1]).T)
        t2 = np.dot(KPRT, np.array([i.p2.x, i.p2.y, i.p2.z, 1]).T)
        plt.plot([t1[0]/t1[2], t2[0]/t2[2]], [t1[1]/t1[2], t2[1]/t2[2]])  

    ax = plt.gca()
    ax.set_xlim([0,1280])
    ax.set_ylim([0, 720])

    ax.invert_yaxis()

    plt.show()
    Axes3D.plot()


#make Matrix(Vehicle to Camera)
#roll, pitch, yaw coordination is calibration coordinate
#In function, transform to vehicle coorinate
#input : tx, ty, tz ~ meter
#input : roll, pitch, yaw ~ degree
def makeMatrixV2C(tx, ty, tz, roll, pitch, yaw):
    #transform calibration coordinate to vehicle coordinate
    pitch = -pitch
    roll = -roll

    sinRoll = math.sin(roll*math.pi/180)
    cosRoll = math.cos(roll*math.pi/180)
    sinPitch = math.sin(pitch*math.pi/180)
    cosPitch = math.cos(pitch*math.pi/180)
    sinYaw = math.sin(yaw*math.pi/180)
    cosYaw = math.cos(yaw*math.pi/180)

    T = np.array([  [1,  0,  0, tx],\
                    [0,  1,  0, ty],\
                    [0,  0,  1, tz],\
                    [0,  0,  0,  1]])

    R_roll =  np.array([  [1,        0,         0,  0],\
                          [0,  cosRoll,  -sinRoll,  0],\
                          [0,  sinRoll,   cosRoll,  0],\
                          [0,        0,         0,  1]])

    R_pitch =  np.array([  [ cosPitch,        0,         sinPitch,  0],\
                           [        0,        1,                0,  0],\
                           [-sinPitch,        0,         cosPitch,  0],\
                           [        0,        0,                0,  1]])

    R_yaw =  np.array([   [cosYaw, -sinYaw,   0,  0],\
                          [sinYaw,  cosYaw,   0,  0],\
                          [     0,       0,   1,  0],\
                          [     0,       0,   0,  1]])

    R = inv(np.dot(np.dot(np.dot(T, R_yaw), R_pitch), R_roll))

    return R


def ReadVehicleParameter():
    tree = ET.parse('VehicleSpec.xml')
    root = tree.getroot()
    for node in root.iter('parameter'):
        if node.get('name') == "fWheelbase" :
            veh.fWheelbase = float(node.get('value'))
        elif node.get('name') == "fTireRadius":
            veh.fTireRadius = float(node.get('value'))

def ReadWorldModel():
    try:
        f = open('world_model_x+5.txt', 'r')
        f.readline() #remove first line
        for line in f:
            #print (line)
            if line == "# Lines (2 points)\n":
                flag = FLAG_LINE
            elif line == "# Rectangles (2 points)\n":
                flag = FLAG_RECT
            else:
                read_number(line, flag)
        f.close()
    except IOError:
        print("Cannot open world_model File")
        sys.exit(1)

def ReadCameraParameter():
    tree = ET.parse('Calibration.xml')
    root = tree.getroot()
    for node in root.iter('parameter'):
        if node.get('name') == "fCameraMountPose_x_factory" :
            cam.x = float(node.get('value'))
        elif node.get('name') == "fCameraMountPose_y_factory":
            cam.y = float(node.get('value'))
        elif node.get('name') == "fCameraMountPose_z_factory":
            cam.z = float(node.get('value'))
        elif node.get('name') == "fCameraMountPose_roll_factory":
            cam.roll = float(node.get('value'))
        elif node.get('name') == "fCameraMountPose_pitch_factory":
            cam.pitch = float(node.get('value'))
        elif node.get('name') == "fCameraMountPose_yaw_factory":
            cam.yaw = float(node.get('value'))
        elif node.get('name') == "fFocallengthU_factory":
            cam.focal_U = float(node.get('value'))
        elif node.get('name') == "fFocallengthV_factory":
            cam.focal_V = float(node.get('value'))
        elif node.get('name') == "fOpticalCenterU_factory":
            cam.CenterU = float(node.get('value'))
        elif node.get('name') == "fOpticalCenterV_factory":
            cam.CenterV = float(node.get('value'))
        else:
            print ("name is not found")

    #transform calibration coordinate to vehicle coordinate
    #calibaration coordination and vehicle coordinate differ in 180 degree
    R = makeMatrixV2C(0,0,0,0,0,180)
    PointInVehicle = np.dot(R, np.array([[cam.x, cam.y, cam.z, 1]]).T)

    cam.x = PointInVehicle[0]
    cam.y = PointInVehicle[1]
    cam.z = PointInVehicle[2]



def read_number(line, flag):
    if flag == FLAG_LINE:
        str = re.split('[, ]', line)
        LineList.append(Line(str))
    elif flag == FLAG_RECT:
        str = re.split('[, ]', line)
        if(str[0] == str[3]):
            p1 = [str[0], str[1], str[2]]
            p2 = [str[0], str[4], str[2]]
            p3 = [str[3], str[4], str[5]]
            p4 = [str[0], str[1], str[5]]

            LineList.append(Line(p1+p2))
            LineList.append(Line(p2+p3))
            LineList.append(Line(p3+p4))
            LineList.append(Line(p4+p1))
        elif(str[1] == str[4]):
            p1 = [str[0], str[1], str[2]]
            p2 = [str[3], str[1], str[2]]
            p3 = [str[3], str[4], str[5]]
            p4 = [str[0], str[1], str[5]]

            LineList.append(Line(p1+p2))
            LineList.append(Line(p2+p3))
            LineList.append(Line(p3+p4))
            LineList.append(Line(p4+p1))
        elif(str[2] == str[5]):
            print ("not implemented")
        else:
            print ("not implemented") 


if __name__== "__main__": main()




