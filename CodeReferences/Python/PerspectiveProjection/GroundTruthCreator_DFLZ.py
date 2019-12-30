# -*- coding: utf-8 -*-
# @package Ground Truth Image and Coordinate value Creator

import sys
import homography as hm

##################
# Configurations #
##################
TARGET_DIST_FROM_AXLE = 5.3
TARGET_HEIGHT         = 1.2

# DFLZ requirement
DFLZ_TARGET_ROWS               = 2
DFLZ_TARGET_COLS               = 3
DFLZ_TARGET_DIST_BW_TWO_BOARDS = 1.5
DFLZ_TARGET_SQUARE_SIZE        = 0.15

# Get the x, y limits
IMAGE_WIDTH = 2880
IMAGE_HEIGHT = 640

class ChessTargetSpec(object):
    Daxle = TARGET_DIST_FROM_AXLE           # Distance from the front axle to the target plane
    Height = TARGET_HEIGHT                  # Target mid-point from the floor
    Wcl = DFLZ_TARGET_DIST_BW_TWO_BOARDS    # Distance between two chess boards
    SqSize = DFLZ_TARGET_SQUARE_SIZE        # A length of four sides of a square
    rotation_in_calibration_coordinate = hm.Rotation3D(0.0,0.0,0.0)

    def __init__(self, **kwargs):
        for key in kwargs:
            if key == 'Wcl':
                self.Wcl = kwargs[key]
            elif key == 'Daxle':
                self.Daxle = kwargs[key]
            elif key == 'Height':
                self.Height = kwargs[key]
            elif key == 'SqSize':
                self.SqSize = kwargs[key]
            elif key == 'Rotation':
                self.rotation_in_calibration_coordinate = kwargs[key]
        return super(ChessTargetSpec, self).__init__()

class ChessBoardShapeInRoadCoordinate(object):
    """A class for generating chess board in road coordinate"""
    sq_size    = ChessTargetSpec().SqSize
    rows       = DFLZ_TARGET_ROWS
    cols       = DFLZ_TARGET_COLS
    Y_left_end = None
    Z_top_end  = None
    black_first= None
    translation = hm.Translation3D(0.0,0.0,0.0)

    def __init__(self, **kwargs):
        try:
            self.black_rectangles = []
            self.white_rectangles = []
            self.update(**kwargs)

        except:
            print("[Error] Unexpected error at ChessBoardShapeInRoadCoordinate()", sys.exc_info()[0])
                    
        return super(ChessBoardShapeInRoadCoordinate, self).__init__()

    def update(self, **kwargs):
        try:
            homography = hm.Homography()

            for key in kwargs:
                if key == 'black_rectangles':
                    self.black_rectangles = kwargs[key]
                elif key == 'sq_size':
                    self.sq_size = kwargs[key]
                elif key == 'rows':
                    self.rows = kwargs[key]
                elif key == 'cols':
                    self.cols = kwargs[key]
                elif key == 'Y_left_end':
                    self.Y_left_end = kwargs[key]
                elif key == 'Z_top_end':
                    self.Z_top_end = kwargs[key]
                elif key == 'black_first':
                    self.black_first = kwargs[key]
                elif key == 'translation':
                    self.translation = kwargs[key]

            if len(self.black_rectangles) != 0:
                self.white_rectangles.append(0)
                # To do: white_rect with black_rects
            else:                
                if self.Y_left_end == None:
                    self.Y_left_end =   (self.translation.y 
                                        + self.sq_size * self.cols * 0.5)  # Left-end Y value in road coordi
                if self.Z_top_end == None:
                    self.Z_top_end =    (self.translation.z
                                        + self.sq_size * self.rows * 0.5)  # Top-end Y value in road coordi

                self.detectable_corner_points = []
                for row in range(self.rows):
                    for col in range(self.cols):
                        rect_top_left = hm.Point3D( self.translation.x,
                                                    self.Y_left_end - self.sq_size*col, 
                                                    self.Z_top_end - self.sq_size*row)
                        rect_bottom_right = hm.Point3D( self.translation.x,
                                                        self.Y_left_end - self.sq_size*(col+1), 
                                                        self.Z_top_end - self.sq_size*(row+1))

                        if (row != self.rows-1) and (col != self.cols-1):
                            self.detectable_corner_points.append(rect_bottom_right)

                        if self.black_first == True:
                            if row % 2 == col % 2:
                                four_lines  = homography.generate_rectangle_with_diagonal_2_points_in_3D(
                                            [rect_top_left, rect_bottom_right])
                                self.black_rectangles.append(four_lines)
                            else:
                                four_lines  = homography.generate_rectangle_with_diagonal_2_points_in_3D(
                                            [rect_top_left, rect_bottom_right])
                                self.white_rectangles.append(four_lines)
                        elif self.black_first == False:
                            if row % 2 != col % 2:
                                four_lines  = homography.generate_rectangle_with_diagonal_2_points_in_3D(
                                            [rect_top_left, rect_bottom_right])
                                self.black_rectangles.append(four_lines)
                            else:
                                four_lines  = homography.generate_rectangle_with_diagonal_2_points_in_3D(
                                            [rect_top_left, rect_bottom_right])
                                self.white_rectangles.append(four_lines)

        except:
            print("[Error] Unexpected error at update()", sys.exc_info()[0])
                    
        return

