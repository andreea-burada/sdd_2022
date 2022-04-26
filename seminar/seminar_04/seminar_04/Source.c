#include "stdio.h"
#include "string.h"

short letters[26], copy[26];						 // global declaration for the frequency and indexes array

typedef struct Student {
	char* name;
}Student;

struct Node {
	Student* info;
	struct Node* pNext;
};

typedef struct Node Node;

/*function signature/prototype for memory management*/
Student* createInfo(char*);
Node* createNode(Student*);				 // we only need to pass the useful information (Student*) because pNext is NULL for
										 // a standalone Node
/*function signature/prototype for list operations - insertion, deletion, search/traversing*/
void insertHead(Node**, Student*);
Node* insertTail(Node*, Student*);
void printList(Node*);

void main()
{
	Node* list = NULL;					 // at the start it is initialized with NULL
	FILE* pFile = fopen("Names.txt", "r");
	char buffer[128];
	char* names[50];					 // sizeof names will be 50 * 4 bytes
	char** agenda[26];
	int index = 0;

	// initiating names
	for (int i = 0; i < 50; i++) {
		names[i] = NULL;
	}
	// use memset

	// initiating agenda
	for (int i = 0; i < 26; i++) {
		agenda[i] = NULL;
	}
	// use memset

	memset(names, NULL, sizeof(char*) * 50);	// same thing as the for does

	if (pFile) {
		fscanf(pFile, "%s", buffer);

		// char** [] implementation -> first we go through the entire file to compute the freq. array
		while (!feof(pFile)) {
			names[index] = (char*)malloc(strlen(buffer) + 1);  // malloc will always return a pointer to void
																 // - that will be casted automatically to whatever type we need
			int pos = *buffer - 'A';
			letters[pos]++;
			strcpy(names[index++], buffer);
			fscanf(pFile, "%s", buffer);
		}

		// copying freq vector
		/*for (int i = 0; i < 26; i++) {
			copy[i] = letters[i];
		}*/
		memcpy(copy, letters, 26 * sizeof(short));

		for (int i = 0; i < 50; i++) {
			if (names[i]) {
				int pos = *(names[i] + 0) - 'A';
				if (agenda[pos] == NULL) // not allocated matrix
					agenda[pos] = (char**)malloc(sizeof(char*)*letters[pos]);
				agenda[pos][letters[pos] - 1] = (char*)malloc(strlen(names[i]) + 1);
				strcpy(agenda[pos][letters[pos] - 1], names[i]);
				letters[pos]--;
			}
		}

		// printing agenda
		for (int i = 0; i < 26; i++) {
			if (agenda[i]) {
				printf("Group %c:\n", i + 'A');
				for (int j = 0; j < copy[i]; j++) {
					printf("%s; ", agenda[i][j]);
					Student* student = createInfo(agenda[i][j]);
					insertHead(&list, student);
					//list = insertTail(list, student);
				}
				printf("\n");
			}
		}

		printf("\n\nThe list:\n");
		printList(list);
		int a = 2;	// for testing because the console keeps closing
	}
}

Student* createInfo(char* name) {
	Student* value = (Student*)malloc(sizeof(Student));
	value->name = (char*)malloc(strlen(name) + 1);
	strcpy(value->name, name);
	return value;
}

Node* createNode(Student* info) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->pNext = NULL;
	return node;
}

void insertHead(Node** head, Student* info) {
	Node* newHead = createNode(info);

	// structure = head
	// node = newHead
	// DO NOT FORGET TO USE *HEAD
	// 1. connect the node to the structure
	newHead->pNext = *head;
	
	// 2. connect the structure to the node
	*head = newHead;
}

Node* insertTail(Node* head, Student* info) {
	Node* newTail = createNode(info);

	// 1. connect the node to the structure 
	// only when the head = NULL
	if (head == NULL) {
		head = newTail;
		return head;
	}
	// 2. connect the structure to the node
	Node* tmp = head;
	while (tmp->pNext) {
		tmp = tmp->pNext;
	}
	tmp->pNext = newTail;
	return head;
}

void printList(Node* head) {
	for (; head; head = head->pNext) {
		printf("%s; ", head->info->name);
	}
}