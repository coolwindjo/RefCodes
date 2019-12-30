# -*- coding: utf-8 -*-
# @package Optical Flow Image and Vanishing Point GT Creator and Visualizer

import sys
import homography as hm
import fileinput

# Get the x, y limits
HOMOGRAPHY_IMAGE_WIDTH = 2880
HOMOGRAPHY_IMAGE_HEIGHT = 640

class OpticalFlowFromFile(object):
    """A class for loading of optical flows"""

    def __init__(self, **kwargs):
        for key in kwargs:
            if key == 'filename':
                self.filename = kwargs[key]

        return super(OpticalFlowFromFile, self).__init__()

    def load_optical_flows(self):
        try:
            fi = fileinput.FileInput()
            optical_flows_file, confidences_file = fi.read_optical_flows_and_confidences_from_csv(self.filename)
            optical_flows = []
            confidences = []
            for optical_flow, confidence in zip(optical_flows_file, confidences_file):
                optical_flows.append(
                    [hm.Point2D(optical_flow[0][0], optical_flow[1][0]),
                    hm.Point2D(optical_flow[0][1], optical_flow[1][1])])
                confidences.append(confidence)

        except:
            print("[Error] Unexpected error at load_optical_flows()", sys.exc_info()[0])

        return optical_flows, confidences

    def load_optical_flow_image(self, filename, image_width, image_height):
        from matplotlib import pyplot as plt
        import numpy as np
        import cv2

        try:
            fi = fileinput.FileInput()
            binary = fi.load_binary_image(filename, HOMOGRAPHY_IMAGE_WIDTH, HOMOGRAPHY_IMAGE_HEIGHT)
            resized_binary = cv2.resize(binary, (image_width, image_height), interpolation=cv2.INTER_CUBIC)
            resized_binary >>= 4
            bin_8bit = np.uint8(resized_binary)
            # resized_binary.dtype = 'uint8'

            rgb_img = cv2.cvtColor(bin_8bit, cv2.COLOR_GRAY2RGB)
            cv2.imwrite('binary_cv.png', rgb_img)
            self.image = rgb_img

        except:
            print("[Error] Unexpected error at load_optical_flow_image()", sys.exc_info()[0])

        return self.image


class OpticalFlowSpec(object):
    """A class for defining specification of optical flows"""

    def __init__(self, **kwargs):
        for key in kwargs:
            if key == 'num_features':
                self.num_features = kwargs[key]
            elif key == 'frame_per_second':
                self.frame_per_second = kwargs[key]
            elif key == 'velocity':
                self.velocity = kwargs[key]*0.27778 #0.27778 = 1000/3600
            elif key == 'yaw_rate':
                self.yaw_rate = kwargs[key]*0.017453 #0.017453 = PI/180

        return super(OpticalFlowSpec, self).__init__()


