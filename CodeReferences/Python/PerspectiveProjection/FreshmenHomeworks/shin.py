#--------------------------------------------------------
#       Tip
#--------------------------------------------------------
#Road coordinate : any point which is just on a road.
#Vehicle coordinate : Vehicle Back axle
#Calibration coordinate : Vehicle Front axle
#--------------------------------------------------------

import matplotlib.pyplot as plt
import numpy as np
from lxml import etree
from io import StringIO, BytesIO
import math

total = []

f = open('world_model_x+5.txt','rt')
lines = f.readlines()

for line in lines: 
    total.append(line)

Vehicle_pLine = []    #Total Lines from txt file
Vehicle_pRec = []    #Total Rectangle from txt file

#for Line - read Points
for i in range(2,12):
    a = total[i].split(',')
    b = a[2].split(' ')

    del a[2]
    a.insert(2,b[0])
    a.insert(3,b[1])

    Vehicle_pLine_temp = []
    for j in range(0,6):
        c = int(a[j])
        Vehicle_pLine_temp.append(c)
    Vehicle_pLine.append(Vehicle_pLine_temp)

#for Rectangle - read Points
for i in range(13,21):
    a = total[i].split(',')
    b = a[2].split(' ')

    del a[2]
    a.insert(2,b[0])
    a.insert(3,b[1])

    Vehicle_pRec_temp = []
    for j in range(0,6):
        c = int(a[j])
        Vehicle_pRec_temp.append(c)
    Vehicle_pRec.append(Vehicle_pRec_temp)

#Rectangle to Lines
for i in range(0, len(Vehicle_pRec)):
    if (Vehicle_pRec[i][0] == Vehicle_pRec[i][3]):
        a = [ Vehicle_pRec[i][0], Vehicle_pRec[i][1], Vehicle_pRec[i][2], Vehicle_pRec[i][3], Vehicle_pRec[i][1], Vehicle_pRec[i][5] ]
        b = [ Vehicle_pRec[i][0], Vehicle_pRec[i][1], Vehicle_pRec[i][5], Vehicle_pRec[i][3], Vehicle_pRec[i][4], Vehicle_pRec[i][5] ]
        c = [ Vehicle_pRec[i][0], Vehicle_pRec[i][4], Vehicle_pRec[i][5], Vehicle_pRec[i][3], Vehicle_pRec[i][4], Vehicle_pRec[i][2] ]
        d = [ Vehicle_pRec[i][0], Vehicle_pRec[i][4], Vehicle_pRec[i][2], Vehicle_pRec[i][3], Vehicle_pRec[i][1], Vehicle_pRec[i][2] ]
        Vehicle_pLine.append(a)
        Vehicle_pLine.append(b)
        Vehicle_pLine.append(c)
        Vehicle_pLine.append(d)
    if (Vehicle_pRec[i][1] == Vehicle_pRec[i][4]):
        a = [ Vehicle_pRec[i][0], Vehicle_pRec[i][1], Vehicle_pRec[i][2], Vehicle_pRec[i][0], Vehicle_pRec[i][4], Vehicle_pRec[i][5] ]
        b = [ Vehicle_pRec[i][0], Vehicle_pRec[i][1], Vehicle_pRec[i][5], Vehicle_pRec[i][3], Vehicle_pRec[i][4], Vehicle_pRec[i][5] ]
        c = [ Vehicle_pRec[i][3], Vehicle_pRec[i][1], Vehicle_pRec[i][5], Vehicle_pRec[i][3], Vehicle_pRec[i][4], Vehicle_pRec[i][2] ]
        d = [ Vehicle_pRec[i][3], Vehicle_pRec[i][1], Vehicle_pRec[i][2], Vehicle_pRec[i][0], Vehicle_pRec[i][4], Vehicle_pRec[i][2] ]
        Vehicle_pLine.append(a)
        Vehicle_pLine.append(b)
        Vehicle_pLine.append(c)
        Vehicle_pLine.append(d)
    if (Vehicle_pRec[i][2] == Vehicle_pRec[i][5]):
        a = [ Vehicle_pRec[i][0], Vehicle_pRec[i][1], Vehicle_pRec[i][2], Vehicle_pRec[i][0], Vehicle_pRec[i][4], Vehicle_pRec[i][5] ]
        b = [ Vehicle_pRec[i][0], Vehicle_pRec[i][4], Vehicle_pRec[i][2], Vehicle_pRec[i][3], Vehicle_pRec[i][4], Vehicle_pRec[i][5] ]
        c = [ Vehicle_pRec[i][3], Vehicle_pRec[i][4], Vehicle_pRec[i][2], Vehicle_pRec[i][3], Vehicle_pRec[i][1], Vehicle_pRec[i][5] ]
        d = [ Vehicle_pRec[i][3], Vehicle_pRec[i][1], Vehicle_pRec[i][2], Vehicle_pRec[i][0], Vehicle_pRec[i][1], Vehicle_pRec[i][5] ]
        Vehicle_pLine.append(a)
        Vehicle_pLine.append(b)
        Vehicle_pLine.append(c)
        Vehicle_pLine.append(d)



