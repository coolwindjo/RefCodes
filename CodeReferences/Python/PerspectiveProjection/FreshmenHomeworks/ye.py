import matplotlib.pyplot as plt
import numpy as np
from lxml import etree
import math

input_folder='/'
world_model_file='world_model_x+5.txt'
vehicle_spec_file='VehicleSpec.xml'
calibration_file='Calibration.xml'

################################ define a function ################################
def foward_transformation(t_x, t_y, t_z, roll, pitch, yaw):
    transformation_matrix = np.identity(4)
    # roll
    rotation_roll=np.matrix(((1, 0, 0, 0),
                            (0, math.cos(roll*math.pi/180.0), -math.sin(roll*math.pi/180.0), 0),
                            (0, math.sin(roll*math.pi/180.0), math.cos(roll*math.pi/180.0), 0),
                            (0, 0, 0, 1)))
    # pitch
    rotation_pitch=np.matrix(((math.cos(pitch*math.pi/180.0), 0, math.sin(pitch*math.pi/180.0), 0),
                            (0, 1, 0, 0),
                            (-math.sin(pitch*math.pi/180.0), 0, math.cos(pitch*math.pi/180.0), 0),
                            (0, 0, 0, 1)))
    # yaw
    rotation_yaw=np.matrix(((math.cos(yaw*math.pi/180.0), -math.sin(yaw*math.pi/180.0), 0, 0),
                            (math.sin(yaw*math.pi/180.0), math.cos(yaw*math.pi/180.0), 0, 0),
                            (0, 0, 1, 0),
                            (0, 0, 0, 1)))
    # translation
    translation_mat=np.matrix(((1, 0, 0, t_x),
                               (0, 1, 0, t_y),
                               (0, 0, 1, t_z),
                               (0, 0, 0, 1)))
    return np.linalg.inv(translation_mat * rotation_yaw * rotation_pitch * rotation_roll)


################################ parsing data ################################
## parsing model file
flag=0
line_list=[]
rectangle_list=[]
rect_line_list = []
try:
    f=open(world_model_file)
    line=f.readline()
    while line !='':
        if line=='# Lines (2 points)\n':
            flag=1
            line=f.readline()
            continue 
        if line=='# Rectangles (2 points)\n':
            flag=2
            line=f.readline()
            continue

        if flag==1:
            splited_line = line.replace(' ', ',').replace('\n', '').split(',')
            line_list.append(list(map(float, splited_line)))
        if flag==2:
            splited_line = line.replace(' ', ',').replace('\n', '').split(',')
            rectangle_list.append(list(map(float, splited_line)))
        line=f.readline()
    f.close()
except IOError:
    print('error')
line_list = np.asarray(line_list)
rectangle_list = np.asarray(rectangle_list)
# create four lines from given two points(rectangular)
for rect in rectangle_list:
    same_index = -1
    diff_value = []
    for index in range(len(rect)-3):
        if rect[index] == rect[index+3]:
            same_index = index
        else:
            diff_value.append([rect[index], rect[index+3]])
    
    diff_value = np.transpose(diff_value)
    rect_points = []
    for index in [[0, 0], [0, 1], [1, 1], [1, 0]]:
        rect_point = [diff_value[index[0]][0], diff_value[index[1]][1]]
        rect_point = np.insert(rect_point, [same_index], [rect[same_index]])
        rect_points.append(rect_point)

    for index in [[0, 1], [1, 2], [2, 3], [3, 0]]:
        rect_line_list.append(np.array([rect_points[index[0]], rect_points[index[1]]]).flatten())
rect_line_list = np.asarray(rect_line_list)

