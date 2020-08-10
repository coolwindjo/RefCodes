#include <stdio.h>
  
char s[50+10];
int  sol;
  
int main(void)
{
      // 입력받는 부분
      scanf("%s", s);
  
      // 여기서부터 작성
      int i = 0;
      int h = 0;
      char prev = '0';
      while(s[i] != '\0'){
          if(s[i] == prev){
              h += 5;
          }
          else{
              h += 10;
          }
          prev = s[i];
          i++;
      }
      sol = h; 
 
      // 출력하는 부분
      printf("%d", sol);
  
      return 0;
}