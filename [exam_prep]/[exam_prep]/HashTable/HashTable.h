
#include "../zNodeInfo/z.NodeInfo.h"
#define HASHTABLE_INIT_CAPACITY 65

/*		-------------- Hash Table - Linear Probing --------------*/

typedef struct HashTable
{
	NodeInfo** items;
	int size;
}HashTable;

/*hash tables specific methods*/
int hash_func(char*, int);

void initHashTable(HashTable*, int);

void putHashTable(HashTable*, NodeInfo*);

int probing_Linear(HashTable*, int, char*);

void resizeHashTable(HashTable*);

NodeInfo* extractHashTable(HashTable*, char*);

NodeInfo* searchHashTable(HashTable*, char*);

void printHashTable(HashTable);

// info
/*

 */

 // implementation
int hash_func(char* key, int size)
{
	return key[0] % size;
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
		index = probing_Linear(hashT, index, nodeInfo->name);
	}


	hashT->items[index] = nodeInfo;
}



int probing_Linear(HashTable* hashT, int index, char* key)
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



NodeInfo* extractHashTable(HashTable* hashT, char* key)
{
	int index = hash_func(key, hashT->size);
	NodeInfo* toReturn = NULL;
	if (hashT->items != NULL)
	{
		while (hashT->items[index]) {
			if (strcmp(hashT->items[index]->name, key) == 0) {
				// we extract
				toReturn = hashT->items[index];
				//free(hashT->items[index]);	// only if using lists
				hashT->items[index] = NULL;
				break;
			}
			else
			{
				index++;
			}
		}
	}
	return toReturn;
}



NodeInfo* searchHashTable(HashTable* hTable, char* key)
{
	NodeInfo* value = NULL;
	int index = hash_func(key, hTable->size);
	if (hTable->items[index] != NULL)
	{
		NodeInfo* aux = hTable->items[index];
		while (hTable->items[index] && (strcmp(key, hTable->items[index]->name) != 0))
			index++;
		if (hTable->items[index])
			value = hTable->items[index];
	}
	return value;
}

void printHashTable(HashTable hashTable)
{
	printf("\n---\n");
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