## parsing calibration file
tree = etree.parse(calibration_file)
root = tree.getroot()
param_table = root.find('parameterTable')
# intrinsic
focal_length_u = float(param_table.findall('parameter')[0].attrib['value'])
focal_length_v = float(param_table.findall('parameter')[1].attrib['value'])
optic_center_u = float(param_table.findall('parameter')[2].attrib['value'])
optic_center_v = float(param_table.findall('parameter')[3].attrib['value'])
# extrinsic
cam_pose_x = float(param_table.findall('parameter')[5].attrib['value'])
cam_pose_y = float(param_table.findall('parameter')[6].attrib['value'])
cam_pose_z = float(param_table.findall('parameter')[7].attrib['value'])
cam_pose_roll = float(param_table.findall('parameter')[8].attrib['value'])
cam_pose_pitch = float(param_table.findall('parameter')[9].attrib['value'])
cam_pose_yaw = float(param_table.findall('parameter')[10].attrib['value'])

## parsing vehicle spec file
tree = etree.parse(vehicle_spec_file)
root = tree.getroot()
param_table = root.find('parameterTable')
# intrinsic
wheel_base = float(param_table.findall('parameter')[6].attrib['value'])
tire_radius = float(param_table.findall('parameter')[11].attrib['value'])
### plot data
#plt.plot(line_list[:,[1,4]].T, line_list[:, [0,3]].T, 'r', label='data_a')
#plt.plot(rect_line_list[:,[1,4]].T, rect_line_list[:, [0,3]].T, 'r', label='data_a')
#plt.xlabel('y axis')
#plt.ylabel('x axis')
#plt.ylim(-41, 41)
#plt.xlim(-5, 5)
#plt.show()


