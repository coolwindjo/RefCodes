# -*- coding: utf-8 -*-
##  @package Template_ClassAndFunctions_FileIO
#   Documentation for this module.
#
#   More details.

##  Documentation for a function.
#
#   More details.
def function1():

    return

##  Documentation for a class.
#
#   More details.
class PyClass:
    
    ##  The constructor.
    def __init__(self, **kwargs):
        return super().__init__(**kwargs)

    ##  Documentation for a method.
    #   @param self The object pointer.
    def PyMethod(self):
        pass

    ## A class variable.
    nClassVar = 0
    

##  Documentation for a function.
#
#   More details.
def assert_test(arg):
    assert type(arg) != int, "[Assert] Input value should be an integer."
    return

import sys  # Recommended form.
def GetNumbersFromFile(strFileName):
    
    numList = []
    try:
        with open(strFileName, 'r') as f:
            for line in f.readlines():
                numList.append(line.strip())
                assert_test(numList[-1])
    except IOError as e:
        print("[Error] I/O error({0}):  {1}".format(e.errno, e.strerror))
    except ValueError:
        print("[Error] Could not convert data to an integer.")
    except :
        print("[Error] Unexpected error", sys.exc_info()[0])
        raise
    f.close()

    return numList


##  Documentation for the main function.
#
#   More details.
def main():
    
    nNumList = GetNumbersFromFile("input_file.txt")

    ret = function1()

    print(ret)

    return

if __name__ == "__main__":
    main()