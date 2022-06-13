
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Priority Queue - Array --------------*/

// data structure definition
typedef struct PriorityQueue
{
	NodeInfo** items;
	int size;
	int nextIndex; //next available position to insert
} PriorityQueue;

/*priority queue specific methods*/
PriorityQueue putPQ_Val(PriorityQueue, NodeInfo*);
void putPQ_Ref(PriorityQueue*, NodeInfo*);

NodeInfo* getPQ(PriorityQueue*);

NodeInfo* peekPQ(const PriorityQueue);	// same as MAX/MIN

void redoPriorityOrder(PriorityQueue*, int);
void redoPriorityOrderUpDown(PriorityQueue*, int);

void printPQ(PriorityQueue);

// info
/*
 - heap or priority queue
 - uses arrays but also some char. from trees (complete binary trees)
 - heap = specialized tree-based data structure that satisfies: if A parent of B 
		-> between A and B - semnatic relation of total order applied

 - if values of children lower than the parent -> MAX heap
 - if values of children higher than the parent -> MIN heap
 - queue as array -> array 0 1 2 3 4 -> 0 - get; 4 - put
	-> we go from left to right when we insert/extract
	-> we use two indexes: left and right or first and last

 - full binary tree = all parents have 2 children except the leaves
 - complete binary tree = the last level does not necesarily have all the leaves
 						-> complete binary trees are completed from left to right
						-> when deleting from binary trees we go from right to left

 --- decendent formulas ---
 left desc = 2 * i + 1
 right desc = 2 * i + 2

 --- parent formula --- 
 (i - 1) / 2	(partea intreaga)

 - liniarization of a binary tree -> putting element after element, taken level by level
 - in a MAX/MIN heap the MAX/MIN values can be accessed with constant (O(1)) complexity
 - priority queues -> HEAP SORT
 --- priority queue specific functions ---
 insert - put
 extract - get
 max/min - peek
 increasePriority

 - finding a MAX in a MIN heap -> extracting all of the elements -> the last one will be the MAX (O(n) complexity)
 - finding a MIN in a MAX heap -> extracting all of the elements -> the last one will be the MIN (O(n) complexity)
 */

// implementation
PriorityQueue putPQ_Val(PriorityQueue pQueue, NodeInfo* emp)
{
	//initial allocation of memory
	if (pQueue.items == NULL)
	{
		pQueue.items = (NodeInfo**)malloc(sizeof(NodeInfo*) * 7);
		pQueue.size = 7;
		if (pQueue.items)
			memset(pQueue.items, NULL, sizeof(NodeInfo*) * 7);
	}
	//resizing PQ structure if it's full
	if (pQueue.nextIndex == pQueue.size) // queue overflow
	{
		NodeInfo** tmp;
		tmp = (NodeInfo**)malloc(sizeof(NodeInfo*) * pQueue.size * 2);
		if (tmp) {
			memset(tmp, NULL, sizeof(NodeInfo*) * pQueue.size * 2);
			memcpy(tmp, pQueue.items, pQueue.size * sizeof(NodeInfo*));
		}
		free(pQueue.items);
		pQueue.items = tmp;
		pQueue.size *= 2;
	}
	if (pQueue.items)
		pQueue.items[pQueue.nextIndex] = emp;
	redoPriorityOrder(&pQueue, pQueue.nextIndex);
	pQueue.nextIndex++;

	return pQueue;
}
void putPQ_Ref(PriorityQueue* pQueue, NodeInfo* emp)
{
	//initial allocation of memory
	if (pQueue->items == NULL)
	{
		pQueue->items = (NodeInfo**)malloc(sizeof(NodeInfo*) * 7);
		pQueue->size = 7;
		if (pQueue->items)
			memset(pQueue->items, NULL, sizeof(NodeInfo*) * 7);
	}
	//resizing PQ structure if it's full
	if (pQueue->nextIndex == pQueue->size) // queue overflow
	{
		NodeInfo** tmp;
		tmp = (NodeInfo**)malloc(sizeof(NodeInfo*) * pQueue->size * 2);
		if (tmp) {
			memset(tmp, NULL, sizeof(NodeInfo*) * pQueue->size * 2);
			memcpy(tmp, pQueue->items, pQueue->size * sizeof(NodeInfo*));
		}
		free(pQueue->items);
		pQueue->items = tmp;
		pQueue->size *= 2;
	}
	if(pQueue->items)
		pQueue->items[pQueue->nextIndex] = emp;
	redoPriorityOrder(pQueue, pQueue->nextIndex);
	pQueue->nextIndex++;
}



