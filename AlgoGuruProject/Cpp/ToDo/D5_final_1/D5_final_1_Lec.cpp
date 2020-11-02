#include <stdio.h>
  
int N;
int in[4];
int out[4];
int sol;
  
int main(void)
{
      int i;
      int t =0;
  
      
      for(i=0; i<4; i++)
      {
            scanf("%d %d", &out[i], &in[i]);
      }
  
      
      for (i=0; i<4; i++)
      {
            t = t - out[i] + in[i];
            if (sol < t) sol = t;
      }
  
      
      printf("%d", sol);
  
      return 0;
}
/**************************************************************
    Problem: 1209
    User: SWT01006
    Language: C
    Result: Accepted
    Time:2 ms
    Memory:1156 kb
****************************************************************/