/*
	Author: Bailey Gulsby
	Description: This program generates a doubly linked list using any given data type
*/

#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//struct definition for each node in the linked list
typedef struct Node
{
	void *itemVal;
	struct Node *next;
	struct Node *prev;	
} Node;

//struct definition for list implementation
struct dll
{
	//DLL *items;
	Node *head;
	Node *tail;
	Node *iterator;
	int size;
	void (*display)(void *, FILE *);
	void (*free)(void *);
};



//constuctor for allocating memory and initializing functions of DLL
DLL *newDLL(void (*d)(void *, FILE *), void (*f)(void *))
{
	DLL *items = malloc(sizeof(DLL));
	items->head = malloc(sizeof(Node));
	assert(items != NULL);
	items->head->itemVal = NULL;
	items->head->next = NULL;
	items->head->prev = NULL;
	items->tail = items->head;
	items->iterator = NULL;
	items->size = 0;
	items->display = d;
	items->free = f;
	return items;
}

//This function is used to insert a new Node at the index given to the function
void *insertDLL(DLL *items, int index, void *value)
{

	assert(index >= 0 && index <= items->size);
	Node *newNode = malloc(sizeof(Node));
	newNode->itemVal = value;
	Node *curNode;
	int i = 0;

	//initialization of the empty linked list
	if (items->size == 0)
	{
		items->head->next = newNode;
		items->tail = newNode;
		newNode->next = NULL;
		newNode->prev = items->head;
	}
	//inserting at the front of the list
	else if (index == 0)
	{
		newNode->next = items->head->next;
		newNode->next->prev = newNode;
		items->head->next = newNode;
		newNode->prev = items->head;
	}
	//inserting at the back of the list
	else if (index == items->size)
	{
		items->tail->next = newNode;
		newNode->prev = items->tail;
		newNode->next = NULL;
		items->tail = newNode;
	}
	//inserting in the middle
	else
	{
		if (index > items->size / 2)
		{
			curNode = items->tail;
			while(i < (items->size - index) - 1)
			{
				curNode = curNode->prev;
				i++;
			}
			curNode->prev->next = newNode;
			newNode->prev = curNode->prev;
			curNode->prev = newNode;
			newNode->next = curNode;
			
		}
		else
		{
			curNode = items->head->next;
			
			while(i < index-1)
			{
				curNode = curNode->next;
				i++;
			}
			curNode->next->prev = newNode;
			newNode->next = curNode->next;
			curNode->next = newNode;
			newNode->prev = curNode;
		}
	}
	items->size++;
	return newNode;
	
}

//this function removes a node from the list and returns its value
void *removeDLL(DLL *items, int index)
{
	assert(items->size > 0);
	assert(index >= 0 || (index = 0 && index < items->size));
	Node *curNode;
	void *valReturn;
	int i = 0;

	//base case: removing the last item from the list
	if (items->size == 1)
	{
		curNode = items->head->next;
		valReturn = curNode->itemVal;
		items->head->next = NULL;
		items->tail = items->head;
	}
	else if (index == 0)
	{
		curNode = items->head->next;
		valReturn = curNode->itemVal;
		items->head->next = curNode->next;
	}
	else if (index == items->size-1)
	{
		curNode = items->tail;
		valReturn = curNode->itemVal;
		items->tail = items->tail->prev;
		items->tail->next = NULL;
	}
	else
	{
		if (index > items->size / 2)
		{
			curNode = items->tail;
			while(i < (items->size - index) - 1)
			{
				curNode = curNode->prev;
				i++;
			}
			Node *prevNode = curNode->prev;
			valReturn = curNode->itemVal;
			curNode->next->prev = prevNode;
			prevNode->next = curNode->next;
		}
		else
		{
			curNode = items->head->next;
			while(i != index)
			{
				curNode = curNode->next;
				i++;
			}
			Node *prevNode = curNode->prev;
			valReturn = curNode->itemVal;
			curNode->next->prev = prevNode;
			prevNode->next = curNode->next;
		}
	}
	free(curNode);
	items->size--;
	return valReturn;
}

