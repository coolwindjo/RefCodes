# -*- coding: utf-8 -*-
##  @package FileInput
#   Documentation for this module
#
#   More details
import sys

class FileInput(object):
    """A class for getting input from a user"""
    
    def __init__(self, *args, **kwargs):
        return super(FileInput, self).__init__(*args, **kwargs)

    def load_binary_image(self, filename, width, height):
        import numpy as np

        try:
            binary = np.fromfile(filename, dtype='int16', sep="")
            binary = binary.reshape([height, width])

        except:
            print("[Error] Unexpected error at load_binary_image().", sys.exc_info()[0])
        return binary
    
    def read_optical_flows_and_confidences_from_csv(self, filename):

        try:
            optical_flows = []
            confidences = []
            with open(filename, "r") as csvfile:
                data_lines = csvfile.readlines()
                for data_line in data_lines :
                    data = data_line.split(',')
                    begin_point_u = int(data[0])
                    end_point_u = begin_point_u + int(data[1])
                    confidence_u = int(data[2])
                    begin_point_v = int(data[3])
                    end_point_v = begin_point_v + int(data[4])
                    confidence_v = int(data[5])
                    optical_flows.append([[begin_point_u, end_point_u],[begin_point_v, end_point_v]])
                    confidences.append([confidence_u, confidence_v])

        except :
            print("[Error] Unexpected error at read_optical_flows_from_csv().", sys.exc_info()[0])
                        
        return optical_flows, confidences

    def read_3d_coordinates_from_numbers(self, word):

        try:
            coordinate = []
            numbers = word.split(',')
            coordinate.append(int(numbers[0]))
            coordinate.append(int(numbers[1]))
            coordinate.append(int(numbers[2]))
        except :
            print("[Error] Unexpected error at read_3d_coordinates_from_numbers().", sys.exc_info()[0])
            print("len(numbers) = " + str(len(numbers)))

        return  coordinate

    def read_world_model_from_txt(self, filename):

        try:
            sharp_num = 0
            linesX = []
            linesY = []
            linesZ = []
            rectsX = []
            rectsY = []
            rectsZ = [] 

            with open(filename, "r") as textfile:
                textlines = textfile.readlines()
                for textline in textlines:
                    words = textline.split()
                    if (words[0] != '#'):
                        if (sharp_num == 2):
                            line_begin = self.read_3d_coordinates_from_numbers(words[0])
                            line_end = self.read_3d_coordinates_from_numbers(words[1])
                            linesX.append([line_begin[0], line_end[0]])
                            linesY.append([line_begin[1], line_end[1]])
                            linesZ.append([line_begin[2], line_end[2]])
                        elif (sharp_num == 3):
                            rect_begin = self.read_3d_coordinates_from_numbers(words[0])
                            rect_end = self.read_3d_coordinates_from_numbers(words[1])
                            rectsX.append([rect_begin[0], rect_end[0]])
                            rectsY.append([rect_begin[1], rect_end[1]])
                            rectsZ.append([rect_begin[2], rect_end[2]])
                        else:
                            pass
                    else:
                        sharp_num += 1
        except :
            print("[Error] Unexpected error at read_world_model_from_txt().", sys.exc_info()[0])
            print("len(words) = " + str(len(words)))
                        
        return linesX, linesY, linesZ, rectsX, rectsY, rectsZ 

    def read_input_parameters_from_xml(self, filename):

        import homography as hm
        import xml.etree.ElementTree

        try:
            e = xml.etree.ElementTree.parse(filename).getroot()
            parameters = e.find("parameterTable")
            #parameter_list = parameters.findall("parameter")
            parameter_dict = {}
                
            for param in parameters:
                parameter_dict[param.attrib["name"]] = param.attrib["value"]
            
            return_tuple = (0, 0)
            front_axis_height = float(parameter_dict.get("fFrontAxisHeight", 0.0))
            target_position = hm.Point3D(-float(parameter_dict.get("fTargetPosition_x", 0)),0.0,0.0)
            target_angle = hm.Rotation3D(float(parameter_dict.get("fTargetAngle_roll", 0xFFFFFFFF)),0.0,0.0)
            frame_per_second = int(parameter_dict.get("nFPS", 0))
            use_default = int(parameter_dict.get("use_default", 0xFFFFFFFF))
            if front_axis_height != 0.0:
                camera_loc = hm.Point3D(float(parameter_dict.get("fEffectiveCameraPosition_x", 0.0)),
                                        float(parameter_dict.get("fEffectiveCameraPosition_y", 0.0)), 
                                        float(parameter_dict.get("fEffectiveCameraPosition_z", 0.0)))
                camera_rot = hm.Rotation3D( float(parameter_dict.get("fExtrinsicDeviation_roll_SECAL", 0.0)), 
                                            float(parameter_dict.get("fExtrinsicDeviation_pitch_SECAL", 0.0)), 
                                            float(parameter_dict.get("fExtrinsicDeviation_yaw_SECAL", 0.0)))
                camera_int = hm.Intrinsic(   F_u=float(parameter_dict.get("fFocalLength_u_undistorted", 0.0)), 
                                            F_v=float(parameter_dict.get("fFocalLength_v_undistorted", 0.0)), 
                                            C_u=float(parameter_dict.get("fOpticalCenter_u_undistorted", 0.0)),
                                            C_v=float(parameter_dict.get("fOpticalCenter_v_undistorted", 0.0)))
                calibration_parameters = hm.CameraCalibrationParameters(location=camera_loc,
                                                                        rotation=camera_rot,
                                                                        intrinsic=camera_int )
                return_tuple = (calibration_parameters, front_axis_height)
            elif target_position.x != 0.0:
                target_position.y = -float(parameter_dict.get("fTargetPosition_y", 0.0))
                target_position.z = float(parameter_dict.get("fTargetPosition_z", 0.0))
                target_type = int(parameter_dict.get("nTargetType", 0))
                return_tuple = (target_position, target_type)
            elif target_angle.roll != 0xFFFFFFFF:
                target_angle.pitch = float(parameter_dict.get("fTargetAngle_pitch", 0.0))
                target_angle.yaw = float(parameter_dict.get("fTargetAngle_yaw", 0.0))
                noise_config = int(parameter_dict.get("noise", 0))
                return_tuple = (target_angle, noise_config)
            elif frame_per_second != 0:
                num_flows = int(parameter_dict.get("nNumFlows", 0))
                num_line_pairs = int(parameter_dict.get("nNumLinePairs", 0))
                image_width = int(parameter_dict.get("nImageWidth", 0))
                image_height = int(parameter_dict.get("nImageHeight", 0))
                x_offset = float(parameter_dict.get("fDistanceFromCamera_X", 0.0))
                x_half_limit = float(parameter_dict.get("fRangeHalfLimit_X", 0.0))
                y_half_limit = float(parameter_dict.get("fRangeHalfLimit_Y", 0.0))
                z_half_limit = float(parameter_dict.get("fRangeHalfLimit_Z", 0.0))
                return_tuple = (frame_per_second, num_flows, num_line_pairs, image_width, image_height,
                                x_offset, x_half_limit, y_half_limit, z_half_limit)
            elif use_default != 0:
                velocity = float(parameter_dict.get("fVehicleVelocity", 0.0))
                jerk_z = float(parameter_dict.get("fVehicleJerkZ", 0.0))
                yaw_rate = float(parameter_dict.get("fVehicleYawRate", 0.0))
                jerk_pitch = float(parameter_dict.get("fVehicleJerkPitch", 0.0))
                return_tuple = (velocity, jerk_z, yaw_rate, jerk_pitch)

        except :
            print("[Error] Unexpected error at read_calibration_parameters_from_xml().", sys.exc_info()[0])
            print("len(parameter_dict) = " + str(len(parameter_dict)))
                    
        return return_tuple

    def get_comparison_matrix_with_given_range( self, strBaseFile, strShiftingFile,
                                                nMinValue, nNumOfValues,
                                                nSelectRepeat=0, nImageOrVehicleSignal=1):
        import codecs
        import csv

        try:
            # Open the 2 csv-files to read.
            with codecs.open(strBaseFile, 'r', 'utf-8') as fileBaseCsv:
                with codecs.open(strShiftingFile, 'r', 'utf-8') as fileShiftingCsv:
                    nmatValues = []
                    narValues = [0,0,0,0,0,0,0,0,0,0]
                    nMaxValue = nMinValue + nNumOfValues
                    baseReader = csv.reader(fileBaseCsv, delimiter=',')
                    shiftingReader = csv.reader(fileShiftingCsv, delimiter=',')
                    
                    # for-loop for finding the row in the base file.
                    for baseRow in baseReader:
                        if nImageOrVehicleSignal == 1:
                            bIsBreak    = self.find_a_same_row_in_two_files_for_vehicle_signal(
                                        shiftingReader, nSelectRepeat, nMinValue, nMaxValue, 
                                        baseRow, narValues, nmatValues)
                        else:
                            bIsBreak    = self.find_a_same_row_in_two_files_for_image(
                                        shiftingReader, nSelectRepeat, nMinValue, nMaxValue, 
                                        baseRow, narValues, nmatValues)

                        if  bIsBreak == 1:
                            break
                        else:
                            pass

        except :
            print("[Error] Unexpected error at get_comparison_matrix_with_given_range().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return nmatValues

    def find_a_same_row_in_two_files_for_image( self, shiftingReader, nSelectRepeat, 
                                                nMinValue, nMaxValue,
                                                baseRow, narValues, nmatValues):
        import csv

        try:
            nFramecount = int(baseRow[1])
            if nFramecount >= nMinValue:
                if nFramecount > nMaxValue:
                    # Finish outer loop.
                    return 1
                elif int(baseRow[0]) == 2:
                    narValues[0] = nFramecount

                    # Copy to the new row.
                    narValues[1] = float(baseRow[3]) 

                    # for-loop for finding the row in the shifting file.
                    for shiftingRow in shiftingReader:
                        bIsBreak    = self.find_the_same_row_in_shifting_file_for_image(
                                    nSelectRepeat, shiftingRow, nFramecount, 
                                    narValues, nmatValues)
                        if  bIsBreak == 1:
                            break
                        else:
                            pass
                else:
                    pass
            else:
                pass
        except :
            print("[Error] Unexpected error at find_a_same_row_in_two_files_for_image().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return 0

    def find_the_same_row_in_shifting_file_for_image(   self, nSelectRepeat, 
                                                        shiftingRow, nFramecount,
                                                        narValues, nmatValues):
        from copy import deepcopy

        try:
            nFramecountInShiftingFile = int(shiftingRow[1])
            if nFramecountInShiftingFile >= nFramecount:
                # Frame count in Range.
                if nFramecountInShiftingFile > nFramecount:
                    # Frame count is over the target frame count.
                    pass
                elif nFramecountInShiftingFile == nFramecount:
                    # Frame count of interest.
                    if int(shiftingRow[0]) == 2:
                        # Info of Interest
                        if nSelectRepeat > 0:
                            # Not for this repeat, maybe next one.
                            nSelectRepeat -= 1
                        else:
                            # RIGHT NOW!! 
                            # Copy to the new row.
                            narValues[6] = float(shiftingRow[3]) 
                            narValues[5] = nFramecountInShiftingFile

                            # Register the new aligned row.
                            cnarValues = deepcopy(narValues)
                            nmatValues.append(cnarValues)
                            #if nFramecountInShiftingFile > nMaxValue:
                            #    nSelectRepeat = -1
                            return 1
                    else:
                        pass
                else:
                    pass
            else:
                pass
        except :
            print("[Error] Unexpected error at find_the_same_row_in_shifting_file_for_image().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return 0

    def find_a_same_row_in_two_files_for_vehicle_signal(self, shiftingReader, nSelectRepeat, 
                                                        nMinValue, nMaxValue,
                                                        baseRow, narValues, nmatValues):
        import csv

        try:
            nFramecount = int(baseRow[1])
            if nFramecount >= nMinValue-1:
                if nFramecount > nMaxValue:
                    # Finish outer loop.
                    return 1;
                elif int(baseRow[0]) == 1:
                    # Info of Interest.
                    # Check the change of the frame count.
                    if nFramecount >= narValues[0] + 1:
                        # Finally, store the right Frame count.
                        narValues[0] = nFramecount

                        # for-loop for finding the row in the shifting file.
                        for shiftingRow in shiftingReader:
                            bIsBreak    = self.find_the_same_row_in_shifting_file_for_vehicle_signal(
                                        nSelectRepeat, shiftingRow, nFramecount, 
                                        narValues, nmatValues)
                            if  bIsBreak == 1:
                                break
                            else:
                                pass
                    else:
                        pass

                    # Copy to the new row.
                    for i in range(2, 6):
                        narValues[i-1] = float(baseRow[i]) 

                else:
                    pass
            else:
                pass
        except :
            print("[Error] Unexpected error at find_a_same_row_in_two_files_for_vehicle_signal().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return 0

    def find_the_same_row_in_shifting_file_for_vehicle_signal(  self, nSelectRepeat, 
                                                                shiftingRow, nFramecount,
                                                                narValues, nmatValues):
        from copy import deepcopy

        try:
            nFramecountInShiftingFile = int(shiftingRow[1])
            if nFramecountInShiftingFile >= nFramecount:
                # Frame count in Range.
                if nFramecountInShiftingFile > nFramecount + 1:
                    # Frame count is over the target frame count.
                    pass
                elif nFramecountInShiftingFile == nFramecount + 1:
                    # The frame must be a image frame with new Frame count,
                    # which can be skipped.
                    # Finish inner loop.
                    if nSelectRepeat == 0:
                        return 1;
                    else:
                        pass
                elif nFramecountInShiftingFile == nFramecount:
                    # Frame count of interest.
                    if int(shiftingRow[0]) != 1:
                        # Image frame is expected to only one for each Frame count.
                        if nSelectRepeat > 0:
                            # Image frame can be used to count down the repetition.
                            nSelectRepeat -= 1
                        else:
                            pass
                    else:
                        # Info of Interest.
                        # Vehicle signal frames are more than one for each Frame count.
                        if nSelectRepeat > 0:
                            pass
                        elif nSelectRepeat == 0:
                            # RIGHT NOW!! 
                            # Check the change of the frame count.
                            if nFramecountInShiftingFile >= narValues[5] + 1:
                                # Finally, store the right Frame count.
                                narValues[5] = nFramecountInShiftingFile

                                # Register the new aligned row.
                                cnarValues = deepcopy(narValues)
                                nmatValues.append(cnarValues)
                            else:
                                pass

                            # Copy to the new row.
                            for i in range(2, 6):
                                narValues[i+4] = float(shiftingRow[i])
                        else:
                            pass
                else:
                    pass
            else:
                pass
        except :
            print("[Error] Unexpected error at find_the_same_row_in_shifting_file_for_vehicle_signal().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return 0

def main():
    from matplotlib import pyplot as plt
    import cv2

    try:
        fi = FileInput()
        binary = fi.load_binary_image("ForwardImage.bin", 2880, 640)
        resized_binary = cv2.resize(binary, None, fx=0.5, fy=0.5, interpolation=cv2.INTER_CUBIC)
        optical_flows, confidences = fi.read_optical_flows_and_confidences_from_csv("OpticalFlow.csv")
        resized_binary.dtype = 'uint16'
        resized_binary *= 32
        plt.imshow(resized_binary, cmap="gray")
        for i in range(len(optical_flows)):
            begin_point = (optical_flows[i][0][0], optical_flows[i][1][0])
            end_point = (optical_flows[i][0][1], optical_flows[i][1][1])
            cv2.line(resized_binary, begin_point, end_point, (255))
        cv2.imwrite('binary_cv.png', resized_binary)
        cv2.imshow('OpticalFlow_image', resized_binary)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
        # fig = plt.figure()
        # plt.savefig("binary.png", dpi=fig.dpi, bbox_inches='tight')
        # plt.show()

    except:
            print("[Error] Unexpected error at main().", sys.exc_info()[0])

    return

if __name__ == "__main__":
    main()