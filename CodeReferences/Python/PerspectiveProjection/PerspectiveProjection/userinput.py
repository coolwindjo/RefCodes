# -*- coding: utf-8 -*-
##  @package UserInput
#   Documentation for this module
#
#   More details
class UserInput(object):
    """A class for getting input from a user"""
    
    def __init__(self, *args, **kwargs):
        return super(UserInput, self).__init__(*args, **kwargs)
    
    def get_title(self, strDefaultTitle=''):
        
        if (strDefaultTitle == ''):
            strTitle = self.try_string_input("Enter a data title: ")
        else:
            strTitle = strDefaultTitle

        return strTitle

    def get_filename(self, strBaseOrShifting):
        
        strTitle = self.try_string_input("Enter a " + strBaseOrShifting + " File Name: ")

        return strTitle

    def try_string_input(self, strOutput):

        import sys
        for i in range(1,10):
            try:
                strInputValue = input(strOutput)
                break
            except ValueError:
                print("[Error] Could not convert data to a string.")
                continue
            except NameError:
                print("[Error] The input is not a string.")
                continue
            except :
                print("[Error] Unexpected error at try_string_input().", sys.exc_info()[0])
                continue
        
        return strInputValue

    def get_number(self, strValueKind):
        
        nNumber = self.try_integer_input("Enter " + strValueKind + " number : ")

        return nNumber

    def get_float(self, strValueKind):
        
        fValue = self.try_float_input("Enter " + strValueKind + " value : ")

        return fValue

    def try_integer_input(self, strOutput):

        import sys
        for i in range(1,10):
            try:
                nInputValue = int(input(strOutput))
                break
            except ValueError:
                print("[Error] Could not convert data to an integer.")
                continue
            except NameError:
                print("[Error] The input is not a integer.")
                continue
            except :
                print("[Error] Unexpected error at try_integer_input().", sys.exc_info()[0])
                continue
        
        return nInputValue

    def try_float_input(self, strOutput):

        import sys
        for i in range(1,10):
            try:
                fInputValue = float(input(strOutput))
                break
            except ValueError:
                print("[Error] Could not convert data to a floating point number.")
                continue
            except NameError:
                print("[Error] The input is not a floating point number.")
                continue
            except :
                print("[Error] Unexpected error at try_float_input().", sys.exc_info()[0])
                continue
        
        return fInputValue

def try_matrix_input(self):

        import sys
        try:
            narInput = [int(item) for item in input().split()]
        except ValueError:
            print("[Error] Could not convert data to an integer.")
        except NameError:
            print("[Error] The input is not a integer.")
        except :
            print("[Error] Unexpected error at try_matrix_input().", sys.exc_info()[0])
        
        return narInput

def main():
   
    nMinIndex = get_number("Minimum")
    nMaxIndex = get_number("Maximum")
    print(nMinIndex, nMaxIndex)
    
    if nMaxIndex <= nMinIndex:
        print("[Error] Maximum index is not bigger than Minimum index.")

    strBaseFile = get_filename("Base")
    strShiftingFile = get_filename("Shifting")
 
    nmatValues1 = get_vehicle_signal_matrix_with_given_range(strBaseFile, strShiftingFile, nMinIndex, nMaxIndex-nMinIndex)
    print(nmatValues1)

    return

if __name__ == "__main__":
    main()