class OpticalFlowInICS(object):
    """A class for generating optical flows in Interface Coordinate System"""

    rotation = hm.Rotation3D(0.0,0.0,0.0)
    translation = hm.Translation3D(0.0,0.0,0.0)

    def __init__(self, spec=None, **kwargs):
        try:
            self.update(**kwargs)
            self.shape = None
            if spec == None:
                self.spec = OpticalFlowSpec()
            else:
                self.spec = spec
        except:
            print("[Error] Unexpected error at OpticalFlowInICS()", sys.exc_info()[0])
                    
        return super(OpticalFlowInICS, self).__init__()

    def update(self, **kwargs):
        try:
            for key in kwargs:
                if key == 'rotation':
                    self.rotation = kwargs[key]
                elif key == 'translation':
                    self.translation = kwargs[key]
                elif key == 'x_offset':
                    self.x_offset = kwargs[key]
                elif key == 'z_offset':
                    self.z_offset = kwargs[key]
                elif key == 'x_half_limit':
                    self.x_half_limit = kwargs[key]
                elif key == 'y_half_limit':
                    self.y_half_limit = kwargs[key]
                elif key == 'z_half_limit':
                    self.z_half_limit = kwargs[key]
                elif key == 'H_matrix':
                    self.H_matrix = kwargs[key]

        except:
            print("[Error] Unexpected error at update()", sys.exc_info()[0])
                    
        return

    def generate_random_float(self, offset, half_limit, num_decimal_places):
        import numpy as np

        try:
            num_changing_dec_places = np.power(10, num_decimal_places)
            changed_half_limit = half_limit * num_changing_dec_places

            val = offset * num_changing_dec_places + np.random.randint(-changed_half_limit, changed_half_limit)
            val /= num_changing_dec_places

        except:
            print("[Error] Unexpected error at generate_random_float()", sys.exc_info()[0])

        return val

    def generate_features(self, optical_flow_spec):
        try:
            features = [
                hm.Point3D(self.generate_random_float(self.x_offset, self.x_half_limit, 3),
                           self.generate_random_float(0, self.y_half_limit, 3),
                           self.generate_random_float(self.z_offset, self.z_half_limit, 3))
                    for i in range(optical_flow_spec.num_features)
                ]

        except:
            print("[Error] Unexpected error at generate_features()", sys.exc_info()[0])

        return features

    def set_optical_flow_in_ICS(self, optical_flow_spec, homography_matrix, begin_points):
        try:
            # Calculate moved distance for every frame
            self.moved_distance_x = self.spec.velocity/self.spec.frame_per_second

            # Set end points and optical flow lines
            self.lines = []
            self.end_points = []
            for point in begin_points:
                end_point = hm.Point3D.copy(point).move(-self.moved_distance_x,0,0)
                self.end_points.append(end_point)
                self.lines.append([point, end_point])

        except:
            print("[Error] Unexpected error at set_optical_flow_in_ICS()", sys.exc_info()[0])

        return

    def generate_optical_flow_in_ICS(self):
        try:
            # Generate the features to be tracked
            self.begin_points = self.generate_features(self.spec)

            # Transform the optical flows into ICS
            self.set_optical_flow_in_ICS(self.spec, self.H_matrix, self.begin_points)
        
        except:
            print("[Error] Unexpected error at generate_optical_flow_in_ICS()", sys.exc_info()[0])

        return

    def rotate_and_translate_points(self, RT_matrix, points):
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

    def draw_optical_flow_image(self, image, image_width, image_height, H_matrix):
        import cv2
        import numpy as np

        try:
            hm_method = hm.Homography()

            # Draw the optical flow lines
            self.optical_flow_lines = hm_method.compute_pairs_of_2_points_onto_image(H_matrix, self.lines)
            sclae_u = float(image_width/HOMOGRAPHY_IMAGE_WIDTH)
            sclae_v = float(image_height/HOMOGRAPHY_IMAGE_HEIGHT)
            for i in range(len(self.optical_flow_lines)):
                for j in range(2):
                    self.optical_flow_lines[i][j].x *= sclae_u
                    self.optical_flow_lines[i][j].y *= sclae_v

            self.confidences = []
            for i in range(len(self.lines)):
                stdev = np.random.randint(1, 30)
                conf = 0.0 + 1/(stdev*stdev)
                # conf = 0.0025 + 0.5 + self.generate_random_float(0, 0.49876, 5) # conf = 1/var = 1/20^2 
                self.optical_flow_lines[i][1].y += stdev*float(np.random.normal(0,1,1))
                # conf = 1
                self.confidences.append([0, conf])

            for optical_flow in self.optical_flow_lines:
                cv2.line(image, optical_flow[0].int().tuple(), optical_flow[1].int().tuple(), (0))

        except:
            print("[Error] Unexpected error at draw_optical_flow_image()", sys.exc_info()[0])

        return image

    def draw_optical_flow_image_with_jerk(self, image, H_mat_1, H_mat_2):
        import cv2

        try:
            hm_method = hm.Homography()

            # Draw the optical flow lines
            self.optical_flow_lines = []
            for line in self.lines:
                point_pair_pt1_computed = hm_method.compute_3d_to_2d_with_3x4_homography(H_mat_1, line[0])
                point_pair_pt2_computed = hm_method.compute_3d_to_2d_with_3x4_homography(H_mat_2, line[1])
                self.optical_flow_lines.append([point_pair_pt1_computed, point_pair_pt2_computed])

            for optical_flow in self.optical_flow_lines:
                cv2.line(image, optical_flow[0].int().tuple(), optical_flow[1].int().tuple(), True, (0))

        except:
            print("[Error] Unexpected error at draw_optical_flow_image_with_jerk()", sys.exc_info()[0])

        return image