################################ road to vehicle ################################
### transformation from road coordinate system to vehicle coordinate system
## make transformation matrix
road_to_vehicle = foward_transformation(wheel_base, 0, tire_radius, 0, 0, 0)
## apply the transform matrix
for i in line_list:
    i[0:3] = (road_to_vehicle * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (road_to_vehicle * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
for i in rect_line_list:
    i[0:3] = (road_to_vehicle * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (road_to_vehicle * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
### plot data
#plt.clf() #clears the entire current figure 
#plt.plot(line_list[:,[1,4]].T, line_list[:, [0,3]].T, 'r', label='data_a')
#plt.plot(rect_line_list[:,[1,4]].T, rect_line_list[:, [0,3]].T, 'r', label='data_a')
#plt.xlabel('y axis')
#plt.ylabel('x axis')
#plt.ylim(-41, 41)
#plt.xlim(-5, 5)
#plt.show()


################################ vehicle to calibration ################################
### transformation from vehicle coordinate system to calibration coordinate system
## make transformation matrix
vehicle_to_calibration = np.matrix(((-1, 0, 0, 0), (0, -1, 0, 0), (0, 0, 1, 0), (0, 0, 0, 1)))
#vehicle_to_calibration = foward_transformation(0, 0, 0, 0, 0, 180)
## apply the transform matrix
for i in line_list:
    i[0:3] = (vehicle_to_calibration * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (vehicle_to_calibration * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
for i in rect_line_list:
    i[0:3] = (vehicle_to_calibration * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (vehicle_to_calibration * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
### plot data
#plt.clf() #clears the entire current figure 
#plt.plot(line_list[:,[1,4]].T, line_list[:, [0,3]].T, 'r', label='data_a')
#plt.plot(rect_line_list[:,[1,4]].T, rect_line_list[:, [0,3]].T, 'r', label='data_a')
#plt.xlabel('y axis')
#plt.ylabel('x axis')
#plt.ylim(-41, 41)
#plt.xlim(-5, 5)
#plt.show()


################################ calibration to camera ################################
### transformation from calibration coordinate system to camera coordinate system
## make transformation matrix
cal_to_cam = foward_transformation(cam_pose_x, cam_pose_y, cam_pose_z, cam_pose_roll+3.0, cam_pose_pitch, cam_pose_yaw)
## apply transformation matrix
for i in line_list:
    i[0:3] = (cal_to_cam * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (cal_to_cam * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
for i in rect_line_list:
    i[0:3] = (cal_to_cam * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (cal_to_cam * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
### plot data
#plt.clf() #clears the entire current figure 
#plt.plot(line_list[:,[1,4]].T, line_list[:, [0,3]].T, 'r', label='data_a')
#plt.plot(rect_line_list[:,[1,4]].T, rect_line_list[:, [0,3]].T, 'r', label='data_a')
#plt.xlabel('y axis')
#plt.ylabel('x axis')
#plt.ylim(-41, 41)
#plt.xlim(-5, 5)
#plt.show()

################################ camera to projection ################################
### transformation from camera coordinate system to projection coordinate system
## make transformation matrix
cam_to_projec = np.matrix(((0, 1, 0, 0), (0, 0, -1, 0), (-1, 0, 0, 0), (0, 0, 0, 1)))
#cam_to_projec = foward_transformation(0, 0, 0, -90, -90, 0)
print(cam_to_projec)
## apply transformation matrix
for i in line_list:
    i[0:3] = (cam_to_projec * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (cam_to_projec * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
for i in rect_line_list:
    i[0:3] = (cam_to_projec * np.matrix(np.append(i[0:3], 1)).transpose())[0:3].transpose()
    i[3:6] = (cam_to_projec * np.matrix(np.append(i[3:6], 1)).transpose())[0:3].transpose()
### plot data
#plt.clf() #clears the entire current figure 
#plt.plot(line_list[:,[0,3]].T, line_list[:, [2,5]].T, 'r', label='data_a')
#plt.plot(rect_line_list[:,[0,3]].T, rect_line_list[:, [2,5]].T, 'r', label='data_a')
#plt.xlabel('x axis')
#plt.ylabel('z axis')
#plt.ylim(-41, 41)
#plt.xlim(-5, 5)
#plt.show()

################################ projection to image ################################
### transformation from projection coordinate system to image coordinate system
## make transformation matrix
cam_to_image = np.matrix(((focal_length_u, 0, optic_center_u, 0)
                  ,(0, focal_length_v, optic_center_v, 0)
                  ,(0, 0, 1, 0)
                  ,(0, 0, 0, 1)))
## apply transformation matrix
proj_line_list = [[0 for col in range(4)] for row in range(len(line_list))]
proj_rect_line_list = [[0 for col in range(4)] for row in range(len(rect_line_list))]
for line,proj_line in zip(line_list,proj_line_list):
    line[0:3] = (cam_to_image * np.matrix(np.append(line[0:3], 1)).transpose())[0:3].transpose()
    line[3:6] = (cam_to_image * np.matrix(np.append(line[3:6], 1)).transpose())[0:3].transpose()
    proj_line[0:2] = line[0:2]/line[2]
    proj_line[2:4] = line[3:5]/line[5]
for rect_line,proj_rect_line in zip(rect_line_list,proj_rect_line_list):
    rect_line[0:3] = (cam_to_image * np.matrix(np.append(rect_line[0:3], 1)).transpose())[0:3].transpose()
    rect_line[3:6] = (cam_to_image * np.matrix(np.append(rect_line[3:6], 1)).transpose())[0:3].transpose()
    proj_rect_line[0:2] = rect_line[0:2]/rect_line[2]
    proj_rect_line[2:4] = rect_line[3:5]/rect_line[5]
proj_line_list = np.asarray(proj_line_list)
proj_rect_line_list = np.asarray(proj_rect_line_list)
## plot data
plt.clf() #clears the entire current figure
plt.plot(proj_line_list[:,[0,2]].T, proj_line_list[:, [1,3]].T, 'r', label='data_a')
plt.plot(proj_rect_line_list[:,[0,2]].T, proj_rect_line_list[:, [1,3]].T, 'r', label='data_a')
plt.xlabel('u axis')
plt.ylabel('v axis')
plt.xlim(0,1280)
plt.ylim(0,720)
plt.gca().invert_yaxis()
plt.show()