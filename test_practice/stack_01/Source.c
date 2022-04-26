#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFER 256
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>

// stacks -> the topStack is the top of the stack
// NodeInfo; Node; Stack; initializeStack; isEmtpy; popStack; pushStack; peekStack; printStack; deleteStack

typedef struct Apartament
{
	int number;
	char* address;
	int floor;
	float rent;
	char* owner;
} NodeInfo;

typedef struct Node
{
	NodeInfo* info;
	struct Node* pNext;
}Stack;

/* --- functions' signature - memory management --- */
NodeInfo* createInfo(int, char*, int, float, char*);
Stack* createStack(NodeInfo*);			// this will be used inside the function pushStack if the stack is empty

/* --- functions' signature - stack specific --- */
bool isEmpty(Stack*);
void pushStack_p(Stack**, NodeInfo*);	// pushStack_p - push onto stack method using pointer to Stack*
Stack* pushStack(Stack*, NodeInfo*);
NodeInfo* popStack(Stack**);
NodeInfo* peekStack(Stack*);
void printStack(Stack**);				// stack -> flip it twice in order to display it
void printInfo(NodeInfo*);
void deleteStack_p(Stack**);			// deleteStack_p - delete the stack using pointer to Stack*
Stack* deleteStack(Stack*);

void main() {
	FILE* file = fopen("Apartments.txt", "r");
	char buffer[LINE_BUFFER], * token, separator_list[] = ",\n";
	NodeInfo* apartmentDummy = NULL;
	Stack* stack = NULL;

	if (!file) {
		printf("File could not be found. Please check the file name.\n");
	}
	else {
		printf("File opened successfully!\n");

		while (fgets(buffer, LINE_BUFFER, file)) {
			// allocate one apartment
			apartmentDummy = (NodeInfo*)malloc(sizeof(NodeInfo));
			// we parse the info
			token = strtok(buffer, separator_list);
			apartmentDummy->number = atoi(token);
			token = strtok(NULL, separator_list);
			apartmentDummy->address = (char*)malloc(strlen(token) + 1);
			strcpy(apartmentDummy->address, token);
			token = strtok(NULL, separator_list);
			apartmentDummy->floor = atoi(token);
			token = strtok(NULL, separator_list);
			apartmentDummy->rent = atof(token);
			token = strtok(NULL, separator_list);
			apartmentDummy->owner = (char*)malloc(strlen(token) + 1);
			strcpy(apartmentDummy->owner, token);

			//pushStack_p(&stack, apartmentDummy);
			stack = pushStack(stack, apartmentDummy);

			/*NodeInfo* peeked = peekStack(stack);
			printInfo(peeked);*/
		}

		printStack(&stack);

		printf("\n\nThe stack is %s\n", (isEmpty(stack) == true) ? "empty" : "NOT empty");

		//deleteStack_p(&stack);
		stack = deleteStack(stack);

		printf("\n\nWe deleted the stack.\nThe stack is %s\n", (isEmpty(stack) == true) ? "empty" : "NOT empty");


	}
	/*if (isEmpty(stack) == false)
		printf("\nNOT EMTPY!\n");*/
}

// function implementations
NodeInfo* createInfo(int number, char* address, int floor, float rent, char* owner) {
	NodeInfo* created = (NodeInfo*)malloc(sizeof(NodeInfo));
	created->number = number;
	created->address = (char*)malloc(strlen(address) + 1);
	strcpy(created->address, address);
	created->floor = floor;
	created->rent = rent;
	created->owner = (char*)malloc(strlen(owner) + 1);
	strcpy(created->owner, owner);

	return created;
}

void printInfo(NodeInfo* info) {
	if (info) {
		printf("\nNumber - %d; Address - %s; Floor - %d; Rent - %.2f; Owner - %s",
			info->number, info->address, info->floor, info->rent, info->owner);
	}
	else
	{
		printf("\nEmployee is empty.");
	}
}

void printStack(Stack** topStack) {
	Stack* auxStack = NULL;
	NodeInfo* dummy = NULL;
	if (isEmpty(*topStack))
		printf("Stack is empty!\n");
	else {
		// extracting the stack to another stack
		while (!isEmpty(*topStack)) {
			dummy = popStack(&(*topStack));
			printInfo(dummy);
			pushStack_p(&auxStack, dummy);
		}
		// reversing it back
		while (!isEmpty(auxStack)) {
			dummy = popStack(&auxStack);
			pushStack_p(&(*topStack), dummy);
		}
	}
}

Stack* createStack(NodeInfo* info) {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	newStack->info = info;
	newStack->pNext = NULL;
	return newStack;
}

bool isEmpty(Stack* topStack) {
	return (topStack == NULL) ? true : false;
}

void pushStack_p(Stack** topStack, NodeInfo* info) {
	Stack* newtopStack = createStack(info);
	// connect the node to the stack
	newtopStack->pNext = *topStack;
	// connect the stack to the node
	*topStack = newtopStack;
}

Stack* pushStack(Stack* topStack, NodeInfo* info) {
	Stack* newTop = createStack(info);
	newTop->pNext = topStack;
	return newTop;
}

NodeInfo* popStack(Stack** topStack) {
	NodeInfo* popped = NULL;

	if (isEmpty(*topStack) == false) {
		Stack* toDelete = *topStack;
		popped = (*topStack)->info;
		*topStack = (*topStack)->pNext;		// moving the next item 
		free(toDelete);
	}

	return popped;
}

NodeInfo* peekStack(Stack* topStack) {
	NodeInfo* peekedApartment = NULL;
	if (isEmpty(topStack) == false)
		peekedApartment = createInfo(topStack->info->number, topStack->info->address, topStack->info->floor, topStack->info->rent, topStack->info->owner);
	return peekedApartment;
}

void deleteStack_p(Stack** topStack) {
	NodeInfo* dummy = NULL;
	while (isEmpty(*topStack) == false) {
		dummy = popStack(&(*topStack));
		free(dummy->address);
		free(dummy->owner);
		free(dummy);
		dummy = NULL;
	}
}

Stack* deleteStack(Stack* topStack) {
	NodeInfo* toDelete = NULL;
	while (isEmpty(topStack) == false) {
		toDelete = popStack(&topStack);
		free(toDelete->address);
		free(toDelete->owner);
		free(toDelete);
		toDelete = NULL;
	}
	return topStack;
}