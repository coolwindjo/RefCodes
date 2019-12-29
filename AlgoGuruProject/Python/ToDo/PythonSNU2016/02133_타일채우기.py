# -*- coding: utf-8 -*-

def GetValue():
    
    import sys
    try:
        nValue = int(input())
    except:
        print("[Error] Unexpeced error.", sys.exc_info()[0])

    return  nValue


def CalculateAnswer(nValue):

    
    return  


def main():
    
    nValueOfN = GetValue()
    nTotalCases = CalculateAnswer(nValueOfN)
    print(nTotalCases)
    
    return

if __name__ == "__main__":
    main()