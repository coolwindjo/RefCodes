# -*- coding: utf-8 -*-
##  @package Homography
#   Documentation for this module
#
#   More details
import sys
import numpy as np

class Point2D(object):
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
        return super(Point2D, self).__init__()

    def int(self):
        self.x = int(round(self.x)) 
        self.y = int(round(self.y))
        return self

    def tuple(self):
        return (self.x, self.y)

    def copy(self):
        return Point2D(self.x, self.y)

    def move(self, x, y):
        self.x += x 
        self.y += y
        return self

class Point3D(Point2D):
    def __init__(self, x=0, y=0, z=0):
        self.z = z
        return super(Point3D, self).__init__(x, y)

    def int(self):
        self.x = int(round(self.x)) 
        self.y = int(round(self.y))
        self.z = int(round(self.z))
        return self

    def tuple(self):
        return (self.x, self.y, self.z)

    def list(self):
        return [self.x, self.y, self.z]

    def copy(self):
        return Point3D(self.x, self.y, self.z)

    def move(self, x, y, z):
        self.x += x
        self.y += y
        self.z += z
        return self

class Translation3D(Point3D):
    def __init__(self, x, y, z):
        return super(Translation3D, self).__init__(x, y, z)

class Rotation3D(object):
    def __init__(self, roll, pitch, yaw):
        self.roll = roll
        self.pitch = pitch
        self.yaw = yaw
        return super(Rotation3D, self).__init__()

class Intrinsic(object):
    def __init__(self, **kwargs):
        for key in kwargs:
            if key == 'F_u':
                self.F_u = kwargs[key]
            elif key == 'F_v':
                self.F_v = kwargs[key]
            elif key == 'C_u':
                self.C_u = kwargs[key]
            elif key == 'C_v':
                self.C_v = kwargs[key]
        return super(Intrinsic, self).__init__()

class CameraCalibrationParameters(object):
    location  = Point3D(0.0, 0.0, 0.0)
    rotation  = Rotation3D(0.0, 0.0, 0.0)
    intrinsic = Intrinsic(F_u=0.0, F_v=0.0, C_u=0.0, C_v=0.0)
    
    def __init__(self, **kwargs):
        for key in kwargs:
            if key == 'location':
                self.location = kwargs[key]
            elif key == 'rotation':
                self.rotation = kwargs[key]
            elif key == 'intrinsic':
                self.intrinsic = kwargs[key]
        return super(CameraCalibrationParameters, self).__init__()
    

