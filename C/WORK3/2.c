/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
void ConvertMinutesToHM(int, int*, int*);
void main()
{
	int time, minutes, hours;
	printf("Enter number of minutes \n");
	scanf("%d", &time);
	ConvertMinutesToHM(time, &hours, &minutes);
	printf("Hours=%d\n", hours);//Print hours
	printf("Minutes=%d\n", minutes);//Print minutes
}
void ConvertMinutesToHM(int time_minutes, int *phours, int *pminutes)
{
	*phours = time_minutes / 60;//Hours without minutes
	*pminutes = time_minutes % 60;//Remain minutes
}