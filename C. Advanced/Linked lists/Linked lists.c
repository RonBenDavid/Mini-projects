#define _CRT_SECURE_NO_DEPRECATE
/*
Assigned by:
Ron ben david #307906263
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
typedef int type;
typedef struct LNode
{
	type data;
	struct LNode *next;
	struct LNode *prev;
}LNode;
typedef struct List
{
	struct LNode *head, *tail;
}List;
List copyList(const List* lst);
List makeEmptyList();
LNode* getLinkByIndex(List* lst, int idx);
LNode* createNewNode(type newData, LNode* next);
LNode* findData(List lst, type data);
int getlistLength(const List* lst);
void printList(const List* lst);
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
void main()
{
	int i,num,value,length=0,k=0;
	char ch[256];
	/*List lst=makeEmptyList();
	printf("Enter how many numbers in the list\n");
	scanf("%d", &num);
	for(i=0;i<num;i++)
	{
		printf("enter #%d number: ", i + 1);
		scanf("%d", &value);
		insertValueToTail(&lst, value);
	}
	length=getlistLength(&lst);
	printf("length of the list: %d\n", length);
	printf("%s", checkpelndrom(&lst, length) ? "The number is palendrum\n" : "The number is not palendrum\n");
	//Q2
	printf("Enter K number: ");
	scanf("%d", &k);
	Qtwo(&lst,k,length);
	//Q3*/
	List lststring = makeEmptyList();
	printf("Please enter string\n");
	scanf("%s", &ch);
	for (i = 0; i < strlen(ch); i++)
	{
		insertValueToTail(&lststring, ch[i]);
	}
	printf("The new string without duplicates is : ");
	Qtree(&lststring);

}
void removeAll(List* lst, type toremove)
{
	LNode* current=lst->head, * next;
	if (current == NULL)
		return;
	while (current->data==toremove)
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
void Qtwo(List* lst, int k,int length)
{
	List temp = makeEmptyList();
	int i = 0,j=0;
	for (; i < length; i++)
	{
		if (getLinkByIndex(lst, i)->data == k)
		{
			insertValueToTail(&temp, 0);
			insertValueToTail(&temp, getLinkByIndex(lst, i)->data);
		}
		else
		{
			insertValueToTail(&temp, getLinkByIndex(lst, i)->data);
		}
	}
	printf("The New List is : ");
	printList(&temp);
}
void Qtree(const List* lst)
{
	int i;
	char c;
	List temp = makeEmptyList();
	temp = copyList(lst);
	List new = makeEmptyList();
	int length = getlistLength(&temp);
	for (i = 0; i < length; i++)
	{
		c=getLinkByIndex(&temp, i)->data;
		removeAll(&temp, c);
		insertValueToTail(&new, c);
		length = getlistLength(&temp);
	}
	printCharList(&new);
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
int checkpelndrom(const List* lst,int len)
{
	int i;
		for (i = 0; i < len / 2; i++)
		{
			if (getLinkByIndex(lst, i)->data != getLinkByIndex(lst, len - 1 - i)->data)
				return 0;
		}
		return 1;
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
	while (temp!=NULL)
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
void printList(const List* lst)
{
	LNode* temp = lst->head;
	while (temp != NULL)
	{
		printf("%d", temp->data);
		temp = temp->next;
	}
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