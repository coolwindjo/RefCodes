#include <stdio.h>
 
int N;
int a[100+10][100+10];
int sol;
 
int main(void)
{
      int i, j;
 
      // 입력받는 부분
      scanf("%d", &N);
      for(i=1;i<=N;i++)
      {
            for(j=1;j<=N;j++)
            {
                  scanf("%1d", &a[i][j]);
            }
      }
 
      // 여기서부터 작성
      
 
      // 출력하는 부분
      printf("%d", sol);
 
      return 0;
}