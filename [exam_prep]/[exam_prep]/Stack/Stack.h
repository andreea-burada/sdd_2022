
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Stack - Simple List --------------*/

// data structure definition
typedef struct Node {
	Employee* info;
	struct Node* pNext;
} Node, Stack;

/*stack specific methods*/
Node* createNode(Employee*);
bool isEmpty(const Stack*);

Stack* push_Val(Stack*, Employee*);
void push_Ref(Stack**, Employee*);

Employee* pop(Stack**);

Employee* peek(const Stack*);

Stack* deleteStack_Val(Stack*);
void deleteStack_Ref(Stack**);

Stack* deleteStackCond_Val(Stack*);
void deleteStackCond_Ref(Stack**);

void printStack(Stack**);


// implementation
Node* createNode(Employee* emp) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode)
	{
		newNode->info = emp;
		newNode->pNext = NULL;
	}
	return newNode;
}
bool isEmpty(const Stack* topStack) {
	return (topStack == NULL);
}



Stack* push_Val(Stack* topStack, Employee* info) {
	Stack* newTop = createNode(info);
	// 1. connect the node to the stack
	newTop->pNext = topStack;
	// 2. connect the stack to the node
	topStack = newTop;

	return topStack;
}
void push_Ref(Stack** topStack, Employee* info) {
	Stack* newTop = createNode(info);
	// 1. connect the node to the stack
	newTop->pNext = *topStack;
	// 2. connect the stack to the node
	*topStack = newTop;
}



Employee* pop(Stack** topStack) {
	Employee* toReturn = NULL;	// in case we have no data
	if (!isEmpty(*topStack)) {
		toReturn = (*topStack)->info;
		Node* toDelete = *topStack;
		*topStack = (*topStack)->pNext;
		free(toDelete);	// we do not deallocate the Employee* from the Node* because we will lose the information
	}
	return toReturn;
}



Employee* peek(const Stack* topStack) {
	Employee* toReturn = NULL;
	if (!isEmpty(topStack))
		toReturn = createNodeInfo(topStack->info->code, 
					topStack->info->name, 
					topStack->info->dept, 
					topStack->info->salary);
	return toReturn;
}



Stack* deleteStack_Val(Stack* topStack) {
	Employee* dummy = NULL;
	while (!isEmpty(topStack)) {
		dummy = pop(&topStack);
		free(dummy->name);
		free(dummy->dept);
		free(dummy);
		dummy = NULL;
	}
	return topStack;
}
void deleteStack_Ref(Stack** topStack) {
	Employee* dummy = NULL;
	while (!isEmpty(*topStack)) {
		dummy = pop(&(*topStack));
		free(dummy->name);
		free(dummy->dept);
		free(dummy);
		dummy = NULL;
	}
}



Stack* deleteStackCond_Val(Stack* topStack) {
	Stack* auxStack = NULL;
	Employee* emp = NULL;
	if (isEmpty(topStack))
		printf("\nStack is empty!\n");
	else {
		printf("\n// Top\n\n");
		// extracting the stack to another stack
		while (!isEmpty(topStack)) {
			emp = pop(&(topStack));
			printInfo(emp);
			push_Ref(&auxStack, emp);
			//*topStack = push_Val(topStack, emp);
		}
		printf("\n// Base\n");
		// reversing it back
		while (!isEmpty(auxStack)) {
			emp = pop(&auxStack);
			if (emp->code % 2 == 0)
			{
				free(emp->dept);
				free(emp->name);
				free(emp);
				emp = NULL;
			}
			else
			{
				push_Ref(&(topStack), emp);
				//*topStack = push_Val(topStack, emp);
			}
		}
	}
	return topStack;
}
void deleteStackCond_Ref(Stack** topStack) {
	Stack* auxStack = NULL;
	Employee* emp = NULL;
	if (isEmpty(*topStack))
		printf("\nStack is empty!\n");
	else {
		printf("\n// Top\n\n");
		// extracting the stack to another stack
		while (!isEmpty(*topStack)) {
			emp = pop(&(*topStack));
			printInfo(emp);
			push_Ref(&auxStack, emp);
			//*topStack = push_Val(*topStack, emp);
		}
		printf("\n// Base\n");
		// reversing it back
		while (!isEmpty(auxStack)) {
			emp = pop(&auxStack);
			if (emp->code % 2 == 0)
			{
				free(emp->dept);
				free(emp->name);
				free(emp);
				emp = NULL;
			}
			else
			{
				push_Ref(&(*topStack), emp);
				//*topStack = push_Val(*topStack, emp);
			}
		}
	}
	return topStack;
}



void printStack(Stack** topStack) {
	Stack* auxStack = NULL;
	Employee* emp = NULL;
	if (isEmpty(*topStack))
		printf("\nStack is empty!\n");
	else {
		printf("\n// Top\n\n");
		// extracting the stack to another stack
		while (!isEmpty(*topStack)) {
			emp = pop(&(*topStack));
			printInfo(emp);
			push_Ref(&auxStack, emp);
			//*topStack = push_Val(*topStack, emp);
		}
		printf("\n// Base\n");
		// reversing it back
		while (!isEmpty(auxStack)) {
			emp = pop(&auxStack);
			push_Ref(&(*topStack), emp);
			//*topStack = push_Val(*topStack, emp);
		}
	}
}