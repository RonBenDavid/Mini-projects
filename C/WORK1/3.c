/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
int reverse(int);//prototype
void main()
{
	int num, i;
	do
	{
		printf("Please select positive number that you want to reverse\n\n");
		scanf("%d", &num);
		if (num<0)
			printf("ERROR:You can try again\nNote: Write down only positive numbers\n\n");
	} while (num < 0);
	printf("the reverse number is: %d", reverse(num));//in the print we call the function.
}
int reverse(int i)
{
	int result, helper;
	result = 0;
	while (i != 0)
	{
		helper = i % 10;//take the first number like 3 from 20453
		result = result * 10 + helper;//take the previous number and multiply him by 10 and add the single number
		i /= 10;//Get out the first number like 3 from 20453
	}
	return result;
}