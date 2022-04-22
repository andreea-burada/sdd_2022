/*-------------------- seminar 05 --------------------*/
// working with lists
// ways of storing data in .txt files in order to work with data structures
#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFER 128
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "memory.h"

// keyboard - stdin
// console - stdout

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

/* functions' signatures for memory management */
Employee* createInfo(short, char*, char*, double);
Node* createNode(Employee*);

/* functions' signatures for list operations */
// inserting tail
Node* insertHead(Node*, Employee*);
void insertTail(Node**, Employee*);
Node* insertListPos(Node*, Employee*, int);
Node* deleteListPos(Node*, int);
void printList(const Node*);

void main() {
	FILE* pFile = fopen("Data.txt", "r");
	char lineBuffer[LINE_BUFFER], * token, separator_list[] = ",\n";
	Employee* emp = NULL;
	Node* list = NULL;

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

			insertTail(&list, emp);
		}
		printList(list);

		Employee* e1 = createInfo(20001, "Badulescu Cristian", "Cybersecurity", 2100.2);
		int pos = 10;
		list = insertListPos(list, e1, pos);

		printf("\n---After position insert---\n");
		printList(list);

		list = deleteListPos(list, pos);
		printf("\n---After position deletion---\n");
		printList(list);
	}
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

Node* insertHead(Node* head, Employee* emp) {
	Node* newHead = createNode(emp);
	newHead->pNext = head;
	head = newHead;
	return head;
}

Node* insertListPos(Node* head, Employee* emp, int pos) {
	Node* newNode = createNode(emp);
	if (pos <= 1) {
		// insert at the head	
		/*newNode->pNext = head;
		head = newNode;*/
		head = insertHead(head, emp);
	}
	else {
		// insert at the position
		Node* aux = head;
		int index = 1;
		while (index++ < (pos - 1) && aux->pNext) {
			aux = aux->pNext;
		}
		//if (aux->pNext) {
		//	// newNode->pNext = aux->pNext;
		//}
		//aux->pNext = newNode;
		aux->pNext = insertHead(aux->pNext, emp);
	}
	return head;
}

void insertTail(Node** head, Employee* emp) {
	Node* newTail = createNode(emp);
	// 1. connect node to the structure
	if (*head == NULL) {
		*head = newTail;
	}
	// 2. connect the structure to the node
	else {
		Node* tmp = *head;
		while (tmp->pNext) {
			tmp = tmp->pNext;
		}
		tmp->pNext = newTail;
	}
}

Node* deleteListPos(Node* head, int pos) {
	int index = 1;
	// we need to save the node we want to delete in order to deallocate memory
	Node* aux = NULL;
	if (pos <= 1) {
		// head deletion
		aux = head;
		head = head->pNext;
	}
	else {
		Node* tmp = head;
		while (index++ < (pos - 1) && tmp->pNext) {
			tmp = tmp->pNext;
		}
		if (tmp->pNext) {
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
		}
		else {
			aux = tmp;
			Node* tmp = head;
			while (tmp->pNext->pNext) {
				tmp = tmp->pNext;
			}
			tmp->pNext = NULL;
		}
	}
	if (aux) {
		free(aux->info->name);
		free(aux->info->department);
		free(aux->info);
		free(aux);
	}
	return head;
}

void printInfo(Employee* emp) {
	printf("Code: %d; Name: %s; Department: %s; Salary: %.2f\n", emp->code, emp->name, emp->department, emp->salary);
}

void printList(const Node* head) {
	while (head) {
		printInfo(head->info);
		head = head->pNext;
	}
}