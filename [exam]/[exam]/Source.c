#define _CRT_SECURE_NO_WARNINGS
#define FILE_NAME "CPU.txt"
#define LINE_BUFFEER 1024
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>

// change this to fit the problem
typedef struct Process
{
	char* processName;
	unsigned short priority;
	unsigned int memory;
	unsigned short executionTime;
} Process, NodeInfo;

// data structure definition
typedef struct Node {
	NodeInfo* info;
	struct Node* pNext;
	struct Node* pPrev;
} Node, Queue;

// simple linked list ciruclar
typedef struct SimpleListC_Tail {
	NodeInfo* info;
	struct SimpleListC_Tail* pNext;
} SimpleListC_Tail;

NodeInfo* createNodeInfo(char*, unsigned short, unsigned int, unsigned short);
void printInfo(NodeInfo*);

/*queue specific methods*/
Node* createNode(NodeInfo*);
Queue* put_Val(Queue*, NodeInfo*);
NodeInfo* get(Queue**);
void processByPriority(Queue**, unsigned short);
void printQueue(Queue**);

/*list specific methods*/
SimpleListC_Tail* createNodeList(NodeInfo*);
void printList(SimpleListC_Tail*);

// exam task methods
SimpleListC_Tail* insertFromQueueToList(SimpleListC_Tail*, NodeInfo*);

void displayMinResource(SimpleListC_Tail*);
int calcMinTime(SimpleListC_Tail*);

SimpleListC_Tail* deleteInterval(SimpleListC_Tail*, int, int, int);

void splitList(SimpleListC_Tail**, SimpleListC_Tail**, char*);

void main()
{
	Queue* queueHead = NULL;

	// pName, prior, mem, exeT
	FILE* pFile = fopen(FILE_NAME, "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	char* pName = NULL; unsigned short prio, execT; unsigned int mem;
	int size = 0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			pName = strtok(lineBuffer, sepList);
			token = strtok(NULL, sepList);
			prio = atoi(token);
			token = strtok(NULL, sepList);
			mem = atoi(token);
			token = strtok(NULL, sepList);
			execT = atoi(token);

			NodeInfo* info = createNodeInfo(pName, prio, mem, execT);

			// insert into data structure
			queueHead = put_Val(queueHead, info);

			size++;
		}
		// print data structure
		printQueue(&queueHead);

		// do other data structure specific actions and test
		unsigned short pCond = 2;
		processByPriority(&queueHead, pCond);

		printf("\n--- Queue after processing ---\n");
		printQueue(&queueHead);

		SimpleListC_Tail* tail = NULL;
		tail = insertFromQueueToList(tail, &queueHead);

		printf("\n--- List from Queue ---\n");
		printList(tail);

		displayMinResource(tail);

		int base = 16, x = 4;
		tail = deleteInterval(tail, base, x, size);

		printf("\n--- After interval [%d-%d;%d+%d] MB delete ---\n", base, x, base, x);
		printList(tail);

		SimpleListC_Tail* newList = NULL;
		char* condProcName = "Paste Clipboard";
		splitList(&tail, &newList, condProcName);

		printf("\n--- First List ---\n");
		printList(tail);

		printf("\n--- Second List ---\n");
		printList(newList);

	}
	else
		printf("\nFile \"%s\" could not be opened\n", FILE_NAME);

	int a = 2;
}

