#include <stdio.h>
extern void func(void);
int main(void)
{
	printf("main: Hi!\n");
	func();
	return 0;
}
