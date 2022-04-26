// debugging a classmate's problem 

//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "stdlib.h"
//#include "string.h"
//#include "memory.h"
//#include <stdbool.h>
//
//
//typedef struct Employee {
//	short code;
//	char* name;
//	char* dep;
//	double salary;
//}Employee;
//
//typedef struct node {
//	Employee* empInfo;
//	struct node* pNext;
//}Node;
//
//typedef struct Queue {
//	Node* head;
//	Node* tail;
//}Queue;
//
//
//#define LINE_BUFFER 128
//
////functions for memory management
//Employee* createEmployee(short, char*, char*, double);
//Node* createNode(Employee*);
//
////functions for list operations
//void printEmployee(Employee*);
//bool isEmpty(Queue);
//void printQueue(Node*);
//Employee* createInfo(short, char*, char*, double);
//void put(Employee*, Queue*);
//Employee* get(Queue*);
//void deleteQueue(Queue*);
//
//
//
//void main()
//{
//	Queue queue = { .head = NULL, .tail = NULL };
//	//or like this
//	//queue->head = NULL;
//	//queue->tail = NULL;
//	FILE* pFile = fopen("Data.txt", "r");
//	char* token = NULL, lineBuffer[LINE_BUFFER], * sepList = ",\n";
//	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
//	if (pFile)
//	{
//		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
//		{
//			token = strtok(lineBuffer, sepList);
//			code = atoi(token);
//			name = strtok(NULL, sepList);
//			dept = strtok(NULL, sepList);
//			token = strtok(NULL, sepList);
//			salary = atof(token);
//
//			Employee* info = createInfo(code, name, dept, salary);
//			put(info, &queue);
//
//		}
//		Employee* info = get(&queue);
//		printEmployee(info);
//		deleteQueue(&queue);
//
//	}
//
//}
//
//void deleteQueue(Queue* queue)
//{
//	Employee* emp = NULL;
//	while ((emp = get(queue)) != NULL)
//	{
//		printEmployee(emp);
//		free(emp->dep);
//		free(emp->name);
//		free(emp);
//	}
//}
//Employee* createInfo(short code, char* name, char* dept, double salary)
//{
//	struct Employee* emp = (Employee*)malloc(sizeof(Employee));
//	emp->code = code;
//	emp->name = (char*)malloc(strlen(name) + 1);
//	strcpy(emp->name, name);
//	emp->dep = (char*)malloc(strlen(dept) + 1);
//	strcpy(emp->dep, dept);
//	emp->salary = salary;
//	return emp;
//}
//
//void put(Employee* emp, Queue* queue)
//{
//	Node* node = createNode(emp);
//	if (isEmpty(*queue)==true)
//	{
//		queue->head = queue->tail = node;
//	}
//	else {
//		queue->tail->pNext = node;
//		queue->tail = node;
//	}
//
//}
//
//Employee* get(Queue* queue)
//{
//	Employee* value = NULL;
//	if (isEmpty(*queue)==false)
//	{
//		value = queue->head->empInfo;
//
//		Node* tmp = queue->head;
//
//		if (queue->head == queue->tail)
//		{
//			queue->head = queue->tail = NULL;
//		}
//		else {
//			queue->head = tmp->pNext;
//		}
//		free(tmp);
//	}
//	return value;
//}
////Employee* get(Queue* queue) {
////
////	Employee* emp = NULL;
////	if (!isEmpty(queue))
////	{
////		if (queue->head == queue->tail)
////		{
////			emp = queue->head->empInfo;
////			queue->head = queue->tail = NULL;
////		}
////		else {
////			emp = queue->head->empInfo;
////			queue->head = queue->head->pNext;
////		}
////	}
////	return emp;
////
////}
//
//bool isEmpty(Queue queue)
//{
//	return (queue.head == NULL && queue.tail == NULL);
//}
//
//void printEmployee(Employee* emp)
//{
//	printf("Code: %d\n Name: %s\n Department: %s\n Salary %f\n\n", emp->code, emp->name, emp->dep, emp->salary);
//}
//
//
//Employee* createEmployee(short code, char* dep, char* name, double salary)
//{
//	Employee* emp = (Employee*)malloc(sizeof(Employee));
//	emp->code = code;
//	emp->name = (char*)malloc(strlen(name) + 1);
//	strcpy(emp->name, name);
//	emp->dep = (char*)malloc(strlen(dep) + 1);
//	strcpy(emp->dep, dep);
//	emp->salary = salary;
//
//	return emp;
//}
//
//Node* createNode(Employee* emp)
//{
//	Node* node = (Node*)malloc(sizeof(Node));
//	node->empInfo = emp;
//	node->pNext = NULL;
//	return node;
//}

