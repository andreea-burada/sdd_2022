#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFER 128
#define NO_STUDENTS 10
#define FILE_NAME "Students.txt"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>

// 2.crearea unui vector de elemente de tip Student* (nu sunt acceptate memory leaks) care sa contina 
// elementele listei sortate descrescator dupa medie, cunoscandu-se numarul de elemente din lista;
// procesarea listei initiale se face cu O(n);

typedef struct Student
{
	char* name;
	double grade;
} NodeInfo, Student;

typedef struct Node {
	NodeInfo* info;
	struct Node* pNext;
} List, Node;

Node* createNode(Student*);
void addList(List**, Student);
void printList(List*);

void main() {
	FILE* file = fopen(FILE_NAME, "r");
	char separator_list[] = ",\n", * token, buffer[LINE_BUFFER];
	Student allStudents[10];
	memset(allStudents, NULL, 10 * sizeof(Student));
	int index = 0;
	if (!file)
		printf("File \"%s\" could not be found\n", FILE_NAME);
	else {
		printf("File opened!\n");
		while (fgets(buffer, LINE_BUFFER, file) != NULL) {
			token = strtok(buffer, separator_list);
			allStudents[index].name = (char*)malloc(strlen(token) + 1);
			strcpy(allStudents[index].name,token);
			token = strtok(NULL, separator_list);
			allStudents[index++].grade = atof(token);

			// print the student
			printf("Student name: %s; grade: %.2f\n", allStudents[index - 1].name, allStudents[index - 1].grade);
		}

		fclose(file);

		// sorting the students
		for (int i = 0; i < NO_STUDENTS - 1; i++)
			for (int j = i + 1; j < NO_STUDENTS; j++) {
				if (allStudents[i].grade < allStudents[j].grade) {
					Student* aux = (Student*)malloc(sizeof(Student));
					aux->grade = allStudents[i].grade;
					aux->name = (char*)malloc(strlen(allStudents[i].name) + 1);
					strcpy(aux->name, allStudents[i].name);
					allStudents[i].grade = allStudents[j].grade;
					free(allStudents[i].name);
					allStudents[i].name = (char*)malloc(strlen(allStudents[j].name) + 1);
					strcpy(allStudents[i].name, allStudents[j].name);

					allStudents[j].grade = aux->grade;
					free(allStudents[j].name);
					allStudents[j].name = (char*)malloc(strlen(aux->name) + 1);
					strcpy(allStudents[j].name, aux->name);

					free(aux->name);
					free(aux);
				}
			}

		printf("\n---\n\n");

		for (int i = 0; i < 10; i++) {
			printf("Student name: %s; grade: %.2f\n", allStudents[i].name, allStudents[i].grade);
		}

		//creating the list
		List* head = NULL;
		for (int i = 0; i < 10; i++) {
			addList(&head, allStudents[i]);
		}

		printList(head);
	}

	int a = 2;
}

Node* createNode(Student* info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = info;
	newNode->pNext = NULL;

	return newNode;
}

void addList(List** head, Student info) {
	Student* nodeInfo = (Student*)malloc(sizeof(Student));
	nodeInfo->grade = info.grade;
	nodeInfo->name = (char*)malloc(strlen(info.name) + 1);
	strcpy(nodeInfo->name, info.name);

	List* node = createNode(nodeInfo);
	if (*head == NULL) {
		*head = node;
	}
	else {
		Node* dummy = *head;
		while (dummy->pNext != NULL)
			dummy = dummy->pNext;
		dummy->pNext = node;
	}
}

void printList(List* head) {
	printf("\n\n---Printing the list---\n\n");
	while (head != NULL) {
		printf("Student name: %s\n\tgrade: %.2f\n", head->info->name, head->info->grade);
		head = head->pNext;
	}
}