class ChessTargetShape(object):
    """A class for generating chess target shape"""

    def __init__(self, spec=None):

        if spec == None:
            self.spec = ChessTargetSpec()
        else:
            self.spec = spec

        return super(ChessTargetShape, self).__init__()

    def rotate_and_translate_points(self, RT_matrix, points):
        import numpy as np

        try:
            for i, point in enumerate(points):
                pt_xyz1 = point.list() + [1]
                new_pt_xyz1 = np.dot(RT_matrix, np.array(pt_xyz1).T)
                points[i] = hm.Point3D(new_pt_xyz1[0], new_pt_xyz1[1], new_pt_xyz1[2])
        except:
            print("[Error] Unexpected error at rotate_points()", sys.exc_info()[0])

        return

    def rotate_and_translate_rectangles(self, RT_matrix, rectangles):
        import numpy as np

        try:
            for rect in rectangles:
                for line_num in range(4):
                    for point_num in range(2):
                        pt_xyz1 = rect[line_num][point_num].list() + [1]
                        new_pt_xyz1 = np.dot(RT_matrix, np.array(pt_xyz1).T)
                        rect[line_num][point_num] = hm.Point3D(new_pt_xyz1[0], new_pt_xyz1[1], new_pt_xyz1[2])
        except:
            print("[Error] Unexpected error at rotate_rectangles()", sys.exc_info()[0])

        return

    def rotate_and_translate_target(self, rotation, translation):
        import numpy as np

        try:
            # Change origin to target posture in World coordinate
            homography= hm.Homography()
            RT = np.array(homography.generate_4x4_RT_matrix(rotation, translation))

            self.rotate_and_translate_points(RT, self.detectable_points)
            self.rotate_and_translate_rectangles(RT, self.left_board.black_rectangles)
            self.rotate_and_translate_rectangles(RT, self.left_board.white_rectangles)
            self.rotate_and_translate_rectangles(RT, self.right_board.black_rectangles)
            self.rotate_and_translate_rectangles(RT, self.right_board.white_rectangles)
            self.rotate_and_translate_rectangles(RT, [self.background])

        except:
            print("[Error] Unexpected error at rotate_target()", sys.exc_info()[0])

        return

    def generate_DFLZ_target_shape_in_road_coordinate(self):
        try:
            homography = hm.Homography()

            half_wcl = self.spec.Wcl * 0.5
            left_shift = hm.Translation3D(0, half_wcl, 0) 
            right_shift = hm.Translation3D(0, -half_wcl, 0)

            self.left_board     = ChessBoardShapeInRoadCoordinate(  
                                translation=left_shift, black_first=True, sq_size=self.spec.SqSize,
                                rows=DFLZ_TARGET_ROWS, cols=DFLZ_TARGET_COLS)
            self.right_board    = ChessBoardShapeInRoadCoordinate( 
                                translation=right_shift, black_first=False, sq_size=self.spec.SqSize, 
                                rows=DFLZ_TARGET_ROWS, cols=DFLZ_TARGET_COLS)
            self.background = homography.generate_rectangle_with_diagonal_2_points_in_3D(
                            [hm.Point3D(    0, 
                                            self.left_board.Y_left_end + 0.1, 
                                            self.left_board.Z_top_end + 0.1),
                            hm.Point3D(     0,
                                            self.right_board.Y_left_end - self.right_board.cols*self.spec.SqSize - 0.1,
                                            self.right_board.Z_top_end - self.right_board.rows*self.spec.SqSize - 0.1)])
            self.detectable_points = self.left_board.detectable_corner_points + self.right_board.detectable_corner_points

            target_location = hm.Translation3D((self.spec.Daxle), 0, self.spec.Height)
            self.rotate_and_translate_target(   self.spec.rotation_in_calibration_coordinate,
                                                target_location)

        except:
            print("[Error] Unexpected error at generate_DFLZ_target_shape_in_road_coordinate()", sys.exc_info()[0])

        return
    
    def compute_onto_image_using_homography(self, H_matrix):
        try:
            homography= hm.Homography()
            
            black_rects_in_3D = []
            white_rects_in_3D = []
            white_rects_in_3D.append(self.background)
            for rect in self.left_board.black_rectangles:
                black_rects_in_3D.append(rect)
            for rect in self.left_board.white_rectangles :
                white_rects_in_3D.append(rect)
            for rect in self.right_board.black_rectangles:
                black_rects_in_3D.append(rect)
            for rect in self.right_board.white_rectangles :
                white_rects_in_3D.append(rect)

            black_rects_on_image = []
            white_rects_on_image = []
            for four_lines in black_rects_in_3D:
                four_lines_computed = homography.compute_pairs_of_2_points_onto_image(H_matrix, four_lines)
                black_rects_on_image.append(four_lines_computed)
            for four_lines in white_rects_in_3D:
                four_lines_computed = homography.compute_pairs_of_2_points_onto_image(H_matrix, four_lines)
                white_rects_on_image.append(four_lines_computed)
        except:
            print("[Error] Unexpected error at compute_onto_image_using_homography()", sys.exc_info()[0])

        return black_rects_on_image, white_rects_on_image

