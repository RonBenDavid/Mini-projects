/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
#include <stdio.h>
#define COLS 5//Number of Columns
#define ROWS 5//Number of Rows
int Check(int[][COLS], int, int);//prototype
void main()
{
	int arry[ROWS][COLS], i, j, result;
	printf("Please write down the numbers of the matrix or table\n");
	for (i = 0; i < ROWS; i++)//Initialize array by user
		for (j = 0; j < COLS; j++)
		{
			printf("Row %d Column %d\narry[%d][%d]=", i, j, i, j);
			scanf("%d", &arry[i][j]);
			printf("\n");
		}
	result = Check(arry, ROWS, COLS);
	if (result == 0)
		printf("More than one row or column of the array, not sorted in ascending order\n");
	if (result == 1)
		printf("One of the rows or columns of the array are not sorted in ascending order\n");
	if (result == 2)
		printf("All rows and all columns of the array are sorted in ascending order\n");
}
int Check(int a[][COLS], int rows, int cols)
{
	int i, j, x = 0;
	for (i = 0;i < rows;i++)//Rows check, As long as X is different from one, I don't want the loop to continue working(double break)
		for (j = 0; j < cols - 1; j++)
			if (a[i][j] >= a[i][j + 1])//the "if" Checks if the number from left in the row bigger from the right number
			{
				x++;//add to the result
				goto end1;//i use "goto" because i want a double break and not continue to check
			}
	end1:;
	for (i = 0;i < rows - 1;i++)//Columns check,As long as X<=1, I don't want the loop to continue working (double break)
		for (j = 0; j < cols; j++)
			if (a[i][j] >= a[i + 1][j])//the "if" Checks if the number from the top in the column bigger from the low number
			{
				x++;//add to the result
				if (x >= 2)//fast exit
					return 0;
				goto end2;//i use "goto" because i want a double break and not continue to check
			}
	end2:;
	if (x == 1)
		return 1;
	return 2;
}