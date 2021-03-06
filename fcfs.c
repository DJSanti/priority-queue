/************************************** 
Name: Samantha Santiago
Class: 345-002 (Operating Systems)
Date: 03/27/2018
Program: sjf.c
***************************************/
/*
* ADT Priority Queue in C
*/
/* Purpose: To take in new processes and execute them according to the order in which they arrived in 
	    the queue. Processes are displayed left to right, with the leftmost burst time being P1 and
	    the rightmost being whichever process has most recently arrived. This program implements First
	    Come First Serve.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 15
// got rid of dispatch_by_priority() since it wasn't being used
void insert_by_priority(int); 
void delete_by_priority(int);
void create();
// check function was deleted
void display_pqueue();

int pri_que[MAX]; // priority queue, and variables to identify first and last spots in the queue (which is an array)
int front, rear;
int x=1; // identifies process

int main()
{
	int n, ch;
	int i=0, Tot_time=0; //i=0 so that I can do the functions below (arrays start at 0). It's a counter.

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
			printf("\nEnter Estimated Burst time of process %d: ", x); // made global variable for PID (x)
			scanf("%d",&n);
			insert_by_priority(n); 
			x=x+1; // moves on to next process the next time this case is called
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
		// counter of rear increased, while front is always kept at 0
		front = 0;
		rear++;
		pri_que[rear] = data; // every new burst time is inserted to the right of the last one
		return;

}
// got rid of check function, since it wasn't being used for this program

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
	rear = -1; // makes it so that technically, the array is 'emptied'. This works because the array has to start at 0.
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
		printf(" %d ", pri_que[front]); // prints contents of queue, which are now reading from left to right in the order in which they arrived
	}	// for the sake of this program, we'll say the program all the way on the left is executed first, since it's FCFS
	
	front = 0; // front is made equal to 0
}
