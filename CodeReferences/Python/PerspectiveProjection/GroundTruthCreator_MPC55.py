# -*- coding: utf-8 -*-
# @package Ground Truth Image and Coordinate value Creator

import sys
import homography as hm

##################
# Configurations #
##################
# [meters]
TARGET_X_DISTANCE_IN_ICS = 0.840
TARGET_CENTER_HEIGHT  = 1.275

# MPC5.5 requirements
# [meters]
NIGHTVIEW_WIDTH = 0.315
NIGHTVIEW_HEIGHT = 0.200
NIGHTVIEW_INNER_CIRCLE_DIAMETER = 0.015
NIGHTVIEW_OUTER_CIRCLE_DIAMETER = 0.045
NIGHTVIEW_CIRCLE_CENTER_OFFSET = 0.120
NIGHTVIEW_CROSS_THICKNESS = 0.003
NIGHTVIEW_CROSS_LENGTH = 0.060
NIGHTVIEW_GROSS_WIDTH = 1.000
NIGHTVIEW_GROSS_HEIGHT = 0.2265
NIGHTVIEW_GROSS_INNER_CIRCLE_DIAMETER = 0.0225
NIGHTVIEW_GROSS_OUTER_CIRCLE_DIAMETER = 0.0675
NIGHTVIEW_GROSS_CIRCLE_CENTER_OFFSET = 0.180
NIGHTVIEW_GROSS_CROSS_THICKNESS = 0.0045
NIGHTVIEW_GROSS_CROSS_LENGTH = 0.090
NIGHTVIEW_GROSS_CROSS_CENTER_OFFSET = 0.25225

# Get the x, y limits
# [pixels]
IMAGE_WIDTH = 2880
IMAGE_HEIGHT = 640

def get_max_width_and_height(rectangle):
    import numpy as np

    try:
        vertical_sorted = []
        rect = np.array(rectangle, np.float32)
        for [i, j] in rect.argsort(axis=0):
            vertical_sorted.append(rect[j])
        sorted = []
        top2 = np.array(vertical_sorted, np.float32)[0:2,:]
        for [i, j] in top2.argsort(axis=0):
            sorted.append(top2[i])
        bottom2 = np.array(vertical_sorted, np.float32)[2:4,:]
        for [i, j] in bottom2.argsort(axis=0)[::-1]:
            sorted.append(bottom2[i])

        # now that we have our rectangle of points, let's compute
        # the width of our new image
        (tl, tr, br, bl) = sorted
        widthA = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
        widthB = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))

        # ...and now for the height of our new image
        heightA = np.sqrt(((tr[0] - br[0]) ** 2) + ((tr[1] - br[1]) ** 2))
        heightB = np.sqrt(((tl[0] - bl[0]) ** 2) + ((tl[1] - bl[1]) ** 2))

        rectangle = [[point[0], point[1]] for point in sorted]

        # take the maximum of the width and height values to reach
        # our final dimensions
        maxWidth = max(int(widthA), int(widthB))
        maxHeight = max(int(heightA), int(heightB))

    except:
        print("[Error] Unexpected error at get_max_width_and_height()", sys.exc_info()[0])

    return maxWidth, maxHeight

class NightviewTargetSpec(object):
    """A class for defining specification of Nightview target"""
    target_width               = NIGHTVIEW_WIDTH
    target_height              = NIGHTVIEW_HEIGHT
    target_inner_circle_radius = NIGHTVIEW_INNER_CIRCLE_DIAMETER/2.0
    target_outer_circle_radius = NIGHTVIEW_OUTER_CIRCLE_DIAMETER/2.0
    target_circle_offset       = NIGHTVIEW_CIRCLE_CENTER_OFFSET
    target_cross_thickness     = NIGHTVIEW_CROSS_THICKNESS
    target_cross_length        = NIGHTVIEW_CROSS_LENGTH
    target_center_offset       = NIGHTVIEW_GROSS_CROSS_CENTER_OFFSET

    def __init__(self, **kwargs):
        for key in kwargs:
            if key == 'target_width':
                self.target_width = kwargs[key]
            elif key == 'target_height':
                self.target_height = kwargs[key]
            elif key == 'target_inner_circle_radius':
                self.target_inner_circle_radius = kwargs[key]
            elif key == 'target_outer_circle_radius':
                self.target_outer_circle_radius = kwargs[key]
            elif key == 'target_circle_offset':
                self.target_circle_offset = kwargs[key]
            elif key == 'target_cross_thickness':
                self.target_cross_thickness = kwargs[key]
            elif key == 'target_cross_length':
                self.target_cross_length = kwargs[key]
            elif key == 'target_center_offset':
                self.target_center_offset = kwargs[key]

        return super(NightviewTargetSpec, self).__init__()


