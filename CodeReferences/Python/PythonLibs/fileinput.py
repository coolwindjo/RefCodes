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
    
    def read_3d_coordinates_from_numbers(self, word, coordinate):

        try:
            numbers = word.split(',')
            coordinate.append(int(numbers[0]))
            coordinate.append(int(numbers[1]))
            coordinate.append(int(numbers[2]))
        except :
            print("[Error] Unexpected error at read_3d_coordinates_from_numbers().", sys.exc_info()[0])
            print("len(numbers) = " + str(len(numbers)))

        return

    def read_world_model_from_txt(self, filename, lineX, lineY, lineZ, rectX, rectY, rectZ):

        try:
            sharp_num = 0
            with open(filename, "r") as textfile:
                textlines = textfile.readlines()
                for textline in textlines:
                    words = textline.split()
                    if (words[0] != '#'):
                        if (sharp_num == 2):
                            line_begin = []
                            line_end = []
                            self.read_3d_coordinates_from_numbers(words[0], line_begin)
                            self.read_3d_coordinates_from_numbers(words[1], line_end)
                            lineX.append([line_begin[0], line_end[0]])
                            lineY.append([line_begin[1], line_end[1]])
                            lineZ.append([line_begin[2], line_end[2]])
                        elif (sharp_num == 3):
                            rect_begin = []
                            rect_end = []
                            self.read_3d_coordinates_from_numbers(words[0], rect_begin)
                            self.read_3d_coordinates_from_numbers(words[1], rect_end)
                            rectX.append([rect_begin[0], rect_end[0]])
                            rectY.append([rect_begin[1], rect_end[1]])
                            rectZ.append([rect_begin[2], rect_end[2]])
                        else:
                            pass
                    else:
                        sharp_num += 1
        except :
            print("[Error] Unexpected error at read_world_model_from_txt().", sys.exc_info()[0])
            print("len(words) = " + str(len(words)))
                        
        return

    def read_calibration_parameters_from_xml(self, filename, F_uv, C_uv, baseline, C_xyz, C_rpy):

        import xml.etree.ElementTree

        try:
            e = xml.etree.ElementTree.parse(filename).getroot()
            parameters = e.find("parameterTable")
            #parameter_list = parameters.findall("parameter")
            parameter_dict = {}

            for param in parameters:
                parameter_dict[param.attrib["name"]] = param.attrib["value"]

            F_uv.append(float(parameter_dict["fFocallengthU_factory"]))
            F_uv.append(float(parameter_dict["fFocallengthV_factory"]))
            C_uv.append(float(parameter_dict["fOpticalCenterU_factory"]))
            C_uv.append(float(parameter_dict["fOpticalCenterV_factory"]))
            C_xyz.append(float(parameter_dict["fCameraMountPose_x_factory"]))
            C_xyz.append(float(parameter_dict["fCameraMountPose_y_factory"]))
            C_xyz.append(float(parameter_dict["fCameraMountPose_z_factory"]))
            C_rpy.append(float(parameter_dict["fCameraMountPose_roll_factory"]))
            C_rpy.append(float(parameter_dict["fCameraMountPose_pitch_factory"]))
            C_rpy.append(float(parameter_dict["fCameraMountPose_yaw_factory"]))
            baseline = float(parameter_dict["fBaseLine_factory"]);

        except :
            print("[Error] Unexpected error at read_calibration_parameters_from_xml().", sys.exc_info()[0])
            print("len(parameter_dict) = " + str(len(parameter_dict)))
                    
        return


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

    def find_a_same_row_in_two_files_for_vehicle_signal( self, shiftingReader, nSelectRepeat, 
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
   
    nMinIndex = get_number("Minimum")
    nMaxIndex = get_number("Maximum")
    print(nMinIndex, nMaxIndex)
    
    if nMaxIndex <= nMinIndex:
        print("[Error] Maximum index is not bigger than Minimum index.")

    strBaseFile = get_filename("Base")
    strShiftingFile = get_filename("Shifting")
 
    nmatValues1 = get_vehicle_signal_matrix_with_given_range(strBaseFile, strShiftingFile, nMinIndex, nMaxIndex-nMinIndex)
    print(nmatValues1)

    return

if __name__ == "__main__":
    main()