#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <stdbool.h>

#define FILE_NAME "Data.txt"
#define BUFFER_SIZE 128

typedef struct Employee {
	int code;
	char* name;
	char* dep;
	double salary;
}Employee;

typedef struct Node {
	Employee* info;
	struct Node* next;
} Node;


Node* insertHead(Node* tail, Employee* info);
Node* insertTail(Node* tail, Employee* info);
Node* insertNthPos(Node* tail, Employee* info, int pos);
void deleteNthPos(Node** tail, int pos);
//Node* deleteNthPos(Node** tail, int pos);
Node* createNode(Employee* info);
Employee* createInfo(int code, char* name, char* dep, double salary);
void printList(Node* tail);

void main() {
	FILE* file = fopen(FILE_NAME, "r");
	Node* tail = NULL;
	char buffer[BUFFER_SIZE], sep_list[] = ",\n", * token;
	int index = 0;

	if (file) {
		printf("File \"%s\" opened!\n", FILE_NAME);
		while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
			Employee* emp = (Employee*)malloc(sizeof(Employee));
			token = strtok(buffer, sep_list);
			emp->code = atoi(token);
			token = strtok(NULL, sep_list);
			emp->name = (char*)malloc(strlen(token) + 1);
			strcpy(emp->name, token);
			token = strtok(NULL, sep_list);
			emp->dep = (char*)malloc(strlen(token) + 1);
			strcpy(emp->dep, token);
			token = strtok(NULL, sep_list);
			emp->salary = atof(token);
			index++;

			tail = insertHead(tail, emp);

			//printf("\nEmployee %d %s %s %f", emp->code, emp->name, emp->dep, emp->salary);

		}

		printList(tail);


		printf("\nAfter insertion \n");
		Employee* e1 = createInfo(21000, "Caramihai Athena", "IT", 32000);
		int pos = 11;
		tail = insertNthPos(tail, e1, pos);
		printList(tail);

		printf("\n\n\nAfter deletion\n\n");
		//tail = deleteNthPos(&tail, 1);
		deleteNthPos(&tail, 1);
		printList(tail);

	}
	else {
		printf("File \"%s\" could not be opened.\n", FILE_NAME);
	}

	int a = 2;
}
void deleteNthPos(Node** tail, int pos)
{
	Node* toDelete = NULL;

	if (pos <= 1)
	{
		toDelete = (*tail)->next;
		(*tail)->next = toDelete->next;
	}
	else
	{
		Node* tmp = (*tail)->next;
		for (int i = 0; i < pos - 1; i++)
		{
			tmp = tmp->next;
		}
		if ((*tail) == (*tail)->next)
		{
			toDelete = tmp->next;
			tmp->next = NULL;
		}
		//if we have more than one element
		else
		{
			toDelete = tmp->next;
			tmp->next = tmp->next->next;
		}
	}
	if (toDelete)
	{
		free(toDelete->info->name);
		free(toDelete->info->dep);
		free(toDelete->info);
		free(toDelete);
	}

	//return toDelete;
}

Node* insertNthPos(Node* tail, Employee* info, int pos)
{
	if (tail == NULL)
	{
		return NULL;
	}
	Node* node = createNode(info);
	Node* p = tail->next;
	do
	{
		for (int i = 1; i < pos - 1; i++)
		{
			p = p->next;
		}
		//if we insert at first position
		if (pos == 1)
		{
			tail = insertHead(tail, info);
		}
		// if we have only one element
		if (tail == tail->next)
		{
			tail->next = node;
			node->next = tail;
			tail = node;	// we move the tail
		}
		// we have more than one element
		else
		{
			node->next = p->next;
			// Adding newly allocated node after p.
			p->next = node;
			// Checking for the last node.
			if (p == tail)
				tail = node;
		}
		return tail;

		p = p->next;
	} while (p != tail->next);

	printf("%s", " not present in the list.");
	return tail;
}

Node* insertTail(Node* tail, Employee* info) {
	Node* node = createNode(info);
	// if the list is empty
	if (tail == NULL)
	{
		tail = node;
		tail->next = tail;
	}
	//if we have elements in the list
	else
	{
		// if we have only one element
		if (tail == tail->next)
		{
			tail->next = node;
			node->next = tail;
			tail = node;	// we move the tail
		}
		else {
			//if we have more than one element
			node->next = tail->next;
			tail->next = node;
			tail = node;
		}
	}
}

Node* insertHead(Node* tail, Employee* info)
{
	Node* node = createNode(info);
	// if the list is empty
	if (tail == NULL)
	{
		node->info = info;
		tail = node;
		node->next = tail;
	}
	//if we have elements in the list
	else
	{
		node->next = tail->next;
		tail->next = node;
	}

	return tail;
}


// function for printing the list;
// displays a message if the list is empty
void printList(Node* tail) {
	if (tail != NULL)
	{
		Node* saved = tail->next;
		tail = tail->next;
		printf("\nCode: %d; Name: %s; Department: %s; Salary: %.3f", tail->info->code, tail->info->name, tail->info->dep, tail->info->salary);
		while (tail->next != saved)
		{
			tail = tail->next;
			printf("\nCode: %d; Name: %s; Department: %s; Salary: %.3f", tail->info->code, tail->info->name, tail->info->dep, tail->info->salary);
		}
	}
	else
		printf("\nList is empty!\n");
}

Node* createNode(Employee* info) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->next = NULL;

	return node;
}

Employee* createInfo(int code, char* name, char* dep, double salary)
{
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->dep = (char*)malloc(strlen(dep) + 1);
	strcpy(emp->dep, dep);
	emp->salary = salary;
	return emp;
}