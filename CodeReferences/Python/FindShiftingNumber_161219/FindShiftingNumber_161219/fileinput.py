# -*- coding: utf-8 -*-
##  @package FileInput
#   Documentation for this module
#
#   More details
class FileInput(object):
    """A class for getting input from a user"""
    
    def __init__(self, *args, **kwargs):
        return super(FileInput, self).__init__(*args, **kwargs)
    
    def find_the_same_row_in_shifting_file_for_image(   self, nSelectRepeat, 
                                                        shiftingRow, nFramecount,
                                                        narValues, nmatValues):
        import sys
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

    def find_a_same_row_in_two_files_for_image( self, shiftingReader, nSelectRepeat, 
                                                    nMinValue, nMaxValue,
                                                    baseRow, narValues, nmatValues):
        import sys
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

    def find_the_same_row_in_shifting_file_for_vehicle_signal(  self, nSelectRepeat, 
                                                                shiftingRow, nFramecount,
                                                                narValues, nmatValues):
        import sys
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

    def find_a_same_row_in_two_files_for_vehicle_signal( self, shiftingReader, nSelectRepeat, 
                                                    nMinValue, nMaxValue,
                                                    baseRow, narValues, nmatValues):
        import sys
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

    def get_comparison_matrix_with_given_range_from_two_files(  self, strBaseFile, strShiftingFile,
                                                                nMinValue, nNumOfValues,
                                                                nSelectRepeat=0, nImageOrVehicleSignal=1):

        import sys
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
            print("[Error] Unexpected error at get_comparison_matrix_with_given_range_from_two_files().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return nmatValues

    def make_matrix_of_yaw_from_signal_and_image_with_given_range(self, nMinValue, nMaxValue, initial_yaw, baseRow, narValues, nmatValues):

        import sys
        import csv
        from copy import deepcopy

        try:
            nFramecount = int(baseRow[1])
            if nFramecount >= nMinValue-1:
                if nFramecount > nMaxValue:
                    # Finish outer loop.
                    return 1;
                elif int(baseRow[0]) == 0:
                    if len(nmatValues) > 0:
                        if baseRow[4] != "":    
                            # store yaw angle from image.
                            narValues[6] = float(baseRow[4])
                        else:
                            narValues[6] = nmatValues[-1][6]
                        # Integrate signal yaw-rate for signal yaw angle.
                        narValues[5] = nmatValues[-1][5] + narValues[2]*0.0454545
                    else:
                        narValues[5] = initial_yaw

                elif int(baseRow[0]) == 1:
                    # Info of Interest.
                    # Check the change of the frame count.
                    if nFramecount >= narValues[0] + 1:
                        # Finally, store the right Frame count.
                        narValues[0] = nFramecount

                        # Register the new aligned row.
                        cnarValues = deepcopy(narValues)
                        nmatValues.append(cnarValues)
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
            print("[Error] Unexpected error at make_matrix_of_yaw_from_signal_and_image_with_given_range().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return 0

    def get_comparison_matrix_with_given_range( self, strBaseFile, nMinValue, nNumOfValues, initial_yaw):

        import sys
        import codecs
        import csv

        try:
            # Open the csv-file to read.
            with codecs.open(strBaseFile, 'r', 'utf-8') as fileBaseCsv:
                nmatValues = []
                narValues = [0,0,0,0,0,0,0]
                nMaxValue = nMinValue + nNumOfValues
                baseReader = csv.reader(fileBaseCsv, delimiter=',')
                
                # for-loop for finding the row in the base file.
                for baseRow in baseReader:
                    bIsBreak    = self.make_matrix_of_yaw_from_signal_and_image_with_given_range(
                                nMinValue, nMaxValue, initial_yaw, baseRow, narValues, nmatValues)
                    if  bIsBreak == 1:
                        break
                    else:
                        pass

        except :
            print("[Error] Unexpected error at get_comparison_matrix_with_given_range().", sys.exc_info()[0])
            print("len(nmatValues) = " + str(len(nmatValues)))

        return nmatValues

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