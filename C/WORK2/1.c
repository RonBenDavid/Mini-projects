/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
#define SIZE 10
void SelectionSort(int [],int);//prototype-return nothing
int RemoveDup(int [],int);//prototype-return number
void main()
{
	int listarray[SIZE], i, count;
	printf("Plese insert numbers to the array\n");
	for (i = 0;i < SIZE;i++)
	{
		printf("a[%d]=", i);
		scanf("%d", &listarray[i]);
	}
	SelectionSort(listarray, SIZE);
	printf("\nsort of the arry\n");//Print short array
	for (i = 0;i < SIZE;i++)
		printf("a[%d]=%d\n", i, listarray[i]);
	count = RemoveDup(listarray, SIZE);//recive the result from the function
	printf("\nafter remove duplicates\n");//Print after remove duplicate numbers
	for (i = 0;i < count;i++)
		printf("a[%d]=%d\n", i, listarray[i]);
	printf("\n%d duplicates numbers are remove\n", (SIZE - count));
}
void SelectionSort(int a[], int n)
{
	int i, j, min, swap;
	for (i = 0; i < n - 1; i++)
	{
		min = i;//min number coordinate
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])//scan the min number
				min = j;//the new min coordinate
		swap = a[min];//swap with the first number with the min number loction
		a[min] = a[i];
		a[i] = swap;
	}
}
int RemoveDup(int a[], int n)
{
	int i, count = 0;
	for (i = 0;i < n;i++)
		if (a[count] != a[i + 1])//if its false go to the next loop and move it to the left
		{
			a[count + 1] = a[i + 1];//number move to the left and remove the duplicate number
			count++;//Count the number that not duplicate
		}
	return count;
}