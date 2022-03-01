/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define N 1001
void main()
{
	int i, j;
	printf("All the prime numbers between 1 to 1000:\n\n");
	bool Is_prime[N] = {false};
	for (i = 2;i < N;i++)//Initialize all array to true
		Is_prime[i] = true;
	for (i = 2;i <= (int)sqrt(N);i++)//check up to a square root of 1000
		if (Is_prime[i])//Checks if the number has already become False
			for (j = i;j*i < N;j++)//Changes all multiples of the current number
				Is_prime[j*i] = false;
	j = 0;//j is now number counter
	for (i = 2;i < N;i++)//Check the number that left True
		if (Is_prime[i])
		{
			printf(" %3d", i);//Print the prime number
			j++;
			if((j%10)==0)//For a better look
				printf("\n");
		}
	printf("\n\n%d Prime numbers\n\n",j);//Number of prime number
}