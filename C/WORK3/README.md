question 1
Write a GetDate function with the following prototype:

void GetDate (char * date, int * dp, int * mp, int * yp);

The function accepts as a parameter a date string that contains a date in the following format:

dd - mmm - yy: two digits to mark the day, three short letters to mark the month, and a year in two digits.

The function should separate the components and pass them by reference as numbers.

Write a program that picks up the string and activates the function.

It can be assumed that the string input is correct.


Question 2
Write a plan that converts time given (received) in minutes, to separate values ​​of hours and minutes.
The program should use the function responsible for performing the actual conversion, with the following possible prototype:
void ConvertMinutesToHM (int time_minutes, int * phours, int * pminutes);
  
Question 3
Write a FindFirstVowel function that receives a string and returns the first movement (Vowel) that appears in the string in the scan from left to right.

The group of movements contains the following five letters (both small and large!): A, E, I, O, U

For example, for the string Her name is Ann the function will return the letter e.

The program that executes the function will pick up the string and print the returned character.

If there are no movements in the string being tested, the function will return '\ 0' and the program will print an appropriate message.


Question 4
Write a function called powerArray that takes an integer n and returns a pointer to an array of size n and of the dynamically assigned unsigned int type (within the function).

Each cell in the array should contain 2 to the power of the remainder of the index divided by 32. That is, the value of a cell instead of i will be 2i mod 32.

For example, if given:
int * p;

Following the instruction:
p = powerArray (5);


Question 5
Write a program that captures a string that contains a series of simple declarations of variables in C and prints the amount of memory to be allocated for each variable.

Each input line must contain:
- One of the following six data types: float, long, short, int, char, double.
- One or more bootable variables (which can also be pointers and one-dimensional arrays) separated by commas.
A semicolon to indicate the end of a line.
- Unlimited profits in appropriate places (as in a real announcement line).

It can be assumed that the input line is normal.

The program ends when it encounters a blank line.