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

    for _ in range(nNumOfRows+1):
        nmatCasesSoFar.append([0]*3)
    
    nmatCasesSoFar[1][0] = 1
    nmatCasesSoFar[1][1] = 1
    nmatCasesSoFar[1][2] = 1

    for row_idx in range(2, nNumOfRows+1):
        nmatCasesSoFar[row_idx][0] = nmatCasesSoFar[row_idx-1][0] + nmatCasesSoFar[row_idx-1][1] + nmatCasesSoFar[row_idx-1][2]
        nmatCasesSoFar[row_idx][1] = nmatCasesSoFar[row_idx-1][0] + nmatCasesSoFar[row_idx-1][2]
        nmatCasesSoFar[row_idx][2] = nmatCasesSoFar[row_idx-1][0] + nmatCasesSoFar[row_idx-1][1]

    nTotalCases = sum(nmatCasesSoFar[nNumOfRows])
    
    return  nTotalCases


def main():
    
    nValueOfN = GetValueOfN()
    nTotalCases = CalculateCasesOfLionDeployment(nValueOfN)
    print(nTotalCases)
    
    return

if __name__ == "__main__":
    main()