#-------------------------------------------------------------------------
#           read XML - Vehicle coordinate to Calibration coordiante
#-------------------------------------------------------------------------
#read XML file - Vehicle to Calibration
xmlFile2 = "VehicleSpec.xml"
tree2 = etree.parse(xmlFile2)
root2 = tree2.getroot()
Parameters2 = root2.getchildren()[1]
Param2 = Parameters2.findall('parameter')

#Parameter - Vehicle to Calibration
pVtoCal = [ [None], [0,1,0,0], [None], [0,0,0,1] ]
yaw = math.radians(180)
pVtoCal_yaw = [ [math.cos(yaw),-math.sin(yaw),0,0], [math.sin(yaw),math.cos(yaw),0,0], [0,0,1,0], [0,0,0,1] ]


for Parameter2 in Param2:
    if "name" in Parameter2.keys():
        #Extrinsic Parameter
        if Parameter2.attrib['name'] == "fWheelbase" :
            values = Parameter2.attrib['value']
            pVtoCal[0] = [ 1, 0, 0, float(values) ]
        if Parameter2.attrib['name'] == "fTireRadius" :
            values = Parameter2.attrib['value']
            pVtoCal[2] = [ 0, 0, 1, float(values) ]
#-------------------------------------------------------------------------


#-------------------------------------------------------------------------
#           read XML - Calibration to Image
#-------------------------------------------------------------------------
#read XML file
xmlFile = "Calibration.xml"
tree = etree.parse(xmlFile)
root = tree.getroot()
Parameters = root.getchildren()[1]
Param = Parameters.findall('parameter')

#For Extrinsic parameter - The others
pTrans = [ [None], [None], [None], [0,0,0,1] ]
pRot_roll = [ [None], [None], [None], [0,0,0,1] ]
pRot_pitch = [ [None], [None], [None], [0,0,0,1] ]
pRot_yaw = [ [None], [None], [None], [0,0,0,1] ]

#For Intrinsic parameter
OpticalCenter_u = 0
OpticalCenter_v = 0
Focallength_u = 0
Focallength_v = 0