//this function appends a donor list onto the end of a recipient list
void unionDLL(DLL *recipient, DLL *donor)
{
	//base case: both lists are empty
	if (recipient->size == 0 && donor->size == 0)
	{
		return;
	}
	//second case: recipient is a NULL list
	else if (recipient->size == 0 && donor->size != 0)
	{
		recipient->head->next = donor->head->next;
		recipient->tail = donor->tail;
		donor->head->next = NULL;
		donor->tail = donor->head;
		recipient->size = donor->size;
		donor->size = 0;


		// Node *emptyNode = malloc(sizeof(Node));
		// emptyNode->itemVal = NULL;
		// emptyNode->next = NULL;
		// donor->tail = emptyNode;
		return;
	}
	//third case: donor is a NULL list
	else if (recipient->size != 0 && donor->size == 0)
	{
		return;
	}

	//fourth case: both lists are not NULL
	else
	{
		recipient->tail->next = donor->head->next;
		donor->head->next->prev = recipient->tail;		
		recipient->tail = donor->tail;
		recipient->size = recipient->size + donor->size;
		donor->size = 0;
		donor->head->next = NULL;
		donor->tail = donor->head;


		// Node *emptyNode = malloc(sizeof(Node));
		// emptyNode->itemVal = NULL;
		// emptyNode->next = NULL;
		// donor->head->next = emptyNode;
		// donor->tail = emptyNode;

		return;
	}
}

//this function returns the value at a given index in the list
void *getDLL(DLL *items, int index)
{
	assert(index >= 0 && index < items->size);
	if (index == items->size - 1)
	{
		return items->tail->itemVal;
	}
	Node *curNode;
	int i = 0;
	if (index > items->size / 2)
	{
		curNode = items->tail;
		while(i < (items->size - index) - 1)
		{
			curNode = curNode->prev;
			i++;
		}
		return curNode->itemVal;
	}
	else
	{
		curNode = items->head->next;
		while(i < index)
		{
			curNode = curNode->next;
			i++;
		}
		return curNode->itemVal;
	}
}

//this value sets the value of the node at the given index to the given value
void *setDLL(DLL *items, int index, void *value)
{
	assert(index >= 0 && index <= items->size);
	void *valReturn;
	if (index == items->size - 1)
	{
		valReturn = items->tail->itemVal;
		items->tail->itemVal = value;
		return items->tail->itemVal;
	}
	Node *curNode;
	int i = 0;
	if (index > items->size / 2)
	{
		//printf("here i am\n");
		curNode = items->tail;
		while(i < (items->size - index) - 1)
		{
			curNode = curNode->prev;
			i++;
		}
	}
	else
	{
		curNode = items->head->next;
		while(i < index)
		{
			curNode = curNode->next;
			i++;
		}
	}
	valReturn = curNode->itemVal;
	curNode->itemVal = value;
	return valReturn;	
}

//this function returns the size of the list
int sizeDLL(DLL *items)
{
	return items->size;
}

//function displays the list given to it
void displayDLL(DLL *items, FILE *fp)
{

	fprintf(fp, "{{");
	if (items->size != 0)
	{
		Node *curNode;
		curNode = items->head->next;
		int i=0;
		while(curNode != NULL)
		{
			items->display(curNode->itemVal, fp);
			if (i != items->size - 1)
			{
				fprintf(fp, ",");
			}
			curNode = curNode->next;
			i++;
		}
	}
	fprintf(fp, "}}");
}

//this function displays the head and tail pointers of the list as well as the list itself
void displayDLLdebug(DLL *items, FILE *fp)
{
	fprintf(fp, "head->");
	displayDLL(items, fp);
	//fprintf(fp, "}");
	fprintf(fp, ",tail->{{");
	if (items->size != 0)
	{
		items->display(items->tail->itemVal, fp);
	}
	fprintf(fp, "}}");
}

