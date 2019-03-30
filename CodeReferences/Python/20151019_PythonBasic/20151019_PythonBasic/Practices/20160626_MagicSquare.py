# -*- coding: utf-8 -*-
##  @package MagicSqaure

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
            print("[Error] Could not convert data to a string.")
            continue
        except  NameError:
            print("[Error] The input is not a string.")
            continue
        except  :
            print("[Error] Unexpected error.", sys.exc_info()[0])
            continue
 
    return nInputValue

def GetUserInput():
   
    nInputNum = try_input("Enter a number: ")
    
    return nInputNum



##  Documentation for 
#
#   More details.
def PrintMagicSquare(arrMagicSquare, nInputNum):

        
    for i in range(0, nInputNum):
        for j in range(0, nInputNum):
            print (arrMagicSquare[i][j], end='\t'),
        print ("")
    print ("")

    return


##  Documentation for 
#
#   More details.
def MakeMagicSqaure(nInputNum):

    matSquare = []
    for _ in range(nInputNum):
        matSquare.append([0]*nInputNum)
    
    nRow = 0
    nCol = int(nInputNum/2)
    nNum = 1

    for _ in range (pow(nInputNum,2)):
        if matSquare[nRow][nCol] > 0:
            nRow += 2
            nCol -= 1
            nRow %= nInputNum
            nCol %= nInputNum

        matSquare[nRow][nCol] = nNum
        nRow -= 1
        nCol += 1            
        nRow %= nInputNum
        nCol %= nInputNum
        nNum += 1

    return matSquare


##  Documentation for the main function.
#
#   More details.
def main():
    
    nInputNum = GetUserInput()
    
    matSquare = MakeMagicSqaure(nInputNum)

    PrintMagicSquare(matSquare, nInputNum)

    return

if __name__ == "__main__":
    main()
