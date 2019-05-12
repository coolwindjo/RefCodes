# -*- coding: utf-8 -*-
## @pagkage Cal2xnTiling

def GetValueOfN(strOutput):
    
    import sys
    try:
        nInputValue = int(input(strOutput))
    except ValueError:
        print("[Error] Could not convert")
    except :
        print("[Error] Unexpected error.", sys.exc_info()[0])

    return nInputValue


def GetPivoValue(n):

    ret_val = 0
    if n < 0 :
        ret_val = 0
    elif (n == 0) | (n == 1):
        ret_val = 1
    elif n >= 2 :
        ret_val = GetPivoValue(n-1) + GetPivoValue(n-2)

    return ret_val


def main():

    nValueOfN = GetValueOfN('')
    nValue = GetPivoValue(nValueOfN)    
    print(nValue)

    return

if __name__ == '__main__':
    main()