// task 2
void processByPriority(Queue** queueHead, unsigned short priorityCondition)
{
	printf("\nProcessing all processes with priorty %d\n\n", priorityCondition);
	Queue* altQ = NULL;
	if (*queueHead) {
		while (*queueHead)
		{
			NodeInfo* toPut = get(&(*queueHead));
			altQ = put_Val(altQ, toPut);
		}
		while (altQ)
		{
			NodeInfo* toPut = get(&altQ);
			if (toPut->priority == priorityCondition)
			{
				printInfo(toPut);
				free(toPut->processName);
				free(toPut);
				toPut = NULL;
			}
			else {
				*queueHead = put_Val(*queueHead, toPut);
			}
		}
	}
}
// task 3
SimpleListC_Tail* insertFromQueueToList(SimpleListC_Tail* tail, Queue** queueHead)
{
	// we go through the queue
	while (*queueHead)
	{
		NodeInfo* extracted = get(&(*queueHead));
		// we add it to the list
		// if list empty -> head insert
		SimpleListC_Tail* toAdd2List = createNodeList(extracted);
		if (tail == NULL)
		{
			toAdd2List->pNext = toAdd2List; // circular
			tail = toAdd2List;
		}
		else
		{
			// 3 cases:
			//	- toAdd2List->memory is the smallest of all -> tail insert
			//  - toAdd2List->memory is the biggest of all -> head insert
			//  - toAdd2List->memory is in between -> we add before the first node that is smaller

			// smallest of all
			if (tail->info->memory >= toAdd2List->info->memory) {
				// tail insert
				toAdd2List->pNext = tail->pNext;
				tail->pNext = toAdd2List;
				tail = toAdd2List;
			}
			// biggest of all
			else if (tail->pNext->info->memory <= toAdd2List->info->memory) {
				// head insert
				toAdd2List->pNext = tail->pNext;
				tail->pNext = toAdd2List;
			}
			else {
				// insert at the position
				SimpleListC_Tail* aux = tail->pNext;
				while (aux->pNext->info->memory >= extracted->memory) {
					aux = aux->pNext;
				}
				toAdd2List->pNext = aux->pNext;
				aux->pNext = toAdd2List;
			}
		}

		//print for testing
		/*printf("\n----\n\n");
		printList(tail);*/
	}
	return tail;
}
// task 4
void displayMinResource(SimpleListC_Tail* tail)
{
	int minRes = calcMinTime(tail);
	int minMem = tail->info->memory;
	// print
	printf("\n\n--- Min resources: %d s. | %4d MB ---\n\n", minRes, tail->info->memory);
	if (tail == NULL) {
		printf("List is empty!\n");
		return;
	}

	int pos = 1;
	SimpleListC_Tail* aux = tail->pNext;
	tail = tail->pNext;
	if (minRes == tail->info->executionTime || minMem == tail->info->memory) {
		printf("%2d - ", pos++);
		printInfo(tail->info);
	}
	while (tail->pNext != aux) {
		tail = tail->pNext;
		if (minRes == tail->info->executionTime || minMem == tail->info->memory) {
			printf("%2d - ", pos++);
			printInfo(tail->info);
		}
	}
}
int calcMinTime(SimpleListC_Tail* tail)
{
	if (tail)
	{
		if (tail == tail->pNext)
		{
			// one element
			return tail->info->executionTime;
		}
		else
		{
			SimpleListC_Tail* aux = tail;
			int min = tail->info->executionTime;
			aux = aux->pNext; // head
			while (aux != tail)
			{
				if (aux->info->executionTime < min)
					min = aux->info->executionTime;
				aux = aux->pNext;
			}
			return min;
		}
	}
	return 0;
}
// task 5
SimpleListC_Tail* deleteInterval(SimpleListC_Tail* tail, int base, int x, int size)
{
	Node* savedTail = tail;
	bool deleteConfirm;
	// we treat the tail outside the loop
	while (savedTail == tail && savedTail->pNext != tail)
	{
		if (savedTail->info->memory <= (base + x) &&
			savedTail->info->memory >= (base - x))
		{
			Node* toDelete = savedTail;
			// redoing the circular link
			Node* tmp = tail->pNext;
			while (tmp->pNext != tail)
				tmp = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;

			tail = tmp;
			savedTail = tail;

			free(toDelete->info->processName);
			free(toDelete->info);
			free(toDelete);
			toDelete = NULL;
			size--;
		}
		else
			break;
	}
	// we check if we only have one node in the structure
	if (tail == tail->pNext && (tail->info->memory <= (base + x) &&
		tail->info->memory >= (base - x)))
	{
		// delete the head and make the list null
		free(tail->info->processName);
		free(tail->info);
		free(tail);
		tail = NULL;
		return tail;
	}
	for (int i = 0; i < size - 1; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedTail && savedTail->pNext) {
			if (savedTail->pNext->info->memory <= (base + x) &&
				savedTail->pNext->info->memory >= (base - x)) {
				Node* toDelete = savedTail->pNext;
				deleteConfirm = true;

				savedTail->pNext = savedTail->pNext->pNext;

				if (toDelete)
				{
					free(toDelete->info->processName);
					free(toDelete->info);
					free(toDelete);
				}
				toDelete = NULL;
			}
		}
		if (savedTail && deleteConfirm == false)
			savedTail = savedTail->pNext;
	}
	return tail;
}
// task 6
void splitList(SimpleListC_Tail** tailOriginal, SimpleListC_Tail** tailNewList, char* condName)
{
	if (*tailOriginal)
	{
		if (*tailOriginal == (*tailOriginal)->pNext)
		{
			if (strcmp((*tailOriginal)->info->processName, condName) == 0)
			{
				*tailNewList == NULL;
			}
			return;
		}
		else
		{
			SimpleListC_Tail* aux = *tailOriginal;
			if (strcmp(aux->info->processName, condName) == 0)
			{
				// only 2 elements
				if (aux->pNext->pNext == *tailOriginal)
				{
					*tailNewList = aux;
					(*tailNewList)->pNext = aux;

					(*tailOriginal)->pNext = *tailOriginal;
				}
				else
				{
					if (aux == *tailOriginal)
					{
						*tailNewList = NULL;
						return;
					}
					SimpleListC_Tail* oldHead = (*tailOriginal)->pNext;
					*tailNewList = *tailOriginal;
					(*tailNewList)->pNext = aux->pNext;


					(*tailOriginal) = aux;
					(*tailOriginal)->pNext = oldHead;
				}
				return;
			}
			aux = aux->pNext;
			while (aux != *tailOriginal)
			{
				if (strcmp(aux->info->processName, condName) == 0)
				{
					// only 2 elements
					if (aux->pNext == *tailOriginal && (*tailOriginal)->pNext == aux)
					{
						*tailNewList = aux;
						(*tailNewList)->pNext = aux;

						(*tailOriginal)->pNext = *tailOriginal;
					}
					else
					{
						SimpleListC_Tail* oldHead = (*tailOriginal)->pNext;
						*tailNewList = *tailOriginal;
						(*tailNewList)->pNext = aux->pNext;


						(*tailOriginal) = aux;
						(*tailOriginal)->pNext = oldHead;

					}
					return;
				}
				aux = aux->pNext;
			}
			*tailNewList = NULL;
		}
	}
	*tailNewList = NULL;
}

