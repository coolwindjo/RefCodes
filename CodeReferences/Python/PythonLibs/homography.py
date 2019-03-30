# -*- coding: utf-8 -*-
##  @package Homography
#   Documentation for this module
#
#   More details
import sys
import numpy as np

class Homography(object):
    """A class for getting input from a user"""
    
    def __init__(self, *args, **kwargs):
        return super(Homography, self).__init__(*args, **kwargs)
    
    def generate_3x3_roll_rotation_matrix(self,angle):
        
        R_roll = []

        R_roll.append([1, 0,             0])
        R_roll.append([0, np.cos(angle), -np.sin(angle)])
        R_roll.append([0, np.sin(angle), np.cos(angle)])
        
        return R_roll

    def generate_3x3_pitch_rotation_matrix(self, angle):
        
        R_pitch = []

        R_pitch.append([np.cos(angle),   0, np.sin(angle)])
        R_pitch.append([0,               1, 0])
        R_pitch.append([-np.sin(angle),  0, np.cos(angle)])
        
        return R_pitch

    def generate_3x3_yaw_rotation_matrix(self, angle):
        
        R_yaw = []

        R_yaw.append([np.cos(angle), -np.sin(angle),  0])
        R_yaw.append([np.sin(angle), np.cos(angle),   0])
        R_yaw.append([0,             0,               1] )
        
        return R_yaw

    def generate_3x4_change_extrinsic_view_matrix(self, F_uv, C_uv, C_xyz, C_rpy):

        try:
            E = []

            # Extrinsic calibration.
            R_roll  = np.array(self.generate_3x3_roll_rotation_matrix(np.deg2rad(C_rpy[0])))
            R_pitch = np.array(self.generate_3x3_pitch_rotation_matrix(np.deg2rad(C_rpy[1])))
            R_yaw   = np.array(self.generate_3x3_yaw_rotation_matrix(np.deg2rad(C_rpy[2])))
            
            R_pr = np.dot(R_pitch, R_roll)
            R_ypr = np.dot(R_yaw, R_pr)

            if np.linalg.det (R_ypr) <= 0:
                sys.exc_info()[0]
            else:
                pass

            R_inv = np.linalg.inv(R_ypr)
            T = np.array([[C_xyz[0], C_xyz[1], C_xyz[2]]])
            T_inv = -T
            RT = np.concatenate((R_inv, T_inv.T), axis = 1)

            E.append( RT[0] )
            E.append( RT[1] )
            E.append( RT[2] )

        except :
            print("[Error] Unexpected error at generate_camera_calibration_numpy_matrix().", sys.exc_info()[0])
            print("len(RT) = " + str(len(RT)))

        return E

    def generate_3x4_homography_matrix(self, F_uv, C_uv, C_xyz, C_rpy, Homography):
        
        try:
            # Change origin to camera posture in world coordinate.
            E = np.array(self.generate_3x4_change_extrinsic_view_matrix(F_uv, C_uv, C_xyz, C_rpy))

            # From Vehicle Coordinate to Projection Coordinate.
            P_v2p = np.array(   [[0,-1, 0],
                                [0, 0,  -1],
                                [1, 0,  0]])
            world_to_camera = np.dot(P_v2p, E)

            # Intrinsic calibration matrix.
            skew = 0
            A = np.array(   [[F_uv[0],  skew,       C_uv[0]],
                            [0,         F_uv[1],    C_uv[1]],
                            [0,         0,          1     ]])

            H = np.dot(A, world_to_camera)
            
            Homography.append([H[0][0], H[0][1], H[0][2], H[0][3]])
            Homography.append([H[1][0], H[1][1], H[1][2], H[1][3]])
            Homography.append([H[2][0], H[2][1], H[2][2], H[2][3]])

        except :
            print("[Error] Unexpected error at compute_homography_matrix_LGADAS().", sys.exc_info()[0])
            print("len(H) = " + str(len(H)))
        
        return 

    def compute_3d_to_2d_with_3x4_homography(self, Homography, xyz, xy):

        try:
            Mat_homography = np.array(  [Homography[0],
                                        Homography[1],
                                        Homography[2]])
            xyz1 = xyz + [1]
            Mat_xyz1 = np.array(xyz1) 
            Mat_xy1 = np.dot(Mat_homography, Mat_xyz1.T)

            x = 0.0
            y = 0.0
            z = 0.0
            if Mat_xy1[2] == 0.0:
                if Mat_xy1[0] > 0:
                    x = float(math.inf)
                else:
                    x = float(-math.inf)
                if Mat_xy1[1] > 0:
                    y = float(math.inf)
                else:
                    y = float(-math.inf)
            else:
                x = float(Mat_xy1[0]/Mat_xy1[2])
                y = float(Mat_xy1[1]/Mat_xy1[2])

            xy.append(x)
            xy.append(y)
            xy.append(1.0)

        except :
            print("[Error] Unexpected error at compute_3d_to_2d_with_3x4_homography().", sys.exc_info()[0])
            print("len(Mat_xy1) = " + str(len(Mat_xy1)))

        return

    def draw_line_with_world_coordi_using_homography(self, Homography, lineX, lineY, lineZ):

        try:
            world_xyz_p1 = [lineX[0], lineY[0], lineZ[0]]
            world_xyz_p2 = [lineX[1], lineY[1], lineZ[1]]
            image_xy_p1 = []
            image_xy_p2 = []
            self.compute_3d_to_2d_with_3x4_homography(Homography, world_xyz_p1, image_xy_p1)
            self.compute_3d_to_2d_with_3x4_homography(Homography, world_xyz_p2, image_xy_p2)
            lineX_computed = [image_xy_p1[0], image_xy_p2[0]]
            lineY_computed = [image_xy_p1[1], image_xy_p2[1]]
        except :
            print("[Error] Unexpected error at draw_line_with_world_coordi_using_homography().", sys.exc_info()[0])
            print("len(Mat_xy1) = " + str(len(Mat_xy1)))

        return lineX_computed, lineY_computed

    def draw_rectangle_with_world_coordi_using_homography(self, Homography, rectX, rectY, rectZ):

        try:
            lineX_computed = []
            lineY_computed = []
            lineZ_computed = []

            world_xyz_points = []
            image_xyz_points = []
            rect_line_count = 0
            for j in range(0, 6):
                x_idx = int(j>0 and j<4)    # 011100
                y_idx = int(j>1 and j<5)    # 001110
                z_idx = int(j>2)            # 000111

                if j == 0:
                    world_xyz_points.append([rectX[0], rectY[0], rectZ[0]])
                elif (rectX[x_idx] != world_xyz_points[rect_line_count-1][0] or
                        rectY[y_idx] != world_xyz_points[rect_line_count-1][1] or
                        rectZ[z_idx] != world_xyz_points[rect_line_count-1][2]):
                    world_xyz_points.append([rectX[x_idx], rectY[y_idx], rectZ[z_idx]])
                else:
                    continue

                image_xyz_points.append([])
                self.compute_3d_to_2d_with_3x4_homography(Homography, world_xyz_points[rect_line_count], image_xyz_points[rect_line_count])
                if rect_line_count > 0:
                    lineX_computed.append([image_xyz_points[rect_line_count-1][0], image_xyz_points[rect_line_count][0]])
                    lineY_computed.append([image_xyz_points[rect_line_count-1][1], image_xyz_points[rect_line_count][1]])
                    lineZ_computed.append([image_xyz_points[rect_line_count-1][2], image_xyz_points[rect_line_count][2]])
                else:
                    pass
                rect_line_count += 1
            if rect_line_count == 4:
                lineX_computed.append([image_xyz_points[3][0], image_xyz_points[0][0]])
                lineY_computed.append([image_xyz_points[3][1], image_xyz_points[0][1]])
                lineZ_computed.append([image_xyz_points[3][2], image_xyz_points[0][2]])
            else:
                pass

        except :
            print("[Error] Unexpected error at draw_line_with_world_coordi_using_homography().", sys.exc_info()[0])
            print("len(Mat_xy1) = " + str(len(Mat_xy1)))

        return lineX_computed, lineY_computed

