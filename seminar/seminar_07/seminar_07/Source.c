/*-------------------- seminar 07 --------------------*/
// working with stacks
// push, pop, peek, isempty
#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFER 128
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>

typedef struct Employee {
	short code;
	char* name;
	char* department;
	double salary;
}Employee;
//typedef struct Employee Employee;

typedef struct Node {
	Employee* info;
	struct Node* pNext;
}Node;

typedef struct Node Stack;

/* functions' signatures for memory management */
Employee* createInfo(short, char*, char*, double);
Node* createNode(Employee*);

/* functions' signatures for stack operations */
// push
void push(Stack**, Employee*);
// pop
Employee* pop(Stack**); // Stack** because we change the stack
// peek
Employee* peek(const Stack*);
// isEmpty
bool isEmpty(const Stack*);
// delete
void deleteStack(Stack**);
// display
void displayStack(Stack**);
void printInfo(Employee*);

void main() {
	FILE* pFile = fopen("Data.txt", "r");
	char lineBuffer[LINE_BUFFER], *token, separator_list[] = ",\n";
	Employee* emp = NULL;
	Stack* stack = NULL;

	if (pFile) {
		//fgets(lineBuffer, LINE_BUFFER, pFile);
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile)) {
			emp = (Employee*)malloc(sizeof(Employee));
			// we initially pass the buffer then we pass NULL so that we do not lose our data

			// parsing the code
			token = strtok(lineBuffer, separator_list);
			emp->code = atoi(token);

			// parsing the name
			token = strtok(NULL, separator_list);
			emp->name = (char*)malloc(strlen(token) + 1);
			strcpy(emp->name, token);

			// parsing the department
			token = strtok(NULL, separator_list);
			emp->department = (char*)malloc(strlen(token) + 1);
			strcpy(emp->department, token);

			// parsing the salary
			token = strtok(NULL, separator_list);
			emp->salary = atof(token);

			push(&stack, emp);

			emp = peek(stack);
			//printInfo(emp);
		}
		displayStack(&stack);
		printf("-----------------\n");
		/*if (!isEmpty(stack))
			printf("not empty\n");
		else
			printf("empty\n");*/
	}
	deleteStack(&stack);
	printf("---after stack deletion---\n");
	displayStack(&stack);
	/*if (!isEmpty(stack))
		printf("not empty\n");
	else
		printf("empty\n");*/

	int a = 2;
}

Employee* createInfo(short code, char* name, char* dep, double salary) {
	Employee* newEmp = (Employee*)malloc(sizeof(Employee));
	newEmp->code = code;
	newEmp->name = (char*)malloc(strlen(name) + 1);
	strcpy(newEmp->name, name);
	newEmp->department = (char*)malloc(strlen(dep) + 1);
	strcpy(newEmp->department, dep);
	newEmp->salary = salary;

	return newEmp;
}

Node* createNode(Employee* emp) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = emp;
	newNode->pNext = NULL;
	return newNode;
}

// push
// ** MEAN DEREFERENCING IN THE FUNCTION
void push(Stack** topStack, Employee* info) {
	Stack* newTop = createNode(info);
	// 1. connect the node to the stack
	newTop->pNext = *topStack;
	// 2. connect the stack to the node
	*topStack = newTop;
}

// pop - delete from the head
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
		toReturn = createInfo(topStack->info->code, topStack->info->name, topStack->info->department, topStack->info->salary);
	return toReturn;
}

// delete
void deleteStack(Stack** topStack) {
	Employee* dummy = NULL;
	while (!isEmpty(*topStack)) {
		dummy = pop(&(*topStack));
		free(dummy->name);
		free(dummy->department);
		free(dummy);
		dummy = NULL;
	}
}

// display
void displayStack(Stack** topStack) {
	Stack* auxStack = NULL;
	Employee* emp = NULL;
	if (isEmpty(*topStack))
		printf("Stack is empty!\n");
	else {
		// extracting the stack to another stack
		while (!isEmpty(*topStack)) {
			emp = pop(&(*topStack));
			printInfo(emp);
			push(&auxStack, emp);
		}
		// reversing it back
		while (!isEmpty(auxStack)) {
			emp = pop(&auxStack);
			push(&(*topStack), emp);
		}
	}
}

bool isEmpty(const Stack* topStack) {
	return (topStack == NULL);
}

void printInfo(Employee* emp) {
	printf("Code: %d; Name: %s; Department: %s; Salary: %.2f\n", emp->code, emp->name, emp->department, emp->salary);
}
