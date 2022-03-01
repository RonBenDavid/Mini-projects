#define _CRT_SECURE_NO_DEPRECATE
/*
Assigned by:
Ron ben david
*/
#include <stdio.h>
#include <ctype.h>

int countLines(char* filename);
void letterFrequency(char* filename, int counts[]);
void removeSpaces(char* infile, char* outfile);
void print_letter_frequency(int counts[]);

void main()
{
	int numLines, counts[26];
	char c,st[350];
	FILE* out;
	out = fopen("input.txt", "w");

	if (out == NULL)
	{
		printf("File could not be opened.\n");
		return;
	}
	fprintf(out, "CHAPTER I\n\n");
	fprintf(out, "Down the Rabbit-Hole\n\n");
	fprintf(out, "Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do:\n");
	fprintf(out, "once or twice she had peeped into the book her sister was reading,\n");
	fprintf(out, "but it had no pictures or conversations in it, \n");
	fprintf(out, "`and what is the use of a book,' thought Alice `without pictures or conversation?'\n");
	fclose(out);
	out = fopen("input.txt", "r");
	while(fgets(st,350,out))
		printf("%s",st);
	fclose(out);
	numLines = countLines("input.txt");
	printf("\n");
	printf("The number of lines is %d\n", numLines);
	printf("\n");
	letterFrequency("input.txt", counts);
	print_letter_frequency(counts);
	removeSpaces("input.txt", "output.txt");
}

int countLines(char* filename)
{
	FILE* f = fopen(filename, "r");//read text file
	int c;
	int count = 0;
	if (!f)//if file dont open
		return -1;
	while ((c = fgetc(f)) != EOF)//run by one-one char
		if (c == '\n')//if get end line
			count++;
	fclose(f);//close file
	return count;
}

void letterFrequency(char* filename, int counts[])
{
	int i, c;
	FILE* f = fopen(filename, "r");
	for (i = 0; i < 26; i++)//number of english letters
		counts[i] = 0;
	if (!f)
		return;
	while ((c = fgetc(f)) != EOF)
		if (isalpha(c))//checks whether a character is an alphabet or not
			counts[tolower(c) - 'a']++;//ascii(c)-ascii('a')
	fclose(f);
}

void removeSpaces(char* infile, char* outfile)
{
	int c;
	FILE* f = fopen(infile, "r");//read file
	FILE* g = fopen(outfile, "w");//write file
	if (f && g)//if both file open
		while ((c = fgetc(f)) != EOF)//file not end
			if (c != ' ')//if not space
				fputc(c, g);//write only char
	if (f)
		fclose(f);
	if (g)
		fclose(g);
}

void print_letter_frequency(int counts[])
{
	char c;
	for (c = 'a'; c <= 'z'; c++)
		printf("%c - %d times\n", c, counts[c - 'a']);
}