// --- list specific functions ---
SimpleListC_Tail* createNodeList(NodeInfo* info) {
	SimpleListC_Tail* newNode = (SimpleListC_Tail*)malloc(sizeof(SimpleListC_Tail));
	if (newNode) {
		newNode->info = info;
		newNode->pNext = NULL;
	}
	return newNode;
}
void printList(SimpleListC_Tail* tail) {
	printf("\n");
	if (tail == NULL) {
		printf("List is empty!\n");
		return;
	}
	int pos = 1;
	SimpleListC_Tail* aux = tail->pNext;
	tail = tail->pNext;
	printf("%2d - ", pos++);
	printInfo(tail->info);
	while (tail->pNext != aux) {
		tail = tail->pNext;
		printf("%2d - ", pos++);
		printInfo(tail->info);
	}
}

// --- nodeInfo specific functions ---
NodeInfo* createNodeInfo(char* pName, unsigned short pr, unsigned int mem, unsigned short exeT)
{
	NodeInfo* toReturn = (NodeInfo*)malloc(sizeof(NodeInfo));
	if (toReturn != NULL)
	{
		toReturn->processName = (char*)malloc(strlen(pName) + 1);
		strcpy(toReturn->processName, pName);
		toReturn->priority = pr;
		toReturn->memory = mem;
		toReturn->executionTime = exeT;
	}
	return toReturn;
}
void printInfo(NodeInfo* info)
{
	if (info)
		printf("Process Name: %15s; Priority: %3d, Memory: %4d MB; Exec. Time: %3d s.\n",
			info->processName, info->priority,
			info->memory, info->executionTime);
	else
		printf("No data to print!");
}

// --- queue specific functions ---
Node* createNode(NodeInfo* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node) {
		node->info = info;
		node->pNext = NULL;
		node->pPrev = NULL;
	}
	return node;
}
Queue* put_Val(Queue* queueHead, NodeInfo* info)
{
	Node* node = createNode(info);
	if (queueHead == NULL)
	{
		node->pNext = node->pPrev = node;
		queueHead = node;
	}
	else
	{
		node->pNext = queueHead;
		node->pPrev = (queueHead)->pPrev;

		(queueHead)->pPrev->pNext = node;
		(queueHead)->pPrev = node;
	}
	return queueHead;
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
void printQueue(Queue** queueHead)
{
	Queue* altQ = NULL;
	if (*queueHead) {
		printf("\n// Head/Front\n\n");
		while (*queueHead)
		{
			NodeInfo* toPut = get(&(*queueHead));
			altQ = put_Val(altQ, toPut);
			printInfo(toPut);
		}
		printf("\n// Tail/Back\n");
		while (altQ)
		{
			NodeInfo* toPut = get(&altQ);
			*queueHead = put_Val(*queueHead, toPut);
		}
	}
	else
	{
		printf("\nQueue is empty!\n");
	}
}

