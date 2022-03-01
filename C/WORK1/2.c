/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
#include <math.h>
void main()
{
	int num1, num2, number, i, check;
	double sq;
	do
	{
		printf("Please select a range of positive numbers from low to high\n\n");
		printf("Plese enter the first positive number\n");
		scanf("%d", &num1);
		printf("Please enter the positive second number\n");
		scanf("%d", &num2);
		if (num1<0 || num2<0)
			printf("ERROR:You can try again\nNote: Write down only positive numbers\n\n");
	} while (num1 < 0 || num2 < 0);

	if (num1 > num2)
	{
		printf("You put a higher number in the first place but I will help you! :)\n");//change num1 with num2
		num1 = num1 - num2;
		num2 = num1 + num2;
		num1 = num2 - num1;
	}
	printf("The prime numbers between %d to %d is: ", num1, num2);
	for (number = num1; number <= num2; number++)//run number between num1 to num2
	{
		sq = sqrt(number);//I don't want to run on all the numbers. So, as far as we know, there must be at least one divider between 1 and the root of the number.
		check = 1;
		for (i = 2; i <= (int) sq; i++)//i do casting to get the integer number of the sqrt
		{
			if ((number%i) == 0)//If a number is divided once, it is not a prime number.
			{
				check = 0;
				break;//We don't have to keep looking for prime number.
			}
		}
		if (check == 1 && number != 1)//If we dont enter to loop above so the number not divded and the number is never included becuse is not prime number.
		{
			printf("%d ", number);
		}
	}
}