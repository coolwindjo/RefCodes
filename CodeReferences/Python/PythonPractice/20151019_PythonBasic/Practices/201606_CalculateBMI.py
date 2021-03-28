# -*- coding: utf-8 -*-
##  @package CalculateBMI

##  Documentation for GetHeightAndWeight()
#
#   More details.
def try_input(strOutput):

    import sys
    for i in range(1,10):
        try:
            fInputValue = float(input(strOutput))
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
 
    return fInputValue

def GetHeightAndWeight():
   
    nHeight = try_input("Enter your height: ")
    nWeight = try_input("Enter your weight: ")
    
    return nHeight, nWeight


##  Documentation for CalculateBMI()
#
#   More details.
def CalculateBMI(nHeight, nWeight):

    heightInMeter = nHeight/100
    nBMI = nWeight/pow(heightInMeter,2)

    return nBMI


##  Documentation for the main function.
#
#   More details.
def main():
    
    nHeight, nWeight = GetHeightAndWeight()
    print(nHeight, nWeight)
    
    nBMI = CalculateBMI(nHeight, nWeight)
    print("Your BMI is {:.2f}".format(nBMI))

    return

if __name__ == "__main__":
    main()
