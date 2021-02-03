#include <stdio.h>
 
int N;
double d[10000+10];
double sol;
 
int main(void)
{
      int i;
 
      // 입력받는 부분
      scanf("%d", &N);
      for(i=0; i<N; i++)
      {
            scanf("%lf", &d[i]);
      }
 
      // 여기서부터 작성
      double s = 1;
      for(i=0; i<N; i++)
      {
            s *= d[i];
      }

      double max = s;
      int fr = 0;
      int f = 0;
      int r = N-1;
      for(int j=0; j<N; j++)
      {
            if (fr == 0)
            {
                  i = f;
                  f++;
            }
            else{
                  i = r;
                  r--;
            }

            s /= d[i];
            if(max < s) {
                  max = s;
            }
            else{
                  fr = (fr + 1)%2;
            }
      }
      sol = max;
 
      // 출력하는 부분
      printf("%.3lf", sol);
 
      return 0;
}