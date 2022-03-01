#define _CRT_SECURE_NO_DEPRECATE
/*
Assigned by:
Ron ben david #307906263
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define max_student 30
struct student
{
	char* name;
	int grade;
}typedef student_t;
struct class
{
	student_t classtudents;
	int  numofstudent;
	student_t* students[max_student];
	int avargeclass;
}typedef class_t;

void createclass(class_t* theclass);
void createstudent(student_t* theclass);
void freeclass(class_t* theclass);
void printavarge(class_t* theclass);
void main()
{
	class_t newclass;
	createclass(&newclass);
	printavarge(&newclass);
	freeclass(&newclass);

}
void createclass(class_t* theclass)
{
	int i,count=0;
	printf("how many students?");
	scanf("%d", &theclass->numofstudent);
	for (i = 0; i < theclass->numofstudent; i++)
	{
		theclass->students[i] = (student_t*)malloc(sizeof(student_t));
		printf("enter information about student #&d: \n", (i + 1));
		createstudent(theclass->students[i]);
	}

}
void createstudent(student_t* thestudent)
{
	char temp[20];
	printf("enter full name\n");
	scanf("%s",&thestudent->name);
	printf("enter avarge grade\n");
	scanf("%d", &thestudent->grade);
}
void freeclass(class_t* theclass)
{
	int i;
	for (i = 0; i < theclass->numofstudent; i++)
		free(theclass->students[i]);
}
void printavarge(class_t* theclass)
{
	int i,count=0;
	for (i = 0; i < theclass->numofstudent; i++)
	{
		count += theclass->students[i]->grade;
	}
theclass->avargeclass = count / theclass->numofstudent;
	printf("the avarge is %d", theclass->avargeclass);
}