#Parameters
#----------
#image : ndarray
#    Input image data. Will be converted to float.
#mode : str
#    One of the following strings, selecting the type of noise to add:

#    'gauss'     Gaussian-distributed additive noise.
#    'poisson'   Poisson-distributed noise generated from the data.
#    's&p'       Replaces random pixels with 0 or 1.
#    'speckle'   Multiplicative noise using out = image + n*image,where
#                n is uniform noise with specified mean & variance.
def noisy(noise_typ,image):
    import os
    import numpy as np
    import cv2

    if noise_typ == "gauss":
        row,col,ch= image.shape
        mean = 0
        var = 0.1
        sigma = var**0.5
        gauss = np.random.normal(mean,sigma,(row,col,ch))
        gauss = gauss.reshape(row,col,ch)
        noisy = image + gauss
    elif noise_typ == "s&p":
        row,col,ch = image.shape
        s_vs_p = 0.5
        amount = 0.004
        out = np.copy(image)
        # Salt mode
        num_salt = np.ceil(amount * image.size * s_vs_p)
        coords = [np.random.randint(0, i - 1, int(num_salt))
                for i in image.shape[:2]]
        out[coords] = 1

        # Pepper mode
        num_pepper = np.ceil(amount* image.size * (1. - s_vs_p))
        coords = [np.random.randint(0, i - 1, int(num_pepper))
                for i in image.shape[:2]]
        out[coords] = 0
        return out
    elif noise_typ == "poisson":
        vals = len(np.unique(image))
        vals = 2 ** np.ceil(np.log2(vals))
        noisy = np.random.poisson(image * vals) / float(vals)
    elif noise_typ =="speckle":
        row,col,ch = image.shape
        gauss = np.random.randn(row,col,ch)
        gauss = gauss.reshape(row,col,ch)        
        noisy = image + image * gauss
    elif noise_typ =="lines":
        row,col,ch = image.shape
        lines = 0.005
        amount = 0.004
        out = np.copy(image)
        num_lines = int(np.ceil(amount * image.size * lines))
        coords1 = [np.random.randint(0, i - 1, num_lines) for i in [col, row]]
        coords2 = [np.random.randint(0, i - 1, num_lines) for i in [col, row]]
        for i in range(num_lines):
            cv2.line(   out, 
                        (int(coords1[0][i]), int(coords1[1][i])), 
                        (int(coords2[0][i]), int(coords2[1][i])), (0), 1)
        return out
    elif noise_typ =="ortholines":
        row,col,ch = image.shape
        lines = 0.01
        amount = 0.005
        out = np.copy(image)
        num_lines = int(np.ceil(amount * image.size * lines))
        coords1 = [np.random.randint(0, i - 1, num_lines) for i in [col, row]]
        coords2 = [np.random.randint(0, i - 1, num_lines) for i in [col, row]]
        coords3 = [np.random.randint(0, i - 1, num_lines) for i in [col, row]]
        thickness = [np.random.randint(0, i - 1, num_lines) for i in [30, 30]]
        color = [np.random.randint(0, i - 1, num_lines) for i in [255, 255]]
        for i in range(num_lines):
            # Vertical lines
            cv2.line(   out, 
                        (int(coords1[0][i]), int(coords2[1][i])), 
                        (int(coords1[0][i]), int(coords3[1][i])), 
                        (int(color[0][i])), thickness[0][i])
            # Horizontal lines
            cv2.line(   out, 
                        (int(coords2[0][i]), int(coords1[1][i])), 
                        (int(coords3[0][i]), int(coords1[1][i])), 
                        (int(color[1][i])), thickness[1][i])
        return out
    return noisy

