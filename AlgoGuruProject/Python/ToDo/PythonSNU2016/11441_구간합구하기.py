# -*- coding: utf-8 -*-

def GetValue():
    
    import sys
    try:
        nValue = int(input())
    except:
        print("[Error] Unexpeced error.", sys.exc_info()[0])

    return  nValue

def GetList(nNum):
    
    import sys
    naNumList = []
    if nNum == 1:
        naNumList = [int(item) for item in input().split()]
    else:
        for _ in range(nNum):
            try:
                num_set = [int(item) for item in input().split()]
            except:
                print("[Error] Unexpected error.", sys.exc_info()[0])
            naNumList.append(num_set)

    return naNumList

def Calculation(nValueOfN, naNumList, nValueOfM, nmatIntervalList):
    
    cumulative_list = [0]*nValueOfN
    sum = 0
    for idx in range(nValueOfN):
        sum += naNumList[idx]
        cumulative_list[idx] = sum
        
    naSumList = [0]*nValueOfM
    for i in range(nValueOfM):
        naSumList[i] = cumulative_list[nmatIntervalList[i][1]] - cumulative_list[nmatIntervalList[i][0]-1]

    return naSumList


def main():

    nValueOfN = GetValue()
    naNumList = GetList(1)
    nValueOfM = GetValue()
    nmatIntervalList = GetList(nValueOfM)
    naSumList = Calculation(nValueOfN, naNumList, nValueOfM, nmatIntervalList)
    print(naSumList)

    return

if __name__ == "__main__":
    main()