// gets highest priority
NodeInfo* getPQ(PriorityQueue* pQueue)
{
	NodeInfo* toReturn = NULL;
	if (pQueue->items && pQueue->size > 0) {
		toReturn = createNodeInfo(pQueue->items[0]->code,
			pQueue->items[0]->name,
			pQueue->items[0]->dept,
			pQueue->items[0]->salary);
		// last added node becomes new index[0]
		pQueue->items[0] = pQueue->items[pQueue->nextIndex - 1];
		// resizing
		pQueue->items[pQueue->nextIndex - 1] = NULL;
		pQueue->nextIndex--;
		redoPriorityOrderUpDown(&(*pQueue), 0);
	}

	return toReturn;
}


NodeInfo* peekPQ(const PriorityQueue pQueue)
{
	NodeInfo* toReturn = NULL;
	if (pQueue.items && pQueue.size > 0)
		toReturn = createNodeInfo(pQueue.items[0]->code,
			pQueue.items[0]->name,
			pQueue.items[0]->dept,
			pQueue.items[0]->salary);
	return toReturn;
}


void redoPriorityOrder(PriorityQueue* pQueue, int childIndex)
{
	if (childIndex > 0)
	{
		int parentIndex = (childIndex - 1) / 2;
		if (pQueue->items[childIndex]->code > pQueue->items[parentIndex]->code)
		{
			NodeInfo* aux = pQueue->items[childIndex];
			pQueue->items[childIndex] = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = aux;
			redoPriorityOrder(pQueue, parentIndex);
		}
	}
}

void redoPriorityOrderUpDown(PriorityQueue* pQueue, int parentIndex)
{
	if (parentIndex < pQueue->nextIndex)
	{
		int leftChildIndex = 2 * parentIndex + 1;	// left child
		int rightChildIndex = 2 * parentIndex + 2;	// right child
		if (leftChildIndex < pQueue->nextIndex)
			if (pQueue->items[leftChildIndex]->code > pQueue->items[parentIndex]->code)
			{
				NodeInfo* aux = pQueue->items[leftChildIndex];
				pQueue->items[leftChildIndex] = pQueue->items[parentIndex];
				pQueue->items[parentIndex] = aux;
				redoPriorityOrderUpDown(pQueue, leftChildIndex);
			}
		if(rightChildIndex < pQueue->nextIndex)
			if (pQueue->items[rightChildIndex]->code > pQueue->items[parentIndex]->code)
			{
				NodeInfo* aux = pQueue->items[rightChildIndex];
				pQueue->items[rightChildIndex] = pQueue->items[parentIndex];
				pQueue->items[parentIndex] = aux;
				redoPriorityOrderUpDown(pQueue, rightChildIndex);
			}
	}
}


void printPQ(PriorityQueue pQueue)
{
	printf("\n");
	if (pQueue.items)
	{
		for (int i = 0; i < pQueue.nextIndex; i++) {
			printInfo(pQueue.items[i]);
			if (i != 0)
				printf("\tParent: \t%d\n", pQueue.items[(i - 1) / 2]->code);
			else
				printf("\tRoot\n");
			if (pQueue.nextIndex > 2 * i + 1) {
				printf("\tLeft Desc: \t%d\n", pQueue.items[2 * i + 1]->code);
			}
			if (pQueue.nextIndex > 2 * i + 2) {
				printf("\tRight Desc: \t%d\n", pQueue.items[2 * i + 2]->code);
			}
			printf("\n");
		}
	}
	else
	{
		printf("Priority Queue empty!\n");
	}
}