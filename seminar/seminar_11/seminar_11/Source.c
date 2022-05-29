#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#define LINE_BUFFEER 1024
#define FILE_NAME "Data.txt"
#define HASHTABLE_INIT_CAPACITY 65

// ------------ HASH TABLES ------------
// linear probation in the case of collision for hash tables
// implementation through array of pointers to Employee

typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} Employee, NodeInfo;

typedef struct HashTable {
	NodeInfo** items;
	int size;
} HashTable;



/* functions signatures for memory management */
NodeInfo* createInfo(short, char*, char*, double);
void printInfo(NodeInfo* info);
/* functions signatures for HT operations */
void initHashTable(HashTable*, int);
void putHashTable(HashTable*, NodeInfo*);
int probing(HashTable*, int, char*);
void resizeHashTable(HashTable*);
NodeInfo* extractHashTable(HashTable*, char*);

void main()
{
	FILE* pFile = fopen(FILE_NAME, "r");
	HashTable hashTable = { .items = NULL, .size = 0 };
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

			NodeInfo* nodeInfoToAdd = createInfo(code, name, dept, salary);

			putHashTable(&hashTable, nodeInfoToAdd);
			// NodeInfo* extracted = extractHashTable(&hashTable, nodeInfoToAdd->name);

			printf("\n***********************************\n");
			printf("\nSize: %d\n\n", hashTable.size);
			int occupiedPos = 0;
			for (int i = 0; i < hashTable.size; i++)
			{
				if (hashTable.items[i] != NULL)
				{
					printf("Index[%2d]: ", i);
					printInfo(hashTable.items[i]);
					occupiedPos += 1;
				}
			}
			printf("\nOccupied indexes: %d\n\n", occupiedPos);
		}
		int a = 2;
	}
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

int hash_func(char* key, int size)
{
	return key[0] % size;
}

void resizeHashTable(HashTable* hashT)
{
	NodeInfo** aux = hashT->items;
	hashT->items = (NodeInfo**)malloc(hashT->size * 2 * sizeof(NodeInfo*));		// we double the size
	// if (hashT->items != NULL)
	memset(hashT->items, NULL, hashT->size * 2 * sizeof(NodeInfo*));
	hashT->size *= 2;

	// we need to replace the old items into the new hash table
	for (int i = 0; i < hashT->size / 2; i++) {		// i < hashT->size because we doubled the size before
		if (aux[i] != NULL)
			putHashTable(hashT, aux[i]);
	}
	free(aux);
}

//int probing(HashTable* hTable, int index, char* key) {
//	int i = index;
//	while (i < hTable->size) {
//		if (hTable->items[i] == NULL) {
//			return i;
//		}
//		else if (strcmp(hTable->items[i]->name, key) == 0) {
//			return i;
//		}
//		//index = (index + 1) % hTable->size;
//		i++;
//	}
//	resizeHashTable(hTable);
//	index = hash_func(key, hTable->size);
//	return index;
//}

int probing(HashTable* hashT, int index, char* key)
{
	// we probe while: array positions are occupied
	// !!! we check if the occupied array position is a duplicate of what we want to insert
	//	-> in which case we return that index and override the information on that position
	while (hashT->items[index] != NULL)
	{
		if (strcmp(hashT->items[index]->name, key) == 0)
			return index;
		index++;
		if (index == hashT->size)
		{
			// resizing hash table
			resizeHashTable(hashT);
			index = hash_func(key, hashT->size);
		}
	}
	return index;
}

void initHashTable(HashTable* hashT, int size)
{
	hashT->items = (NodeInfo**)malloc(sizeof(NodeInfo*) * size);
	memset(hashT->items, NULL, sizeof(NodeInfo*) * size);
	hashT->size = size;
}

void putHashTable(HashTable* hashT, NodeInfo* nodeInfo) 
{
	if ((*hashT).items == NULL)	// if array empty
	{
		initHashTable(hashT, HASHTABLE_INIT_CAPACITY);
	}
	int index = hash_func(nodeInfo->name, hashT->size);
	if (hashT->items[index] != NULL)	// position is occupied -> probing
	{
		// linear probing
		index = probing(hashT, index, nodeInfo->name);
	}

	
	hashT->items[index] = nodeInfo;
}

NodeInfo* extractHashTable(HashTable* hashT, char* key)
{
	int index = hash_func(key, hashT->size);
	NodeInfo* toReturn = NULL;
	if (hashT->items != NULL)
	{
		// we extract
		toReturn = hashT->items[index];
		free(hashT->items[index]);
		hashT->items[index] = NULL;
	}

	return toReturn;
}

void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s\n", info->code, info->name);
	else
		printf("No data to print!");
}


