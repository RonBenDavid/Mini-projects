/*
Assigned by:
Ron ben david #307906263
*/
#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char* path;
	if (argc < 3)
	{
		printf("Valid Arguments\n");
		printf("---------------\n");
		printf("To insert a new playlist: program.exe usersPath.txt itemsPath.txt[-sortindex]\n");
		
	}
	/*
	* if data import wasn't successful exit the programm
	*/
	menu(argv[1], argv[2]);
	return 0;
}
