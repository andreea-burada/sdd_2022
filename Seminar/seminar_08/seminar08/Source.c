#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#include "stdbool.h"
#define LINE_BUFFEER 1024

struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
};
typedef struct Employee NodeInfo;

typedef struct node
{
	struct Employee* info;
	struct node* pNext;
}Node;

typedef struct queue {
	Node* head;
	Node* tail;
}Queue;

/*functions' signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);

/*functions' signatures for list operations*/
void put(Queue*, NodeInfo*);
void printInfo(NodeInfo*);
NodeInfo* get(Queue* );
bool isEmpty(Queue);
void deleteQueue(Queue*);

void main()
{
	Queue queue = { .head = NULL, .tail = NULL };   //to initialize attributes of a struct
	/*queue.head = NULL;
	queue.tail = NULL;*/

	FILE* pFile = fopen("Data.txt", "r");
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
		NodeInfo* info = get(&queue);
		printInfo(info);

		deleteQueue(&queue);
	}
}

void deleteQueue(Queue* queue) {
	/*NodeInfo* tmp = NULL;
	while ((tmp = get(&*queue)) != NULL) {
		printInfo(tmp);
	}*/
	while (!isEmpty(*queue)) {
		NodeInfo* info = get(queue);
		printInfo(info);
		free(info->dept);
		free(info->name);
		free(info);
	}
	
}

bool isEmpty(Queue queue) {
	return (queue.head == NULL && queue.tail==NULL);
}

NodeInfo* get(Queue* queue) {
	NodeInfo* value = NULL;
	if (!isEmpty(*queue)) {
		value = queue->head->info;
		Node* tmp = queue->head;
		// if the queue had just one element
		if (queue->head == queue->tail){
			queue->head = queue->tail = NULL;
		}
		// if the queue had more than 1 element
		else {
			queue->head = tmp->pNext;
		}
		free(tmp);
	}
	return value;
}

void put(Queue* queue, NodeInfo* info) {
	Node* node = createNode(info);
	/*if (queue->tail != NULL) {
		queue->tail->pNext = node;
	}
	else {
		queue->head = node;
		queue->tail = node;
	}*/
	/*if (queue->head == NULL && queue->tail == NULL)
		queue->head = queue->tail = node;
	else {
		queue->tail->pNext = node;
		queue->tail = node;
	}*/
	if (isEmpty(*queue))
		queue->head = queue->tail = node;
	else {
		queue->tail->pNext = node;
		queue->tail = node;
	}
}

void printInfo(NodeInfo* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
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
	return node;
}