def get_optical_flow_samples(optical_flow_lines, confidences, num_samples):
    import numpy as np

    try:
        optical_flow_samples = []
        confidence_samples = []
        count = 0
        index_list = list(np.random.permutation(len(optical_flow_lines)))
        for i in index_list:
            if line_length(optical_flow_lines[i]) > 400 :
                optical_flow_samples.append(optical_flow_lines[i]) 
                confidence_samples.append(confidences[i]) 
                count += 1
                if count >= num_samples:
                    break

    except:
        print("[Error] Unexpected error at get_optical_flow_samples()", sys.exc_info()[0])

    return optical_flow_samples, confidence_samples

def line_length(line=[hm.Point2D(), hm.Point2D()]):
    #import numpy as np

    try:
        x2_sub_x1 = line[1].x-line[0].x
        # y1_sub_y2 = line[0].y-line[1].y
        y2_sub_y1 = line[1].y-line[0].y
        line_len = (x2_sub_x1*x2_sub_x1-y2_sub_y1*y2_sub_y1)

    except:
        print("[Error] Unexpected error at line_length()", sys.exc_info()[0])

    return line_len

def get_converging_point_with_crossing_points(num_line_pairs):
    import itertools as it

    try:
        optical_flow_combination2 = it.combinations(self.optical_flow_lines, 2)
        sum_u = 0
        sum_v = 0
        count = 0
        for lineA, lineB in optical_flow_combination2:
            if self.line_length(lineA) > 10000 and self.line_length(lineB) > 10000:
                x1y2_sub_y1x2 = lineA[0].x*lineA[1].y - lineA[0].y*lineA[1].x
                x3_sub_x4 = lineB[0].x - lineB[1].x
                x1_sub_x2 = lineA[0].x - lineA[1].x
                x3y4_sub_y3x4 = lineB[0].x*lineB[1].y - lineB[0].y*lineB[1].x
                y3_sub_y4 = lineB[0].y - lineB[1].y
                y1_sub_y2 = lineA[0].y - lineA[1].y
                denominator = (x1_sub_x2*y3_sub_y4 - y1_sub_y2*x3_sub_x4)
                if denominator == 0:
                    sum_u += 0
                    sum_v += 0
                else:
                    sum_u += (x1y2_sub_y1x2*x3_sub_x4 - x1_sub_x2*x3y4_sub_y3x4)/denominator
                    sum_v += (x1y2_sub_y1x2*y3_sub_y4 - y1_sub_y2*x3y4_sub_y3x4)/denominator
                    count += 1
                    if (count >= num_line_pairs):
                        break
            else:
                continue
        if count <= 0:
            avg_u = 0
            avg_v = 0
        else:
            avg_u = sum_u/count
            avg_v = sum_v/count
            
    except:
        print("[Error] Unexpected error at get_converging_point_with_crossing_points()", sys.exc_info()[0])

    return hm.Point2D(avg_u, avg_v)

