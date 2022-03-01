#define _CRT_SECURE_NO_DEPRECATE
/*
Assigned by:
Ron ben david
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
typedef struct songs_t
{
	int id;
	int trackNo;
	char artistName[31];
	char albumName[31];
	char trackName[31];
}songs_t;
typedef const songs_t* type;
typedef struct LNode
{
	int data;
	songs_t songsindex;
	struct LNode* next;
	struct LNode* prev;
}LNode;

typedef struct List
{
	LNode* head;
	LNode* tail;
}List;
List copyList(const List* lst);
List makeEmptyList();
LNode* getLinkByIndex(List* lst, int idx);
LNode* createNewNode(type newData, LNode* next);
LNode* findData(List lst, type data);
int getlistLength(const List* lst);
void printList(const List* lst, int i);
void freeList(List* thelist);
int isEmpty(const List* lst);
void insertValueToHead(List* lst, type newData);
void insertValueToTail(List* lst, type newData);
void insertAfterValue(List* lst, type insertAfter, type newValue);
int insertAfter(List* lst, LNode* item, LNode* link);
int insertBefore(List* lst, LNode* item, LNode* link);
int insertFirst(List* lst, LNode* item);
void Qtwo(List* lst, int k, int length);
void Qtree(const List* lst);
void removeAll(List* lst, type toremove);
void printCharList(const List* lst);
void menu();
int importData(char* path, songs_t* thePlaylist, LNode* head, LNode* tail, List* lst);
int createplaylist(char* path, songs_t* thePlaylist);
LNode* addNode(LNode* head, int value);
void playsong(LNode* head);
int moveforward(LNode* current, LNode* head, LNode* tail);
int movebackward(LNode* current, LNode* head, LNode* tail);
void search(LNode* head, LNode* tail);
int deletedata(char* path, songs_t* thePlaylist, LNode* head, LNode* tail, int count);
int adddata(char* path, songs_t* thePlaylist, LNode* head, LNode* tail, int count);
void sortby(List* lst, char* path, int count, LNode* head);
void fprintsong(char path, LNode* head);
void sortList(LNode* head);
void removedata(List* lst, int toremove, LNode* head);
char* removespace(char txt[]);
int deleteLast(List* lst);
void bsort(List* lst);
void initList(List* lst);
struct LNode* swap(struct LNode* ptr1, struct LNode* ptr2);
int bubbleSortArtist(char* path, LNode** head, int count, List* lst);
int bubbleSortAlbum(char* path, LNode** head, int count, List* lst);
int bubbleSortTrack(char* path, LNode** head, int count, List* lst);
void main()
{
	int count = 0, k = 0, x = 0, err = -1;
	char  operator;
	LNode* current;
	LNode* newNode = &current;
	LNode* newNode2;
	LNode* head;
	LNode* tail;
	newNode = (LNode*)calloc(1, sizeof(LNode));
	List lst = makeEmptyList();
	lst.head = newNode;
	newNode2 = (LNode*)calloc(1, sizeof(LNode));
	lst.tail = newNode;
	songs_t playlist;
	count = importData("playlist.txt", &playlist, lst.head, lst.tail, &lst);
	current = lst.head;
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	do {
		printf("Play :press 1\n");fprintf(flog, "Play :press 1\n");
		printf("Previous Song : Press 2\n"); fprintf(flog, "Previous Song : Press 2\n");
		printf("Next Song : Press 3\n"); fprintf(flog, "Next Song : Press 3\n");
		printf("Search : Press 4\n"); fprintf(flog, "Search : Press 4\n");
		printf("Delete : Press 5\n"); fprintf(flog, "Delete : Press 5\n");
		printf("Add Song : Press 6\n"); fprintf(flog, "Add Song : Press 6\n");
		printf("Sort Playlist by : \n Artist Press 7\nAlbum Press 8\nSong Press 9\n"); fprintf(flog, "Sort Playlist by : \n Artist Press 7\nAlbum Press 8\nSong Press 9\n");
		printf("For Exit Press 0\n"); fprintf(flog, "For Exit Press 0\n");
		scanf(" %c", &operator);
		switch (operator)
		{
		case '1':
			playsong(current);
			printf("\n"); fprintf(flog, "\n");
			break;
		case '2':
			current = movebackward(current, lst.head, lst.tail);
			printf("\n"); fprintf(flog, "\n");
			break;
		case '3':
			current = moveforward(current, lst.head, lst.tail);
			break;
		case '4':
			search(lst.head, lst.tail);
			printf("\n"); fprintf(flog, "\n");
			break;
		case '5':
			count = deletedata("playlist.txt", &playlist, lst.head, lst.tail, count);
			break;
		case '6':
			count = adddata("playlist.txt", &playlist, lst.head, lst.tail, count);
			count = importData("playlist.txt", &playlist, lst.head, lst.tail, &lst);
			break;
		case '7':
			bubbleSortArtist("playlist.txt", &lst.head, count - 1, &lst);
			printf("\n"); fprintf(flog, "\n");
			break;
		case '8':
			bubbleSortAlbum("playlist.txt", &lst.head, count - 1, &lst);
			printf("\n"); fprintf(flog, "\n");
			break;
		case '9':
			bubbleSortTrack("playlist.txt", &lst.head, count - 1, &lst);
			printf("\n"); fprintf(flog, "\n");
			break;
		default:
		case '0':
			err = 0;
			break;
		}
	} while (err != 0);
	fclose(flog);
	freeList(&lst);

}
struct LNode* swap(struct LNode* ptr1, struct LNode* ptr2)
{
	LNode* tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return ptr2;
}

/* Function to sort the list */
int bubbleSortArtist(char* path, LNode** head, int count, List* lst)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	LNode** h;
	int i, j, swapped;
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i; j++) {

			LNode* p1 = *h;
			LNode* p2 = p1->next;
			if (p2 == NULL)
				continue;
			if (_strcmpi(p1->songsindex.artistName, p2->songsindex.artistName) > 0) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
	FILE* fp = fopen(path, "r");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog, "File not found!\n");
		return 0;
	}
	fscanf(fp, "%5s%30s%30s%10s%30s", h1, h2, h3, h4, h5);
	fclose(fp);
	fp = fopen(path, "w+");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog, "File not found!\n");
		return 0;
	}
	fprintf(fp, "%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5); fprintf(flog, "%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	printf("%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	fclose(fp);
	for (i = 0; i <= count; i++)
	{
		fprintsong("playlist.txt", getLinkByIndex(&lst->head, i));
		playsong(getLinkByIndex(&lst->head, i));
	}
	fclose(flog);
}
int bubbleSortAlbum(char* path, LNode** head, int count, List* lst)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	LNode** h;
	int i, j, swapped;
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i; j++) {

			LNode* p1 = *h;
			LNode* p2 = p1->next;
			if (p2 == NULL)
				continue;
			if (_strcmpi(p1->songsindex.albumName, p2->songsindex.albumName) > 0) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
	FILE* fp = fopen(path, "r");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog, "File not found!\n");
		return 0;
	}
	fscanf(fp, "%5s%30s%30s%10s%30s", h1, h2, h3, h4, h5);
	fclose(fp);
	fp = fopen(path, "w+");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog, "File not found!\n");
		return 0;
	}
	fprintf(fp, "%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5); fprintf(fp, "%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	printf("%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	fclose(fp);
	for (i = 0; i <= count; i++)
	{
		fprintsong("playlist.txt", getLinkByIndex(&lst->head, i));
		playsong(getLinkByIndex(&lst->head, i));
	}
	fclose(flog);
}
int bubbleSortTrack(char* path, LNode** head, int count, List* lst)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	LNode** h;
	int i, j, swapped;
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i; j++) {

			LNode* p1 = *h;
			LNode* p2 = p1->next;
			if (p2 == NULL)
				continue;
			if (_strcmpi(p1->songsindex.trackName, p2->songsindex.trackName) > 0) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
	FILE* fp = fopen(path, "r");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog, "File not found!\n");
		return 0;
	}
	fscanf(fp, "%5s%30s%30s%10s%30s", h1, h2, h3, h4, h5);
	fclose(fp);
	fp = fopen(path, "w+");
	if (!fp)
	{
		printf("File not found!\n");
		return 0;
	}
	fprintf(fp, "%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5); fprintf(fp, "%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	printf("%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	fclose(fp);
	for (i = 0; i <= count; i++)
	{
		fprintsong("playlist.txt", getLinkByIndex(&lst->head, i));
		playsong(getLinkByIndex(&lst->head, i));
	}
	fclose(flog);
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
void playsong(LNode* head)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	printf("%5d %30s %30s %10d %30s \n", head->songsindex.id, head->songsindex.artistName, head->songsindex.albumName, head->songsindex.trackNo, head->songsindex.trackName);
	fprintf(flog,"%5d %30s %30s %10d %30s \n", head->songsindex.id, head->songsindex.artistName, head->songsindex.albumName, head->songsindex.trackNo, head->songsindex.trackName);
	fclose(flog);
}
void fprintsong(char* path, LNode* head)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	FILE* fp = fopen(path, "a");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog,"File not found!\n");
		return 0;
	}
	fprintf(fp, "%5d %30s %30s %10d %30s \n", head->songsindex.id, head->songsindex.artistName, head->songsindex.albumName, head->songsindex.trackNo, head->songsindex.trackName);
	fclose(fp,flog);
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
void search(LNode* head, LNode* tail)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	char string[100];
	char aj[1000], mj[1000];
	char operator;
	int x = 0;
	int i, j, len;
	printf("search by artist name: press 1\n"); fprintf(flog,"search by artist name: press 1\n");
	printf("search by track name: press 2\n"); fprintf(flog,"search by track name: press 2\n");
	printf("search by album name: press 3\n"); fprintf(flog,"search by album name: press 3\n");
	scanf(" %c", &operator);
	do {
		switch (operator)
		{
		case '1':
			printf("Enter artist name for search: "); fprintf(flog,"Enter artist name for search: ");
			scanf("%s", &string);
			while (head != NULL)
			{
				i = 0, j = 0;
				strcpy(aj, head->songsindex.artistName);
				len = strlen(aj);   // len stores the length of the input string
				while (aj[i] != '\0')    // till string doesn't terminate
				{
					if (aj[i] != ' ')  // if the char is not a white space
					{
						mj[j++] = aj[i];
					}

					i++;
				}
				mj[j] = '\0';
				if (_strcmpi(mj, string) == 0)
					playsong(head);
				head = head->next;
			}
			break;

		case '2':
			printf("Enter track name for search: "); fprintf(flog,"Enter track name for search: ");
			scanf("%s", &string);
			while (head != NULL)
			{
				i = 0, j = 0;
				strcpy(aj, head->songsindex.trackName);
				len = strlen(aj);   // len stores the length of the input string
				while (aj[i] != '\0')    // till string doesn't terminate
				{
					if (aj[i] != ' ')  // if the char is not a white space
					{

						mj[j++] = aj[i];
					}

					i++;
				}
				mj[j] = '\0';
				if (_strcmpi(mj, string) == 0)
					playsong(head);
				head = head->next;
			}
			break;

		case '3':
			printf("Enter album name for search: "); fprintf(flog,"Enter album name for search: ");
			scanf("%s", &string);
			while (head != NULL)
			{
				i = 0, j = 0;
				strcpy(aj, head->songsindex.albumName);
				len = strlen(aj);   // len stores the length of the input string
				while (aj[i] != '\0')    // till string doesn't terminate
				{
					if (aj[i] != ' ')  // if the char is not a white space
					{

						mj[j++] = aj[i];
					}

					i++;
				}
				mj[j] = '\0';
				if (_strcmpi(mj, string) == 0)
					playsong(head);
				head = head->next;
			}
		default:
			x = 0;
			break;
		}
	} while (x != 0);
	fclose(flog);
}
int deletedata(char* path, songs_t* thePlaylist, LNode* head, LNode* tail, int count)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	printf("\n"); fprintf(flog,"\n");
	int id, trackNo, i = 0;
	char artistName[31], albumName[31], trackName[31];	//note +1 for '\0'
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	FILE* fp = fopen(path, "r");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog,"File not found!\n");
		return 0;
	}
	fscanf(fp, "%5s%30s%30s%10s%30s", h1, h2, h3, h4, h5);
	printf("%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5); fprintf(flog,"%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	while (fscanf(fp, "%5d%30[^\n]%30[^\n]%5d%30[^\n]", &id, artistName, albumName, &trackNo, trackName) > 0)
	{
		if (i > count - 2)
			break;
		head->songsindex.id = id;
		strcpy(head->songsindex.artistName, artistName);
		strcpy(head->songsindex.albumName, albumName);
		head->songsindex.trackNo = trackNo;
		strcpy(head->songsindex.trackName, trackName);
		printf("%5d %30s %30s %10d %30s \n", id, artistName, albumName, trackNo, trackName); fprintf(flog,"%5d %30s %30s %10d %30s \n", id, artistName, albumName, trackNo, trackName);
		addNode(head, 1);
		head = head->next;
		i++;
	}
	fclose(fp,flog);
	return i;
}
int adddata(char* path, songs_t* thePlaylist, LNode* head, LNode* tail, int count)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	printf("\n"); fprintf(flog,"\n");
	int id, trackNo, i = 0;
	char artistName[31], albumName[31], trackName[31];	//note +1 for '\0'
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	FILE* fp = fopen(path, "a");
	if (!fp)
	{
		printf("File not found!\n"); fprintf(flog,"File not found!\n");
		return count;
	}
	printf("Enter track information\n"); fprintf(flog,"Enter track information\n");
	addNode(tail, count);
	head = tail->next;
	printf("enter track id: "); fprintf(flog,"enter track id: ");
	scanf("%d", &id);
	head->songsindex.id = id;

	printf("enter artist name: "); fprintf(flog,"enter artist name: ");
	scanf("%s", artistName);
	strcpy(head->songsindex.artistName, removespace(artistName));

	printf("enter album name: ");
	scanf("%s", albumName);
	strcpy(head->songsindex.albumName, removespace(albumName));

	printf("enter track number: "); fprintf(flog,"enter track number: ");
	scanf("%5d", &trackNo);
	head->songsindex.trackNo = trackNo;

	printf("enter track name: "); fprintf(flog,"enter track name: ");
	scanf("%s", trackName);
	strcpy(head->songsindex.trackName, removespace(trackName));

	fprintf(fp, "%-5d %-30s %-30s%-10d%-30s\n", id, artistName, albumName, trackNo, trackName);
	head = head->next;
	count = count + 1;
	fclose(fp,flog);
	return count;
}
int importData(char* path, songs_t* thePlaylist, LNode* head, LNode* tail, List* lst)
{
	FILE* flog = fopen("logfile.txt", "a+");
	if (!flog)
	{
		printf("File not found!\n");
		return 0;
	}
	int id, trackNo, i = -1, k = 0;
	char artistName[31], albumName[31], trackName[31];	//note +1 for '\0'
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	FILE* fp = fopen(path, "r");
	if (!fp)
	{
		printf("File not found!\n");
		return 0;
	}
	fscanf(fp, "%5s%30s%30s%10s%30s", h1, h2, h3, h4, h5);
	printf("%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5); fprintf(flog,"%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	while (fscanf(fp, "%5d%30[^\n]%30[^\n]%5d%30[^\n]", &id, artistName, albumName, &trackNo, trackName) > 0)
	{

		head->songsindex.id = id;
		strcpy(head->songsindex.artistName, removespace(artistName));
		strcpy(head->songsindex.albumName, removespace(albumName));
		head->songsindex.trackNo = trackNo;
		strcpy(head->songsindex.trackName, removespace(trackName));
		printf("%5d %30s %30s %10d %30s \n", id, artistName, albumName, trackNo, trackName); fprintf(flog,"%5d %30s %30s %10d %30s \n", id, artistName, albumName, trackNo, trackName);
		i++;
		addNode(head, i + 1);
		head = head->next;
	}
	lst->tail = head;
	k = deleteLast(lst);
	fclose(fp,flog);
	return (i + 1);
}
char* removespace(char txt[])
{
	char aj[100], mj[100], temp[1001], temp2[100];
	int n, m, len;
	n = 0, m = 0;
	strcpy(aj, txt);
	len = strlen(aj);   // len stores the length of the input string
	bool raitiot = false;
	while (aj[n] != '\0')    // till string doesn't terminate
	{
		if (aj[n] != ' ') {
			raitiot = true;
		}
		if (!raitiot) {
			if (aj[n] != ' ')  // if the char is not a white space
			{
				mj[m++] = aj[n];
			}
		}
		else {
			mj[m++] = aj[n];
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
void removeAll(List* lst, type toremove)
{
	LNode* current = lst->head, * next;
	if (current == NULL)
		return;
	while (current->data == toremove)
	{
		lst->head = current->next;
		if (lst->head == NULL)
			lst->tail = NULL;
		free(current);
		if (lst->head == NULL)
			return;
		else
			current = lst->head;
	}
	current = lst->head;
	next = current->next;
	while (next)
	{
		if (next->data == toremove)
		{
			current->next = next->next;
			free(next);
			if (current->next == NULL)
			{
				lst->tail = current;
				next = NULL;
			}
			else
			{
				next = current->next;
			}
		}
		else
		{
			current = next;
			next = current->next;
		}
	}
}
int insertLast(List* lst, LNode* item)
{
	if (item != NULL)
	{
		//reset item pointers
		item->next = item->prev = NULL;

		if (isEmpty(lst))
		{
			//make head & tail pointing to item
			lst->head = lst->tail = item;
		}
		else
		{
			//update last next link
			lst->tail->next = item;
			//point item to old last link
			item->prev = lst->tail;
			//point last to new last node
			lst->tail = item;
		}
		return 1;
	}
	return 0;
}
int insertAfter(List* lst, LNode* item, LNode* link)
{
	if (!isEmpty(lst))
	{
		if ((item == NULL) || (link == NULL))
			return 0;
		if (link == lst->tail)
			return insertLast(lst, item);

		//assign new item pointers
		item->prev = link;
		item->next = link->next;
		//chain link and link->next to new item
		link->next->prev = item;
		link->next = item;
		return 1;
	}
	return 0;
}
int insertBefore(List* lst, LNode* item, LNode* link)
{
	if (!isEmpty(lst))
	{
		if ((item == NULL) || (link == NULL))
			return 0;
		if (link == lst->head)
			return insertFirst(lst, item);

		//assign new item pointers
		item->next = link;
		item->prev = link->prev;
		//chain link and link->prev to new item
		link->prev->next = item;
		link->prev = item;
		return 1;
	}
	return 0;
}
int insertFirst(List* lst, LNode* item)
{
	if (item != NULL)
	{
		//reset item pointers
		item->next = item->prev = NULL;

		if (isEmpty(lst))
		{
			//make head & tail pointing to item
			lst->head = lst->tail = item;
		}
		else
		{
			//update first prev link
			lst->head->prev = item;
			//point item to old first link
			item->next = lst->head;
			//point head to new first node
			lst->head = item;
		}
		return 1;
	}
	return 0;
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
List copyList(const List* lst)
{
	List res = makeEmptyList();
	LNode* temp = lst->head;
	while (temp)
	{
		insertValueToTail(&res, temp->data);
		temp = temp->next;
	}
	return res;
}
List makeEmptyList()
{
	List lst;
	lst.head = lst.tail = NULL;
	return lst;
}
LNode* createNewNode(type newData, LNode* next)
{
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	newNode->data = newData;
	newNode->next = next;
	return newNode;
}
LNode* findData(List lst, type data)
{
	LNode* temp = lst.head;
	while (temp)
	{
		if (temp->data == data)
			return temp;
		temp = temp->next;
	}
	return NULL;
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
void insertValueToHead(List* lst, type newData)
{
	LNode* newNode = createNewNode(newData, lst->head);
	if (isEmpty(lst))
		lst->head = lst->tail = newNode;
	else
		lst->head = newNode;
}
void insertValueToTail(List* lst, type newData)
{
	LNode* newNode = createNewNode(newData, NULL);
	if (isEmpty(lst))
		lst->head = lst->tail = newNode;
	else
	{
		lst->tail->next = newNode;
		lst->tail = newNode;
	}
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
void insertAfterValue(List* lst, type insertAfter, type newValue)
{
	LNode* temp = lst->head;
	temp = findData(*lst, insertAfter);
	if (temp)
	{
		LNode* newNode = createNewNode(newValue, temp->next);
		temp->next = newNode;
		if (newNode->next == NULL)
			lst->tail = newNode;
	}
}
void removedata(List* lst, int toremove, LNode* head)
{
	LNode* current, * next;
	current = lst->head;
	if (current == NULL)
		return;
	if (current->data == toremove)
	{
		lst->head = current->next;
		if (lst->head = NULL)
			lst->tail = NULL;
		free(current);
		return;
	}
	next = current->next;
	while (next)
	{
		if (next->data == toremove)
		{
			current->next = next->next;
			if (current->next == NULL)
				lst->tail = current;
			free(next);
		}
		else
		{
			current = next;
			next = current->next;
		}
	}
}
