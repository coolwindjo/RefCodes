# -*- coding: utf-8 -*-
##  @package palindrome

##  Documentation for 
#
#   More details.
def try_input(strOutput):

    import sys
    for i in range(1,10):
        try:
            strInputValue = input(strOutput)
            break

        except  ValueError:
            print("[Error] Could not convert data to a string.")
            continue
        except  NameError:
            print("[Error] The input is not a string.")
            continue
        except  :
            print("[Error] Unexpected error.", sys.exc_info()[0])
            continue
 
    return strInputValue

def GetUserInput():
   
    strInputString = try_input("Enter a string: ")
    
    return strInputString


##  Documentation for 
#
#   More details.
def CheckIfPalindrome(strInputString):

    nStrLenth = len(strInputString)
    strResult = "a Palindrome"
    
    for i in range(0,int(nStrLenth/2)):
     
        if strInputString[i] == strInputString[-1-i]:
            continue
        else:
            strResult = "NOT a Palindrome"
            break

    return strResult


##  Documentation for the main function.
#
#   More details.
def main():
    
    strInputString = GetUserInput()
    print(strInputString)
    
    strResult = CheckIfPalindrome(strInputString)
    print("Your String is " + strResult)

    return

if __name__ == "__main__":
    main()
