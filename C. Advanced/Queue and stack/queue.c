#define _CRT_SECURE_NO_DEPRECATE
/*
Assigned by:
Ron ben david #307906263
*/
// C program for array implementation of queue 
#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 

// A structure to represent a queue 
struct Queue {
	int front, rear, size;
	unsigned capacity;
	int* array;
};

// function to create a queue 
// of given capacity. 
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity)
{
	struct Queue* queue = (struct Queue*)malloc(
		sizeof(struct Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;

	// This is important, see the enqueue 
	queue->rear = capacity - 1;
	queue->array = (int*)malloc(
		queue->capacity * sizeof(int));
	return queue;
}

// Queue is full when size becomes 
// equal to the capacity 
int isFull(struct Queue* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0 
int isEmpty(struct Queue* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue. 
// It changes rear and size 
void enqueue(struct Queue* queue, int item)
{
	if (isFull(queue))
		return;
	queue->rear = (queue->rear + 1)
		% queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
	printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue. 
// It changes front and size 
int dequeue(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1)
		% queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

// Function to get front of queue 
int front(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}

// Function to get rear of queue 
int rear(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->rear];
}

// Driver program to test above functions./ 
int main()
{
	struct Queue* queue1 = createQueue(10);
	struct Queue* queue2 = createQueue(10);
	int temp, i;
	char opertaor = 'a';
	enqueue(queue1, 3);
	enqueue(queue1, 7);
	enqueue(queue1, 13);
	enqueue(queue1, 20);
	enqueue(queue1, 47);
	enqueue(queue1, 70);
	enqueue(queue2, 12);
	enqueue(queue2, 20);
	enqueue(queue2, 65);
	enqueue(queue2, 70);
	enqueue(queue2, 75);
	printf("Press 1 to Q1\nPress 2 to Q2");
	scanf_s(" %c", &opertaor);
	switch (opertaor)
	{
	case '1':
		while (isEmpty(queue1) != 1 || isEmpty(queue2) != 1)
		{
			if (front(queue1) < front(queue2))
				dequeue(queue1);
			if (front(queue1) == front(queue2))
			{
				printf("\nThe lower number that equal between 2 queues is = %d\n", front(queue1));
				break;
			}
			if (front(queue2) < front(queue1))
				dequeue(queue2);
		}
			break;
	case '2':
		printf("start sort\n");
		i = queue2->size;
		temp = front(queue1);
		while (isEmpty(queue2) != 1 || i == 1)
		{
			i = queue2->size;
			if (front(queue1) < front(queue2)) {
				enqueue(queue1, front(queue1));
				dequeue(queue1);
			}

			if (front(queue1) == front(queue2))
			{
				enqueue(queue1, front(queue2));
				dequeue(queue1);
				dequeue(queue2);
			}
			if (front(queue2) < front(queue1)) {
				enqueue(queue1, front(queue2));
				dequeue(queue2);
			}
			if (temp == front(queue1))
				if (i == 1)
				{
					enqueue(queue1, front(queue2));
					dequeue(queue2);
					break;
				}
		}
		printf("\n\nAfter sort\n\n");
		temp = front(queue1);
		do {
			enqueue(queue1, front(queue1));
			dequeue(queue1);
		} while (temp != front(queue1));
		break;

	default:
		break;
		}
		return 0;
	}

