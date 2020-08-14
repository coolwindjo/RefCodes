#include<stdio.h>

int cnt;
void f(int n);

int main()
{
	int  num = 10 ;
	f(num);
	printf("%d\n" , cnt) ;
	getchar();
	return 0;
}
void f(int n)
{
	if(n<=1)
		cnt++;	/* n<=1 ÀÌ¸é cnt 1Áõ°¡ */
	else
	{
		f(n/2);	/* nÀ» 2·Î ³ª´« ¸òÀ¸·Î Àç±ÍÈ£Ãâ */
		f(n/2);	/* nÀ» 2·Î ³ª´« ¸òÀ¸·Î Àç±ÍÈ£Ãâ */
	}
    return;
}
