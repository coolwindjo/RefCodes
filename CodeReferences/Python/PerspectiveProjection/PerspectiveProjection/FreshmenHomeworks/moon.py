import matplotlib.pyplot as plt
import numpy as np
import re 
import math as mt
from numpy.linalg import inv

#readling text file
file = open('world_model_x+5.txt', 'r')
#reading xml file
xmlFile = open('Calibration.xml', 'r')


param = []
select = 0
for line in xmlFile.readlines() :
   E_x = re.findall('value="(\d+.\d+.+)"', line)
   if(E_x and (not E_x[0].isalnum()) ) :  
     param.append(float(E_x[0]))

th_x, th_y, th_z = mt.radians(param[8]),  mt.radians((param[9])),  mt.radians(param[10])
tx, ty, tz = param[5], param[6], param[7]
f_x, f_y, c_u, c_v = param[0], param[1], param[2], param[3]

P_veh2cal = np.array([
    [-1, 0, 0, 0], 
    [0, -1, 0, 0], 
    [0, 0, 1, 0], 
    [0, 0, 0, 1]
])
P_cal2cam = np.array([
    [0, -1, 0, 0], 
    [0, 0, -1, 0], 
    [1, 0, 0, 0],
    [0, 0, 0, 1]
])
P_forward = np.array([
    [-1, 0, 0, 0], 
    [0, -1, 0, 0], 
    [0, 0, 1, 0], 
    [0, 0, 0, 1]
])
T = np.array([
    [1, 0, 0, tx], 
    [0, 1, 0, ty], 
    [0, 0, 1, tz], 
    [0, 0, 0, 1] 
])
R_yaw = np.array([
    [mt.cos(th_z), -mt.sin(th_z), 0, 0], 
    [mt.sin(th_z), mt.cos(th_z), 0, 0], 
    [0, 0, 1, 0], 
    [0, 0, 0, 1]
])
R_pit = np.array([
    [mt.cos(th_y), 0, mt.sin(th_y), 0], 
    [0, 1, 0, 0], 
    [-mt.sin(th_y), 0, mt.cos(th_y), 0], 
    [0, 0, 0, 1]
])
R_rol = np.array([
    [1, 0, 0, 0], 
    [0, mt.cos(th_x), -mt.sin(th_x), 0], 
    [0, mt.sin(th_x), mt.cos(th_x), 0], 
    [0, 0, 0, 1]
])
K = np.array([
    [f_x, 0, c_u, 0], 
    [0, f_y, c_v, 0], 
    [0, 0, 1, 0]
])
RT_cal = np.array([
    [1, 0, 0, 2.84], 
    [0, 1, 0, 0], 
    [0, 0, 1, 0.317], 
    [0, 0, 0, 1]
])

inv_veh2cal_RT = inv(RT_cal)
inv_cal2cam_RT = inv(T.dot(R_yaw.dot(R_pit.dot(R_rol))))


#Function Defintion
def Convert3Dto2D(X) :
    x = K.dot(P_cal2cam.dot(P_forward.dot(inv_cal2cam_RT.dot(P_veh2cal.dot(inv_veh2cal_RT.dot((X)))))))
    return x

def DrawLine(p1, p2) :

    x1, y1, x2, y2 = p1[0], p1[1], p2[0], p2[1]
  
    if(y1 == y2) : 
        lin_x = np.linspace(x1, x2, 2)
        lin_y = np.linspace(y1, y2, 2)
    elif(x1 == x2) : 
        lin_x = np.linspace(x1, x2, 2)
        lin_y = np.linspace(y1, y2, 2) 
    else :
        lin_x = np.linspace(x1, x2, 2)
        lin_y = (y2 - y1)/(x2 - x1) * (lin_x - x1) + y1                 
 
    lines = plt.plot(lin_x, lin_y, color = 'b', linewidth=1.0) 
    

for line in file.readlines() :
    piece = re.findall('[-]?\d+\,[-]?\d+\,[-]?\d+', line)
    split_line = line.split(' ')

    if(split_line[1] == "Lines") : 
        select = 1
    elif(split_line[1] == "Rectangles") : 
        select = 2  

    if(piece and (select == 1)) : 
        
        p1 = piece[0].split(',')
        p2 = piece[1].split(',')    
       
        X1  = np.array([ int(p1[0]), int(p1[1]), int(p1[2]), 1 ])
        X2  = np.array([ int(p2[0]), int(p2[1]), int(p2[2]), 1 ])
       
        h_p1 = Convert3Dto2D(X1)
        h_p2 = Convert3Dto2D(X2)        
        
        DrawLine( [h_p1[0]/h_p1[2], h_p1[1]/h_p1[2]], [h_p2[0]/h_p2[2], h_p2[1]/h_p2[2]] )
    
    elif(piece and select == 2) :      
        
        p1 = piece[0].split(',')
        p2 = piece[1].split(',')

        x1, y1, z1 = int(p1[0]), int(p1[1]), int(p1[2])
        x2, y2, z2 = int(p2[0]), int(p2[1]), int(p2[2])

        if(z1 == z2) : 
            X1  = np.array( [x1, y1, z1, 1] )
            X2  = np.array( [x1, y2, z1, 1] )
            X3  = np.array( [x2, y1, z1, 1] )
            X4  = np.array( [x2, y2, z1, 1] )

        elif(x1 == x2) : 
            X1  = np.array( [x1, y1, z1, 1] )
            X2  = np.array( [x1, y1, z2, 1] )
            X3  = np.array( [x1, y2, z1, 1] )
            X4  = np.array( [x1, y2, z2, 1] )

        elif(y1 == y2) : 
            X1  = np.array( [x1, y1, z1, 1] )
            X2  = np.array( [x1, y1, z2, 1] )
            X3  = np.array( [x2, y1, z1, 1] )
            X4  = np.array( [x2, y1, z2, 1] )

        h_p1 = Convert3Dto2D(X1)
        h_p2 = Convert3Dto2D(X2)
        h_p3 = Convert3Dto2D(X3)
        h_p4 = Convert3Dto2D(X4)
        
        DrawLine( [h_p1[0]/h_p1[2], h_p1[1]/h_p1[2]], [h_p2[0]/h_p2[2], h_p2[1]/h_p2[2]] )
        DrawLine( [h_p1[0]/h_p1[2], h_p1[1]/h_p1[2]], [h_p3[0]/h_p3[2], h_p3[1]/h_p3[2]] )
        DrawLine( [h_p4[0]/h_p4[2], h_p4[1]/h_p4[2]], [h_p3[0]/h_p3[2], h_p3[1]/h_p3[2]] )
        DrawLine( [h_p4[0]/h_p4[2], h_p4[1]/h_p4[2]], [h_p2[0]/h_p2[2], h_p2[1]/h_p2[2]] )

ax = plt.gca()
ax.set_xlim([0,1280])
ax.set_ylim([0, 720])
ax.invert_yaxis()
plt.show()  

file.close()      
xmlFile.close()
