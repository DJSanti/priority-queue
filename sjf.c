/************************************** 
Name: Samantha Santiago
Class: 345-002 (Operating Systems)
Date: 03/26/2018
Program: sjf.c
***************************************/
/*
* ADT Priority Queue in C
*/
/* Purpose: To sort incoming processes by burst time and display them from longest to shortest
	    times, with the largest value on the left and the smallest value on the right. The 
	    processes are then dispatched right to left since it is organized for the shortest
	    job to be executed first.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 15
// got rid of dispatch_by_priority() since it wasn't being used
void insert_by_priority(int); 
void delete_by_priority(int);
void create();
void check(int);
void display_pqueue();

int pri_que[MAX];
int front, rear;
int x=1; // identifies process

int main()
{
	int n, ch;
	int i=0, Tot_time=0; //i=0 so that I can do the functions below (arrays start at 0)

	printf("\n1 - Insert a process into queue");
	printf("\n2 - Dispatch processes in queue");
	printf("\n3 - Delete a process from queue");
	printf("\n4 - Display queue elements");
	printf("\n5 - Exit");
	create();
	while (1)
	{
		printf("\nEnter your choice : ");
		scanf("%d", &ch); // variable is choice
		
		switch (ch)
		{
		case 1: 
			printf("\nEnter Estimated Burst time of process %d: ", x); // made global variable for PID
			scanf("%d",&n);
			insert_by_priority(n); 
			x=x+1; // moves on to next process
			break;
		case 2: // Dispatch i.e. invoke CPU scheduler
			// function to get total time, which is the sum of all the burst times
			for (i=0; i <= rear; i++)
			{
				Tot_time += pri_que[i];
			}
			// total time is printed
			printf("\nTotal time: %d", Tot_time);
			//clears total time ./so that it doesn't keep getting added on to previous value
			Tot_time = 0;
			// clears out the queue after total time is found
			for (; front <= rear; front++)
			{
				n = pri_que[front];
				delete_by_priority(n);
			}
			break;
		case 3: // Delete from Queue -- this is in case you make a mistake
			printf("\nEnter burst time of process to be deleted : ");
			scanf("%d",&n);
			delete_by_priority(n);
			break;
		case 4: 
			display_pqueue();
			break;
		case 5: 
			exit(0);
		default: 
			printf("\nChoice is incorrect. Enter a correct choice");				
		}
	}
}

/* Function to create an empty priority queue */
void create()
{
	front = rear = -1;
}

/* Function to insert value into priority queue */
void insert_by_priority(int data) // data is n from above
{
	if (rear >= MAX - 1)
	{
		printf("\nQueue overflow - no more elements can be inserted");
		return;
	}
	if ((front == -1) && (rear == -1)) // we reach end of queue
	{
		front++; // counters of front and rear increased
		rear++;
		pri_que[front] = data; // item at beginning of queue is made equal to data.
		return;
	}
	else
		check(data); //check function is ran on data
	rear++;
}

/* Function to check priority and place element */
void check(int data) // data is n from above -- this function was pretty much kept the same
{
	int i,j;
	// for i in priority queue, as long as it's not at the end of the queue
	for (i = 0; i <= rear; i++)
	{
		if (data >= pri_que[i]) 
		{
			for (j = rear + 1; j > i; j--) // j is the outer bound
			{
				pri_que[j] = pri_que[j - 1]; // priority queue
			}
			pri_que[i] = data; // item is equal to data
			return;
		}
	}
	pri_que[i] = data; //item i in priority queue made equal to data
}

/* Function to delete queue elements */
void delete_by_priority(int data) 
{
	int i; // counter established
	
	if ((front == -1) || (rear == -1)) // changed all of these front/rear to OR statements so that it can actually show when queue is empty
	{
		printf("\nQueue is empty. No elements to delete");
		return;
	}
	
	for (i = 0; i <= rear; i++) 
	{
		if (data == pri_que[i]) 
		{
			for (; i < rear; i++) 
			{
				pri_que[i] = 0; // by default, array is full of zeroes anyway
			}
		}
	}
	front = -1;
	rear = -1; // makes it so that technically, the array is 'emptied'
	x = 1; // resets process counter so that the next batch of processes starts at 1
	
	// got rid of printf here because it irked me
}

/* Function to display queue elements */
void display_pqueue()
{
	if ((front == -1) || (rear == -1)) 
	{
		printf("\nQueue is empty");
		return;
	}
	
	for (; front <= rear; front++)
	{
		printf(" %d ", pri_que[front]); // prints contents of queue -- when read from left to right, the output of the sorted burst times goes from greatest to least, as originally programmed
	}									// for the sake of this program, we'll say the program all the way on the right is executed first
	
	front = 0;
}
