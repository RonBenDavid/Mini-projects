/*
Assigned by:
Ron ben david
*/
#ifndef store
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <time.h>
/*
* programm menu - options to choose what to do with the playlist
* e.g.: play song, next song, prev song, etc.
*/

void menu(char* userspath, char* itemspath);
#define _CRT_SECURE_NO_WARNINGS
#define MAXsearch 50
#define USERS_PATH "users.txt"
/***
* This is the path where the users are located.
***/
#define ITEMS_PATH "items.txt"
/***
* This is the path where the item file is located.
***/
#define LOG_PATH "log.txt"
/***
* This is the path where the log file is located.
* Open this file and append new records into it.
***/

typedef struct users
{
	int level;
	char temp[100];
	char username[16];
	char password[16];
	char fullname[21];
}users_t;
typedef struct date
{
	int day;
	int month;
	int year;
	int hours;
	int mins;
}date_t;
typedef struct items
{
	int serial;
	char category[17];
	char brand[17];
	char productName[31];
	double pricE;
	bool stock;
	date_t dateIndex;
	struct items_t* next;
	struct items_t* prev;

}items_t;
typedef struct LNode
{
	int data;
	users_t usersIndex;
	items_t itemsIndex;
	struct LNode* next;
	struct LNode* prev;
}LNode;
typedef struct List
{
	LNode* head;
	LNode* tail;
}List;
int readUserswithoutprint(char* path, users_t* theusers, LNode* head, LNode* tail, List* lst);
int Short(LNode* head,List* lst);
void fprintitem(char path, LNode* head);
fprintTOlog(char* line);
int adddataUser(char* path, users_t* theUsers, LNode* head, LNode* tail, int count);
int adddataItems(char* path, items_t* theItems, LNode* head, LNode* tail, int count);
List makeEmptyList();
LNode* getLinkByIndex(List* lst, int idx);
int getlistLength(const List* lst);
void freeList(List* thelist);
int isEmpty(const List* lst);
void printCharList(const List* lst);
void menu(char* userpath, char* itemspath);
LNode* addNode(LNode* head, int value);
void Printitem(LNode* head);
int moveforward(LNode* current, LNode* head, LNode* tail);
int movebackward(LNode* current, LNode* head, LNode* tail);
void searchByBorC(LNode* head, List* lst, int level);
void searchByValue(LNode* head, List* lst, int level);
void searchByStock(LNode* head, List* lst, int level);
void searchByDate(LNode* head, List* lst, int level);
char* removespace(char txt[]);
int deleteLast(List* lst);
void initList(List* lst);
void getDateTime(int* day, int* month, int* year, int* hours, int* mins);
int readUsers(char* path, users_t* theusers, LNode* head, LNode* tail, List* lst);
void edititem(LNode* head, char operator);
int fPrintNewitemfile(char* path, items_t* theItems, LNode* head, LNode* tail, int count);
void editSingleuser(LNode* head, char* username);
void editSingelitem(LNode* head, int serial);
int fPrintitemRemove(char* path, items_t* theItems, LNode* head, LNode* tail, int count, int serial);
int fPrintuserRemove(char* path, users_t* theItems, LNode* head, LNode* tail, int count, char* username);
#endif
