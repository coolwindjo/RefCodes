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


def Calculation(nValueOfN, naNumList, nValueOfM, naKeyList):
    
    import bisect

    naNumList.sort()
    exist_list = [0]*nValueOfM
    for idx in range(nValueOfM):
        next_pos_of_key = bisect.bisect(naNumList, naKeyList[idx])
        
        if naNumList[next_pos_of_key-1] == naKeyList[idx]:
            exist_list[idx] = 1
        else:
            exist_list[idx] = 0        
   
    return exist_list


def main():

    nValueOfN = GetValue()
    naNumList = GetList(1)
    nValueOfM = GetValue()
    naKeyList = GetList(1)
    naExsitList = Calculation(nValueOfN, naNumList, nValueOfM, naKeyList)
    for _, val in enumerate(naExsitList):
        print(val)

    return

if __name__ == "__main__":
    main()