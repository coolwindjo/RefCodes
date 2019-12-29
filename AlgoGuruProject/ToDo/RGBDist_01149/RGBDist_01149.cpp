#include "../../ProbSolvStart.h"

int GetInputValue()
{
    int nValue = 0;

    cin >> nValue;

    return nValue;
}

int* GetRgbCosts(int nNumOfHouses)
{
    int** rgb_cost_matrix = { 0, };
    rgb_cost_matrix[0] = (int*) calloc(3, sizeof(int));

    return NULL;
}

int CalculatePaintingCost(int nNumOfHouses)
{
    return 0;
}


int main()
{
    int nNumOfHouses = GetInputValue();
    int* pnRgbCostForEachHouse = GetRgbCosts(nNumOfHouses);
    int nTotalCost = CalculatePaintingCost(nNumOfHouses);
    printf("%d", nTotalCost);

    return 0;
}