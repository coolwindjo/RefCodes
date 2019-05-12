# -*- coding: utf-8 -*-

def GetInputValue():
    
    import sys
    try:
        nValue = int(input())
    except:
        print("[Error] Unexpeced error.", sys.exc_info()[0])

    return  nValue


def CalculateCasesOfLionDeployment(nNumOfRows):

    nmatLionDeploy = [[0]*3]
    nmatLionDeploy.append([0]*3)

    toggle = 0
    previous = 0

    nmatLionDeploy[0][0] = 1
    nmatLionDeploy[0][1] = 1
    nmatLionDeploy[0][2] = 1

    for idx in range(1, nNumOfRows):
        toggle = idx%2
        nmatLionDeploy[toggle][0] = nmatLionDeploy[previous][0] + nmatLionDeploy[previous][1] + nmatLionDeploy[previous][2]
        nmatLionDeploy[toggle][1] = nmatLionDeploy[previous][0] + nmatLionDeploy[previous][2]
        nmatLionDeploy[toggle][2] = nmatLionDeploy[previous][0] + nmatLionDeploy[previous][1]
        previous = toggle

    nTotalCases = sum(nmatLionDeploy[toggle]) % 9901
    
    return  nTotalCases


def main():
    
    nValueOfN = GetInputValue()
    nTotalCases = CalculateCasesOfLionDeployment(nValueOfN)
    print(nTotalCases)
    
    return

if __name__ == "__main__":
    main()