// debugging code from my professor's GitHub
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "memory.h"
#include "string.h"
struct Student
{
	char* name;
};
typedef struct Student Student;
struct Node //a node from the list
{
	Student* info;
	struct Node* pNext;
};
typedef struct Node Node;

/*function headers for memory manipulation*/
Student* createInfo(char* name);
Node* createNode(Student* info);

/*function headers for list operations*/
//insert - delete - traversal
void insertHead(Node** head, Student* info);
Node* insertTail(Node* head, Student* info);
void deletePosition(Node** head, int pos);
void printList(Node* head);

void main() {
	FILE* pFile = fopen("Names.txt", "r");
	Node* list = NULL;

	char* names[100];
	static short freq[26];
	char** agenda[26];
	memset(names, NULL, 100 * sizeof(char*));
	memset(agenda, NULL, 26 * sizeof(char*));
	if (pFile) {
		char buffer[128];
		int index = 0;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile)) {
			names[index] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(names[index++], buffer);
			int pos = *buffer - 'A';
			freq[pos]++;
			fscanf(pFile, "%s", buffer);
		}
		//for (int i = 0; i < 99; i++)
		//	for (int j = i + 1; j < 100; j++)
		//	{
		//		if (names[j] != NULL)
		//		{
		//			//if (names[i][0] > names[j][0]) {
		//			if (*names[i] > *names[j]) {
		//				char* temp = names[i];
		//				names[i] = names[j];
		//				names[j] = temp;
		//			}
		//		}
		//	}
		short temp[26];
		for (int i = 0; i < 26; i++)
			temp[i] = freq[i];
		for (int i = 0; i < 99; i++)
			if (names[i])
			{
				int pos = *names[i] - 'A';
				if (agenda[pos] == NULL)
					agenda[pos] = (char**)malloc(freq[pos] * sizeof(char*));
				agenda[pos][freq[pos] - 1] = (char*)malloc((strlen(names[i]) + 1) * sizeof(char));
				strcpy(agenda[pos][freq[pos] - 1], names[i]);
				freq[pos]--;
			}
		for (int i = 0; i < 26; i++)
		{
			if (agenda[i])
			{
				printf("Group %c\n", i + 'A');
				for (int j = 0; j < temp[i]; j++)
				{
					printf("Name %s\n", agenda[i][j]);

					//create the Student* info
					Student* student = createInfo(agenda[i][j]);
					//insert the name into the list
					//insertHead(&list, student);
					list = insertTail(list, student);

				}
			}
		}
		printList(list);
	}
	int a = 2;
}

Student* createInfo(char* name)
{
	Student* student = (Student*)malloc(sizeof(Student));
	student->name = (char*)malloc(strlen(name) + 1);
	strcpy(student->name, name);
	return student;
}

Node* createNode(Student* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->pNext = NULL;
	return node;
}
void insertHead(Node** head, Student* info)
{
	Node* node = createNode(info);
	//1. to connect the node to the structure
	node->pNext = *head;
	//2. to connect the structure to the node
	*head = node;
}
Node* insertTail(Node* head, Student* info)
{
	Node* node = createNode(info);
	//1. to connect the node to the structure
	if (head == NULL)
		head = node;
	else
	{
		//2. to connect the structure to the node
		Node* tmp = head;
		while (tmp->pNext)
			tmp = tmp->pNext;
		tmp->pNext = node;
	}
	return head;
}
void deletePosition(Node** head, int pos);
void printList(Node* head)
{
	for (; head; head = head->pNext)
	{
		printf("Student Node: %s\n", head->info->name);
	}
}