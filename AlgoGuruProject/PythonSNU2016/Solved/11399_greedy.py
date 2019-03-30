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


def Calculation(nValueOfN, naNumList):
    
    naNumList.sort()
    sum = 0
    #cumulative_list = [0]*naNumList
    for idx in range(nValueOfN):
        sum += naNumList[idx]*(nValueOfN-idx)
   
    return sum


def main():

    nValueOfN = GetValue()
    naNumList = GetList(1)
    nSum = Calculation(nValueOfN, naNumList)
    print(nSum)

    return

if __name__ == "__main__":
    main()