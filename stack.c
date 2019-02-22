/*
	Author: Bailey Gulsby
	Description: This program generates a stack using a doubly linked list substructure
*/

#include "stack.h"
#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct stack
{
	DLL *stackList;
	void (*display)(void *, FILE *);
	void (*free)(void *);
};

STACK *newSTACK(void (*d)(void *, FILE *), void (*f)(void *))
{
	STACK *items = malloc(sizeof(STACK));
	assert(items != NULL);
	items->stackList = newDLL(d,f);
	items->display = d;
	items->free = f;
	return items;
}

void push(STACK *items, void *value)
{
	insertDLL(items->stackList,0,value);
}

void *pop(STACK *items)
{
	assert(sizeSTACK(items) > 0);
	void *valReturn = removeDLL(items->stackList,0);
	return valReturn;
}

void *peekSTACK(STACK *items)
{
	assert(sizeSTACK(items) > 0);
	void *valReturn = getDLL(items->stackList,0);
	return valReturn;
}

int sizeSTACK(STACK *items)
{
	int stackSize = sizeDLL(items->stackList);
	return stackSize;
}

void displaySTACK(STACK *items, FILE *fp)
{
	fprintf(fp, "|");
	int i;
	for (i = 0; i < sizeSTACK(items); i++)
	{
		items->display(getDLL(items->stackList,i),fp);
		if (i != sizeSTACK(items) - 1)
		{
			fprintf(fp, ",");
		}
	}
	fprintf(fp, "|");
}

void displaySTACKdebug(STACK *items, FILE *fp)
{
	displayDLLdebug(items->stackList,fp);
}

void freeSTACK(STACK *items)
{
	freeDLL(items->stackList);
	free(items);
}