for Parameter in Param:
    if "name" in Parameter.keys():
        #Extrinsic Parameter
        if Parameter.attrib['name'] == "fCameraMountPose_x_factory" :
            values = Parameter.attrib['value']
            pTrans[0] = [ 1, 0, 0, (float(values)) ]
        if Parameter.attrib['name'] == "fCameraMountPose_y_factory" :
            values = Parameter.attrib['value']
            pTrans[1] = [ 0, 1, 0, float(values) ]
        if Parameter.attrib['name'] == "fCameraMountPose_z_factory" :
            values = Parameter.attrib['value']
            pTrans[2] = [ 0, 0, 1, float(values) ]
        if Parameter.attrib['name'] == "fCameraMountPose_roll_factory" :
            values = Parameter.attrib['value']
            roll = float(values)
            d_roll = math.radians(roll)
            pRot_roll[0] = [ 1, 0, 0, 0 ]
            pRot_roll[1] = [ 0, math.cos(d_roll), -math.sin(d_roll), 0 ]
            pRot_roll[2] = [ 0 , math.sin(d_roll), math.cos(d_roll), 0 ]
        if Parameter.attrib['name'] == "fCameraMountPose_pitch_factory" :
            values = Parameter.attrib['value']
            pitch = float(values)
            d_pitch = math.radians(pitch)
            pRot_pitch[0] = [ math.cos(d_pitch), 0, math.sin(d_pitch), 0 ]
            pRot_pitch[1] = [ 0, 1, 0, 0 ]
            pRot_pitch[2] = [ -math.sin(d_pitch), 0, math.cos(d_pitch), 0 ]
        if Parameter.attrib['name'] == "fCameraMountPose_yaw_factory" :
            values = Parameter.attrib['value']
            yaw = float(values)
            d_yaw = math.radians(yaw)
            pRot_yaw[0] = [ math.cos(d_yaw), -math.sin(d_yaw),0, 0 ]
            pRot_yaw[1] = [ math.sin(d_yaw), math.cos(d_yaw), 0, 0 ]
            pRot_yaw[2] = [ 0, 0, 1, 0 ]
        #Intrinsic Parameter
        if Parameter.attrib['name'] == "fOpticalCenterU_factory" :
            values = Parameter.attrib['value']
            OpticalCenter_u = float(values)
        if Parameter.attrib['name'] == "fOpticalCenterV_factory" :
            values = Parameter.attrib['value']
            OpticalCenter_v = float(values)
        if Parameter.attrib['name'] == "fFocallengthU_factory" :
            values = Parameter.attrib['value']
            Focallength_u = float(values)
        if Parameter.attrib['name'] == "fFocallengthV_factory" :
            values = Parameter.attrib['value']
            Focallength_v = float(values)
#-------------------------------------------------------------------------

#Vehicle to Calibration
pVtoCal = np.dot(pVtoCal, pVtoCal_yaw)
pVtoCal = np.linalg.inv(pVtoCal)

#Extrinsic
pTrans = np.dot(pTrans, pRot_yaw)
pTrans = np.dot(pTrans, pRot_pitch)
pTrans = np.dot(pTrans, pRot_roll)
pTrans = np.linalg.inv(pTrans)

#Projection
pProjection = [ [0, -1, 0, 0], [0, 0, -1, 0], [1, 0, 0, 0] ]

#Intrinsic
pIntrinsic = [ [Focallength_u, 0, OpticalCenter_u], [0, Focallength_v, OpticalCenter_v], [0,0,1] ]

Image_Total_Lines = []

for i in range( 0, len(Vehicle_pLine) ):
    
    #Get line
    V_point1 = [ [Vehicle_pLine[i][0]], [Vehicle_pLine[i][1]], [Vehicle_pLine[i][2]], [1] ]
    V_point2 = [ [Vehicle_pLine[i][3]], [Vehicle_pLine[i][4]], [Vehicle_pLine[i][5]], [1] ]

    #Vehicle to Calibration
    Cal_point1 = np.dot(pVtoCal,V_point1)           #Calibration coordinate
    Cal_point2 = np.dot(pVtoCal,V_point2)

    #Extrinsic
    C_point1 = np.dot(pTrans,Cal_point1)            #Camera point
    C_point2 = np.dot(pTrans,Cal_point2)

    #Projection
    C_point1 = np.dot(np.linalg.inv(pVtoCal_yaw),C_point1)
    C_point2 = np.dot(np.linalg.inv(pVtoCal_yaw),C_point2)
    P_point1 = np.dot(pProjection, C_point1)
    P_point2 = np.dot(pProjection, C_point2)

    #Intrinsic
    I_point1 = np.dot(pIntrinsic,P_point1)          #Image point
    I_point2 = np.dot(pIntrinsic,P_point2)

    depth1 = I_point1[2]
    depth2 = I_point2[2]

    I_point1 = I_point1 / depth1
    I_point2 = I_point2 / depth2

    Image_Total_Lines.append([I_point1[0], I_point1[1], 1, I_point2[0], I_point2[1], 1])

#Plot Line - 2D
a = np.array(Image_Total_Lines)
plt.plot( a[:,::3].T, a[:, 1::3].T, 'k')
plt.xlim(0, 1280)
plt.ylim(720, 0)
plt.show()