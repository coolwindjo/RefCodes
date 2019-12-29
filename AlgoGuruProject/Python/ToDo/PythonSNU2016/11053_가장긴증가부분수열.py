# -*- coding: utf-8 -*-

def GetValueOfN():
    
    import sys
    try:
        nValueOfN = int(input())
    except:
        print("[Error] Unexpeced error.", sys.exc_info()[0])

    return  nValueOfN

def GetList(nNum):
    
    import sys
    naNumList = []
    try:
        naNumList = [int(item) for item in input().split()]
    except:
        print("[Error] Unexpected error.", sys.exc_info()[0])
  
    return naNumList

def CalculateNumOfIncreasingSeqs(nNumOfSeqs, naNumList):

    d = [1]*len(naNumList)

    for idx, _ in enumerate(naNumList):
        for inner_idx in range(idx):
            if naNumList[inner_idx] < naNumList[idx]:
                d[inner_idx] = max(d[idx], d[inner_idx]+1)

    return  max(d)


def main():
    
    nValueOfN = GetValueOfN()
    naNumList = GetList(nValueOfN)
    nLongestNum = CalculateNumOfIncreasingSeqs(nValueOfN, naNumList)
    print(nLongestNum)
    
    return

if __name__ == "__main__":
    main()