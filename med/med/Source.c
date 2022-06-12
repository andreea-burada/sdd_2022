#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>
//keyboad - stdin
//console - stdout
#define LINE_BUFFER 128
typedef struct Employee {
	short code;
	char* name;
	char* department;
	double salary;
}Employee;
//typedef struct Employee Employee;
typedef struct Node
{
	Employee* info;
	struct Node* pNext;
}Node;

typedef struct Node Stack;
/* functions' signatures for memory management*/
Employee * createInfo(short, char*, char*, double);
Node* createNode(Employee*);
/* functions' signatures for list operations*/
Stack * push(Stack*, Employee*);
Employee* pop(Stack**);
Employee* peek(Stack*);
bool isEmpty(Stack*);
void deleteStack(Stack**);
void printInfo(Employee*);
Stack* printStack(Stack*);
void deleteEmployee(char*, Stack*);
void main()
{
	Stack* stack = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	char lineBuffer[LINE_BUFFER], * token, sep_list[] = ",\n";
	Employee* emp = NULL;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			emp = (Employee*)malloc(sizeof(Employee));
			//parsing the code
			token = strtok(lineBuffer, sep_list);
			emp->code = atoi(token);

			//parsing the name
			token = strtok(NULL, sep_list);
			emp->name = (char*)malloc(strlen(token) + 1);
			strcpy(emp->name, token);

			//parsing the dept
			token = strtok(NULL, sep_list);
			emp->department = (char*)malloc(strlen(token) + 1);
			strcpy(emp->department, token);

			//parsing the salary
			token = strtok(NULL, sep_list);
			emp->salary = atof(token);

			stack = push(stack, emp);
		}
		Employee* emp = pop(&stack);
		printInfo(emp);
		stack = printStack(stack);
		deleteEmployee("Testing", emp);
		stack = printStack(stack);
		deleteStack(&stack);


	}
}

void printInfo(Employee* emp)
{
	printf("Code: %d - Name: %s - Dept: %s - Salary: %f\n",
		emp->code,
		emp->name,
		emp->department,
		emp->salary);
}

Stack* printStack(Stack* stack)
{
	Stack* tmp = NULL;
	while (stack)
	{
		Employee* emp = pop(&stack);
		printInfo(emp);
		tmp = push(tmp, emp);
	}
	while (tmp)
		stack = push(stack, pop(&tmp));
	return stack;
}
Employee* createInfo(short code, char* name, char* dept, double salary)
{
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->department = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->department, dept);
	emp->salary = salary;
	return emp;
}

Node* createNode(Employee* emp)
{
	//declare and allocate memory
	Node* node = (Node*)malloc(sizeof(Node));
	//initialize variable
	node->info = emp;
	node->pNext = NULL;

	//return value
	return node;
}
//retrieving the first element
Employee* peek(Stack* topStack)
{
	Employee* emp = NULL;
	if (!isEmpty(topStack))
	{
		emp = createInfo(topStack->info->code,
			topStack->info->name,
			topStack->info->department,
			topStack->info->salary);
	}
	return emp;
}

bool isEmpty(const Stack* topStack)
{
	return (topStack == NULL);
}

Employee* pop(Stack** topStack)
{
	Employee* emp = NULL;
	if (!isEmpty(*topStack))
	{
		emp = (*topStack)->info;
		Node* aux = *topStack;
		*topStack = aux->pNext;
		free(aux);
	}
	return emp;
}

Stack* push(Stack* topStack, Employee* info)
{
	Node* node = createNode(info);
	node->pNext = topStack;
	//*topStack = node or(void function) 
	return node;
}



void deleteStack(Stack** topStack)
{
	Employee* emp = NULL;
	while ((emp = pop(&*topStack)) != NULL)
	{
		printInfo(emp);
		free(emp->department);
		free(emp->name);
		free(emp);
	}
}
//delete the employee of a given department
void deleteEmployee(char* dept, Stack* stack)
{
	Stack* auxStack = NULL;
	while ((stack))
	{
		if (strcmp((stack)->info->department, dept))
		{
			Employee* auxE = pop(stack);
			auxStack = push(auxStack, auxE);
			break;
		}
		Employee* auxE = pop(stack);
		auxStack = push(auxStack, auxE);
	}
	if ((stack) != NULL)
	{
		free(pop(stack)->department);
	}
	while (auxStack)
	{
		Employee* auxE2 = pop(&auxStack);
		(stack) = push((stack), auxE2);
	}

}