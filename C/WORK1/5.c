/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
#include <math.h>
int perfect(int);//prototype
void main()
{
	int i, j;
	printf("The perfect number between 1 to 1000 is: \n");
	for (i = 1, j = 1; i <= 1000; ++i)//run from 1 to 1000
	{
		if (perfect(i) == i)//If the result of the function is equal to the same i, we will print the perfect number.
		{
			printf("%d)%d\n", j, i);
			j = j++;
		}
	}

}
int perfect(number)
{
	int i, export = 0;
	for (i = 1; i <= number / 2; i++)//run from 1 to half of the i number that we recive from the main.
	{
		if (number%i == 0)//if the number we get devision with the i --> add it to the variable epxort.
		{
			export += i;
		}
	}
	return export;
}