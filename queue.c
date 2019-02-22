/*
	Author: Bailey Gulsby
	Description: This program generates a queue using a singly linked list substructure
*/

#include "queue.h"
#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct queue
{
	SLL *stackList;
	void (*display)(void *, FILE *);
	void (*free)(void *);
};

QUEUE *newQUEUE(void (*d)(void *, FILE *), void(*f)(void *))
{
	QUEUE *items = malloc(sizeof(QUEUE));
	assert(items != NULL);
	items->stackList = newSLL(d,f);
	items->display = d;
	items->free = f;
	return items;
}

void enqueue(QUEUE *items, void *value)
{
	insertSLL(items->stackList,sizeQUEUE(items),value);
}

void *dequeue(QUEUE *items)
{
	assert(sizeQUEUE(items) > 0);
	void *valReturn = removeSLL(items->stackList,0);
	return valReturn;
}

void *peekQUEUE(QUEUE *items)
{
	assert(sizeQUEUE(items) > 0);
	void *valReturn = getSLL(items->stackList,0);
	return valReturn;
}

int sizeQUEUE(QUEUE *items)
{
	int stackSize = sizeSLL(items->stackList);
	return stackSize;
}

void displayQUEUE(QUEUE *items, FILE *fp)
{
	fprintf(fp, "<");
	int i;
	for (i = 0; i < sizeQUEUE(items); i++)
	{
		items->display(getSLL(items->stackList,i),fp);
		if (i != sizeQUEUE(items) - 1)
		{
			fprintf(fp, ",");
		}
	}
	fprintf(fp, ">");
}

void displayQUEUEdebug(QUEUE *items, FILE *fp)
{
	displaySLLdebug(items->stackList,fp);
}

void freeQUEUE(QUEUE *items)
{
	freeSLL(items->stackList);
	free(items);
}