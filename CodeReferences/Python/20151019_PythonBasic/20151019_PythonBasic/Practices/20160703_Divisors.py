# -*- coding: utf-8 -*-
##  @package CalculateDivisors()

##  Documentation for 
#
#   More details.
def try_input(strOutput):

    import sys
    for i in range(1,10):
        try:
            nInputValue = int(input(strOutput))
            break

        except  ValueError:
            print("[Error] Could not convert data to an integer.")
            continue
        except  NameError:
            print("[Error] The input is not an integer.")
            continue
        except  :
            print("[Error] Unexpected error.", sys.exc_info()[0])
            continue
 
    return nInputValue

def GetANumber():
   
    nNumber = try_input("Enter a number: ")
    
    return nNumber


def GetTwoNumbers():
   
    nNum1 = try_input("Enter a number: ")
    nNum2 = try_input("Enter another number: ")
    
    return nNum1, nNum2


def CalculateDivisors(nNumber):
   
    naDivisors = []
    
    count = nNumber
    while (count >= 1):
        if nNumber % count == 0:
            naDivisors.append(count)    
        count -= 1    

    return naDivisors

def CalculateGreatestCommonDivisor(nNum1, nNum2):
   
    nGCD = 0    
    count = nNum1
    if count < nNum2:
        count = nNum2
    while (count >= 1):
        if (nNum1 % count == 0) & (nNum2 % count == 0):
            nGCD = count
            break   
        count -= 1    

    return nGCD


def CalculateLeastCommonMultiple(nNum1, nNum2):
   
    nGCD = CalculateGreatestCommonDivisor(nNum1, nNum2)
    nNum1Res = nNum1/nGCD    
    nNum2Res = nNum2/nGCD
   
    nLCM = nGCD * nNum1Res * nNum2Res

    return nLCM


def IsAPerfectNumber(nNumber):
   
    naDivisors = CalculateDivisors(nNumber)
    #nNumDivisors = len(naDivisors)
    nSumDiv = 0
    for nDiv in naDivisors:
        if nDiv != nNumber:
            nSumDiv += nDiv
    if nNumber == nSumDiv:
        return True
    else:
        return False


##  Documentation for the main function.
#
#   More details.
def main():
    
    #nNumber = GetANumber()
    #naDivisors = CalculateDivisors(nNumber)
    #print(naDivisors)

    #nNum1, nNum2 = GetTwoNumbers()
    #nGCD = CalculateGreatestCommonDivisor(nNum1, nNum2)
    #print (nGCD)
    #nLCM = CalculateLeastCommonMultiple(nNum1, nNum2)
    #print (nLCM)
  
    nNumber = GetANumber()
    print (IsAPerfectNumber(nNumber))
    #print(naDivisors)
 
    return

if __name__ == "__main__":
    main()
