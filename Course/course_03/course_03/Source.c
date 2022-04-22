#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct Node {
	char* data;
	struct Node* next;
}List;
//typedef struct Node List;

void insertHead(List**, char*); 
List* insertTail(List*, char*);
void printList(List*);

void main() {
	// struct Node* list = NULL;
	List* list = NULL;
	FILE* source;
	char fileName[] = "names.txt";
	source = fopen(fileName, "r");
	char buffer[128];
	while (!feof(source)) {
		fscanf(source, "%s", buffer);
		//insertHead(&list, buffer);
		list = insertTail(list, buffer);
	}
	printList(list);
}

// data = buffer from void main()
void insertHead(List** list, char* data) {
	List* newNode = malloc(sizeof(List));
	newNode->data = malloc(strlen(data) + 1);
	strcpy(newNode->data, data);
	newNode->next = NULL;

	newNode->next = *list;
	*list = newNode;
}

// head = list from void main()
List* insertTail(List* head, char* buffer) {
	List* newNode = malloc(sizeof(List)), * temp = head;
	newNode->data = malloc(strlen(buffer) + 1);
	strcpy(newNode->data, buffer);
	newNode->next = NULL;

	if (head == NULL) {
		head = newNode;
		return head;
	}

	while (temp->next != NULL) {
			temp = temp->next;
		}
	temp->next = newNode;
	return head;
}

void printList(List* head) {
	//List* temp = head; // not necessary in this case
	while (head) {
		printf("Value: %s\n", head->data);
		head = head->next;
	}
}