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
strDefaultTitle = "SiLS+3"
#strDefaultTitle = "HiLS-5"
#strDefaultTitle = ""
strDatDesc = "slalom2"
#strDatDesc = ""
strGivenDate = ""
#strGivenDate = "02"

def select(dicOptions, strLower, default=0):
    return dicOptions.get(strLower, default)

def select_signal(strSignalKind):
    return select({
        'velocity'  : 1,
        'yaw-rate'  : 2,
        'steer'     : 4,
    },strSignalKind, 2)

def get_cost_of_signal_diff_with_shifting(nmatValueTable, strSignalKind, nShiftingNumber):
    
    fCost = 0.0
    fSumOfDiffSq = 0.0

    nMinFrame = 1
    nMaxFrame = len(nmatValueTable)
    if nShiftingNumber < 0:
        nMinFrame -= nShiftingNumber
    else:
        nMaxFrame -= nShiftingNumber

    nSignalKind = select_signal(strSignalKind.lower())
    for i in range(nMinFrame, nMaxFrame):
        fSumOfDiffSq += (nmatValueTable[i][nSignalKind] - nmatValueTable[i+nShiftingNumber][nSignalKind + 5])**2
    fCost = fSumOfDiffSq/(len(nmatValueTable)-1)
    
    return fCost

import drawxlsx
def get_best_shifting_number(nmatValueTable, strSignalKind, nMinShiftingNum, nMaxShiftingNum, strTitle='', oDrawXlsx=drawxlsx.DrawXlsx()):
    
    # Find the minimum cost.
    narShiftingRange = [i for i in range(nMinShiftingNum, nMaxShiftingNum)]
    narCost = []
    
    nBestShiftingNumber = nMinShiftingNum
    fMinCost = get_cost_of_signal_diff_with_shifting(nmatValueTable, strSignalKind, nMinShiftingNum)
    narCost.append(fMinCost)
    for i in range(nMinShiftingNum+1, nMaxShiftingNum):
        fCost = get_cost_of_signal_diff_with_shifting(nmatValueTable, strSignalKind, i)
        narCost.append(fCost)
        if fCost < fMinCost:
            fMinCost = fCost
            nBestShiftingNumber = i

    if strTitle != '':
        # Draw on excel file.
        oDrawXlsx.add_worksheet()

        strXaxisTitle = 'Frame Number'
        strYaxisTitle = strSignalKind
        nSignalKind = select_signal(strSignalKind.lower())
        nNumOfFrames = len(nmatValueTable)
       
        oDrawXlsx.open_chart('scatter', strSignalKind)
        oDrawXlsx.add_base_data_to_chart('A1', strXaxisTitle, strYaxisTitle, [nmatValueTable[i][0] for i in range(1, nNumOfFrames)])
        oDrawXlsx.add_data_to_chart('B1', strBaseSystem, [nmatValueTable[i][nSignalKind] for i in range(1, nNumOfFrames)])
        oDrawXlsx.add_data_to_chart('C1', strTitle, [nmatValueTable[i][nSignalKind + 5] for i in range(1, nNumOfFrames)])
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

    if strGivenDate == "":
        strDate = time.strftime("%Y%m%d")
    else:
        strDate = time.strftime("%Y%m") + strGivenDate 
    strBaseFile = "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_" + strBaseSystem + "_" + strDatDesc + ".csv"
    dicTitles = {
        'sils'          : "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_SILS_",
        'sils+3'        : "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_SILS+3_",
        'silsdebug'     : "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_SILSdebug_",
        'silsdebug+3'   : "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_SILSdebug+3_",
        'hils'          : "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_HILS_",
        'hils-5'        : "./" + strDate + "_VehicleSignal/VEHICLESIGNAL_HILS-5_",
    }

    ui = userinput.UserInput()
    fi = fileinput.FileInput()

    # for-loop for getting user input for title such as HiLS, SiLS, SiLSdebug, etc.
    strShiftingFile = ""
    for _ in range(1, 10):
        strIsSignalComparison = ui.get_number("""
0 for Image CheckSum Comparison
1 for Vehicle Signal Comparison
"""
        )
        nSelectRepeat = ui.get_number("Select Repeat")
        strTitle = ui.get_title(strDefaultTitle)
        strShiftingFile = select(dicTitles, strTitle.lower(), "./")
        if strShiftingFile != "./":
            break
        else:
            for key in dicTitles:
                print(key)
    if strShiftingFile == "":
        return -1
    else:
        strShiftingFile += strDatDesc + ".csv"
 
    print("Test title is " + strTitle)

    # Get user input for range to look through.
    nMinIndex = ui.get_number("Minimum")
    nMaxIndex = ui.get_number("Maximum")
    print("Let's see the Vehicle Signals along with the Frame counts from " + str(nMinIndex) + " to " + str(nMaxIndex))
    
    if nMaxIndex <= nMinIndex:
        print("[Error] Maximum index is not bigger than Minimum index.")

    # Fetch the data from files for given names.
    nmatValueTable  = fi.get_comparison_matrix_with_given_range_from_two_files(
                    strBaseFile, strShiftingFile, 
                    nMinIndex, nMaxIndex-nMinIndex, 
                    nSelectRepeat, strIsSignalComparison)

    # Output the results.
    dx = drawxlsx.DrawXlsx()
    if strIsSignalComparison == 1:
        strXlsxFile = dx.make_xlsx_filename_with_date("FramecountShifting_" + strBaseSystem + "-" + strTitle + "_" + strDatDesc, strGivenDate)
        dx.open_workbook(strXlsxFile)

        # Find the best shifting number while drawing on the excel file.
        print("The best shifting number for Velocity is " + str(get_best_shifting_number(nmatValueTable, 'Velocity', -10, 10, strTitle, dx)))
        print("The best shifting number for Yaw-rate is " + str(get_best_shifting_number(nmatValueTable, 'Yaw-rate', -10, 10, strTitle, dx)))
        print("The best shifting number for Steering is " + str(get_best_shifting_number(nmatValueTable, 'Steer', -10, 10, strTitle, dx)))
    else:
        strXlsxFile = dx.make_xlsx_filename_with_date("ChecksumComparison_" + strBaseSystem + "-" + strTitle + "_" + strDatDesc, strGivenDate)
        dx.open_workbook(strXlsxFile)
        # Draw on excel file.
        dx.add_worksheet()

        strXaxisTitle = 'Frame Number'
        strYaxisTitle = "CheckSum"
        nNumOfFrames = len(nmatValueTable)
       
        dx.open_chart('scatter', strYaxisTitle)
        dx.add_base_data_to_chart('A1', strXaxisTitle, strYaxisTitle, [nmatValueTable[i][0] for i in range(1, nNumOfFrames)])
        dx.add_data_to_chart('B1', strBaseSystem, [nmatValueTable[i][1] for i in range(1, nNumOfFrames)])
        dx.add_data_to_chart('C1', strTitle, [nmatValueTable[i][1 + 5] for i in range(1, nNumOfFrames)])
        dx.close_and_insert_chart('F2')
    dx.close_workbook()

    return

if __name__ == "__main__":
    main()