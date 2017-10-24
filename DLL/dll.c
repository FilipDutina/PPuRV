#if 1
	#define PRINT(a) printf a
#else
	#define PRINT(a) (void)0
#endif

#define MAXSIZE 2147483648


#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

void push(struct Node** headNode, int_least32_t newData)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = newData;

	/*test*/
	struct Node* temp = (*headNode);
	newNode->next = temp;

	/*The address of an object with automatic storage shall not be assigned
	 to another object that may persist after
	 the first object has ceased to exist ("headNode")*/

	/*newNode->next = (*headNode);*/
	newNode->previous = (struct Node*)NULL;

	if((*headNode) != NULL)
	{
		(*headNode)->previous = newNode;
	}

	(*headNode) = newNode;
}

void pop(struct Node** headNode)
{
	if((*headNode) == NULL)
	{
		PRINT(("The queue is empty, pop is not allowed!\n"));
	}
	else if(((*headNode)->previous == NULL) && ((*headNode)->next == NULL))
	{
		(*headNode) = (struct Node*)NULL;
		PRINT(("Last pop, the queue is now empty!\n"));
	}
	else
	{
		while((*headNode)->next != NULL)
		{
			(*headNode) = (*headNode)->next;
		}

		(*headNode)->previous->next = (struct Node*)NULL;
		free(*headNode);

		while((*headNode)->previous != NULL)
		{
			(*headNode) = (*headNode)->previous;
		}
	}
}

void printList(struct Node* headNode)
{
	if(headNode == NULL)
	{
		PRINT(("The queue is empty!\n"));
	}
	else
	{
		struct Node* _temp = headNode;

		PRINT(("Forward direction: "));

		while(_temp != NULL)
		{
			PRINT((" %"PRIdLEAST32, _temp->data));
			_temp = _temp->next;
		}
		PRINT(("\n"));
	}
}