class NightviewTargetShape(object):
    """A class for generating Nightview target shape"""

    rect_background = []
    rectangles = []
    circle_centers = []
    bounding_boxes = []

    def __init__(self, spec=None):

        if spec == None:
            self.spec = NightviewTargetSpec()
        else:
            self.spec = spec

        return super(NightviewTargetShape, self).__init__()

    def generate_target_shape(self):
        try:
            homography = hm.Homography()

            self.spec.target_center_offset = 0.0
            self.rect_background = homography.generate_rectangle_with_diagonal_2_points_in_2D(
                                [hm.Point2D((self.spec.target_width/2.0) + 0.0, 
                                            (self.spec.target_height/2.0) + 0.0),
                                hm.Point2D(-(self.spec.target_width/2.0) - 0.0, 
                                            -(self.spec.target_height/2.0) - 0.0)])

            rect_cross_vertical = homography.generate_rectangle_with_diagonal_2_points_in_2D(
                                    [hm.Point2D((self.spec.target_cross_thickness/2.0) + 0.0, 
                                                (self.spec.target_cross_length/2.0) + 0.0),
                                    hm.Point2D(-(self.spec.target_cross_thickness/2.0) - 0.0, 
                                                -(self.spec.target_cross_length/2.0) - 0.0)])
            self.rectangles.append(rect_cross_vertical)
            rect_cross_horizontal = homography.generate_rectangle_with_diagonal_2_points_in_2D(
                                    [hm.Point2D((self.spec.target_cross_length/2.0) + 0.0, 
                                                (self.spec.target_cross_thickness/2.0) + 0.0),
                                    hm.Point2D(-(self.spec.target_cross_length/2.0) - 0.0, 
                                                -(self.spec.target_cross_thickness/2.0) - 0.0)])
            self.rectangles.append(rect_cross_horizontal)
            self.circle_centers = [ hm.Point2D(-self.spec.target_circle_offset, 0.0), 
                                    hm.Point2D(self.spec.target_circle_offset, 0.0)]
            right_inner_bounding_box = homography.generate_rectangle_with_diagonal_2_points_in_2D(
                                    [hm.Point2D((   self.spec.target_inner_circle_radius - self.spec.target_circle_offset),
                                                    self.spec.target_inner_circle_radius), 
                                     hm.Point2D((   -self.spec.target_inner_circle_radius - self.spec.target_circle_offset), 
                                                    -self.spec.target_inner_circle_radius)])
            self.bounding_boxes.append(right_inner_bounding_box)
            right_outer_bounding_box = homography.generate_rectangle_with_diagonal_2_points_in_2D(
                                    [hm.Point2D((   self.spec.target_outer_circle_radius - self.spec.target_circle_offset),
                                                    self.spec.target_outer_circle_radius), 
                                     hm.Point2D((   -self.spec.target_outer_circle_radius - self.spec.target_circle_offset), 
                                                    -self.spec.target_outer_circle_radius)])
            self.bounding_boxes.append(right_outer_bounding_box)
            left_inner_bounding_box = homography.generate_rectangle_with_diagonal_2_points_in_2D(
                                    [hm.Point2D((   self.spec.target_inner_circle_radius + self.spec.target_circle_offset),
                                                    self.spec.target_inner_circle_radius), 
                                     hm.Point2D((   -self.spec.target_inner_circle_radius + self.spec.target_circle_offset), 
                                                    -self.spec.target_inner_circle_radius)])
            self.bounding_boxes.append(left_inner_bounding_box)
            left_outer_bounding_box = homography.generate_rectangle_with_diagonal_2_points_in_2D(
                                    [hm.Point2D((   self.spec.target_outer_circle_radius + self.spec.target_circle_offset),
                                                    self.spec.target_outer_circle_radius), 
                                     hm.Point2D((   -self.spec.target_outer_circle_radius + self.spec.target_circle_offset), 
                                                    -self.spec.target_outer_circle_radius)])
            self.bounding_boxes.append(left_outer_bounding_box)

        except:
            print("[Error] Unexpected error at generate_target_shape()", sys.exc_info()[0])

        return 