def least_square_with_perpendicular_distance(weight_list, delta_y_list, delta_x_list, x2y1_sub_y2x1_list):
    try:
        sum_delta_x_square = 0
        sum_delta_y_square = 0
        sum_delta_y_delta_x = 0
        sum_delta_x_x2y1_sub_y2x1 = 0
        sum_delta_y_x2y1_sub_y2x1 = 0
        for weight, delta_y, delta_x, x2y1_sub_y2x1 in zip(weight_list, delta_y_list, delta_x_list, x2y1_sub_y2x1_list):
            if weight > 0:
                sum_delta_y_square += delta_y*delta_y
                sum_delta_x_square += delta_x*delta_x
                sum_delta_y_delta_x += delta_y*delta_x
                sum_delta_y_x2y1_sub_y2x1 += delta_y*x2y1_sub_y2x1
                sum_delta_x_x2y1_sub_y2x1 += delta_x*x2y1_sub_y2x1
        denominator = sum_delta_y_square*sum_delta_x_square - sum_delta_y_delta_x*sum_delta_y_delta_x
        numerator_x = -sum_delta_x_square*sum_delta_y_x2y1_sub_y2x1 + sum_delta_y_delta_x*sum_delta_x_x2y1_sub_y2x1
        numerator_y = -sum_delta_y_delta_x*sum_delta_y_x2y1_sub_y2x1 + sum_delta_y_square*sum_delta_x_x2y1_sub_y2x1
        
        if denominator == 0:
            x_0 = 0
            y_0 = 0
        else:
            x_0 = numerator_x/denominator
            y_0 = numerator_y/denominator
            
    except:
        print("[Error] Unexpected error at least_square_with_perpendicular_distance()", sys.exc_info()[0])

    return x_0, y_0

def weighted_least_square_with_perpendicular_distance(weight_list, delta_y_list, delta_x_list, x2y1_sub_y2x1_list):
    try:
        sum_weight_delta_x_square = 0
        sum_weight_delta_y_delta_x = 0
        sum_weight_delta_y_square = 0
        sum_weight_delta_x_x2y1_sub_y2x1 = 0
        sum_weight_delta_y_x2y1_sub_y2x1 = 0
        for weight, delta_y, delta_x, x2y1_sub_y2x1 in zip(weight_list, delta_y_list, delta_x_list, x2y1_sub_y2x1_list):
            if weight > 0:
                sum_weight_delta_y_square += weight*delta_y*delta_y
                sum_weight_delta_x_square += weight*delta_x*delta_x
                sum_weight_delta_y_delta_x += weight*delta_y*delta_x
                sum_weight_delta_y_x2y1_sub_y2x1 += weight*delta_y*x2y1_sub_y2x1
                sum_weight_delta_x_x2y1_sub_y2x1 += weight*delta_x*x2y1_sub_y2x1
        denominator = sum_weight_delta_y_square*sum_weight_delta_x_square - sum_weight_delta_y_delta_x*sum_weight_delta_y_delta_x
        numerator_x = -sum_weight_delta_x_square*sum_weight_delta_y_x2y1_sub_y2x1 + sum_weight_delta_y_delta_x*sum_weight_delta_x_x2y1_sub_y2x1
        numerator_y = -sum_weight_delta_y_delta_x*sum_weight_delta_y_x2y1_sub_y2x1 + sum_weight_delta_y_square*sum_weight_delta_x_x2y1_sub_y2x1
        
        if denominator == 0:
            x_0 = 0
            y_0 = 0
        else:
            x_0 = numerator_x/denominator
            y_0 = numerator_y/denominator
            
    except:
        print("[Error] Unexpected error at weighted_least_square_with_perpendicular_distance()", sys.exc_info()[0])

    return x_0, y_0

def get_converging_point(optical_flow_lines, confidences):
    try:
        delta_y_list = []
        delta_x_list = []
        x2y1_sub_y2x1_list= []
        weight_list = []
        count = 0
        for line, confidence in zip(optical_flow_lines, confidences):
            delta_y_list.append((line[1].y-line[0].y))
            delta_x_list.append((line[1].x-line[0].x))
            x2y1_sub_y2x1_list.append((line[1].x*line[0].y - line[1].y*line[0].x))
            variance_u = 0
            variance_v = 0
            if confidence[0] != 0:
                variance_u = 1/confidence[0]
            if confidence[1] != 0:
                variance_v = 1/confidence[1]
            # if (line[0].x == 0) and (line[1].y == 0):
            #     weight = 0 
            # else:
                # weight = 1/(variance_u*line[0].y*line[0].y + variance_v*line[0].x*line[0].x)
            weight = 1/(variance_u + variance_v)
            weight_list.append(weight)

        # conv_pt_u, conv_pt_v = least_square_with_perpendicular_distance(weight_list, delta_y_list, delta_x_list, x2y1_sub_y2x1_list)
        conv_pt_u, conv_pt_v = weighted_least_square_with_perpendicular_distance(weight_list, delta_y_list, delta_x_list, x2y1_sub_y2x1_list)
            
    except:
        print("[Error] Unexpected error at get_converging_point()", sys.exc_info()[0])

    return hm.Point2D(conv_pt_u, conv_pt_v)