def brightness(image):
    import numpy as np
    import cv2

    try:
        #yuv = cv2.cvtColor(image, cv2.COLOR_BGR2YUV)

        alpha = 0.2 # [1.0 - 3.0]
        beta = 30.0   # [0 - 100]

        #mul_img = cv2.multiply(yuv[:,:,0], np.array([alpha]))
        mul_img = cv2.multiply(image, np.array([alpha]))
        #yuv[:,:,0] = cv2.add(mul_img, np.array([beta]))
        res = cv2.add(mul_img, np.array([beta]))


        #res = cv2.cvtColor(yuv, cv2.COLOR_YUV2BGR)

    except:
        print("[Error] Unexpected error at brightness()", sys.exc_info()[0])

    return res

def contrast(image):
    import numpy as np
    import cv2
    #import matplotlib.pyplot as plt

    try:
        # Histogram Equalization
        MAX_VALUE = 70 
        hist,bins = np.histogram(image.flatten(),256,[0,256])
        cdf = hist.cumsum()
        cdf_normalized = cdf * hist.max()/ cdf.max()

        cdf_m = np.ma.masked_equal(cdf,0)
        cdf_m = (cdf_m - cdf_m.min())*MAX_VALUE/(cdf_m.max()-cdf_m.min())
        cdf = np.ma.filled(cdf_m,0).astype('uint8')
        res = cdf[image]

        #plt.plot(cdf_normalized, color = 'b')
        #plt.hist(image.flatten(),256,[0,256], color = 'r')
        #plt.xlim([0,256])
        #plt.legend(('cdf','histogram'), loc = 'upper left')
        #plt.show()

        #kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))
        #close = cv2.morphologyEx(image, cv2.MORPH_CLOSE, kernel)
        #div = np.float32(image)/(close)
        #res = np.uint8(cv2.normalize(div, div, 50, 100, cv2.NORM_MINMAX))
    
    except:
        print("[Error] Unexpected error at brightness()", sys.exc_info()[0])

    return res