def main():
    
    #from mpl_toolkits.mplot3d   import axes3d
    import matplotlib.pyplot    as plt
    import fileinput
    import homography

    fi = fileinput.FileInput()

    # Get the x, y limits
    image_width = 1280
    image_height = 720

    lineX = []
    lineY = []
    lineZ = []
    rectX = []
    rectY = []
    rectZ = []
    fi.read_world_model_from_txt("world_model.txt", lineX, lineY, lineZ, rectX, rectY, rectZ)

    F_uv = []
    C_uv = []
    C_xyz = []
    C_rpy = []
    baseline = 0.0
    fi.read_calibration_parameters_from_xml("Calibration.xml", F_uv, C_uv, baseline, C_xyz, C_rpy)

    H = []
    H_delta = []
    hm = homography.Homography()
    C_xyz[0] = -C_xyz[0]
    hm.generate_3x4_homography_matrix(F_uv, C_uv, C_xyz, C_rpy, H)
    C_rpy[0] += 3.0
    C_rpy[1] += 3.0
    C_rpy[2] += 3.0
    hm.generate_3x4_homography_matrix(F_uv, C_uv, C_xyz, C_rpy, H_delta)
    
    #fig = plt.figure()
    #ax = fig.add_subplot(111, projection = '3d')

    for i in range(0, 10):
        lineX_computed, lineY_computed = hm.draw_line_with_world_coordi_using_homography(H, lineX[i], lineY[i], lineZ[i])
        #ax.plot(lineX_computed, lineY_computed, lineZ_computed, 'k-', lw=2)
        plt.plot(lineX_computed, lineY_computed, 'k-', lw=2)
    for i in range(0, 8):
        linesX_computed, linesY_computed = hm.draw_rectangle_with_world_coordi_using_homography(H, rectX[i], rectY[i], rectZ[i])
        #ax.plot(lineX_computed, lineY_computed, lineZ_computed, 'k-', lw=2)
        for j in range(0, 4):
            plt.plot(linesX_computed[j], linesY_computed[j], 'k-', lw=2)

    for i in range(0, 10):
        lineX_computed, lineY_computed = hm.draw_line_with_world_coordi_using_homography(H_delta, lineX[i], lineY[i], lineZ[i])
        #ax.plot(lineX_computed, lineY_computed, lineZ_computed, 'k-', lw=2)
        plt.plot(lineX_computed, lineY_computed, 'b--', lw=2)
    for i in range(0, 8):
        linesX_computed, linesY_computed = hm.draw_rectangle_with_world_coordi_using_homography(H_delta, rectX[i], rectY[i], rectZ[i])
        #ax.plot(lineX_computed, lineY_computed, lineZ_computed, 'k-', lw=2)
        for j in range(0, 4):
            plt.plot(linesX_computed[j], linesY_computed[j], 'b--', lw=2)

    #ax.set_xlabel("X")
    #ax.set_ylabel("Y")
    #ax.set_zlabel("Z")
    #ax.view_init(elev=100, azim=90)

    # Set the y limits making the maximum 5% greater
    plt.xlim(0, image_width)
    plt.ylim(0, image_height)
    ax = plt.gca()
    ax.invert_yaxis()
    plt.show()

    return

if __name__ == "__main__":
    main()