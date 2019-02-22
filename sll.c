/*
	Author: Bailey Gulsby
	Description: This program generates a singly linked list using any given data type
*/

#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//struct definition for each node in the linked list
typedef struct Node
{
	void *itemVal;
	struct Node *next;
} Node;

//struct definition for list implementation
struct sll
{
	//SLL *items;
	Node *head;
	Node *tail;
	int size;
	void (*display)(void *, FILE *);
	void (*free)(void *);
};

//constuctor for allocating memory and initializing functions of SLL
SLL *newSLL(void (*d)(void *, FILE *), void (*f)(void *))
{
	SLL *items = malloc(sizeof(SLL));
	items->head = malloc(sizeof(Node));
	assert(items != NULL);
	items->head->itemVal = NULL;
	items->head->next = NULL;
	items->tail = items->head;
	items->size = 0;
	items->display = d;
	items->free = f;
	return items;
}

// This function is used to insert a new Node at the index given to the function
void insertSLL(SLL *items, int index, void *value)
{
	assert(index >= 0 && index <= items->size);
	Node *newNode = malloc(sizeof(Node));
	newNode->itemVal = value;

	//initialization of the empty linked list 
	if (items->size == 0)
	{
		items->head->next = newNode;
		items->tail = newNode;
		newNode->next = NULL;
		items->size++;
	}
	else
	{	
		//inserting at the front of the list
		if (index == 0)
		{
			newNode->next = items->head->next;
			items->head->next = newNode;
		}
		else if (index == items->size)
		{
			items->tail->next = newNode;
			items->tail = newNode;
			newNode->next = NULL;
		}
		//inserting after the first node
		else
		{
			int i = 1;
			Node *curNode;
			curNode = items->head->next;
			while (i < index)
			{
				curNode = curNode->next;
				i++;
			}
			newNode->next = curNode->next;
			curNode->next = newNode;
			//condition for if inserting at the back of the list
			/*
			if (newNode->next == NULL)
			{
				items->tail = newNode;
			}
			for (i = 1; i <= items->size; i++)
			{
				if (i == index)
				{
					newNode->next = curNode->next;
					curNode->next = newNode;
					//condition for if inserting at the back of the list
					if (newNode->next == NULL)
					{
						items->tail = newNode;
					}
				}
				else
				{
					curNode = curNode->next;
				}
			}
			*/
		}
		items->size++;
	}
	return;
}

//this function removes a node from the list and returns its value
void *removeSLL(SLL *items, int index)
{
	assert(items->size > 0);
	assert(index >= 0 || (index = 0 && index < items->size));
	Node *curNode;
	curNode = items->head->next;
	
	//initialization of variable to return value removed from list
	void *valReturn;

	//base case: removing the last item from the list
	if (items->size == 1)
	{
		valReturn = curNode->itemVal;
		items->head->next = NULL;
		items->size--;
		free(curNode);
		return valReturn;
	}

	//removing the first node in the list
	if (index == 0)
	{
		valReturn = items->head->next->itemVal;
		items->head->next = curNode->next;
	}

	//removing a node beyond the first node in the list
	else
	{
		curNode = curNode->next;
		Node *prevNode;
		prevNode = items->head->next;

		//pointing curNode to the node being removed
		int i;
		for (i = 1; i < index; i++)
		{
			curNode = curNode->next;
			prevNode = prevNode->next;
		}

		//special case for removing the last item from the list
		if (index == items->size)
		{
			items->tail = prevNode;
		}
		valReturn = curNode->itemVal;
		prevNode->next = curNode->next;
	}
	free(curNode);
	items->size--;
	return valReturn;
}

//this function appends a donor list onto the end of a recipient list
void unionSLL(SLL *recipient, SLL *donor)
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
			/*
		Node *emptyNode = malloc(sizeof(Node));
		emptyNode->itemVal = NULL;
		emptyNode->next = NULL;
		donor->tail = emptyNode;
		donor->head->next = donor->tail;
		*/
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
		recipient->tail = donor->tail;
		recipient->size = recipient->size + donor->size;
		donor->size = 0;
		donor->head->next = NULL;
		donor->tail = donor->head;
		/*
		Node *emptyNode = malloc(sizeof(Node));
		emptyNode->itemVal = NULL;
		emptyNode->next = NULL;
		donor->head->next = emptyNode;
		donor->tail = emptyNode;
		*/
		return;
	}
}

//this function returns the value at a given index in the list
void *getSLL(SLL *items, int index)
{
	assert(index >= 0 && index < items->size);
	/*
	int i = 1;
	Node *curNode;
	curNode = items->head->next;
	while (i < index)
	{
		curNode = curNode->next;
		i++;
	}
	*/
	if (index == items->size - 1)
	{
		return items->tail->itemVal;
	}
	Node *curNode;
	curNode = items->head->next;
	int i = 0;
	while (i < index)
	{
		// items->display(curNode->itemVal, stdout);
		// printf("\n");
		curNode = curNode->next;
		i++;
	}
	return curNode->itemVal;
}

//this value sets the value of the node at the given index to the given value
void *setSLL(SLL *items, int index, void *value)
{
	assert(index >= 0 && index <= items->size);
	void *valReturn;
	/*
	int i = 1;
	Node *curNode;
	curNode = items->head->next;
	while (i < index)
	{
		curNode = curNode->next;
		i++;
	}
	*/
	if (index == items->size - 1)
	{
		valReturn = items->tail->itemVal;
		items->tail->itemVal = value;
		return items->tail->itemVal;
	}
	Node *curNode;
	curNode = items->head->next;
	int i = 0;
	while (i < index)
	{
		curNode = curNode->next;
		i++;
	}
	
	valReturn = curNode->itemVal;
	curNode->itemVal = value;
	return valReturn;
}

//this function returns the size of the list
int sizeSLL(SLL *items)
{
	return items->size;
}

//function displays the list given to it
void displaySLL(SLL *items, FILE *fp)
{
	fprintf(fp, "{");
	if (items->size != 0)
	{
		Node *curNode;
		curNode = items->head->next;
		int i=0;
		while(curNode != NULL)
		{
			items->display(curNode->itemVal, fp);
			if (i != items->size -1)
			{
				fprintf(fp, ",");
			}
			curNode = curNode->next;
			i++;
		}
	}
	fprintf(fp, "}");
}

//this function displays the head and tail pointers of the list as well as the list itself
void displaySLLdebug(SLL *items, FILE *fp)
{
	fprintf(fp, "head->");
	displaySLL(items, fp);
	fprintf(fp, ",tail->{");
	if (items->size != 0)
	{
		items->display(items->tail->itemVal, fp);
	}
	fprintf(fp, "}");
}

//this function frees the list
void freeSLL(SLL *items)
{
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
		free(curNode);
		items->size--;
	}
	items->free(items->head);
	free(items);
}