def main():
    import fileinput
    import userinput
    import numpy as np
    import cv2

    try:
        # Read parameters from files.
        fi = fileinput.FileInput()
        calibration_parameters, front_axis_height = fi.read_input_parameters_from_xml("Calibration.xml")

        # Generate DFLZ targets for calibration.
        ui = userinput.UserInput()

        #if ui.get_number('0 for using default values, otherwise, press any') != 0:
        #    chess_target = ChessTargetShape(ChessTargetSpec(Daxle=ui.get_float('Target Daxle'),
        #                                                    Height=ui.get_float('Target Height'),
        #                                                    Rotation=hm.Rotation3D(
        #                                                            ui.get_float('Target Roll'),
        #                                                            ui.get_float('Target Pitch'),
        #                                                            ui.get_float('Target Yaw'))))
        #else:
        #    chess_target = ChessTargetShape(ChessTargetSpec())
        chess_target = ChessTargetShape(ChessTargetSpec())
        chess_target.generate_DFLZ_target_shape_in_road_coordinate()

        # Generate homography matrix
        homography = hm.Homography()
        H_3x4 = homography.generate_3x4_homography_matrix(front_axis_height, calibration_parameters)

        (   black_rects_on_image, 
            white_rects_on_image) = chess_target.compute_onto_image_using_homography(H_3x4)

        # Create a white image.
        img = np.full((IMAGE_HEIGHT, IMAGE_WIDTH, 1), 255, dtype=np.uint8)
        img = noisy("lines", img)
        img = noisy("ortholines", img)

        # Draw convex polygons on the image.
        for white_rect in white_rects_on_image:
            points = np.array([[line[i].int().tuple() for line in white_rect for i in range(2)]], np.int32)
            cv2.fillConvexPoly( img, points, (255))
            cv2.polylines( img, points, True, (0))
        for black_rect in black_rects_on_image:
            points = np.array([[line[i].int().tuple() for line in black_rect for i in range(2)]], np.int32)
            cv2.fillConvexPoly( img, points, (0))

        kernel = np.ones((5,5), np.float32)/25
        salt_and_pepper_img = noisy("s&p", img)
        #poisson_img = noisy("poisson", img)
        #speckle_img = noisy("speckle", img)
        #blurred_img2 = cv2.blur(salt_and_pepper_img, (5,5))
        #gaussian_blurred_img = cv2.GaussianBlur(speckle_img, (5,5), 0)
        #median_blurred_img = cv2.medianBlur(img, 5)
        brightened_img = brightness(salt_and_pepper_img)
        contrast_img = contrast(brightened_img)
        blurred_img = cv2.filter2D(contrast_img, -1, kernel)

        #cv2.imshow('blurred_img', blurred_img)
        #cv2.imshow('blurred_img2', blurred_img)
        #cv2.imshow('gaussian_blurred_img', blurred_img)
        #cv2.imshow('median_blurred_img', blurred_img)
        #cv2.imshow('salt_and_pepper_img', salt_and_pepper_img)
        #cv2.imshow('poisson_img', poisson_img)
        #cv2.imshow('speckle_img', speckle_img)
        #cv2.imshow('brightened_img', brightened_img)
        #cv2.imshow('contrast_img', contrast_img)

        cv2.imwrite('GT_image.png', blurred_img)

        # Find and show the ground truth points.
        ground_truth_points_list = []
        debug_gt_x_fronted_list = []

        H_4x4 = homography.generate_4x4_homography_matrix(front_axis_height, calibration_parameters)

        with open('GT.txt', 'w') as fileout:
            for point in chess_target.detectable_points:
                ground_truth_point = homography.compute_3d_to_2d_with_3x4_homography(H_3x4, point)
                debug_gt_x_fronted = homography.compute_3d_to_3d_with_4x4_homography(H_4x4, point)
                ground_truth_points_list.append(ground_truth_point)
                debug_gt_x_fronted_list.append(debug_gt_x_fronted)
                fileout.write(str(point.tuple()))
            fileout.write("\n")
            for debug_gt_x_fronted in debug_gt_x_fronted_list:
                fileout.write(str(debug_gt_x_fronted.tuple()))
            fileout.write("\n")
            for ground_truth_point in ground_truth_points_list:
                fileout.write(str(ground_truth_point.tuple()))
                cv2.circle(blurred_img, ground_truth_point.int().tuple(), 5, (50), 3)

        resized_img = cv2.resize(blurred_img, None, fx=0.5, fy=0.5, interpolation=cv2.INTER_CUBIC)
        cv2.imshow('GT_image', resized_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    except:
        print("[Error] Unexpected error at main()", sys.exc_info()[0])
    
    return

if __name__ == '__main__':
    main()