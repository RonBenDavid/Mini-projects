#define _CRT_SECURE_NO_WARNINGS
#include "store.h"
/*
Assigned by:
Ron ben david #307906263
*/
void menu(char* userpath,char* itemspath) {
	FILE* fp;
	fopen_s(&fp, userpath, "r");
	if (!fp)
	{
		fopen_s(&fp, userpath, "w");
		printf("File not found! Create Default file\n");
		fprintTOlog("File not found! Create Default file");
		fprintf_s(fp, "username        password        L fullname            \n");
		fprintf_s(fp, "admin           admin           3 System Manager      ");
		fclose(fp);
	}
	fclose(fp);
	fopen_s(&fp, itemspath, "r");
	if (!fp)
	{
		fopen_s(&fp, itemspath, "w");
		printf("File not found! Create Default file\n");
		fprintTOlog("File not found! Create Default file");
		fprintf_s(fp, "Serial     Category   Brand      Prodact Name                   Price      In Stock  Date\n");
		fprintf_s(fp, "1234       demo       demo       demo                           23.55      NO        01/01/2000, 10:15");
		fclose(fp);
	}
	fclose(fp);
	fopen_s(&fp, LOG_PATH, "r");
	if (!fp)
	{
		fopen_s(&fp, LOG_PATH, "w");
		fclose(fp);
	}
	fclose(fp);
	int day, month, year, hours, mins;
	int count = 0, i = 0, k = 0, x = -1, err = -1, level, serial=0;
	char  operator,fullname[21];
	LNode* current;
	LNode* newNode = &current;
	LNode* newNode2;
	LNode* head;
	LNode* tail;
	char username[16], password[16];
	newNode = (LNode*)calloc(1, sizeof(LNode));
	List lst = makeEmptyList();
	lst.head = newNode;
	newNode2 = (LNode*)calloc(1, sizeof(LNode));
	lst.tail = newNode;
	users_t storeUsers;
	items_t storeItems;
	count = readUserswithoutprint(userpath, &storeUsers, lst.head, lst.tail, &lst);
	current = lst.head;
	bool welcome;
	char lev = 'a';
	welcome = false;

	printf("Welcome to the Candy shop\n");
	for (i = 0; i < 3; i++)
	{
		fprintTOlog("Log in attempt");
		current = lst.head;
		printf("Enter Username:\n");
		scanf(" %s", &username);
		printf("Enter Password:\n");
		scanf(" %s", &password);
		while (current != NULL)
		{
			if (_strcmpi(username, current->usersIndex.username) == 0)
				if (strcmp(password, current->usersIndex.password) == 0)
					welcome = true;
			if (welcome)
				break;
			current = current->next;
		}
		if (welcome)
			break;
		else
		{
			fprintTOlog("Wrong Username or Password Enterd");
			printf("Wrong Username or Password\n");
			if (i != 2)
				printf("You have %d more attempts\n", 2 - i);
		}

	}
	printf("\n");
	if (welcome)
	{
		fprintTOlog("Successful entry");
		strcpy(fullname, current->usersIndex.fullname);
		level = current->usersIndex.level;
		lev = level + '0';
		switch (lev)
		{
		case '1':
			printf("\nWelcome %s \n\nHow can I help you today?\n\n", fullname);
			do {
				fprintTOlog("Read items file");
				count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
				if (Short(lst.head, &lst))
					printf("\nShorting list!");
				count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
				count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
				printf("\n");
				printf("0.Search Items by Brand or/and Prodact name Press 0\n");
				printf("1.Search Items by Value Press 1\n");
				printf("2.Search Items by Stock Press 2\n");
				printf("3.Search Items by Date Press 3\n");
				printf("4.Add new item to store Press 4\n");
				scanf(" %c", &operator);
				switch (operator)
				{
				case '0':
					searchByBorC(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '1':
					searchByValue(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '2':
					searchByStock(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '3':
					searchByDate(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '4':
					fprintTOlog("Add item");
					count = adddataItems(itemspath, &storeItems, lst.head, lst.tail, count);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				default:
					break;
				}
				printf("Need to do more actions? Press Y(or any key) if not Press N\n");
				scanf(" %c", &operator);
				if (operator=='N')
					x = 0;
			} while (x != 0);
		case '2':
			fprintTOlog("Read items file");
			printf("\nWelcome %s \n\nHow can I help you today?\n\n", fullname);
			do {
				count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
				if (Short(lst.head, &lst))
					printf("/nShorting list!");
				count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
				printf("\n");
				printf("0.Search Items by Brand or/and Prodact name Press 0\n");
				printf("1.Search Items by Value Press 1\n");
				printf("2.Search Items by Stock Press 2\n");
				printf("3.Search Items by Date Press 3\n");

				printf("4.Add new item to store Press 4\n");
				printf("5.Update item Press 5\n");
				printf("6.Delete item Press 6\n");
				scanf(" %c", &operator);
				switch (operator)
				{
				case '0':
					searchByBorC(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '1':
					searchByValue(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '2':
					searchByStock(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '3':
					searchByDate(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '4':
					fprintTOlog("Add item");
					count = adddataItems(itemspath, &storeItems, lst.head, lst.tail, count);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '5':
					fprintTOlog("Update item");
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					printf("Please Enter item Serial number to update\n");
					scanf("%d", &serial);
					editSingelitem(lst.head, serial);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '6':
					fprintTOlog("Delete item");
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					printf("Please Enter item Serial number to Delete\n");
					scanf("%d", &serial);
					count = fPrintitemRemove(itemspath, &storeItems, lst.head, lst.tail, &lst, serial);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				default:
					break;
				}
				printf("Need to do more actions? Press Y(or any key) if not Press N\n");
				scanf(" %c", &operator);
				if (operator=='N')
					x = 0;
			} while (x != 0);
		case '3':
			fprintTOlog("Read items file");
			printf("\nWelcome %s \n\nHow can I help you today?\n\n", fullname);
			do {
				count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
				if (Short(lst.head, &lst))
					printf("/nShorting list!");
				count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
				printf("\n");
				printf("0.Search Items by Brand or/and Prodact name Press 0\n");
				printf("1.Search Items by Value Press 1\n");
				printf("2.Search Items by Stock Press 2\n");
				printf("3.Search Items by Date Press 3\n");

				printf("4.Add new item to store Press 4\n");
				printf("5.Update item Press 5\n");
				printf("6.Delete item Press 6\n");

				printf("7.Add username Press 7\n");
				printf("8.Updte username Press 8\n");
				printf("9.Delete username Press 9\n");
				scanf(" %c", &operator);
				switch (operator)
				{
				case '0':
					searchByBorC(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '1':
					searchByValue(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '2':
					searchByStock(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '3':
					searchByDate(lst.head, &lst, 3);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '4':
					count = adddataItems(itemspath, &storeItems, lst.head, lst.tail, count);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '5':
					fprintTOlog("Update item");
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					printf("Please Enter item Serial number to update\n");
					scanf("%d", &serial);
					editSingelitem(lst.head,serial);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '6':
					fprintTOlog("Delete item");
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					printf("Please Enter item Serial number to Delete\n");
					scanf("%d", &serial);
					count = fPrintitemRemove(itemspath, &storeItems, lst.head, lst.tail, &lst,serial);
					count = readItems(itemspath, &storeItems, lst.head, lst.tail, &lst);
					if (Short(lst.head, &lst))
						printf("/nShorting list!");
					count = fPrintNewitemfile(itemspath, &storeItems, lst.head, lst.tail, &lst);
					break;
				case '7':
					fprintTOlog("Add user");
					count = readUsers(userpath, &storeUsers, lst.head, lst.tail, &lst);
					count =adddataUser(userpath, &storeUsers, lst.head, lst.tail, count);
					count = readUsers(userpath, &storeUsers, lst.head, lst.tail, &lst);
					break;
				case '8':
					fprintTOlog("Update User");
					count = readUsers(userpath, &storeUsers, lst.head, lst.tail, &lst);
					printf("Please Enter to update username\n");
					scanf("%s", &username);
					editSingleuser(lst.head, username);
					fPrintNewuserfile(userpath, &storeItems, lst.head, lst.tail, &lst);
					count = readUsers(userpath, &storeUsers, lst.head, lst.tail, &lst);
					break;
				case '9':
					fprintTOlog("Delete User");
					count = readUsers(userpath, &storeUsers, lst.head, lst.tail, &lst);
					printf("Please Enter username to Delete\n");
					scanf("%s", &username);
					count = fPrintuserRemove(userpath, &storeItems, lst.head, lst.tail, &lst, username);
					count = readUsers(userpath, &storeUsers, lst.head, lst.tail, &lst);
					break;
				default:
					break;
				}
				printf("Need to do more actions? Press Y(or any key) if not Press N\n");
				scanf(" %c", &operator);
				if (operator=='N')
					x = 0;
			} while (x != 0);
		default:
			break;
		}
	}
	else 
	{
		fprintTOlog("User blocked from software");
		printf("You are blocked from the system as a result of too many attempts");
		return 0;
	}
	getDateTime(&day, &month, &year, &hours, &mins);
	printf("\nCurrent computer time: %02d/%02d/%d, %02d:%02d\n", day, month, year, hours, mins);
	fprintTOlog("Exit system");
	system("pause");
}
fprintTOlog(char* line) {
	FILE* fp;
	int day, month, year, hours, mins;
	getDateTime(&day, &month, &year, &hours, &mins);
	fopen_s(&fp, LOG_PATH, "a");
	fprintf(fp,"\n%s:->->->->->->->->->->->->",line);
	fprintf(fp," Current computer time: %02d/%02d/%d, %02d:%02d\n", day, month, year, hours, mins);
	fclose(fp);
}
int readUsers(char* path, users_t* theusers, LNode* head, LNode* tail, List* lst)
{
	FILE* fp;
	int level, i = -1, k = 0;
	char temp[100], username[16], password[16], fullname[21];

	fopen_s(&fp, path, "r");
	if (!fp)
	{
		fprintTOlog("User list not found");
		printf("File not found!\n");
		return;
	}

	//header
	fgets(temp, 100, fp);
	puts(temp);

	while (fscanf_s(fp, "%15[^\n] %15[^\n] %1d %20[^\n] ", username, 16, password, 16, &level, fullname, 21) != EOF)
	{

		strcpy(head->usersIndex.username, removespace(username));
		strcpy(head->usersIndex.password, removespace(password));
		head->usersIndex.level = level;
		strcpy(head->usersIndex.fullname, fullname);
		printf_s("%-15s %-15s %-1d %-20s\n", username, password, level, fullname);
		i++;
		addNode(head, i + 1);
		head = head->next;
	}
	lst->tail = head;
	k = deleteLast(lst);
	fclose(fp);
	return (i + 1);
}
int readUserswithoutprint(char* path, users_t* theusers, LNode* head, LNode* tail, List* lst)
{
	FILE* fp;
	int level, i = -1, k = 0;
	char temp[100], username[16], password[16], fullname[21];

	fopen_s(&fp, path, "r");
	if (!fp)
	{
		fprintTOlog("User list not found");
		printf("File not found!\n");
		return;
	}

	//header
	fgets(temp, 100, fp);
	puts(temp);

	while (fscanf_s(fp, "%15[^\n] %15[^\n] %1d %20[^\n] ", username, 16, password, 16, &level, fullname, 21) != EOF)
	{

		strcpy(head->usersIndex.username, removespace(username));
		strcpy(head->usersIndex.password, removespace(password));
		head->usersIndex.level = level;
		strcpy(head->usersIndex.fullname, fullname);
		i++;
		addNode(head, i + 1);
		head = head->next;
	}
	lst->tail = head;
	k = deleteLast(lst);
	fclose(fp);
	return (i + 1);
}

int readItems(char* path, items_t* theitems, LNode* head, LNode* tail, List* lst)
{
	FILE* fp;
	int i = -1, k = 0;
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	int serial = 0;
	char category[17];
	char brand[17];
	char productName[31];
	char instock[11];
	double pricE = 0;
	bool stock = true;
	char temp[100];
	char t = '1';
	fopen_s(&fp, path, "r");
	if (!fp)
	{
		fprintTOlog("Item list not found");
		printf("File not found!\n");
		return;
	}
	//header
	printf("\nList of items\n");
	fgets(temp, 100, fp);
	while (fscanf_s(fp, "%10d %10[^\n] %10[^\n] %30[^\n] %10lf %9[^\n]%02d/%02d/%d, %02d:%02d", &serial, category, 11, brand, 11, productName, 31, &pricE, instock, 10, &day, &month, &year, &hours, &mins) != EOF)
	{
		head->itemsIndex.serial = serial;
		strcpy(head->itemsIndex.category, removespace(category));
		strcpy(head->itemsIndex.brand, removespace(brand));
		strcpy(head->itemsIndex.productName, removespace(productName));
		head->itemsIndex.pricE = pricE;
		strcpy(instock, removespace(instock));
		if (strcmp(instock, "Yes") == 0)
			head->itemsIndex.stock = true;
		else
			head->itemsIndex.stock = false;
		head->itemsIndex.dateIndex.day = day;
		head->itemsIndex.dateIndex.month = month;
		head->itemsIndex.dateIndex.year = year;
		head->itemsIndex.dateIndex.hours = hours;
		head->itemsIndex.dateIndex.mins = mins;
		i++;
		addNode(head, serial);
		head = head->next;
	}
	lst->tail = head;
	k = deleteLast(lst);
	fclose(fp);
	return (i + 1);
}
int fPrintNewuserfile(char* path, users_t* theItems, LNode* head, LNode* tail, int count)
{

	FILE* fp;
	int level, i = -1, k = 0;
	char temp[100], username[16], password[16], fullname[21];

	fopen_s(&fp, path, "w");
	if (!fp)
	{
		fprintTOlog("User list not found");
		printf("File not found!\n");
		return;
	}
	fprintf(fp, "username        password        L fullname            ");
	while (head != NULL)
	{
		level = head->usersIndex.level;
		strcpy(username, head->usersIndex.username);
		strcpy(password, head->usersIndex.password);
		strcpy(fullname, head->usersIndex.fullname);

		fprintf_s(fp, "\n%-15s %-15s %d %-20s", username, password, level, fullname);
		head = head->next;
		i++;
	}
	fclose(fp);
	return (i + 1);
}
void getDateTime(int* day, int* month, int* year, int* hours, int* mins)
{
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	*day = timeinfo.tm_mday;
	*month = timeinfo.tm_mon + 1;
	*year = timeinfo.tm_year + 1900;
	*hours = timeinfo.tm_hour;
	*mins = timeinfo.tm_min;
}
int fPrintNewitemfile(char* path, items_t* theItems, LNode* head, LNode* tail, int count)
{
	printf("\n");
	FILE* fp;
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	int serial = 0;
	char category[17];
	char brand[17];
	char catinput = 'a';
	char productName[31];
	char instock[11];
	double pricE = 0;
	int temp, x = -1, i = -1;
	bool stock = true;
	fopen_s(&fp, path, "w+");
	if (!fp)
	{
		printf("File not found!\n");
		return;
	}
	fprintf(fp, "Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
	printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date\n");
	while (head != NULL)
	{
		serial = head->itemsIndex.serial;
		strcpy(category, head->itemsIndex.category);
		strcpy(brand, head->itemsIndex.brand);
		strcpy(productName, head->itemsIndex.productName);
		pricE = head->itemsIndex.pricE;
		if (head->itemsIndex.stock)
			strcpy(instock, "Yes");
		else
			strcpy(instock, "NO");
		year = head->itemsIndex.dateIndex.year;
		month = head->itemsIndex.dateIndex.month;
		day = head->itemsIndex.dateIndex.day;
		hours = head->itemsIndex.dateIndex.hours;
		mins = head->itemsIndex.dateIndex.mins;

		fprintf_s(fp, "\n%-10d %-10s %-10s %-30s %-10.2lf %-9s %02d/%02d/%d, %02d:%02d", serial, category, brand, productName, pricE, instock, day, month, year, hours, mins);
		printf("%-10d %-10s %-10s %-30s %-10.2lf %-9s %02d/%02d/%d, %02d:%02d\n", serial, category, brand, productName, pricE, instock, day, month, year, hours, mins);
		head = head->next;
		i++;
	}
	fclose(fp);
	return (i + 1);
}
int Short(LNode* head, List* lst)
{
	fprintTOlog("Shorting list");
	LNode* current =head;
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	int tempday = 0, tempmonth = 0, tempyear = 0, temphours = 0, tempmins = 0;
	int serial = 0,tempserial = 0;
	char category[17], tempcategory[17];
	char brand[17], tempbrand[17];
	char productName[31], tempproductName[31];
	char instock[11], tempinstock[11];
	double pricE = 0, temppricE = 0;
	bool stock = true, tempstock = true;
	bool sort=false;
	while (head->next!= NULL)
	{
		current = head;
		while (current->next != NULL)
		{
			if (head->itemsIndex.serial > current->next->itemsIndex.serial)
			{
				tempserial = head->itemsIndex.serial;
				head->itemsIndex.serial = current->next->itemsIndex.serial;
				current->next->itemsIndex.serial = tempserial;

				strcpy(tempcategory, head->itemsIndex.category);
				strcpy(head->itemsIndex.category, current->next->itemsIndex.category);
				strcpy(current->next->itemsIndex.category, tempcategory);

				strcpy(tempbrand, head->itemsIndex.brand);
				strcpy(head->itemsIndex.brand, current->next->itemsIndex.brand);
				strcpy(current->next->itemsIndex.brand, tempbrand);

				strcpy(tempproductName, head->itemsIndex.productName);
				strcpy(head->itemsIndex.productName, current->next->itemsIndex.productName);
				strcpy(current->next->itemsIndex.productName, tempproductName);

				temppricE = head->itemsIndex.pricE;
				head->itemsIndex.pricE = current->next->itemsIndex.pricE;
				current->next->itemsIndex.pricE = temppricE;

				tempstock = head->itemsIndex.stock;
				head->itemsIndex.stock = current->next->itemsIndex.stock;
				current->next->itemsIndex.stock = tempstock;
				//date
				tempday = head->itemsIndex.dateIndex.day;
				head->itemsIndex.dateIndex.day = current->next->itemsIndex.dateIndex.day;
				current->next->itemsIndex.dateIndex.day = tempday;

				tempmonth = head->itemsIndex.dateIndex.month;
				head->itemsIndex.dateIndex.month = current->next->itemsIndex.dateIndex.month;
				current->next->itemsIndex.dateIndex.month = tempmonth;

				tempyear = head->itemsIndex.dateIndex.year;
				head->itemsIndex.dateIndex.year = current->next->itemsIndex.dateIndex.year;
				current->next->itemsIndex.dateIndex.year = tempyear;

				tempmins = head->itemsIndex.dateIndex.mins;
				head->itemsIndex.dateIndex.mins = current->next->itemsIndex.dateIndex.mins;
				current->next->itemsIndex.dateIndex.mins = tempmins;

				temphours = head->itemsIndex.dateIndex.hours;
				head->itemsIndex.dateIndex.hours = current->next->itemsIndex.dateIndex.hours;
				current->next->itemsIndex.dateIndex.hours = temphours;

				sort = true;
			}
			current = current->next;
		}
		head = head->next;
	}
	if (sort)
		return 1;
	return 0;
}
int adddataUser(char* path, users_t* theUsers, LNode* head, LNode* tail, int count)
{
	printf("\n");
	FILE* fp;
	int level;
	char username[16], password[16], fullname[21];

	fopen_s(&fp, path, "a+");
	if (!fp)
	{
		printf("File not found!\n");
		return;
	}
	printf("Enter username Information:\n\n");
	addNode(tail, count);
	head = tail->next;
	printf("Enter Username: ");
	scanf("%s", username);
	strcpy(head->usersIndex.username, removespace(username));

	printf("enter Password: ");
	scanf("%s", password);
	strcpy(head->usersIndex.password, removespace(password));

	printf("Enter permission level:");
	scanf("%d", &level);
	head->usersIndex.level = level;

	printf("Enter Full name:");
	scanf(" %[^\n]s", fullname);
	strcpy(head->usersIndex.fullname, fullname);

	fprintf_s(fp, "\n%-15s %-15s %-1d %-20s", username, password, level, fullname);
	head = head->next;
	count = count + 1;
	fclose(fp);
	return count;
}
int adddataItems(char* path, items_t* theItems, LNode* head, LNode* tail, int count)
{
	printf("\n");
	FILE* fp;
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	int serial = 0;
	char category[17];
	char brand[17];
	char catinput = 'a';
	char productName[31];
	char instock[11];
 	double pricE = 0;
	int temp, x = -1;
	bool stock = true;
	fopen_s(&fp, path, "a+");
	if (!fp)
	{
		printf("File not found!\n");
		return;
	}
	printf("Enter Prodact Information\n");
	addNode(tail, count);
	head = tail->next;
	printf("\nWhich Category?\n1.For Chocolate Press 1\n2.For Drinks Press 2\n3.For Candy Press 3\n4.For New Category Press 4\n");

	scanf(" %c", &catinput);
	switch (catinput)
	{
	case '1':
		strcpy(category, "Chocolate");
		strcpy(head->itemsIndex.category, "Chocolate");
		printf("Enter Serial: ");
		scanf("%d", &serial);
		head->itemsIndex.serial = serial;

		printf("Enter Brand: ");
		scanf("%s", brand);
		strcpy(head->itemsIndex.brand, removespace(brand));

		printf("Enter Prodact Name: ");
		scanf("%s", productName);
		strcpy(head->itemsIndex.productName, removespace(productName));

		printf("Enter Price: ");
		scanf("%lf", &pricE);
		head->itemsIndex.pricE = pricE;

		printf("In stock?\nPress 0 if No\nPress 1 or else if Yes\n");
		scanf(" %d", &temp);
		if (temp == 0)
		{
			strcpy(instock, "No");
			head->itemsIndex.stock = false;
		}
		else
		{
			strcpy(instock, "Yes");
			head->itemsIndex.stock = true;
		}

		getDateTime(&day, &month, &year, &hours, &mins);
		head->itemsIndex.dateIndex.day = day;
		head->itemsIndex.dateIndex.month = month;
		head->itemsIndex.dateIndex.year = year;
		head->itemsIndex.dateIndex.hours = hours;
		head->itemsIndex.dateIndex.mins = mins;
		head->data = serial;
		break;
	case '2':
		strcpy(category, "Drinks");
		strcpy(head->itemsIndex.category, "Drinks");
		printf("Enter Serial: ");
		scanf("%d", &serial);
		head->itemsIndex.serial = serial;

		printf("Enter Brand: ");
		scanf("%s", brand);
		strcpy(head->itemsIndex.brand, removespace(brand));

		printf("Enter Prodact Name: ");
		scanf("%s", productName);
		strcpy(head->itemsIndex.productName, removespace(productName));

		printf("Enter Price: ");
		scanf("%lf", &pricE);
		head->itemsIndex.pricE = pricE;

		printf("In stock?\nPress 0 if No\nPress 1 or else if Yes\n");
		scanf(" %d", &temp);
		if (temp == 0)
		{
			strcpy(instock, "No");
			head->itemsIndex.stock = false;
		}
		else
		{
			strcpy(instock, "Yes");
			head->itemsIndex.stock = true;
		}

		getDateTime(&day, &month, &year, &hours, &mins);
		head->itemsIndex.dateIndex.day = day;
		head->itemsIndex.dateIndex.month = month;
		head->itemsIndex.dateIndex.year = year;
		head->itemsIndex.dateIndex.hours = hours;
		head->itemsIndex.dateIndex.mins = mins;
		head->data = serial;
		break;
	case '3':
		strcpy(category, "Candy");
		strcpy(head->itemsIndex.category, "Candy");
		printf("Enter Serial: ");
		scanf("%d", &serial);
		head->itemsIndex.serial = serial;

		printf("Enter Brand: ");
		scanf("%s", brand);
		strcpy(head->itemsIndex.brand, removespace(brand));

		printf("Enter Prodact Name: ");
		scanf("%s", productName);
		strcpy(head->itemsIndex.productName, removespace(productName));

		printf("Enter Price: ");
		scanf("%lf", &pricE);
		head->itemsIndex.pricE = pricE;

		printf("In stock?\nPress 0 if No\nPress 1 or else if Yes\n");
		scanf(" %d", &temp);
		if (temp == 0)
		{
			strcpy(instock, "No");
			head->itemsIndex.stock = false;
		}
		else
		{
			strcpy(instock, "Yes");
			head->itemsIndex.stock = true;
		}

		getDateTime(&day, &month, &year, &hours, &mins);
		head->itemsIndex.dateIndex.day = day;
		head->itemsIndex.dateIndex.month = month;
		head->itemsIndex.dateIndex.year = year;
		head->itemsIndex.dateIndex.hours = hours;
		head->itemsIndex.dateIndex.mins = mins;
		head->data = serial;
		break;
	case '4':
		printf("Type New Category");
		scanf("%s", category);
		strcpy(head->itemsIndex.category, category);

		printf("Enter Serial: ");
		scanf("%d", &serial);
		head->itemsIndex.serial = serial;

		printf("Enter Brand: ");
		scanf("%s", brand);
		strcpy(head->itemsIndex.brand, removespace(brand));

		printf("Enter Prodact Name: ");
		scanf("%s", productName);
		strcpy(head->itemsIndex.productName, removespace(productName));

		printf("Enter Price: ");
		scanf("%lf", &pricE);
		head->itemsIndex.pricE = pricE;

		printf("In stock?\nPress 0 if No\nPress 1 or else if Yes\n");
		scanf(" %d", &temp);
		if (temp == 0)
		{
			strcpy(instock, "No");
			head->itemsIndex.stock = false;
		}
		else
		{
			strcpy(instock, "Yes");
			head->itemsIndex.stock = true;
		}

		getDateTime(&day, &month, &year, &hours, &mins);
		head->itemsIndex.dateIndex.day = day;
		head->itemsIndex.dateIndex.month = month;
		head->itemsIndex.dateIndex.year = year;
		head->itemsIndex.dateIndex.hours = hours;
		head->itemsIndex.dateIndex.mins = mins;
		head->data = serial;
		break;
	default:
		break;
	}
	fprintf(fp, "\n%-10d %-10s %-10s %-30s %-10.2lf %-9s %02d/%02d/%d, %02d:%02d", serial, category, brand, productName, pricE, instock, day, month, year, hours, mins);
	head = head->next;
	count = count + 1;
	fclose(fp);
	return count;
}
void searchByBorC(LNode* head, List* lst, int level)
{
	printf("\n");
	LNode* current = lst->head;
	int serial;
	int* arr;
	char string[100], string2[100];
	char aj[1000], mj[1000];
	char operator;
	int x = 0;
	int i = 0, j = 0, len = 0;
	char k;
	bool both = false;
	bool edit = false;
	arr = (int*)malloc(sizeof(int) * MAXsearch);
	printf("search by Brand name: press 1\n");
	printf("search by Prodact name: press 2\n");
	printf("search by Brand and Prodact name: press 3\n");
	printf("For Exit Press 9\n");
	scanf(" %c", &operator);
	do {
		if (operator=='9')
			x = 0;
		switch (operator)
		{
		case '1':
			printf("Enter Brand name for search: \n");
			scanf("%s", &string);
			while (head != NULL)
			{
				strcpy(aj, head->itemsIndex.brand);
				len = strlen(string);   // len stores the length of the input string
				if (_strnicmp(string, aj, len) == 0)
				{
					arr[i] = head->itemsIndex.serial;
					Printitem(head);
					i++;
				}
				head = head->next;
			}
			if (i == 0){
				printf("Nothing Found!");
				break;
				}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;

		case '2':
			printf("Enter Prodact name for search: \n");
			scanf("%s", &string);
			while (head != NULL)
			{
				strcpy(aj, head->itemsIndex.productName);
				len = strlen(string);   // len stores the length of the input string
				if (_strnicmp(string, aj, len) == 0)
				{
					Printitem(head);
					arr[i] = head->itemsIndex.serial;
					i++;
				}
				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;
		case '3':
			printf("Enter Brand name for search: ");
			scanf(" %s", &string);
			printf("Enter Prodact name for search: \n");
			scanf(" %s", &string2);
			while (head != NULL)
			{
				both = false;
				strcpy(aj, head->itemsIndex.brand);
				len = strlen(string);   // len stores the length of the input string
				if (_strnicmp(string, aj, len) == 0)
				{
					both = true;
				}
				strcpy(aj, head->itemsIndex.productName);
				len = strlen(string2);   // len stores the length of the input string
				if (_strnicmp(string2, aj, len) == 0)
				{
					both = true;
				}
				if (both)
				{
					Printitem(head);
					arr[i] = head->itemsIndex.serial;
					i++;
				}
				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;
		case '9':
			x = 0;
			break;
		default:
			printf("Worng Value Enterd choose the currect number from the menu\nFor Exit Press 9");
			scanf(" %c", &operator);
			if (operator=='9')
				x = 0;
			break;
		}
	} while (x != 0);
	free(arr);
}
void searchByValue(LNode* head, List* lst, int level)
{
	printf("\n");
	LNode* current = lst->head;
	int serial;
	int* arr;
	char string[100], string2[100];
	char aj[1000], mj[1000];
	char operator;
	int x = 0;
	int i = 0, j = 0, len = 0;
	char k;
	int price = 0;
	bool both = false;
	arr = (int*)malloc(sizeof(int) * MAXsearch);
	printf("search Items by MAX Value Price: Press 1\n");
	printf("search Items by MIN Value Price: Press 2\n");
	printf("For Exit Press 9\n");
	scanf(" %c", &operator);
	do {
		if (operator=='9')
			x = 0;
		switch (operator)
		{
		case '1':
			printf("Enter MAX value Price for search: ");
			scanf("%d", &price);
			while (head != NULL)
			{
				if (head->itemsIndex.pricE <= price)
				{
					arr[i] = head->itemsIndex.serial;
					Printitem(head);
					i++;
				}
				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;
		case '2':

			printf("Enter MIN value Price for search: ");
			scanf("%d", &price);
			while (head != NULL)
			{
				if (head->itemsIndex.pricE >= price)
				{
					Printitem(head);
					arr[i] = head->itemsIndex.serial;
					i++;
				}
				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;
		case '9':
			x = 0;
			break;
		default:
			printf("Worng Value Enterd choose the currect number from the menu\nFor Exit Press 9");
			scanf(" %c", &operator);
			if (operator=='9')
				x = 0;
			break;
		}
	} while (x != 0);
	free(arr);
}
void searchByStock(LNode* head, List* lst, int level)
{
	printf("\n");
	LNode* current = lst->head;
	int serial;
	int* arr;
	char string[100], string2[100];
	char aj[1000], mj[1000];
	char operator;
	int x = 0;
	int i = 0, j = 0, len = 0;
	char k;
	int price;
	bool both = false;
	arr = (int*)malloc(sizeof(int) * MAXsearch);
	printf("1.search Items that IN Stock: Press 1\n");
	printf("2.search Items that OUT Stock: Press 2\n");
	printf("3.For Exit Press 9\n");
	scanf(" %c", &operator);
	do {
		if (operator=='9')
			x = 0;
		switch (operator)
		{
		case '1':
			while (head != NULL)
			{
				if (head->itemsIndex.stock)
				{
					arr[i] = head->itemsIndex.serial;
					Printitem(head);
					i++;
				}
				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;
		case '2':
			while (head != NULL)
			{
				if (!head->itemsIndex.stock)
				{
					arr[i] = head->itemsIndex.serial;
					Printitem(head);
					i++;
				}
				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;
		case '9':
			x = 0;
			break;
		default:
			printf("Worng Value Enterd choose the currect number from the menu\nFor Exit Press 9");
			scanf(" %c", &operator);
			if (operator=='9')
				x = 0;
			break;
		}
	} while (x != 0);
	free(arr);
}
void searchByDate(LNode* head, List* lst, int level)
{
	printf("\n");
	LNode* current = lst->head;
	int serial;
	int* arr;
	char string[100], string2[100];
	char aj[1000], mj[1000];
	char operator;
	int x = 0;
	int i = 0, j = 0, len = 0;
	char k;
	int price;
	bool time = false;
	bool HourMin = false;
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	arr = (int*)malloc(sizeof(int) * MAXsearch);
	printf("Search Items Before the Date : Press 1\n");
	printf("Search Items After the Date : Press 2\n");
	printf("For Exit Press 9\n");
	scanf(" %c", &operator);
	do {
		if (operator=='9')
			x = 0;
		switch (operator)
		{
		case '1':
			printf("Enter Year\n");
			scanf("%d", &year);
			printf("Enter Month\n");
			scanf("%d", &month);
			printf("Enter day\n");
			scanf("%d", &day);
			printf("You want Also by Hours and Minutes?\nIf YES Press Y(or any key)\nNO? press N\n");
			scanf(" %c", &operator);
			if (operator!='N')
			{
				HourMin = true;
				printf("Print Enter Hours\n");
				scanf("%d", &hours);
				printf("Print Enter Minutes\n");
				scanf("%d", &mins);
			}
			while (head != NULL)
			{
				if (head->itemsIndex.dateIndex.year <= year)
					if (head->itemsIndex.dateIndex.month <= month)
						if (head->itemsIndex.dateIndex.day <= day)
							if (!HourMin)
							{
								arr[i] = head->itemsIndex.serial;
								Printitem(head);
								i++;
							}
							else
								if (head->itemsIndex.dateIndex.hours <= hours)
									if (head->itemsIndex.dateIndex.mins <= mins)
									{
										arr[i] = head->itemsIndex.serial;
										Printitem(head);
										i++;
									}

				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;

		case '2':
			printf("Enter Year\n");
			scanf("%d", &year);
			printf("Enter Month\n");
			scanf("%d", &month);
			printf("Enter day\n");
			scanf("%d", &day);
			printf("You want Also by Hours and Minutes?\nIf YES Press Y(or any key)\nNO? press N\n ");
			scanf(" %c", &operator);
			if (operator!='N')
			{
				HourMin = true;
				printf("Print Enter Hours\n");
				scanf("%d", &hours);
				printf("Print Enter Minutes\n");
				scanf("%d", &mins);
			}
			while (head != NULL)
			{
				if (head->itemsIndex.dateIndex.year >= year)
					if (head->itemsIndex.dateIndex.month >= month)
						if (head->itemsIndex.dateIndex.day >= day)
							if (!HourMin)
							{
								arr[i] = head->itemsIndex.serial;
								Printitem(head);
								i++;
							}
							else
								if (head->itemsIndex.dateIndex.hours >= hours)
									if (head->itemsIndex.dateIndex.mins >= mins)
									{
										arr[i] = head->itemsIndex.serial;
										Printitem(head);
										i++;
									}

				head = head->next;
			}
			if (i == 0) {
				printf("Nothing Found!");
				break;
			}
			if (level != 1)
			{
				printf("\nDo You want to edit the items?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
				scanf(" %c", &operator);
				if (operator!='N')
				{
					i = 0;
					do {
						current = lst->head;
						printf("Enter Item serial number\n");
						scanf("%d", &serial);
						while (current != NULL)
						{
							if (serial == current->itemsIndex.serial)
							{
								printf("\nWhat do you want to change in this item?\n");
								printf("Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
								Printitem(current);
								printf("\n\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n7.Back to previous menu\n");
								scanf(" %c", &k);
								if (k == '7')
									continue;
								edititem(current, k);
								i++;
							}
							current = current->next;
						}
						if (i == 0)
							printf("Wrong serial Number enterd!\n");
						printf("Edit another product?\n1.Press Y(or any key) if Yes\n2.Press N if no\n");
						scanf(" %c", &operator);
					} while (operator!='N');

				}
			}
			break;
		default:
			printf("Worng Value Enterd choose the currect number from the menu\nFor Exit Press 9");
			scanf(" %c", &operator);
			if (operator=='9')
				x = 0;
			break;
		}
	} while (x != 0);
	free(arr);
}
void fprintitem(char path, LNode* head)
{
	char instock='a';
	FILE* fp = fopen(path, "a");
	if (head->itemsIndex.stock)
		strcpy(instock, "Yes");
	else
		strcpy(instock, "NO");
	fprintf(fp, "\n%-10d %-10s %-10s %-30s %-10.2lf %-9s %02d/%02d/%d, %02d:%02d", head->itemsIndex.serial, head->itemsIndex.category, head->itemsIndex.brand, head->itemsIndex.productName, head->itemsIndex.pricE, instock, head->itemsIndex.dateIndex.day, head->itemsIndex.dateIndex.month, head->itemsIndex.dateIndex.year, head->itemsIndex.dateIndex.hours, head->itemsIndex.dateIndex.mins);
	fclose(fp);
}
void edititem(LNode* head, char operator)
{
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	int serial = 0;
	char category[17];
	char brand[17];
	char catinput = 'a';
	char productName[31];
	char instock[11];
	double pricE = 0;
	int x = -1;
	char temp;
	bool stock = true;

	do {
		switch (operator)
		{
		case '1':
			printf("Type Category\n");
			scanf("%s", category);
			strcpy(head->itemsIndex.category, category);
			break;
		case '2':
			printf("Enter Brand: \n");
			scanf("%s", brand);
			strcpy(head->itemsIndex.brand, removespace(brand));
			break;
		case '3':
			printf("Enter Prodact Name: \n");
			scanf("%s", productName);
			strcpy(head->itemsIndex.productName, removespace(productName));
			break;
		case '4':
			printf("Enter Price: \n");
			scanf("%lf", &pricE);
			head->itemsIndex.pricE = pricE;
			break;
		case '5':
			printf("In stock?\n1.Press Y(or any key) if In stock\n2.Press N if Out stock\n");
			scanf(" %c", &temp);
			if (temp == 'N')
			{
				strcpy(instock, "No");
				head->itemsIndex.stock = false;
			}
			else
			{
				strcpy(instock, "Yes");
				head->itemsIndex.stock = true;
			}
			break;
		case '6':
			printf("Enter Year\n");
			scanf("%d", &year);
			head->itemsIndex.dateIndex.year = year;
			printf("Enter Month\n");
			scanf("%d", &month);
			head->itemsIndex.dateIndex.month = month;
			printf("Enter Day\n");
			scanf("%d", &day);
			head->itemsIndex.dateIndex.day = day;
			printf("Enter Hours\n");
			scanf("%d", &hours);
			head->itemsIndex.dateIndex.hours = hours;
			printf("Enter Min\n");
			scanf("%d", &mins);
			head->itemsIndex.dateIndex.mins = mins;
			break;
		default:
			printf("Worng Value Enterd choose the currect number from the menu\n");
			printf("What do you want to change?\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n");
			printf("For Exit Press 9\n");
			scanf(" %c", &operator);
			if (operator=='9')
				x = 0;
			break;
		}
		printf("Want to Edit More? Press Y or any key to exit\n");
		scanf(" %c", &operator);
		if (operator=='Y')
		{
			x = -1;
			printf("What do you want to change more?\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n");
			scanf(" %c", &operator);
		}
		else
			x = 0;
	} while (x != 0);
}
void editSingelitem(LNode* head, int serial)
{
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	char category[17];
	char brand[17];
	char catinput = 'a';
	char productName[31];
	char instock[11];
	double pricE = 0;
	int x = -1;
	char temp;
	char operator;
	bool stock = true;
	while (head != NULL)
	{
		if(head->itemsIndex.serial == serial)
		break;
		head = head->next;
	}

	printf("Worng Value Enterd choose the currect number from the menu\n");
	printf("What do you want to change?\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n");
	printf("For Exit Press 9\n");
	scanf(" %c", &operator);
	do {
		switch (operator)
		{
		case '1':
			printf("Type Category\n");
			scanf("%s", category);
			strcpy(head->itemsIndex.category, category);
			break;
		case '2':
			printf("Enter Brand: \n");
			scanf("%s", brand);
			strcpy(head->itemsIndex.brand, removespace(brand));
			break;
		case '3':
			printf("Enter Prodact Name: \n");
			scanf("%s", productName);
			strcpy(head->itemsIndex.productName, removespace(productName));
			break;
		case '4':
			printf("Enter Price: \n");
			scanf("%lf", &pricE);
			head->itemsIndex.pricE = pricE;
			break;
		case '5':
			printf("In stock?\n1.Press Y(or any key) if In stock\n2.Press N if Out stock\n");
			scanf(" %c", &temp);
			if (temp == 'N')
			{
				strcpy(instock, "No");
				head->itemsIndex.stock = false;
			}
			else
			{
				strcpy(instock, "Yes");
				head->itemsIndex.stock = true;
			}
			break;
		case '6':
			printf("Enter Year\n");
			scanf("%d", &year);
			head->itemsIndex.dateIndex.year = year;
			printf("Enter Month\n");
			scanf("%d", &month);
			head->itemsIndex.dateIndex.month = month;
			printf("Enter Day\n");
			scanf("%d", &day);
			head->itemsIndex.dateIndex.day = day;
			printf("Enter Hours\n");
			scanf("%d", &hours);
			head->itemsIndex.dateIndex.hours = hours;
			printf("Enter Min\n");
			scanf("%d", &mins);
			head->itemsIndex.dateIndex.mins = mins;
			break;
		default:
			printf("Worng Value Enterd choose the currect number from the menu\n");
			printf("What do you want to change?\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n");
			printf("For Exit Press 9\n");
			scanf(" %c", &operator);
			if (operator=='9')
				x = 0;
			break;
		}
		printf("Want to Edit More? Press Y or any key to exit\n");
		scanf(" %c", &operator);
		if (operator=='Y')
		{
			x = -1;
			printf("What do you want to change more?\nPress number from menu\n1.Category\n2.Brand\n3.Prodact Name\n4.Price\n5.In Stock\n6.Date\n");
			scanf(" %c", &operator);
		}
		else
			x = 0;
	} while (x != 0);
}
void editSingleuser(LNode* head, char* username)
{
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	int level;
	char temp[100];
	char newusername[16];
	char password[16];
	char fullname[21];
	int x = -1;
	char operator;
	bool stock = true;
	while (head != NULL)
	{
		if (_strcmpi(head->usersIndex.username,username)==0)
		break;
		head = head->next;
	}

	printf("\nWhat do you want to change?\n\nPress number from menu\n1.Username\n2.Password\n3.level\n4.Full name\n");
	printf("For Exit Press 9\n");
	scanf(" %c", &operator);
	do {
		switch (operator)
		{
		case '1':
			printf("Type username\n");
			scanf("%s", newusername);
			strcpy(head->usersIndex.username, newusername);
			break;
		case '2':
			printf("Enter password: \n");
			scanf("%s", password);
			strcpy(head->usersIndex.password, removespace(password));
			break;
		case '3':
			printf("Enter level: \n");
			scanf("%d", &level);
			head->usersIndex.level = level;
			break;
		case '4':
			printf("Enter Full name: \n");
			scanf("%s", fullname);
			strcpy(head->usersIndex.fullname,fullname);
			break;
		default:
			printf("Worng Value Enterd choose the currect number from the menu\n");
			printf("What do you want to change?\nPress number from menu\n1.Username\n2.Password\n3.level\n4.Full name\n");
			printf("For Exit Press 9\n");
			scanf(" %c", &operator);
			if (operator=='9')
				x = 0;
			break;
		}
		printf("Want to Edit More? Press Y or any key to exit\n");
		scanf(" %c", &operator);
		if (operator=='Y')
		{
			x = -1;
			printf("What do you want to change?\nPress number from menu\n1.Username\n2.Password\n3.level\n4.Full name\n");
			scanf(" %c", &operator);
		}
		else
			x = 0;
	} while (x != 0);
}
void initList(List* lst)
{
	lst->head = lst->tail = NULL;
}
int deleteLast(List* lst)
{
	//if list is empty there is nothing to delete
	if (!isEmpty(lst))
	{
		//save reference to last link
		LNode* temp = lst->tail;

		//if only one link
		if (temp->prev == NULL)
		{
			initList(lst);
		}
		else
		{
			lst->tail->prev->next = NULL;
			lst->tail = lst->tail->prev;
		}
		free(temp);
		return 1;
	}
	return 0;
}
void Printitem(LNode* head)
{
	char instock[11];
	if (head->itemsIndex.stock)
		strcpy(instock, "Yes");
	else
		strcpy(instock, "No");
	printf("\n%-10d %-10s %-10s %-30s %-10.2lf %-9s %02d/%02d/%d, %02d:%02d", head->itemsIndex.serial, head->itemsIndex.category, head->itemsIndex.brand, head->itemsIndex.productName, head->itemsIndex.pricE, instock, head->itemsIndex.dateIndex.day, head->itemsIndex.dateIndex.month, head->itemsIndex.dateIndex.year, head->itemsIndex.dateIndex.hours, head->itemsIndex.dateIndex.mins);
}
int moveforward(LNode* current, LNode* head, LNode* tail)
{
	if (current == tail)
		return head;
	else
		current = current->next;
	return current;
}
int movebackward(LNode* current, LNode* head, LNode* tail)
{
	if (current == head)
		return tail;
	else
		current = current->prev;
	return current;
}
char* removespace(char txt[])
{
	char aj[100], mj[100], temp[1001], temp2[100];
	int n, m, len;
	n = 0, m = 0;
	strcpy(aj, txt);
	len = strlen(aj);   // len stores the length of the input string
	while (aj[n] != '\0')    // till string doesn't terminate
	{
		if (aj[n] != ' ') {
			mj[m++] = aj[n];
		}
		else {
			break;
		}
		n++;
	}
	mj[m] = '\0';
	strcpy(temp, mj);
	return temp;
}
LNode* createNode()
{
	LNode* temp; // declare a node
	temp = (LNode*)malloc(sizeof(LNode)); // allocate memory using malloc()
	temp->next = NULL;// make next point to NULL
	return temp;//return the new node
}
LNode* removeNode()
{
	LNode* temp; // declare a node
	temp = (LNode*)malloc(sizeof(LNode)); // allocate memory using malloc()
	temp->prev = NULL;// make next point to NULL
	return temp;//return the new node
}
LNode* addNode(LNode* head, int value)
{
	LNode* temp, * p;// declare two nodes temp and p
	temp = createNode();//createNode will return a new node with data = value and next pointing to NULL.
	temp->data = value; // add element's value to data part of node
	if (head == NULL)
	{
		head = temp; //when linked list is empty
	}
	else
	{
		p = head;//assign head to p
		while (p->next != NULL)
		{
			p = p->next;//traverse the list until p is the last node.The last node always points to NULL.
		}
		temp->prev = p;
		p->next = temp;//Point the previous last node to the new node created.

	}
	return head;
}
LNode* getLinkByIndex(List* lst, int idx)
{
	int i;
	//start from the first link
	LNode* link = lst->head;

	//navigate through list
	for (i = 0; i < idx && link != NULL; i++)
		link = link->next;

	return link;
}
List makeEmptyList()
{
	List lst;
	lst.head = lst.tail = NULL;
	return lst;
}
int getlistLength(const List* lst)
{
	int count = 0;
	LNode* temp = lst->head;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
void freeList(List* thelist)
{
	LNode* current = thelist->head;
	LNode* next;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	thelist->head = NULL;
}
void printCharList(const List* lst)
{
	LNode* temp = lst->head;
	while (temp != NULL)
	{
		printf("%c", temp->data);
		temp = temp->next;
	}
}
int isEmpty(const List* lst)
{
	return lst->head == NULL;
}
void insertNodeToTail(List* lst, LNode* newNode)
{
	if (isEmpty(lst))
		lst->head = lst->tail = newNode;
	else
	{
		lst->tail->next = newNode;
		lst->tail = newNode;
	}
}
int fPrintitemRemove(char* path, items_t* theItems, LNode* head, LNode* tail, int count,int inputserial)
{
	printf("\n");
	FILE* fp;
	int day = 0, month = 0, year = 0, hours = 0, mins = 0;
	int serial;
	char category[17];
	char brand[17];
	char catinput = 'a';
	char productName[31];
	char instock[11];
	double pricE = 0;
	int temp, x = -1, i = -1;
	bool stock = true;
	fopen_s(&fp, path, "w+");
	if (!fp)
	{
		printf("File not found!\n");
		return;
	}
	fprintf(fp, "Serial     Category   Brand      Prodact Name                   Price      In Stock  Date");
	while (head != NULL)
	{
		if (head->itemsIndex.serial == inputserial) {
			head = head->next;
			continue;
		}
		serial = head->itemsIndex.serial;
		strcpy(category, head->itemsIndex.category);
		strcpy(brand, head->itemsIndex.brand);
		strcpy(productName, head->itemsIndex.productName);
		pricE = head->itemsIndex.pricE;
		if (head->itemsIndex.stock)
			strcpy(instock, "Yes");
		else
			strcpy(instock, "NO");
		year = head->itemsIndex.dateIndex.year;
		month = head->itemsIndex.dateIndex.month;
		day = head->itemsIndex.dateIndex.day;
		hours = head->itemsIndex.dateIndex.hours;
		mins = head->itemsIndex.dateIndex.mins;

		fprintf(fp, "\n%-10d %-10s %-10s %-30s %-10.2lf %-9s %02d/%02d/%d, %02d:%02d", serial, category, brand, productName, pricE, instock, day, month, year, hours, mins);
		head = head->next;
		i++;
	}
	fclose(fp);
	return (i + 1);
}
int fPrintuserRemove(char* path, users_t* theItems, LNode* head, LNode* tail, int count,char* inputusername)
{

	FILE* fp;
	int level, i = -1, k = 0;
	char temp[100], username[16], password[16], fullname[21];

	fopen_s(&fp, path, "w");
	if (!fp)
	{
		printf("File not found!\n");
		return;
	}
	fprintf(fp, "username        password        L fullname            ");
	while (head != NULL)
	{
		if (_strcmpi(head->usersIndex.username,inputusername)==0) {
			head = head->next;
			continue;
		}
		level = head->usersIndex.level;
		strcpy(username, head->usersIndex.username);
		strcpy(password, head->usersIndex.password);
		strcpy(fullname, head->usersIndex.fullname);

		fprintf_s(fp, "\n%-15s %-15s %-1d %-20s", username, password, level, fullname);
		head = head->next;
		i++;
	}
	fclose(fp);
	return (i + 1);
}
