/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
# include <stdio.h>
# include <stdlib.h>
int *powerArray(int);
void main()
{
	int n, i;
	int *p;
	printf("enter size of array\n");
	scanf("%d", &n);
	p = powerArray(n);//Call function.
	printf("The array is\n");
	for (i = 0; i<n; i++)//Print all array index.
	{
		printf("[%3d]=%10u\n",i, p[i]);
	}
	free(p);//Free memory
}
int *powerArray(int n)
{
	int i;
	unsigned int* power = (unsigned int*)malloc(n * sizeof (unsigned int));//Memory Allocation.
	power[0] = 1;
	for (i = 1;i<n;i++)//Fill array.
	{
		if (i % 32 == 0)//(32 MOD 32)=0 so every time i=32*n, n=0,1,2... We get 0 in the exponent but we also can see after i=32*n,We start over again like 33 mod 31=1. 
		{
			power[i] = 1;
		}
		else
		{
			power[i] = 2 * power[i - 1];//Alternative pow function.
		}
	}
	return power;
}