/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
void main()
{
	int num1, num2, result, i;
	do
	{
		printf("Choose 2 positive numbers you want to multiply\n");
		printf("Enter first number\n");
		scanf("%d", &num2);
		printf("Enter second number\n");
		scanf("%d", &num1);
		if (num1 < 0 || num2 < 0)//If the user has entered one or more negative numbers.We will loop until positive values ​​are entered.
		{
			printf("\nERROR:Try again\nNote: Write down only positive numbers\n\n");
		}
		result = 0;
	} while (num1 < 0 || num2 < 0);

	for (i = 1; i <= num2; i++)//Sum all of the addition num1 by itself X times num2
		result += num1;
	printf("\nthe result is:%d", result);
}