class Homography(object):
    """A class for making a homography matrix"""
    
    def __init__(self, *args, **kwargs):
        return super(Homography, self).__init__(*args, **kwargs)
    
    def convert_point_in_ICS_to_calibration_coordinate(self, front_axis_height, point=Point3D()):
        from copy import deepcopy
        try:
            point_in_calibration_coordinate = deepcopy(point)
            point_in_calibration_coordinate.x *= -1
            point_in_calibration_coordinate.y *= -1
            point_in_calibration_coordinate.z -= front_axis_height

        except :
            print("[Error] Unexpected error at convert_point_in_ICS_to_calibration_coordinate().", sys.exc_info()[0])
            print("point_in_calibration_coordinate = " + str(len(point_in_calibration_coordinate)))
        
        return point_in_calibration_coordinate

    def convert_point_in_calibration_coordinate_to_ICS(self, front_axis_height, point=Point3D()):
        from copy import deepcopy
        try:
            point_in_ICS = deepcopy(point)
            point_in_ICS.x *= -1
            point_in_ICS.y *= -1
            point_in_ICS.z += front_axis_height

        except :
            print("[Error] Unexpected error at convert_point_in_ICS_to_ICS().", sys.exc_info()[0])
            print("point_in_ICS = " + str(len(point_in_ICS)))
        
        return point_in_ICS

    def generate_3x3_roll_rotation_matrix(self,angle):
        
        try:
            R_roll = []

            R_roll.append([1, 0,             0])
            R_roll.append([0, np.cos(angle), -np.sin(angle)])
            R_roll.append([0, np.sin(angle), np.cos(angle)])
        except :
            print("[Error] Unexpected error at generate_3x3_roll_rotation_matrix().", sys.exc_info()[0])
            print("len(R_roll) = " + str(len(R_roll)))
        
        return R_roll

    def generate_3x3_pitch_rotation_matrix(self, angle):
        
        try:
            R_pitch = []

            R_pitch.append([np.cos(angle),   0, np.sin(angle)])
            R_pitch.append([0,               1, 0])
            R_pitch.append([-np.sin(angle),  0, np.cos(angle)])
        except :
            print("[Error] Unexpected error at generate_3x3_pitch_rotation_matrix().", sys.exc_info()[0])
            print("len(R_pitch) = " + str(len(R_pitch)))
        
        return R_pitch

    def generate_3x3_yaw_rotation_matrix(self, angle):
        
        try:
            R_yaw = []

            R_yaw.append([np.cos(angle), -np.sin(angle),  0])
            R_yaw.append([np.sin(angle), np.cos(angle),   0])
            R_yaw.append([0,             0,               1] )
        except :
            print("[Error] Unexpected error at generate_3x3_yaw_rotation_matrix().", sys.exc_info()[0])
            print("len(R_yaw) = " + str(len(R_yaw)))
        
        return R_yaw

    def generate_4x4_RT_matrix( self, 
                                rotation=Rotation3D(0.0, 0.0, 0.0), 
                                translation=Translation3D(0.0, 0.0, 0.0)):

        try:
            RT = []

            # Make an inverse rotation matrix
            R_roll  = np.array(self.generate_3x3_roll_rotation_matrix(np.deg2rad(rotation.roll)))
            R_pitch = np.array(self.generate_3x3_pitch_rotation_matrix(np.deg2rad(rotation.pitch)))
            R_yaw   = np.array(self.generate_3x3_yaw_rotation_matrix(np.deg2rad(rotation.yaw)))
            
            R_pr = np.dot(R_pitch, R_roll)
            R_ypr = np.dot(R_yaw, R_pr)

            if np.linalg.det (R_ypr) <= 0:
                sys.exc_info()[0]
            else:
                pass

            # Inverse Translation in the Calibration coordinate
            T = np.array([[ translation.x, 
                            translation.y, 
                            translation.z]])

            # Inverse Rotation and Translation in the Calibration coordinate
            R_yprT = np.concatenate((R_ypr, T.T), axis = 1)

            RT.append( R_yprT[0] )
            RT.append( R_yprT[1] )
            RT.append( R_yprT[2] )
            RT.append( [0, 0, 0, 1] )

        except :
            print("[Error] Unexpected error at generate_4x4_RT_matrix().", sys.exc_info()[0])
            print("len(RT) = " + str(len(RT)))

        return RT

    def generate_4x4_extrinsic_view_matrix(self, calibration_parameters):

        try:
            E = []

            # Using extrinsic calibration parameters
            # Make an inverse rotation matrix in the calibration coordinate
            R_ypr = self.generate_4x4_RT_matrix(rotation=calibration_parameters.rotation)
            R_inv_in_calibration_coordi = np.linalg.inv(np.array(R_ypr))

            # Inverse translation in the calibration coordinate
            T_in_calibration_coordi = np.array([[ calibration_parameters.location.x, 
                                    calibration_parameters.location.y, 
                                    calibration_parameters.location.z]])
            T_4x4   = np.concatenate(
                    (np.concatenate((np.eye(3), np.array([[0,0,0]])), axis = 0),
                    np.concatenate((-T_in_calibration_coordi, np.array([[1]])), axis = 1).T),
                    axis = 1)

            # Transform into calibration coordinate 
            P_xbc2xfc = np.array([   [-1, 0, 0,  0],
                                    [0, -1, 0,  0],
                                    [0, 0,  1,  0],
                                    [0, 0,  0,  1]])

            # Use the same matrix for moving origin from front-axis to calibration coordinate 
            # with x-backed camera coordinate and x-fronted camera coordinate.
            P_fa2cal = P_xbc2xfc

            # Inverse rotation and translation in the calibration coordinate
            T_in_fa = np.dot(T_4x4, P_fa2cal)
            RT_in_fa = np.dot(R_inv_in_calibration_coordi, T_in_fa)
            RT_fa2xfc = np.dot(P_xbc2xfc, RT_in_fa)

            E.append( RT_fa2xfc[0] )
            E.append( RT_fa2xfc[1] )
            E.append( RT_fa2xfc[2] )
            E.append( RT_fa2xfc[3] )

        except :
            print("[Error] Unexpected error at generate_4x4_extrinsic_view_matrix().", sys.exc_info()[0])
            print("len(RT) = " + str(len(RT)))

        return E

    def generate_4x4_homography_matrix(self, front_axis_height, calibration_parameters):
        
        try:
            H_matrix = []

            # From Interface Coordinate to front axis mid-point
            T = np.array([[0, 0, front_axis_height]])
            T_inv = -T
            T_3x4 = np.concatenate((np.eye(3), T_inv.T), axis = 1)
            T_4x4 = np.concatenate((T_3x4, np.array([[0,0,0,1]])), axis = 0)

            # Generate homography matrix for moving origin to camera position in ICS
            E = np.array(self.generate_4x4_extrinsic_view_matrix(calibration_parameters))

            # Generate homography matrix from ICS to x-fronted camera coordinate
            ICS_to_x_fronted_camera = np.dot(E, T_4x4)

            # From x-fronted camera coordinate to camera coordinate.
            P_xfc2c = np.array([ [0, -1, 0,  0],
                                [0, 0,  -1, 0],
                                [1, 0,  0,  0],
                                [0, 0,  0,  1]])
            ICS_to_camera = np.dot(P_xfc2c, ICS_to_x_fronted_camera)

            H = ICS_to_camera
            
            H_matrix.append([H[0][0], H[0][1], H[0][2], H[0][3]])
            H_matrix.append([H[1][0], H[1][1], H[1][2], H[1][3]])
            H_matrix.append([H[2][0], H[2][1], H[2][2], H[2][3]])
            H_matrix.append([H[3][0], H[3][1], H[3][2], H[3][3]])

        except :
            print("[Error] Unexpected error at generate_4x4_homography_matrix().", sys.exc_info()[0])
            print("len(H) = " + str(len(H)))
        
        return H_matrix

    def generate_3x4_homography_matrix(self, front_axis_height, calibration_parameters):
        
        try:
            H_matrix = []

            # From Interface Coordinate to camera coordinate
            ICS_to_camera = np.array(self.generate_4x4_homography_matrix(   front_axis_height,
                                                                            calibration_parameters))

            # Intrinsic calibration matrix.
            skew = 0
            F_u = calibration_parameters.intrinsic.F_u
            F_v = calibration_parameters.intrinsic.F_v
            C_u = calibration_parameters.intrinsic.C_u
            C_v = calibration_parameters.intrinsic.C_v
            A = np.array([  [F_u,   skew,   C_u,    0],
                            [0,     F_v,    C_v,    0],
                            [0,     0,      1,      0]])

            H = np.dot(A, ICS_to_camera)
            
            H_matrix.append([H[0][0], H[0][1], H[0][2], H[0][3]])
            H_matrix.append([H[1][0], H[1][1], H[1][2], H[1][3]])
            H_matrix.append([H[2][0], H[2][1], H[2][2], H[2][3]])

        except :
            print("[Error] Unexpected error at generate_3x4_homography_matrix().", sys.exc_info()[0])
            print("len(H) = " + str(len(H)))
        
        return H_matrix

    def compute_3d_to_3d_with_4x4_homography(self, H_matrix, pt_3d=Point3D()):

        try:
            Mat_4x4_homography = np.array([ H_matrix[0],
                                            H_matrix[1],
                                            H_matrix[2],
                                            H_matrix[3]])
            xyz1 = [pt_3d.x, pt_3d.y, pt_3d.z] + [1]
            Mat_xyz1 = np.array(xyz1) 
            Mat_xyz1prime = np.dot(Mat_4x4_homography, Mat_xyz1.T)

            x = 0.0
            y = 0.0
            z = 0.0
            if Mat_xyz1prime[3] == 0.0:
                if Mat_xyz1prime[0] > 0:
                    x = float(math.inf)
                else:
                    x = float(-math.inf)
                if Mat_xyz1prime[1] > 0:
                    y = float(math.inf)
                else:
                    y = float(-math.inf)
                if Mat_xyz1prime[2] > 0:
                    z = float(math.inf)
                else:
                    z = float(-math.inf)
            else:
                x = float(Mat_xyz1prime[0]/(Mat_xyz1prime[3]))
                y = float(Mat_xyz1prime[1]/(Mat_xyz1prime[3]))
                z = float(Mat_xyz1prime[2]/(Mat_xyz1prime[3]))

            xyz = Point3D(x, y, z)

        except :
            print("[Error] Unexpected error at compute_3d_to_3d_with_4x4_homography().", sys.exc_info()[0])
            print("len(Mat_xyz1prime) = " + str(len(Mat_xyz1prime)))

        return xyz

    def compute_3d_to_2d_with_3x4_homography(self, H_matrix, pt_3d=Point3D()):

        try:
            Mat_3x4_homography = np.array([ H_matrix[0],
                                            H_matrix[1],
                                            H_matrix[2]])
            xyz1 = [pt_3d.x, pt_3d.y, pt_3d.z] + [1]
            Mat_xyz1 = np.array(xyz1) 
            Mat_xyz = np.dot(Mat_3x4_homography, Mat_xyz1.T)

            x = 0.0
            y = 0.0
            z = 0.0
            if Mat_xyz[2] == 0.0:
                if Mat_xyz[0] > 0:
                    x = float(math.inf)
                else:
                    x = float(-math.inf)
                if Mat_xyz[1] > 0:
                    y = float(math.inf)
                else:
                    y = float(-math.inf)
            else:
                x = float(Mat_xyz[0]/(Mat_xyz[2]))
                y = float(Mat_xyz[1]/(Mat_xyz[2]))

            xy = Point2D(x, y)

        except :
            print("[Error] Unexpected error at compute_3d_to_2d_with_3x4_homography().", sys.exc_info()[0])
            print("len(Mat_xyz) = " + str(len(Mat_xyz)))

        return xy

    def compute_pairs_of_2_points_onto_image(self, H_matrix, point_pairs=[[Point3D(), Point3D()]]):

        try:
            point_pairs_computed = []
            for point_pair in point_pairs:
                point_pair_pt1_computed = self.compute_3d_to_2d_with_3x4_homography(H_matrix, point_pair[0])
                point_pair_pt2_computed = self.compute_3d_to_2d_with_3x4_homography(H_matrix, point_pair[1])
                point_pairs_computed.append([point_pair_pt1_computed, point_pair_pt2_computed])
        except:
            print("[Error] Unexpected error at compute_pairs_of_2_points_onto_image()", sys.exc_info()[0])

        return point_pairs_computed

    def generate_rectangle_with_diagonal_2_points_in_2D(self, rectangle=[Point2D(), Point2D()]):

        try:
            four_lines = []
            points =[]
            point_num_in_rect = 0
            for i in range(0, 4):
                x_idx = int(i>0 and i<3)    # 0110
                y_idx = int(i>1)    # 0011

                if i == 0:
                    points.append(rectangle[0])
                elif (rectangle[x_idx].x != points[point_num_in_rect-1].x or
                        rectangle[y_idx].y != points[point_num_in_rect-1].y):
                    points.append(Point2D(rectangle[x_idx].x, rectangle[y_idx].y))
                else:
                    continue

                if point_num_in_rect > 0:
                    line = [points[point_num_in_rect-1], points[point_num_in_rect]]
                    four_lines.append(line)
                else:
                    pass
                point_num_in_rect += 1
            if point_num_in_rect == 4:
                four_lines.append([four_lines[2][1], four_lines[0][0]])
            else:
                pass

        except :
            print("[Error] Unexpected error at generate_rectangle_with_diagonal_2_points_in_2D().", sys.exc_info()[0])
            print("len(four_lines) = " + str(len(four_lines)))

        return four_lines

    def generate_rectangle_with_diagonal_2_points_in_3D(self, rectangle=[Point3D(), Point3D()]):

        try:
            four_lines = []
            points =[]
            point_num_in_rect = 0
            for i in range(0, 6):
                x_idx = int(i>0 and i<5)    # 011110
                y_idx = int(i>1 and i<4)    # 001100
                z_idx = int(i>2)            # 000111

                if i == 0:
                    points.append(rectangle[0])
                elif (rectangle[x_idx].x != points[point_num_in_rect-1].x or
                        rectangle[y_idx].y != points[point_num_in_rect-1].y or
                        rectangle[z_idx].z != points[point_num_in_rect-1].z):
                    points.append(Point3D(  rectangle[x_idx].x, 
                                            rectangle[y_idx].y,
                                            rectangle[z_idx].z))
                else:
                    continue

                if point_num_in_rect > 0:
                    line = [points[point_num_in_rect-1], points[point_num_in_rect]]
                    four_lines.append(line)
                else:
                    pass
                point_num_in_rect += 1
            if point_num_in_rect == 4:
                four_lines.append([four_lines[2][1], four_lines[0][0]])
            else:
                pass

        except :
            print("[Error] Unexpected error at generate_rectangle_with_diagonal_2_points_in_3D().", sys.exc_info()[0])
            print("len(four_lines) = " + str(len(four_lines)))

        return four_lines

    def compute_line_with_points_in_ICS_using_homography(self, H_matrix, lineX, lineY, lineZ):

        try:
            road_p1 = Point3D(lineX[0], lineY[0], lineZ[0])
            road_p2 = Point3D(lineX[1], lineY[1], lineZ[1])
            image_point_pairs = self.compute_pairs_of_2_points_onto_image(H_matrix, [[road_p1, road_p2]])
            lineX_computed = [image_point_pairs[0][0].x, image_point_pairs[0][1].x]
            lineY_computed = [image_point_pairs[0][0].y, image_point_pairs[0][1].y]
        except :
            print("[Error] Unexpected error at compute_line_with_points_in_ICS_using_homography().", sys.exc_info()[0])
            print("len(lineX_computed) = " + str(len(lineX_computed)))

        return lineX_computed, lineY_computed

    def compute_rectangle_with_points_in_ICS_using_homography(self, H_matrix, rectX, rectY, rectZ):

        try:
            four_lines_3D   = self.generate_rectangle_with_diagonal_2_points_in_3D(
                            [Point3D(rectX[0], rectY[0], rectZ[0]),
                            Point3D(rectX[1], rectY[1], rectZ[1])])
            four_lines_2D   = self.compute_pairs_of_2_points_onto_image(
                            H_matrix, 
                            four_lines_3D)
            linesX_computed = [[line[0].x, line[1].x] for line in four_lines_2D]
            linesY_computed = [[line[0].y, line[1].y] for line in four_lines_2D]

        except :
            print("[Error] Unexpected error at compute_rectangle_with_points_in_ICS_using_homography().", sys.exc_info()[0])
            print("len(linesX_computed) = " + str(len(linesX_computed)))

        return linesX_computed, linesY_computed

