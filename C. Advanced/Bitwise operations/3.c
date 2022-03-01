#define _CRT_SECURE_NO_DEPRECATE
/*
Assigned by:
Ron ben david #307906263
*/
#include <stdio.h>
#include <math.h>
int count1(unsigned int N);
int countlong(unsigned int L);
int check(unsigned int N, unsigned int pattren);
void duplicate(unsigned int N);
void displayBits(unsigned value);
void changeloc(unsigned int N, unsigned int lock, unsigned int pattern);
void main()
{
	unsigned int value, pattern,lock;
	printf("Choose number\n");
	scanf("%d", &value);
	printf("Number of bits toggle on=%d\n", count1(value));
	printf("Long of binary number=%d\n", countlong(value));
	printf("Chooce pattern number\n");
	scanf("%d", &pattern);
	printf("Number of same pattern=%d\n", check(value, pattern));
	duplicate(value);
	printf("Chooce lock number\n");
	scanf("%d", &lock);
	changeloc(value,lock,pattern);
	puts("");
}

int count1(unsigned int N)
{
	int count1 = 0;
	while (N > 0) {
		// If current bit is 1
		if (N & 1)//compare first numbers 
		{
			count1++;
		}
		N = N >> 1;//move right
	}
	return count1;
}
int countlong(unsigned int L)
{
	int longg = 0;
	while (L > 0) {
		// If current bit is 1
		if (L != 0) {
			longg++;
		}
		L = L >> 1;//move right
	}
	return longg;
}
int check(unsigned int N, unsigned int pattern)
{
	int lenNUM = countlong(N);
	int lenPat = countlong(pattern);
	int count = 0, i;
	for (i = 0; i < (lenNUM - lenPat + 1); i++)
	{
		if (pattern == (N & pattern))
			count++;
		N = N >> 1;

	}
	return count;
}
void duplicate(unsigned int N)
{
	unsigned int final = 0, temp = N;
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		final = final << 1;
		if (N & 1)
			final = final + 1;
		N = N >> 1;
		if (N == 0)
			N = temp;
	}
	displayBits(final);

}
void displayBits(unsigned value)
{
	unsigned c; /* counter */

	/* declare displayMask and left shift 31 bits */
	unsigned displayMask = 1 << 31;

	printf("%7u = ", value);

	/* loop through bits */
	for (c = 1; c <= 32; c++) {
		putchar(value & displayMask ? '1' : '0');
		value <<= 1; /* shift value left by 1 */

		if (c % 8 == 0) { /* output a space after 8 bits */
			putchar(' ');
		} /* end if */

	} /* end for */

	putchar('\n');
} 
void changeloc(unsigned int N, unsigned int lock, unsigned int pattern)
{
	unsigned int final = N;
	int lenPat = countlong(pattern);
	int i,j;
	for(i=lock-1;i<lock+lenPat-1;i++)
	{
	final  &=  ~(1UL << (i));
	if (pattern & 1)
	final ^= 1 << i;
	pattern=pattern>>1;
	}
	displayBits(N);
	printf("After changes\n");
	displayBits(final);
}