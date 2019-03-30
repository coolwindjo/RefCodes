# -*- coding: utf-8 -*-
##  @package Find Shifting Number
#  Documentation for FindShiftingNumber
#
#   More details.

##################
# Configurations #
##################
#strBaseSystem = "InVehicle"
strBaseSystem = "SiLS"
strGivenDate = ""

def get_cost_of_signal_diff_with_shifting(nmatValueTable, nShiftingNumber):
    
    import sys

    fCost = 0.0
    fSumOfDiffSq = 0.0

    nMinFrame = 1
    nMaxFrame = len(nmatValueTable)
    if nShiftingNumber < 0:
        nMinFrame -= nShiftingNumber
    else:
        nMaxFrame -= nShiftingNumber

    count = 0
    for i in range(nMinFrame, nMaxFrame):
        if (nmatValueTable[i+nShiftingNumber][6] != 0):
            fSumOfDiffSq += (nmatValueTable[i][5] - nmatValueTable[i+nShiftingNumber][6])**2
            count += 1
        else:
            pass
    fCost = fSumOfDiffSq/(count if count != 0 else sys.int_info.min)
    
    return fCost

import drawxlsx
def get_best_shifting_number(nmatValueTable, strSignalKind, nMinShiftingNum, nMaxShiftingNum, strTitle='', oDrawXlsx=drawxlsx.DrawXlsx()):
    
    # Find the minimum cost.
    narShiftingRange = [i for i in range(nMinShiftingNum, nMaxShiftingNum)]
    narCost = []
    
    nBestShiftingNumber = nMinShiftingNum
    fMinCost = get_cost_of_signal_diff_with_shifting(nmatValueTable, nMinShiftingNum)
    narCost.append(fMinCost)
    for i in range(nMinShiftingNum+1, nMaxShiftingNum):
        fCost = get_cost_of_signal_diff_with_shifting(nmatValueTable, i)
        narCost.append(fCost)
        if fCost < fMinCost:
            fMinCost = fCost
            nBestShiftingNumber = i

    if strTitle != '':
        # Draw on excel file.
        oDrawXlsx.add_worksheet()

        strXaxisTitle = 'Frame Number'
        strYaxisTitle = strSignalKind
        nNumOfFrames = len(nmatValueTable)
       
        oDrawXlsx.open_chart('scatter', strSignalKind)
        oDrawXlsx.add_base_data_to_chart('A1', strXaxisTitle, strYaxisTitle, [nmatValueTable[i][0] for i in range(1, nNumOfFrames)])
        oDrawXlsx.add_data_to_chart('B1', strBaseSystem, [nmatValueTable[i][5] for i in range(1, nNumOfFrames)])
        oDrawXlsx.add_data_to_chart('C1', strTitle, [nmatValueTable[i][6] for i in range(1, nNumOfFrames)])
        oDrawXlsx.close_and_insert_chart('F2')

        strXaxisTitle = 'Frame Shifting Number'
        strYaxisTitle = 'Cost of ' + strSignalKind + ' Difference'
        oDrawXlsx.open_chart('scatter', strSignalKind)
        oDrawXlsx.add_base_data_to_chart('D1', strXaxisTitle, strYaxisTitle, narShiftingRange)
        oDrawXlsx.add_data_to_chart('E1', strYaxisTitle, narCost)
        oDrawXlsx.close_and_insert_chart('F17')
    
    return nBestShiftingNumber

def main():
    
    import userinput 
    import fileinput
    import drawxlsx
    import time

    #INITIAL_YAW_ANGLE = -35
    INITIAL_YAW_ANGLE = 8

    if strGivenDate == "":
        strDate = time.strftime("%Y%m%d")
    else:
        strDate = time.strftime("%Y%m") + strGivenDate 
    strBaseFile = "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_" + strBaseSystem + ".csv"

    ui = userinput.UserInput()
    fi = fileinput.FileInput()

    # Get user input for range to look through.
    #nMinIndex = ui.get_number("Minimum")
    #nMaxIndex = ui.get_number("Maximum")
    nMinIndex = 15600
    nMaxIndex = 15950
    print("Let's see the Vehicle Signals along with the Frame counts from " + str(nMinIndex) + " to " + str(nMaxIndex))
    
    if nMaxIndex <= nMinIndex:
        print("[Error] Maximum index is not bigger than Minimum index.")

    # Fetch the data from files for given names.
    nmatValueTable = fi.get_comparison_matrix_with_given_range(strBaseFile, nMinIndex, nMaxIndex-nMinIndex, INITIAL_YAW_ANGLE)
   
    # Output the results.
    dx = drawxlsx.DrawXlsx()
    strXlsxFile = dx.make_xlsx_filename_with_date("FramecountShifting_" + strBaseSystem, strGivenDate)
    dx.open_workbook(strXlsxFile)

    # Find the best shifting number while drawing on the excel file.
    print("The best shifting number for Yaw-rate is " + str(get_best_shifting_number(nmatValueTable, 'Signal-Yaw', -10, 10, "Image-Yaw", dx)))
    dx.close_workbook()

    return

if __name__ == "__main__":
    main()