def main():
    
    from mpl_toolkits.mplot3d   import axes3d
    import matplotlib.pyplot    as plt
    import fileinput
    import homography

    try:
        fi = fileinput.FileInput()

        # Get the x, y limits
        image_width = 1280
        image_height = 720

        (linesX, linesY, linesZ, 
            rectsX, rectsY, rectsZ) = fi.read_world_model_from_txt("world_model_x+5.txt")

        wheelbase_and_tire_radius  = fi.read_wheelbase_and_tire_radius_from_xml("VehicleSpec.xml")
        calibration_parameters     = fi.read_calibration_parameters_from_xml("Calibration.xml")

        hm = homography.Homography()
        H = hm.generate_3x4_homography_matrix(wheelbase_and_tire_radius, calibration_parameters)
        calibration_parameters.rotation.roll = 3.0
        H_delta = hm.generate_3x4_homography_matrix(wheelbase_and_tire_radius, calibration_parameters)
        
        fig = plt.figure()
        ax = fig.add_subplot(111, projection = '3d')

        for i in range(0, 10):
            lineX_computed, lineY_computed, lineZ_computed  = hm.draw_line_with_road_coordi_using_homography(
                                                            H, linesX[i], linesY[i], linesZ[i])
            ax.plot(lineX_computed, lineY_computed, lineZ_computed, 'k-', lw=2)
            #plt.plot(lineX_computed, lineY_computed, 'k-', lw=2)
        for i in range(0, 8):
            linesX_computed, linesY_computed, linesZ_computed   = hm.draw_rectangle_with_road_coordi_using_homography(
                                                                H, rectsX[i], rectsY[i], rectsZ[i])
            for j in range(0, 4):
                ax.plot(linesX_computed[j], linesY_computed[j], linesZ_computed[j], 'k-', lw=2)
                #plt.plot(linesX_computed[j], linesY_computed[j], 'k-', lw=2)

        for i in range(0, 10):
            lineX_computed, lineY_computed, lineZ_computed  = hm.draw_line_with_road_coordi_using_homography(
                                                            H_delta, linesX[i], linesY[i], linesZ[i])
            ax.plot(lineX_computed, lineY_computed, lineZ_computed, 'b--', lw=2)
            #plt.plot(lineX_computed, lineY_computed, 'b--', lw=2)
        for i in range(0, 8):
            linesX_computed, linesY_computed, linesZ_computed   = hm.draw_rectangle_with_road_coordi_using_homography(
                                                                H_delta, rectsX[i], rectsY[i], rectsZ[i])
            for j in range(0, 4):
                ax.plot(linesX_computed[j], linesY_computed[j], linesZ_computed[j], 'b--', lw=2)
                #plt.plot(linesX_computed[j], linesY_computed[j], 'b--', lw=2)

        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.set_zlabel("Z")
        ax.view_init(elev=100, azim=90)

        # Set the y limits making the maximum 5% greater
        plt.xlim(0, image_width)
        plt.ylim(0, image_height)
        #ax = plt.gca()
        #ax.invert_yaxis()
        plt.show()

    except :
        print("[Error] Unexpected error at main().", sys.exc_info()[0])
        print("len(H) = " + str(len(H)))

    return

if __name__ == "__main__":
    main()