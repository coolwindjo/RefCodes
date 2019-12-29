#include "../../ProbSolvStart.h"

int GetInputValue()
{
    int nValue = 0;

    cin >> nValue;

    return nValue;
}

int CalculateCasesOfLionDeployment(int nNumOfRows)
{
    int nTotalCases = 0;
    int nmatLionDeploy[2][3] = { 0, };
    int toggle = 0;
    int previous = 0;
    int i;

    nmatLionDeploy[0][0] = 1;
    nmatLionDeploy[0][1] = 1;
    nmatLionDeploy[0][2] = 1;

    for (i = 1; i < nNumOfRows; ++i)
    {
        toggle = i % 2;
        nmatLionDeploy[toggle][0] = nmatLionDeploy[previous][0] + nmatLionDeploy[previous][1] + nmatLionDeploy[previous][2];
        nmatLionDeploy[toggle][1] = nmatLionDeploy[previous][0] + nmatLionDeploy[previous][2];
        nmatLionDeploy[toggle][2] = nmatLionDeploy[previous][0] + nmatLionDeploy[previous][1];
        previous = toggle;
    }

    nTotalCases = (
        nmatLionDeploy[toggle][0]
        + nmatLionDeploy[toggle][1]
        + nmatLionDeploy[toggle][2]
        ) % 9901;

    return nTotalCases;
}


int main()
{
    int nValOfN = GetInputValue();
    int nTotalCases = CalculateCasesOfLionDeployment(nValOfN);
    cout << nTotalCases << endl;

    return 0;
}