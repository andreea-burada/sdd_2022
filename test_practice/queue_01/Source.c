#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFER 128

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"

/* --- queue implementation with circular double linked list --- */

typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} NodeInfo, Employee;

typedef struct node
{
	struct Employee* info;
	struct node* pNext;
	struct node* pPrev;
} Node, Queue;

// --- signatures ---
NodeInfo* createInfo(short, char*, char*, double);
void putQueue(Queue**, NodeInfo*);
void printInfo(NodeInfo*);
NodeInfo* getQueue(Queue**);

void main()
{
	Queue* queue = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFER], * sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			Employee* dummy = (Employee*)malloc(sizeof(Employee));

			token = strtok(lineBuffer, sepList);
			dummy->code = atoi(token);

			token = strtok(NULL, sepList);
			dummy->name = (char*)malloc(strlen(token) + 1);

			strcpy(dummy->name, token);
			token = strtok(NULL, sepList);

			dummy->dept = (char*)malloc(strlen(token) + 1);
			strcpy(dummy->dept, token);

			token = strtok(NULL, sepList);
			dummy->salary = atof(token);

			// NodeInfo* info = createInfo(code, name, dept, salary);

			putQueue(&queue, dummy);

		}
		NodeInfo* info = NULL;
		while ((info = getQueue(&queue)) != NULL)
			printInfo(info);
	}
}

void putQueue(Queue** head, NodeInfo* info) {
	Queue* newHead = (Queue*)malloc(sizeof(Queue));
	newHead->info = info;
	//newHead->pNext = newHead;
	//newHead->pPrev = newHead;
	if (*head != NULL) {
		if ((*head)->pNext == (*head)) {
			(*head)->pNext = newHead;
			(*head)->pPrev = newHead;
			newHead->pNext = *head;
			newHead->pPrev = *head;
		}
		else {
			(*head)->pPrev->pNext = newHead;
			(*head)->pPrev = newHead;
			newHead->pPrev = (*head)->pPrev;
			newHead->pNext = *head;
		}
	}
	else {
		*head = newHead;
		newHead->pNext = newHead;
		newHead->pPrev = newHead;
	}
}

NodeInfo* getQueue(Queue** head) {
	NodeInfo* returned = NULL;
	if (*head != NULL) {
		if ((*head) == (*head)->pPrev) {
			returned = (*head)->info;
			(*head)->pNext = NULL;
			(*head)->pPrev = NULL;
			*head = NULL;
		}
		else {
			returned = (*head)->info;
			Node* dummy = *head;
			(*head)->pPrev->pNext = (*head)->pNext;
			(*head)->pNext->pPrev = (*head)->pPrev;
			*head = (*head)->pNext;
			free(dummy);
		}
	}

	return returned;
}

void printInfo(NodeInfo* info) {
	printf("Employee - [%d]: %s; Department: %s;\n\tSalary: %.3f\n", info->code, info->name, info->dept, info->salary);
}