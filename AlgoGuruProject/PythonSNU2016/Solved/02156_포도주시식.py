# -*- coding: utf-8 -*-
## @package WineTaste


def GetNumOfWines():
    
    import sys
    try:
        nNumOfWines = int(input())
    except:
        print("[Error] Unexpected error.", sys.exc_info()[0])

    return nNumOfWines


def GetWineAmountList(nNumOfWines):
    
    import sys
    nmatWineAmountList = []
    for _ in range(nNumOfWines):
        try:
            wine_amount_for_each_glass = int(input())
        except:
            print("[Error] Unexpected error.", sys.exc_info()[0])
        nmatWineAmountList.append(wine_amount_for_each_glass)
  
    return nmatWineAmountList


def CalculateWineAmount(nNumOfWines, nmatWineAmountList):
    
    nTotalAmount = 0
    acc_amount = []
    w = nmatWineAmountList
    for _ in range(nNumOfWines):
        acc_amount.append([0]*3)

    acc_amount[0][0] = 0
    acc_amount[0][1] = w[0]
    #acc_amount[0][2] = Impossible

    #acc_amount[1][0] = max(acc_amount[0])
    #acc_amount[1][1] = acc_amount[0][0] + w[1]
    #acc_amount[1][2] = acc_amount[0][1] + w[1]

    #acc_amount[2][0] = max(acc_amount[1])
    #acc_amount[2][1] = acc_amount[1][0] + w[2]
    #acc_amount[2][2] = acc_amount[1][1] + w[2]

    for idx, wine_amount in enumerate(w):
        if idx > 0 :
            acc_amount[idx][0] = max(acc_amount[idx-1])
            acc_amount[idx][1] = acc_amount[idx-1][0] + wine_amount
            acc_amount[idx][2] = acc_amount[idx-1][1] + wine_amount

    nTotalAmount = max(acc_amount[nNumOfWines-1])

    return nTotalAmount


def main():

    nNumOfWines = GetNumOfWines()
    nmatWineAmountList = GetWineAmountList(nNumOfWines)
    
    #print(nNumOfWines)
    #print(nmatWineAmountList)

    nTotalAmount = CalculateWineAmount(nNumOfWines, nmatWineAmountList)
    print(nTotalAmount)

    return

if __name__ == '__main__':
    main()