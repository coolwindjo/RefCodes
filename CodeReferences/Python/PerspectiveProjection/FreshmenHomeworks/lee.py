# ADAS ED Daesik Lee
import matplotlib.pyplot as plt
import re
import numpy as np
import xml.etree.ElementTree as ET   
import math

def isfloat(value):
    try:
        float(value)
        return True
    except ValueError:
        return False

# Read txt file and parsing
coord_fname = "world_model_x+5.txt"
lrs = []
for line in open(coord_fname):
    li = line.strip()
    if not li.startswith("#"):
        for l in re.split(',| ', li):
            lrs.append(l)

lrs = np.array(lrs, dtype='float64')
lrs = lrs.reshape((18, 6))
lrs = np.transpose(lrs)

# Define lines using given points
line_s = lrs[:3, :10]
line_sh = np.append(line_s, np.ones((1, 10)), axis=0)
line_e = lrs[3:, :10]
line_eh = np.append(line_e, np.ones((1, 10)), axis=0)

# Define rectangles using given points
rect_1 = lrs[:3, 10:]
rect_2 = lrs[3:, 10:]

rect_ll = np.minimum(rect_1, rect_2)
rect_uu = np.maximum(rect_1, rect_2)
rect_lu = np.append(rect_ll[:2,:], rect_uu[2:3,:], axis=0)
rect_ul = np.append(rect_uu[:2,:], rect_ll[2:3,:], axis=0)

rect_llh = np.append(rect_ll, np.ones((1, 8)), axis=0)
rect_uuh = np.append(rect_uu, np.ones((1, 8)), axis=0)
rect_luh = np.append(rect_lu, np.ones((1, 8)), axis=0)
rect_ulh = np.append(rect_ul, np.ones((1, 8)), axis=0)

# Read xml file and parsing
fc = open("Calibration.xml", 'r')
root = ET.fromstring(fc.read())
params = {}
for p in root.iter('parameter'):
    if isfloat(p.attrib['value']):
        params[p.attrib['name']] = float(p.attrib['value'])

fv = open("VehicleSpec.xml", 'r', encoding='utf8')
root = ET.fromstring(fv.read())
v_params = {}
for p in root.iter('parameter'):
    if isfloat(p.attrib['value']):
        v_params[p.attrib['name']] = float(p.attrib['value'])

# Vehicle to Calibration
RT_V2Cal = np.linalg.inv(np.array([[1, 0, 0, v_params['fWheelbase']],
                                   [0, 1, 0, 0],
                                   [0, 0, 1, v_params['fTireRadius']],
                                   [0, 0, 0, 1]]))

Proj_V2Cal = np.array([[-1, 0, 0, 0],
                       [0, -1, 0, 0],
                       [0, 0, 1, 0],
                       [0, 0, 0, 1]])

# Calibration to Camera    
roll = math.radians(params['fCameraMountPose_roll_factory'])
pitch = math.radians(params['fCameraMountPose_pitch_factory'])
yaw = math.radians(params['fCameraMountPose_yaw_factory'])

R_Cal2Cam_roll = np.array([[1, 0, 0, 0],
                            [0, np.cos(roll), -np.sin(roll), 0],
                            [0, np.sin(roll), np.cos(roll), 0],
                            [0, 0, 0, 1]])

R_Cal2Cam_pitch = np.array([[np.cos(pitch), 0, np.sin(pitch), 0],
                             [0, 1, 0, 0],
                             [-np.sin(pitch)+0, 0, np.cos(pitch), 0],
                             [0, 0, 0, 1]])   

R_Cal2Cam_yaw = np.array([[np.cos(yaw), -np.sin(yaw), 0, 0],
                            [np.sin(yaw), np.cos(yaw), 0, 0],
                            [0, 0, 1, 0],
                            [0, 0, 0, 1]])   

T_Cal2Cam = np.array([[1, 0, 0, params['fCameraMountPose_x_factory']],
                    [0, 1, 0, params['fCameraMountPose_y_factory']],
                    [0, 0, 1, params['fCameraMountPose_z_factory']],
                    [0, 0, 0, 1]])
    
RT_Cal2Cam = np.linalg.inv(np.dot(T_Cal2Cam, np.dot(R_Cal2Cam_yaw, np.dot(R_Cal2Cam_pitch, R_Cal2Cam_roll))))

Proj_Cal2Forward = Proj_V2Cal

Proj_Forward2Cam = np.array([[0, -1, 0, 0],
                         [0, 0, -1, 0],
                         [1, 0, 0, 0],
                         [0, 0, 0, 1]])

# Intrinsic Matrix
Cam2Img = np.array([[params['fFocallengthU_factory'], 0, params['fOpticalCenterU_factory'], 0],
                  [0, params['fFocallengthV_factory'], params['fOpticalCenterV_factory'], 0],
                  [0, 0, 1, 0]])         

# Homography    
H = np.dot(Cam2Img, np.dot(Proj_Forward2Cam, np.dot(Proj_Cal2Forward, np.dot(RT_Cal2Cam, np.dot(Proj_V2Cal, RT_V2Cal)))))


# Project from vehicle to image coordinate
proj_line_sh = np.dot(H, line_sh)
proj_line_eh = np.dot(H, line_eh)
proj_rect_llh = np.dot(H, rect_llh)
proj_rect_uuh = np.dot(H, rect_uuh)
proj_rect_luh = np.dot(H, rect_luh)
proj_rect_ulh = np.dot(H, rect_ulh)

# Divided by scale 
proj_line_s = proj_line_sh / proj_line_sh[-1,:]
proj_line_e = proj_line_eh / proj_line_eh[-1,:]
proj_rect_ll = proj_rect_llh / proj_rect_llh[-1,:]
proj_rect_uu = proj_rect_uuh / proj_rect_uuh[-1,:]
proj_rect_lu = proj_rect_luh / proj_rect_luh[-1,:]
proj_rect_ul = proj_rect_ulh / proj_rect_ulh[-1,:]

plt.figure()
ax = plt.gca()
ax.set_xlim([0, 1280])
ax.set_ylim([0, 720])
ax.invert_yaxis()
for i in range(10):
    plt.plot([proj_line_s[0, i], proj_line_e[0, i]], 
             [proj_line_s[1, i], proj_line_e[1, i]], 
             color='k', linestyle='-', linewidth=2)

for i in range(8):
    plt.plot([proj_rect_ll[0, i], proj_rect_lu[0, i]], 
             [proj_rect_ll[1, i], proj_rect_lu[1, i]], 
             color='k', linestyle='-', linewidth=2)
    plt.plot([proj_rect_lu[0, i], proj_rect_uu[0, i]], 
             [proj_rect_lu[1, i], proj_rect_uu[1, i]], 
             color='k', linestyle='-', linewidth=2)
    plt.plot([proj_rect_uu[0, i], proj_rect_ul[0, i]], 
             [proj_rect_uu[1, i], proj_rect_ul[1, i]], 
             color='k', linestyle='-', linewidth=2)
    plt.plot([proj_rect_ul[0, i], proj_rect_ll[0, i]], 
             [proj_rect_ul[1, i], proj_rect_ll[1, i]], 
             color='k', linestyle='-', linewidth=2)

plt.show()
