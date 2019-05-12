# -*- coding: utf-8 -*-
## @package RGB distance

def GetInputValue():
    
    import sys
    try:
        nValue = int(input())
    except:
        print("[Error] Unexpected error.", sys.exc_info()[0])

    return nValue

def GetRgbCosts(nNumOfHouses):

    import sys
    rgb_cost_list = []
    for _ in range(nNumOfHouses):
        try:
            rgb_cost_for_each_house = [int(item) for item in input().split()]
        except:
            print("[Error] Unexpected error.", sys.exc_info()[0])
        rgb_cost_list.append(rgb_cost_for_each_house)

    return rgb_cost_list

def CalculatePaintingCost(nNumOfHouses, nmRgbCostForEachHouse):

    total_cost = 0
    cost = []
    a = nmRgbCostForEachHouse
    for _ in range(nNumOfHouses):
        cost.append([0] * 3)

    cost[0][0] = a[0][0]
    cost[0][1] = a[0][1]
    cost[0][2] = a[0][2]

    for idx, _ in enumerate(a):
        if idx > 0:
            cost[idx][0] = a[idx][0] + min(cost[idx-1][1], cost[idx-1][2])
            cost[idx][1] = a[idx][1] + min(cost[idx-1][0], cost[idx-1][2])
            cost[idx][2] = a[idx][2] + min(cost[idx-1][0], cost[idx-1][1])      
    
    total_cost = min(cost[nNumOfHouses-1])

    return total_cost


def main():

    nNumOfHouses = GetInputValue()
    nmRgbCostForEachHouse = GetRgbCosts(nNumOfHouses)
    nTotalCost = CalculatePaintingCost(nNumOfHouses, nmRgbCostForEachHouse)
    print(nTotalCost)

    return

if __name__ == '__main__':
    main()