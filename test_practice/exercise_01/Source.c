#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFER 128
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>
// 1.crearea unei liste avand ca informatie utila un element de tip Student* in care elementele sunt grupate dupa 
// facultate iar dupa fiecare grupa sa se insereze un nod nou de tip DUMMY care sa contina media 
// pe facultatea respectiva; procesarea listei initiale se face cu O(n);

typedef struct Student {
	int id;
	char* name;
	char* university;
	double average;
} NodeInfo;

typedef struct List {
	NodeInfo** info;
	struct List* pNext;
} List;

/* --- function signatures - memory management --- */
NodeInfo* createInfo(int, char*, char*, double);