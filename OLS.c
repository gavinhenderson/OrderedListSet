/*
Gavin Henderson
150010848
Assignment 2
*/

//including the necessary libraries
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ordered_list_set.h"

/*
Static function that creates a node in memory and returns
its location in a pointer
Paramater - integer that you want the node to store in data
Return - A pointer to an OLSNode
*/
static OLSNode* createNode(int v)
{	
	//Allocate and clear memory
	OLSNode* newNode = malloc(sizeof(OLSNode));
	memset(newNode, 0, sizeof(OLSNode));
	
	//Initialise variables in newNode
	newNode->data = v;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

/*
Static function that deletes the node that it is passed
Paramater - A pointer to the node that is to be deleted
*/
static void deleteNode(OLSNode* node)
{
	//Wipes the memory then gives it back to the system
	memset(node, 0, sizeof(OLSNode));
	free(node);
}

/*
Adds a new node to the list in the correct location
Parameters - A pointer to the OrderedListSet that you would like to
add a node too
- The integer value you want the added node to have
*/
void insertOLS(OrderedListSet* ols, int v)
{
	//Create temporary variables
	OLSNode* startingHead = ols->head;
	bool contains = containsOLS(ols, v);
	
	//Checks to see if the OLS already contains the integer so its not
	//added into the list again
	if(contains==true)
	{
		printf("This Ordered List already contains this element\n");
	}
	//If the list is empty the newNode is set as the head and tail
	else if(ols->size==0)
	{
		OLSNode* newNode = createNode(v);
		ols->head = newNode;
		ols->tail = newNode;
		ols->size++;
	}
	//If the newNode is going before the head then this runs
	else if(v<(startingHead->data))
	{
		OLSNode* newNode = createNode(v);
		startingHead->prev=newNode;
		newNode->next=ols->head;
		ols->head=newNode;
		ols->size++;
	}
	else
	{
		//Sets up temp variables
		OLSNode* previous = ols->head;
		OLSNode* current = ols->head;
		bool cont = true;
		//Loop that will traverse through nodes in the list
		while(cont==true)
		{
			//Runs if it gets to the end of the list and not
			//found a place for the node so places it at the tail
			if(current==NULL)
			{
				OLSNode* newNode = createNode(v);
				newNode->prev = ols->tail;
				previous->next = newNode;
				ols->tail = newNode;
				ols->size++;
				cont = false;
			}
			//Traverses to the next node
			else if(v>(current->data))
			{
				previous = current;
				current = previous->next;
			}
			//Places the node in the current position in the list
			else if(v<(current->data))
			{
				OLSNode* newNode = createNode(v);
				newNode->next=current;
				newNode->prev=previous;
				current->prev=newNode;
				previous->next=newNode;
				ols->size++;
				cont = false;
			}
		}
	}
}

/*
Checks to see if a given integer is in the list
Parameters - A pointer to the OLS that you want to check against
- The integer you want to check for
Return - A boolean that tells you wether or not it contains the intger 
*/
bool containsOLS(OrderedListSet* ols, int v)
{
	//Checks to see if the list is empty and if it is return false
	if(ols->size==0)
	{
		return false;
	}
	else
	{
		//Creates temp variables
		bool cont = true;
		OLSNode* current=ols->head;
		
		//Traverses through the list checking the data in the nodes
		while(cont)
		{
			//Returns true if its found
			if(current->data==v)
			{
				cont=false;
				return true;
			}
			//Returns false if its not found
			else if(current->next==NULL)
			{
				cont=false;
				return false;
			}
			//Continues traversing through the loop
			else
			{
				current = current->next;
			}
		}
	}
	return false;
}

/*
Remove a given integer from a list
Parameters - The OLS that you want to remove the node from
-The integer of the node you want to remove
*/
void removeOLS(OrderedListSet* ols, int v)
{
	//Sets up temp variables
	OLSNode* startingHead = ols->head;
	OLSNode* startingTail = ols->tail;
	bool contains = containsOLS(ols, v);
	
	//If the list doesn't contain the integer that wants to be removed
	//we let the user know
	if(!contains)
	{
		printf("The OLS doesnt contain this element\n");
	}
	//If the integer is the last element in the list we have to set
	//the head and tail to null then delete the node
	else if(ols->size==1)
	{
		OLSNode* oldHead = ols->head;
		ols->head=NULL;
		ols->tail=NULL;
		deleteNode(oldHead);
		ols->size--;
	}
	//If you are deleting the head this runs
	else if(startingHead->data==v)
	{
		ols->head = startingHead->next;
		OLSNode* currentHead = ols->head;
		deleteNode(startingHead);
		currentHead->prev = NULL;
		ols->size--;
	}
	//If you are deleting the tail this runs.
	else if(startingTail->data==v)
	{
		ols->tail = startingTail->prev;
		OLSNode* currentTail = ols->tail;
		deleteNode(startingTail);
		currentTail->next=NULL;
		ols->size--;
	}
	else
	{
		//Sets up temp variables
		OLSNode* current=ols->head;
		bool cont = true;
		
		//traverse through list nodes
		while(cont)
		{
			//If the node is found this runs
			if(current->data==v)
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				deleteNode(current);
				ols->size--; 
				cont=false;
			}
			//Continues traversing through the list
			else
			{
				current=current->next;
			}
		}
	}
}

/*
Deletes the ols
Parameter - the OLS that is to be deleted
*/
void deleteOLS(OrderedListSet* ols)
{
	//Sets the memory to 0 and then gives it back to the system
	memset(ols, 0, sizeof(OrderedListSet));
	free(ols);
}

/*
Creates an OLS in memory and returns a pointer
Return - Returns a pointer to the newly made OLS
*/
OrderedListSet* createOLS()
{
	//Creates the new ols in memory
	OrderedListSet* newOLS = calloc(0, sizeof(OrderedListSet));
	
	//Initialise the variables (only if the memory was successfully allocated)
	if (newOLS != NULL) {
		newOLS->size = 0;
		newOLS->head = NULL;
		newOLS->tail = NULL;
	}
	
	//Returns null if it wasnt successfully allocated
	return newOLS;
}
