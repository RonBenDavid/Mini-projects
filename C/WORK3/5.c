/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
void AnalyzeLine(char*);
int GetType(char*);
void AnalyzeWords(char*, int);
void main()
{
	char line[200];
	printf("Enter variable declarations\n");
	gets(line);
	while (line[0] != '\0')//Finish when get blank line.
	{
		AnalyzeLine(line);
		printf("Enter next variable declarations OR ending program with a blank line\n");
		gets(line);
	}
}

void AnalyzeLine(char *line)
{
	int type = GetType(line);//Get size of type value.
	AnalyzeWords(line, type);
}

int GetType(char *line)
{
	int i = 0, sizeoftype;
	char firstletter = line[i];
	while (1)
	{
		if (firstletter == 'd') //8 bytes-double.
		{
			sizeoftype = 8;
			break;
		}
		if ((firstletter == 'i') || (firstletter == 'f') || (firstletter == 'l')) //4 bytes-int,float,long.
		{
			sizeoftype = 4;
			break;
		}
		if (firstletter == 's') //2 bytes-short.
		{
			sizeoftype = 2;
			break;
		}
		if (firstletter == 'c') //1 byte-chart.
		{
			sizeoftype = 1;
			break;
		}

	}
	return sizeoftype;
}

void AnalyzeWords(char *line, int sizetype)
{
	char scanner;//Run letter by letter.
	int i = 0, sizeofarray;
	scanner = line[i];
	while (scanner != ' ')//Jump over letter of the type.
	{
		i++;
		scanner = line[i];
	}
	while (scanner == ' ')//Jump over spaces.
	{
		i++;
		scanner = line[i];
	}

	//Start from all types of variable.
	while (scanner != ';')//until we get ";".
	{
		if (scanner == ',')//jump over comma(",").
		{
			i++;
			scanner = line[i];
			while (scanner == ' ')//Remove spaces between comma(",") to variable.
			{
				i++;
				scanner = line[i];
			}
			continue;//Skip to next variable.
		}

		if (scanner == '*')//If first letter is "*",pointer case.
		{
			i++;
			scanner = line[i];
			while ((scanner != ',') && (scanner != ';')) //Run just over letters of word and print them 1 by 1.
			{
				printf("%c", scanner);
				i++;
				scanner = line[i];//Next letter of variable.
			}
			printf(" requires 4 bytes\n"); //Print the pointer.
			continue;//Skip to next variable.
		}

		while ((scanner != ',') && (scanner != ';')) //Variable case or array case.
		{
			printf("%c", scanner);
			i++;
			scanner = line[i];
			if ((scanner == ',') || (scanner == ';')) //We are done and print.
			{
				printf(" requires %d bytes\n", sizetype);
				continue;
			}

			if (scanner == '[') //Variable array case.
			{
				printf("[");
				i++;
				scanner = line[i]; //The first number between[].
				sizeofarray = 0;
				while (scanner != ']')//Count number between [].
				{
					printf("%c", scanner);//print number
					sizeofarray *= 10;
					sizeofarray = sizeofarray + scanner - (int)('0'); //Char to number.
					i++;
					scanner = line[i];
				}
				printf("] requires %d bytes\n", sizeofarray*sizetype);//Print array case.
				i++;
				scanner = line[i]; //=space or ','-> then we send continue and go back to the main while loop.
				continue;
			}
		}
	}
}
