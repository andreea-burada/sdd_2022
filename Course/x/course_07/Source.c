#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFEER 1024
#define FILE_NAME "Data.txt"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#include <stdbool.h>

typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} NodeInfo;

typedef struct node
{
	struct Employee* info;
	struct node* pNext;
	struct node* pPrev;
} Node, Queue;

/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);

/*functions signatures for list operations*/
bool isEmpty(Queue*);
void put(Queue**, NodeInfo*);
NodeInfo* get(Queue**);
NodeInfo* peek(const Queue*);
void printInfo(NodeInfo*);

void main()
{
	Queue* queue = NULL;

	FILE* pFile = fopen(FILE_NAME, "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			token = strtok(lineBuffer, sepList);
			code = atoi(token);
			name = strtok(NULL, sepList);
			dept = strtok(NULL, sepList);
			token = strtok(NULL, sepList);
			salary = atof(token);

			NodeInfo* info = createInfo(code, name, dept, salary);

			put(&queue, info);

		}
		NodeInfo* info = NULL;
		while ((info = get(&queue)) != NULL)
			printInfo(info);
	}
	else
		printf("\nFile \"%s\" could not be found.\n", FILE_NAME);

	/*NodeInfo* extracted = get(&queue);
	printInfo(extracted);*/
}



NodeInfo* createInfo(short code, char* name, char* dept, double salary)
{
	struct Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->dept = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->dept, dept);
	emp->salary = salary;
	return emp;
}

Node* createNode(NodeInfo* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->pNext = NULL;
	node->pPrev = NULL;
	return node;
}

bool isEmpty(Queue* queueHead) {
	return queueHead == NULL;
}

void put(Queue** queueHead, NodeInfo* info)
{
	Node* node = createNode(info);
	if (*queueHead == NULL)
	{
		node->pNext = node->pPrev = node;
		*queueHead = node;
	}
	else
	{
		node->pNext = *queueHead;
		node->pPrev = (*queueHead)->pPrev;

		(*queueHead)->pPrev->pNext = node;
		(*queueHead)->pPrev = node;
	}
}

NodeInfo* get(Queue** queueHead)
{
	NodeInfo* value = NULL;
	if (*queueHead != NULL)
	{
		value = (*queueHead)->info;
		Node* tmp = *queueHead;
		if (tmp->pNext != tmp && tmp->pPrev != tmp)
		{
			tmp->pNext->pPrev = tmp->pPrev;
			tmp->pPrev->pNext = tmp->pNext;
			*queueHead = tmp->pNext;
		}
		else
			*queueHead = NULL;
		free(tmp);
	}
	return value;
}

NodeInfo* peek(const Queue* queueHead) {
	NodeInfo* peeked = NULL;
	if (isEmpty(queueHead) == false) {
		peeked = queueHead->info;
	}
	return peeked;
}

void printInfo(NodeInfo* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
}