class NightviewTargetInICS(object):
    """A class for generating target board in Interface Coordinate System"""

    target_background = []    
    target_cross = []
    target_circle_centers = []
    target_bounding_box = []
    rotation = hm.Rotation3D(0.0,0.0,0.0)
    translation = hm.Translation3D(TARGET_X_DISTANCE_IN_ICS,0.0,TARGET_CENTER_HEIGHT)

    def __init__(self, **kwargs):
        try:
            self.shape = None
            self.update(**kwargs)
            if self.shape == None:
                self.shape = NightviewTargetShape()

        except:
            print("[Error] Unexpected error at NightviewTargetInCalibrationCoordinate()", sys.exc_info()[0])
                    
        return super(NightviewTargetInICS, self).__init__()

    def update(self, **kwargs):
        try:
            homography = hm.Homography()

            for key in kwargs:
                if key == 'target_background':
                    self.target_background = kwargs[key]
                elif key == 'target_cross':
                    self.target_cross = kwargs[key]
                elif key == 'target_circle_centers':
                    self.target_circle_centers = kwargs[key]
                elif key == 'target_circle_inner_radius':
                    self.target_circle_inner_radius = kwargs[key]
                elif key == 'target_circle_outer_radius':
                    self.target_circle_outer_radius = kwargs[key]
                elif key == 'rotation':
                    self.rotation = kwargs[key]
                elif key == 'translation':
                    self.translation = kwargs[key]
                elif key == 'shape':
                    self.shape = kwargs[key]

        except:
            print("[Error] Unexpected error at update()", sys.exc_info()[0])
                    
        return

    def generate_target_in_ICS(self):
        try:
            # Generate the target shape
            self.shape.generate_target_shape()

            # Transform the target shape into ICS
            self.set_initial_target_position_in_ICS(self.shape)
        
        except:
            print("[Error] Unexpected error at generate_target_in_ICS()", sys.exc_info()[0])

        return

    def set_initial_target_position_in_ICS(self, target_shape):
        import numpy as np

        try:
            # Set background
            for line in target_shape.rect_background:
                line_in_ICS = [ hm.Point3D(0, line[0].x, line[0].y),
                                hm.Point3D(0, line[1].x, line[1].y)]
                self.target_background.append(line_in_ICS)

            # Set cross lines
            for rect in target_shape.rectangles:
                rect_in_ICS = []
                for line in rect:
                    line_in_ICS = [ hm.Point3D(0, line[0].x, line[0].y),
                                    hm.Point3D(0, line[1].x, line[1].y)]
                    rect_in_ICS.append(line_in_ICS)
                self.target_cross.append(rect_in_ICS)

            # Set circles
            for center_point in target_shape.circle_centers:
                center_point_in_ICS = hm.Point3D(0, center_point.x, center_point.y)
                self.target_circle_centers.append(center_point_in_ICS)

            # Set bounding boxes
            for box in target_shape.bounding_boxes:
                box_in_ICS = []
                for line in box:
                    line_in_ICS = [ hm.Point3D(0, line[0].x, line[0].y),
                                    hm.Point3D(0, line[1].x, line[1].y)]
                    box_in_ICS.append(line_in_ICS)
                self.target_bounding_box.append(box_in_ICS)

        except:
            print("[Error] Unexpected error at set_initial_target_position_in_ICS()", sys.exc_info()[0])

        return

    def rotate_and_translate_target(self, rotation, translation):
        import numpy as np

        try:
            # Change origin to target posture in calibration coordinate
            homography= hm.Homography()
            target_RT = np.array(homography.generate_4x4_RT_matrix(rotation, translation))

            self.new_rects = self.rotate_and_translate_rectangles(
                        target_RT, [self.target_background, self.target_cross[0], self.target_cross[1]])
            self.new_circle_centers = self.rotate_and_translate_points(target_RT, self.target_circle_centers)
            self.new_bounding_boxes = self.rotate_and_translate_rectangles(target_RT, self.target_bounding_box)

        except:
            print("[Error] Unexpected error at rotate_and_translate_target()", sys.exc_info()[0])

        return [self.new_rects, self.new_circle_centers, self.new_bounding_boxes] 

    def rotate_and_translate_points(self, RT_matrix, points):
        import numpy as np
        from copy import deepcopy

        try:
            new_points = deepcopy(points)
            for i, point in enumerate(new_points):
                pt_xyz1 = point.list() + [1]
                new_pt_xyz1 = np.dot(RT_matrix, np.array(pt_xyz1).T)
                new_points[i] = hm.Point3D(new_pt_xyz1[0], new_pt_xyz1[1], new_pt_xyz1[2])

        except:
            print("[Error] Unexpected error at rotate_and_translate_points()", sys.exc_info()[0])

        return  new_points

    def rotate_and_translate_rectangles(self, RT_matrix, rectangles):
        import numpy as np
        from copy import deepcopy

        try:
            new_rects = deepcopy(rectangles)
            for rect in new_rects:
                for line_num in range(4):
                    for point_num in range(2):
                        pt_xyz1 = rect[line_num][point_num].list() + [1]
                        new_pt_xyz1 = np.dot(RT_matrix, np.array(pt_xyz1).T)
                        rect[line_num][point_num] = hm.Point3D(new_pt_xyz1[0], new_pt_xyz1[1], new_pt_xyz1[2])
        except:
            print("[Error] Unexpected error at rotate_and_translate_rectangles()", sys.exc_info()[0])

        return  new_rects

    def draw_target_image(self, image, H_matrix, calibration_parameters, rectangels, circle_centers, bounding_boxes):
        import numpy as np
        import cv2

        try:
            homography= hm.Homography()

            # Project the target on the image plane with the given homography matrix
            background_on_image = homography.compute_pairs_of_2_points_onto_image(H_matrix, rectangels[0])

            #For "cv2.getPerspectiveTransform()" function
            background = []
            for line in background_on_image:
                background.append([line[0].x, line[0].y])
            #maxBackgroundWidth, maxBackgroundHeight = get_max_width_and_height(background)

            # Draw the target image
            # Draw background
            points = np.array([[line[i].int().tuple() for line in background_on_image for i in range(2)]], np.int32)
            cv2.fillConvexPoly( image, points, (255))
            cv2.polylines( image, points, True, (0))

            # Draw cross lines
            rectangls_on_image = []
            for i in range(1, 3):
                rectangls_on_image.append(homography.compute_pairs_of_2_points_onto_image(H_matrix, rectangels[i]))
            for rect_on_image in rectangls_on_image:
                points = np.array([[line[i].int().tuple() for line in rect_on_image for i in range(2)]], np.int32)
                cv2.fillConvexPoly( image, points, (0))

            # Draw circles
            bounding_box_on_image = []
            for bounding_box in bounding_boxes:
                bounding_box_on_image.append(
                    homography.compute_pairs_of_2_points_onto_image(H_matrix, bounding_box))
            # Set bounding box
            right_inner_bounding_box = []
            for line in bounding_box_on_image[0]:
                right_inner_bounding_box.append([line[0].x, line[0].y])
            right_inner_max_wdth, right_inner_max_height = get_max_width_and_height(right_inner_bounding_box)
            right_outer_bounding_box = []
            for line in bounding_box_on_image[1]:
                right_outer_bounding_box.append([line[0].x, line[0].y])
            right_outer_max_wdth, right_outer_max_height = get_max_width_and_height(right_outer_bounding_box)
            left_inner_bounding_box = []
            for line in bounding_box_on_image[2]:
                left_inner_bounding_box.append([line[0].x, line[0].y])
            left_inner_max_wdth, left_inner_max_height = get_max_width_and_height(left_inner_bounding_box)
            left_outer_bounding_box = []
            for line in bounding_box_on_image[3]:
                left_outer_bounding_box.append([line[0].x, line[0].y])
            left_outer_max_wdth, left_outer_max_height = get_max_width_and_height(left_outer_bounding_box)

            circle_centers_on_image = homography.compute_pairs_of_2_points_onto_image(H_matrix, [circle_centers])
            point = circle_centers_on_image[0][0].int().tuple()
            axis = (int(right_outer_max_wdth/2.0), int(right_outer_max_height/2.0))
            cv2.ellipse(image, point, axis, 
                        -calibration_parameters.rotation.roll, 0, 360, (0), -1)
            axis = (int(right_inner_max_wdth/2.0), int(right_inner_max_height/2.0))
            cv2.ellipse(image, point, axis, 
                        -calibration_parameters.rotation.roll, 0, 360, (255), -1)        
            point = circle_centers_on_image[0][1].int().tuple()
            axis = (int(left_outer_max_wdth/2.0), int(left_outer_max_height/2.0))
            cv2.ellipse(image, point, axis, 
                        -calibration_parameters.rotation.roll, 0, 360, (0), -1)
            axis = (int(left_inner_max_wdth/2.0), int(left_inner_max_height/2.0))
            cv2.ellipse(image, point, axis, 
                        -calibration_parameters.rotation.roll, 0, 360, (255), -1)        

        except:
            print("[Error] Unexpected error at draw_target_image()", sys.exc_info()[0])

        return background

    def generate_target_image_using_homography(self, image, H_matrix, calibration_parameters):
        import numpy as np
        import matplotlib.pyplot    as plt
        import cv2

        try:
            homography= hm.Homography()
            
            ## Translate the target regarding designated position
            #[no_rotation_rectangels, 
            #no_rotation_points, 
            #no_rotation_boxes] = self.rotate_and_translate_target(hm.Rotation3D(0.0,0.0,0.0), self.translation)

            #calibration_parameters.location.z = self.translation.z
            #calibration_parameters.rotation.roll = 0
            #calibration_parameters.rotation.pitch = 0
            #calibration_parameters.rotation.yaw = 0
            #H_3x4 = homography.generate_3x4_homography_matrix(0.0, calibration_parameters)

            # Project the target on the image plane with the given homography matrix
            #background_on_image = homography.compute_pairs_of_2_points_onto_image(H_3x4, no_rotation_rectangels[0])

            ## Draw the target image
            #points = np.array([[line[i].int().tuple() for line in background_on_image for i in range(2)]], np.int32)
            #cv2.fillConvexPoly( image, points, (255))
            #cv2.polylines( image, points, True, (0))

            #previous_rect = self.draw_target_image(image, H_3x4, no_rotation_rectangels, no_rotation_points, no_rotation_boxes)
            #maxWidth, maxHeight = get_max_width_and_height(previous_rect)

            #width_offset = int(previous_rect[0][0]) + 2
            #height_offset = int(previous_rect[0][1]) + 2
            #target_image = image[ height_offset : height_offset + maxHeight, width_offset : width_offset + maxWidth]
            #cv2.imwrite('target_image.png', target_image)

            # Rotate and translate the target regarding designated position
            [rectangels, points, boxes] = self.rotate_and_translate_target(self.rotation, self.translation)

            current_rect = self.draw_target_image(  image, H_matrix, calibration_parameters,
                                                    rectangels, points, boxes)

            ## Get the perspective matrix for warping
            ##from copy import deepcopy
            ##rect = deepcopy(previous_rect)
            ##rect[0][0] += 100
            #M = cv2.getPerspectiveTransform(previous_rect, rect)
            #H, status = cv2.findHomography( np.array(previous_rect, np.float32), 
            #                                np.array(current_rect, np.float32))

            ##img = cv2.imread('target_image.png')
            #maxWidth, maxHeight = get_max_width_and_height(previous_rect)

            #dst = cv2.warpPerspective(target_image, H, (maxWidth, maxHeight))

            #cv2.imshow('img', target_image)
            #cv2.imshow('dst', dst)
            #cv2.waitKey(0)

        except:
            print("[Error] Unexpected error at generate_target_image_using_homography()", sys.exc_info()[0])

        return image


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

    try:
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
            coords = [np.random.randint(0, i - 1, int(num_salt)) for i in image.shape[:2]]
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
            thickness = [np.random.randint(1, i - 1, num_lines) for i in [30, 30]]
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
    except:
        print("[Error] Unexpected error at main()", sys.exc_info()[0])

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
    #import userinput
    import numpy as np
    import cv2

    try:
        # Read parameters from files
        fi = fileinput.FileInput()
        (calibration_parameters, front_axis_height) = fi.read_input_parameters_from_xml("Calibration.xml")
        (target_position, target_type) = fi.read_input_parameters_from_xml("InstallationInformation.xml")
        (target_angle, noise_config) = fi.read_input_parameters_from_xml("SECAL_target_variation.xml")
        target_position.z += front_axis_height

        # Generate MPC5.5 targets for calibration
        #ui = userinput.UserInput()

        nightview_target = NightviewTargetShape(NightviewTargetSpec())
        target_viewer = NightviewTargetInICS(   shape=nightview_target, 
                                                rotation=target_angle, 
                                                translation=target_position)
        target_viewer.generate_target_in_ICS()

        # Generate homography matrix
        homography = hm.Homography()
        H_3x4 = homography.generate_3x4_homography_matrix(front_axis_height, calibration_parameters)
        H_4x4 = homography.generate_4x4_homography_matrix(front_axis_height, calibration_parameters)

        # Create a white image.
        #img = np.full((IMAGE_HEIGHT, IMAGE_WIDTH, 1), 0, dtype=np.uint8)

        # Create a white image.
        img = np.full((IMAGE_HEIGHT, IMAGE_WIDTH, 1), 255, dtype=np.uint8)
        img = noisy("lines", img)
        img = noisy("ortholines", img)

        # Draw the defined target on the image.
        img = target_viewer.generate_target_image_using_homography(img, H_3x4, calibration_parameters)
        #cv2.imwrite('GT_image.png', img)

        #kernel = np.ones((5,5), np.float32)/25
        salt_and_pepper_img = noisy("s&p", img)
        #poisson_img = noisy("poisson", img)
        #speckle_img = noisy("speckle", img)
        blurred_img2 = cv2.blur(salt_and_pepper_img, (5,5))
        #gaussian_blurred_img = cv2.GaussianBlur(speckle_img, (5,5), 0)
        #median_blurred_img = cv2.medianBlur(img, 5)
        #brightened_img = brightness(salt_and_pepper_img)
        #contrast_img = contrast(brightened_img)
        #img = cv2.filter2D(contrast_img, -1, kernel)

        #cv2.imshow('blurred_img', blurred_img)
        cv2.imshow('blurred_img2', blurred_img)
        #cv2.imshow('gaussian_blurred_img', blurred_img)
        #cv2.imshow('median_blurred_img', blurred_img)
        #cv2.imshow('salt_and_pepper_img', salt_and_pepper_img)
        #cv2.imshow('poisson_img', poisson_img)
        #cv2.imshow('speckle_img', speckle_img)
        #cv2.imshow('brightened_img', brightened_img)
        #cv2.imshow('contrast_img', contrast_img)

        store_img16 = img.astype('uint16')
        store_img16 *= 32
        
        bin_file = open("GT_image.bin", 'wb')
        bin_file.write(store_img16)
        bin_file.close()

        cv2.imwrite('GT_image_16.png', store_img16)


        # Find and show the ground truth points
        ground_truth_points_list = []
        #debug_gt_x_fronted_list = []

        with open('GT.txt', 'w') as fileout:
            for point in target_viewer.new_circle_centers:
                ground_truth_point = homography.compute_3d_to_2d_with_3x4_homography(H_3x4, point)
                #debug_gt_x_fronted = homography.compute_3d_to_3d_with_4x4_homography(H_4x4, point)
                ground_truth_points_list.append(ground_truth_point)
                #debug_gt_x_fronted_list.append(debug_gt_x_fronted)

                # Write ground truth center positions in ICS
                point_in_cal = homography.convert_point_in_ICS_to_calibration_coordinate(front_axis_height, point)
                fileout.write(str(point_in_cal.tuple()))
            fileout.write("\n")
            #for debug_gt_x_fronted in debug_gt_x_fronted_list:
            #    fileout.write(str(debug_gt_x_fronted.tuple()))
            #fileout.write("\n")
            for ground_truth_point in ground_truth_points_list:
                # Write ground truth center positions on image
                fileout.write(str(ground_truth_point.tuple()))
                #cv2.circle(img, ground_truth_point.int().tuple(), 7, (255), 3)

        resized_img = cv2.resize(img, None, fx=0.5, fy=0.5, interpolation=cv2.INTER_CUBIC)
        cv2.imshow('GT_image', resized_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    except:
        print("[Error] Unexpected error at main()", sys.exc_info()[0])
    
    return

if __name__ == '__main__':
    main()