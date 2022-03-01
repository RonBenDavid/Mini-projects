/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void GetDate(char *, int *, int *, int *);
void main()
{
	char date[10];
	int day, month, year;
	printf("enter a date as dd-mmm-yy\n");
	gets(date);
	GetDate(date, &day, &month, &year);//Call function.
	printf("Day = %d\n", day);
	printf("Month = %d\n", month);
	printf("Year = %d\n", year);
}
void GetDate(char *date, int *dp, int *mp, int *yp)
{
	int i;
	char month[4];
	*dp = (int)(date[0] - '0') * 10 + (int)(date[1] - '0');//Do casting by use assci '0'=48 to get the fist decimal number.
	*yp = (int)(date[7] - '0') * 10 + (int)(date[8] - '0');
	for (i = 0;i<3;i++)//Month have 3 letters we want to copy to month array.
	{
		month[i] = tolower(date[i + 3]);//Scan letters after days. tolower for up scale letters
	}
	month[3] = '\0';//Use if-eles ladder.
	if (strcmp(month, "jan") == 0)
		*mp = 1;
	else if (strcmp(month, "feb") == 0)
		*mp = 2;
	else if (strcmp(month, "mar") == 0)
		*mp = 3;
	else if (strcmp(month, "apr") == 0)
		*mp = 4;
	else if (strcmp(month, "may") == 0)
		*mp = 5;
	else if (strcmp(month, "jun") == 0)
		*mp = 6;
	else if (strcmp(month, "jul") == 0)
		*mp = 7;
	else if (strcmp(month, "aug") == 0)
		*mp = 8;
	else if (strcmp(month, "sep") == 0)
		*mp = 9;
	else if (strcmp(month, "oct") == 0)
		*mp = 10;
	else if (strcmp(month, "nov") == 0)
		*mp = 11;
	else if (strcmp(month, "dec") == 0)
		*mp = 12;
}