//this function frees the list
void freeDLL(DLL *items)
{
	while (sizeDLL(items) > 0)
	{
		void *freer = removeDLL(items,0);
		if (items->free) items->free(freer);
	}
	free(items->head);
	free(items);
	/*
	if (items->free == NULL)
	{
		while(items->head->next != NULL)
		{
			Node *curNode;
			curNode = items->head->next;
			items->head->next = curNode->next;
			free(curNode);
			items->size--;
		}
		free(items->head);
		free(items);
		return;
	}
	while(items->head->next != NULL)
	{
		Node *curNode;
		curNode = items->head->next;
		items->head->next = curNode->next;
		items->free(curNode->itemVal);
		items->free(curNode);
	}
	items->free(items->head);
	free(items);
	*/
}

void removeDLLall(DLL *items)
{
	while (items->size > 0)
	{
		removeDLL(items,0);
	}
}

void *removeDLLnode(DLL *items,void *value)
{
	Node *node = value;
	void *returnVal = node->itemVal;

	if (items->size == 1)
	{
		items->tail = items->head;
		items->head->next = NULL;
		items->size--;
		free(node);
		//items->iterator = items->tail;
		return returnVal;
	}
	if (node == items->tail)
	{
		items->tail = node->prev;
		node->prev->next = NULL;
		items->size--;
		free(node);
		//items->iterator = items->tail;
		return returnVal;
	}
	//if (node == items->iterator) items->iterator = items->iterator->next;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	items->size--;
	free(node);
	return returnVal;

	/*
	// assert(items->size > 0);
	// assert(index >= 0 || (index = 0 && index < items->size));
	Node *curNode = items->head->next;
	Node *tempNode = node;
	int index = 0;
	while (tempNode->itemVal != curNode->itemVal)
	{
		index++;
		curNode = curNode->next;
	}
	// void *valReturn;
	int i = 0;

	//base case: removing the last item from the list
	if (items->size == 1)
	{
		curNode = items->head->next;
		// valReturn = curNode->itemVal;
		items->head->next = NULL;
		items->tail = items->head;
	}
	else if (index == 0)
	{
		curNode = items->head->next;
		// valReturn = curNode->itemVal;
		items->head->next = curNode->next;
	}
	else if (index == items->size-1)
	{
		curNode = items->tail;
		// valReturn = curNode->itemVal;
		items->tail = items->tail->prev;
		items->tail->next = NULL;
	}
	else
	{
		if (index > items->size / 2)
		{
			curNode = items->tail;
			while(i < (items->size - index) - 1)
			{
				curNode = curNode->prev;
				i++;
			}
			Node *prevNode = curNode->prev;
			// valReturn = curNode->itemVal;
			curNode->next->prev = prevNode;
			prevNode->next = curNode->next;
		}
		else
		{
			curNode = items->head->next;
			while(i != index)
			{
				curNode = curNode->next;
				i++;
			}
			Node *prevNode = curNode->prev;
			// valReturn = curNode->itemVal;
			curNode->next->prev = prevNode;
			prevNode->next = curNode->next;
		}
	}
	// free(curNode);
	items->size--;
	return curNode; // valReturn;
	*/
}

void firstDLL(DLL *items)
{
	items->iterator = items->head->next;
}

void lastDLL(DLL *items)
{
	items->iterator = items->tail;
}

int moreDLL(DLL *items)
{
	if (items->iterator == NULL) return 0;
	if (items->iterator->itemVal == NULL) return 0;
	else return 1;
}

void nextDLL(DLL *items)
{
	if (!items->iterator) return;
	items->iterator = items->iterator->next;
}

void prevDLL(DLL *items)
{
	items->iterator = items->iterator->prev;
}

void *currentDLL(DLL *items)
{
	if (!items->iterator) return NULL;
	return items->iterator->itemVal;
}