def main():
    # import fileinput
    #import userinput
    import numpy as np
    import cv2

    try:
        # Read parameters from files
        fi = fileinput.FileInput()
        (calibration_parameters, front_axis_height) = fi.read_input_parameters_from_xml("Calibration.xml")
        (FPS, num_flows, num_line_pairs, image_width, image_height,
            x_offset, x_half_limit, y_half_limit, z_half_limit) = fi.read_input_parameters_from_xml("OpticalFlowConfig.xml")
        (vel, jerk_z, yaw_rate, jerk_pitch) = fi.read_input_parameters_from_xml("VehicleMotion.xml")

        # Generate homography matrix
        hm_method = hm.Homography()
        H_3x4 = hm_method.generate_3x4_homography_matrix(front_axis_height, calibration_parameters)
        num_samples = num_line_pairs

        # Generate optical flow for calibration
        #ui = userinput.UserInput()

        z_offset = front_axis_height + calibration_parameters.location.z

        gen_optical_flows = False
        # gen_optical_flows = True 
        if gen_optical_flows == True:
            # Create a white image.
            img = np.full((image_height, image_width, 1), 255, dtype=np.uint8)
            np.random.seed([0])
            optical_flow_spec = OpticalFlowSpec(num_features=num_flows, frame_per_second=FPS,
                                                velocity=vel, yaw_rate=yaw_rate)
            optical_flow = OpticalFlowInICS(optical_flow_spec, x_offset=x_offset, z_offset=z_offset,
                                            x_half_limit=x_half_limit, y_half_limit=y_half_limit, z_half_limit=z_half_limit,
                                            H_matrix=H_3x4)
            optical_flow.generate_optical_flow_in_ICS()

            # Draw the defined target on the image.
            #calibration_parameters.rotation.pitch += jerk_pitch
            #calibration_parameters.location.z += jerk_z
            #H2_3x4 = hm_method.generate_3x4_homography_matrix(front_axis_height, calibration_parameters)
            img = optical_flow.draw_optical_flow_image(img, image_width, image_height, H_3x4)
            #img = optical_flow.draw_optical_flow_image_with_jerk(img, H_3x4, H2_3x4)
            num_trials = int(np.floor(num_flows/num_samples))
            num_trials = 1
        else:
            optical_flow_file = OpticalFlowFromFile(filename="OpticalFlow.csv")
            opt_flows, conf = optical_flow_file.load_optical_flows()
            num_trials = 1
            opt_flows_samples = []
            conf_samples = []
            np.random.seed([0])

        # Try several times
        sum_u = 0
        sum_v = 0
        sum_square_u = 0
        sum_square_v = 0
        if num_trials <= 0:
            num_trials = 1
        for _ in range(num_trials):
            if gen_optical_flows == True:
                opt_flows_sample, conf_sample = get_optical_flow_samples(
                    optical_flow.optical_flow_lines, optical_flow.confidences, num_samples)
            else:
                opt_flows_sample, conf_sample = get_optical_flow_samples(opt_flows, conf, num_samples)
                opt_flows_samples.append(opt_flows_sample)
                conf_samples.append(conf_sample)
                
            converging_point = get_converging_point(opt_flows_sample, conf_sample)
            print(converging_point.x, converging_point.y)
            sum_u += converging_point.x
            sum_square_u += converging_point.x*converging_point.x
            sum_v += converging_point.y
            sum_square_v += converging_point.y*converging_point.y


        # Find and show the ground truth points
        C_u = calibration_parameters.intrinsic.C_u
        C_v = calibration_parameters.intrinsic.C_v
        F_u = calibration_parameters.intrinsic.F_u
        F_v = calibration_parameters.intrinsic.F_v
        Pitch = calibration_parameters.rotation.pitch*0.017453 #0.017453 = PI/180
        Yaw = calibration_parameters.rotation.yaw*0.017453 #0.017453 = PI/180
        ground_truth_point = hm.Point2D(
            (C_u + F_u*np.tan(Yaw))*image_width/HOMOGRAPHY_IMAGE_WIDTH, 
            (C_v + F_v*np.tan(Pitch))*image_height/HOMOGRAPHY_IMAGE_HEIGHT)

        # Write on text files
        with open('OpticalFlowGT.txt', 'w') as fileout:
            fileout.write(str(ground_truth_point.tuple()))
        if ground_truth_point.x < 0.0 or ground_truth_point.y < 0.0:
            ground_truth_point.x = 0
            ground_truth_point.y = 0

        with open('OpticalFlowConverge.txt', 'w') as fileout:
            fileout.write(str(converging_point.tuple()))
        if converging_point.x < 0.0 or converging_point.y < 0.0:
            converging_point.x = 0
            converging_point.y = 0

        # Output the cost
        delta_u = ground_truth_point.x - converging_point.x
        delta_v = ground_truth_point.y - converging_point.y
        distance = np.sqrt(delta_u*delta_u + delta_v*delta_v)

        # Calculate statistics
        if num_trials > 1:
            converging_point.x = sum_u/num_trials
            converging_point.y = sum_v/num_trials
            variance_u = sum_square_u/num_trials-(converging_point.x*converging_point.x)
            variance_v = sum_square_v/num_trials-(converging_point.y*converging_point.y)
            stdev_u = float(np.sqrt(variance_u))
            stdev_v = float(np.sqrt(variance_v))
            buf = "%.3f with Var(%.3f, %.3f)" % (distance, stdev_u, stdev_v)
        else:
            buf = "%.3f from GT(%.3f, %.3f)" % (distance, ground_truth_point.x, ground_truth_point.y)
        print(buf)

        # Draw optical flows on the forward view image
        if gen_optical_flows == False:
            center_u = C_u*image_width/HOMOGRAPHY_IMAGE_WIDTH
            img = optical_flow_file.load_optical_flow_image("InspectImage.bin", image_width, image_height)
            color_factor = 255/15
            for opt_flows_sample, conf_sample in zip(opt_flows_samples, conf_samples) :
                for optical_flow, confidence in zip(opt_flows_sample, conf_sample) :
                    if optical_flow[0].x > center_u and optical_flow[0].x > optical_flow[1].x:
                        cv2.line(img, optical_flow[0].int().tuple(), optical_flow[1].int().tuple(), (255,0,255))
                    elif optical_flow[0].x < center_u and optical_flow[0].x < optical_flow[1].x:
                        cv2.line(img, optical_flow[0].int().tuple(), optical_flow[1].int().tuple(), (255,0,255))
                    else:
                        # High ConfU, High ConfV : Green
                        # High ConfU, Low ConfV : Yellow
                        # Low ConfU, High ConfV : Cyan
                        # Low ConfU, Low ConfV : White
                        B = 255-int(color_factor*confidence[0])
                        R = 255-int(color_factor*confidence[1])
                        cv2.line(img, optical_flow[0].int().tuple(), optical_flow[1].int().tuple(), (B,255,R))

        # Draw GT and converging point
        cv2.circle(img, ground_truth_point.int().tuple(), 15, (0,0,0), 3)
        cv2.circle(img, converging_point.int().tuple(), 3, (0,255,0), 3)
        cv2.putText(img, buf, (10,100), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,255), 2, cv2.LINE_AA)
        #cv2.circle(img, converging_point_2.int().tuple(), 10, (0), 3)

        # Show the image
        resized_img = cv2.resize(img, (image_width, image_height), interpolation=cv2.INTER_LINEAR)
        cv2.imshow('OpticalFlowGT_image', resized_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    except:
        print("[Error] Unexpected error at main()", sys.exc_info()[0])
    
    return

if __name__ == '__main__':
    main()