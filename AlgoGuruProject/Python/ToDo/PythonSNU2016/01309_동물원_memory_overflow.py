# -*- coding: utf-8 -*-

def GetValueOfN():
    
    import sys
    try:
        nValueOfN = int(input())
    except:
        print("[Error] Unexpeced error.", sys.exc_info()[0])

    return  nValueOfN


def CalculateTotalCasesOfLionDeployment(nValueOfN):

    nTotalCases = 0
    nmatLionDeploy = []
    for idx in range(nValueOfN+1):
        nmatLionDeploy.append([0]*(idx+1))
    
    nmatLionDeploy[0][0] = 0

    #nmatLionDeploy[1][0] = 1
    #nmatLionDeploy[1][1] = 2

    #nmatLionDeploy[2][0] = 1
    #nmatLionDeploy[2][1] = nmatLionDeploy[1][1] + 2(nmatLionDeploy[1][0])
    #nmatLionDeploy[2][2] = 2
    
    #nmatLionDeploy[3][0] = 1
    #nmatLionDeploy[3][1] = nmatLionDeploy[2][1] + 2(nmatLionDeploy[2][0])
    #nmatLionDeploy[3][2] = nmatLionDeploy[2][2] + 2(nmatLionDeploy[2][1] - nmatLionDeploy[1][0])
    #nmatLionDeploy[3][3] = 2

    #nmatLionDeploy[4][0] = 1
    #nmatLionDeploy[4][1] = nmatLionDeploy[3][1] + 2(nmatLionDeploy[3][0])
    #nmatLionDeploy[4][2] = nmatLionDeploy[3][2] + 2(nmatLionDeploy[3][1] - nmatLionDeploy[2][0])
    #nmatLionDeploy[4][3] = nmatLionDeploy[3][3] + 2(nmatLionDeploy[3][2] - nmatLionDeploy[2][1] + nmatLionDeploy[1][0])
    #nmatLionDeploy[4][4] = 2

    for idx in range(nValueOfN+1):
        if idx > 0:
            nmatLionDeploy[idx][0] = 1
            nmatLionDeploy[idx][idx] = 2
            
            for num_of_lions in range(1, idx):
                sum = 0
                for i in range(num_of_lions):
                    tmp = nmatLionDeploy[idx-1-i][num_of_lions-1-i]
                    if i % 2 == 0:
                        sum += tmp
                    else:
                        sum -= tmp

                nmatLionDeploy[idx][num_of_lions] = nmatLionDeploy[idx-1][num_of_lions] + 2*sum
    
    for num_of_lions in range(nValueOfN+1):
        nTotalCases += nmatLionDeploy[nValueOfN][num_of_lions]
    nTotalCases = nTotalCases % 9901
    
    return  nTotalCases


def main():
    
    nValueOfN = GetValueOfN()
    nTotalCases = CalculateTotalCasesOfLionDeployment(nValueOfN)
    print(nTotalCases)
    
    return

if __name__ == "__main__":
    main()