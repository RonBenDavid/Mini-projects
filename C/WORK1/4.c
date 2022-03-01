/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
int fib(int);
void main()
{
	int i, num;
	do
	{
		printf("choose number in N place to get fibanochi number\n");
		scanf("%d", &num);
		if (num<0)
			printf("ERROR:You can try again\nNote: Write down only positive numbers\n\n");
	} while (num < 0);
	printf("F%d=%d\n", num, fib(num));
}
int fib(int fn)
{
	int fnow = 0, fnext = 1, nextplus1, i;
	if (fn == 0)
		return fnow;
	for (i = 1; i < fn; i++)
	{
		nextplus1 = fnow + fnext;//F(n+1)=f(n-1)+F(n)
		fnow = fnext;//F(n-1)=F(n)
		fnext = nextplus1;//F(n)=F(n+1)
	}
	return fnext;
}
