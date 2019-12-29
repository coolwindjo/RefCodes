# -*- coding: utf-8 -*-

def GetValueOfN():
    
    import sys
    try:
        nValueOfN = int(input())
    except:
        print("[Error] Unexpeced error.", sys.exc_info()[0])

    return  nValueOfN


def CalculateCasesOfLionDeployment(nNumOfRows):

    nmatCasesSoFar = []
    #nmatSeriesLions = []

    #for row_idx in range(nNumOfRows+1):
    #    nmatCasesSoFar.insert(row_idx, 1)
        #nmatSeriesLions.append([0]*(row_idx+1))
    
    #nmatCasesSoFar[0] = 1
    nmatCasesSoFar.append(1)

    #nmatSeriesLions[1][0] = 1
    #nmatSeriesLions[1][1] = 2
    #nmatCasesSoFar[1] = nmatSeriesLions[1][0] + nmatSeriesLions[1][1]

    #nmatSeriesLions[2][0] = 1
    #nmatSeriesLions[2][1] = 2
    #nmatSeriesLions[2][2] = 2
    #nmatCasesSoFar[2] = nmatSeriesLions[2][0]*(nmatCasesSoFar[1])       \
    #                    + nmatSeriesLions[2][1]*(nmatCasesSoFar[0])     \
    #                    + nmatSeriesLions[2][2] 

    #nmatSeriesLions[3][0] = 1
    #nmatSeriesLions[3][1] = 2
    #nmatSeriesLions[3][2] = 2
    #nmatSeriesLions[3][3] = 2
    #nmatCasesSoFar[3] = nmatSeriesLions[3][0]*(nmatCasesSoFar[2])       \
    #                    + nmatSeriesLions[3][1]*(nmatCasesSoFar[1])     \
    #                    + nmatSeriesLions[3][2]*(nmatCasesSoFar[0])     \
    #                    + nmatSeriesLions[3][3] 
    
    sum = 0
    for row_idx in range(1, nNumOfRows+1):
        sum = nmatCasesSoFar[row_idx-1] + 2
        #nmatCasesSoFar[row_idx] += 1*nmatCasesSoFar[row_idx-1]
        #nmatSeriesLions[row_idx][0] = 1
        #nmatSeriesLions[row_idx][row_idx] = 2
        for num_of_lions in range(1, row_idx):
            #nmatSeriesLions[row_idx][num_of_lions] = 2
            sum += 2*nmatCasesSoFar[row_idx-num_of_lions-1]
            #nmatCasesSoFar[row_idx] += 2*nmatCasesSoFar[row_idx-num_of_lions-1]
            #nmatCasesSoFar[row_idx] += nmatSeriesLions[row_idx][num_of_lions]*nmatCasesSoFar[row_idx-num_of_lions-1]
        #nmatCasesSoFar[row_idx] += nmatSeriesLions[row_idx][row_idx]
        #nmatCasesSoFar[row_idx] += 2
        nmatCasesSoFar.append(sum)

    nTotalCases = sum % 9901
    
    return  nTotalCases


def main():
    
    nValueOfN = GetValueOfN()
    nTotalCases = CalculateCasesOfLionDeployment(nValueOfN)
    print(nTotalCases)
    
    return

if __name__ == "__main__":
    main()