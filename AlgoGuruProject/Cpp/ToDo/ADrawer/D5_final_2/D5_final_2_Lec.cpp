#include <stdio.h>
int X, Y;
int a[1000+10][1000+10];
int main()
{
    int i, j;
    // 입력받는 부분
    scanf("%d %d", &Y, &X);
    for(i=0; i<Y; i++)
    {
        for(j=0; j<X; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
 
    // 여기서부터 작성
    for(i=0; i<Y; i++)
    {
        for(j=1; j<X; j++)
        {
            if (a[i][j] == 0) continue;
            a[i][j] += a[i][j-1];
        }
    }
     
    for(i=0; i<Y; i++)
    {
        for(j=0; j<X; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
 
    return 0;
}
/**************************************************************
    Problem: 1246
    User: SWT01005
    Language: C
    Result: Accepted
    Time:195 ms
    Memory:5140 kb
****************************************************************/
