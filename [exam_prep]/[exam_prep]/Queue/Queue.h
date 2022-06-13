
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Queue - Double List (Head - Circular) --------------*/

// data structure definition
typedef struct Node {
	Employee* info;
	struct Node* pNext;
	struct Node* pPrev;
} Node, Queue;

/*queue specific methods*/
Node* createNode(NodeInfo*);

Queue* put_Val(Queue*, NodeInfo*);
void put_Ref(Queue**, NodeInfo*);

NodeInfo* get(Queue**);

NodeInfo* peek(const Queue*);

Queue* deleteQueue_Val(Queue*);
void deleteQueue_Ref(Queue**);

Queue* deleteQueueCond_Val(Queue*);
void deleteQueueCond_Ref(Queue**);

void printQueue(Queue**);


// implementation
Node* createNode(NodeInfo* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node) {
		node->info = info;
		node->pNext = NULL;
		node->pPrev = NULL;
	}
	return node;
}



Queue* put_Val(Queue* queueHead, NodeInfo* info)
{
	Node* node = createNode(info);
	if (queueHead == NULL)
	{
		node->pNext = node->pPrev = node;
		queueHead = node;
	}
	else
	{
		node->pNext = queueHead;
		node->pPrev = (queueHead)->pPrev;

		(queueHead)->pPrev->pNext = node;
		(queueHead)->pPrev = node;
	}
	return queueHead;
}
void put_Ref(Queue** queueHead, NodeInfo* info)
{
	Node* node = createNode(info);
	if (*queueHead == NULL)
	{
		node->pNext = node->pPrev = node;
		*queueHead = node;
	}
	else
	{
		node->pNext = *queueHead;
		node->pPrev = (*queueHead)->pPrev;

		(*queueHead)->pPrev->pNext = node;
		(*queueHead)->pPrev = node;
	}
}



NodeInfo* get(Queue** queueHead)
{
	NodeInfo* value = NULL;
	if (*queueHead != NULL)
	{
		value = (*queueHead)->info;
		Node* tmp = *queueHead;
		if (tmp->pNext != tmp && tmp->pPrev != tmp)
		{
			tmp->pNext->pPrev = tmp->pPrev;
			tmp->pPrev->pNext = tmp->pNext;
			*queueHead = tmp->pNext;
		}
		else
			*queueHead = NULL;
		free(tmp);
	}
	return value;
}



NodeInfo* peek(const Queue* queueHead)
{
	Employee* toReturn = NULL;
	if (queueHead)
		toReturn = createNodeInfo(queueHead->info->code,
			queueHead->info->name,
			queueHead->info->dept,
			queueHead->info->salary);
	return toReturn;
}



Queue* deleteQueue_Val(Queue* queueHead)
{
	while (queueHead)
	{
		NodeInfo* toDelete = get(&queueHead);
		free(toDelete->dept);
		free(toDelete->name);
		free(toDelete);
	}
	return queueHead;
}
void deleteQueue_Ref(Queue** queueHead)
{
	while (*queueHead)
	{
		NodeInfo* toDelete = get(&(*queueHead));
		free(toDelete->dept);
		free(toDelete->name);
		free(toDelete);
	}
}

Queue* deleteQueueCond_Val(Queue* queueHead)
{
	Queue* altQ = NULL;
	if (queueHead) {
		while (queueHead)
		{
			NodeInfo* toPut = get(&(queueHead));
			altQ = put_Val(altQ, toPut);
		}
		while (altQ)
		{	
			NodeInfo* toPut = get(&altQ);
			if (toPut->code % 2 == 0)
			{
				free(toPut->dept);
				free(toPut->name);
				free(toPut);
				toPut = NULL;
			}
			else {
				queueHead = put_Val(queueHead, toPut);
			}
		}
	}
	return queueHead;
}
void deleteQueueCond_Ref(Queue** queueHead)
{
	Queue* altQ = NULL;
	if (*queueHead) {
		while (*queueHead)
		{
			NodeInfo* toPut = get(&(*queueHead));
			altQ = put_Val(altQ, toPut);
		}
		while (altQ)
		{
			NodeInfo* toPut = get(&altQ);
			if (toPut->code % 2 == 0)
			{
				free(toPut->dept);
				free(toPut->name);
				free(toPut);
				toPut = NULL;
			}
			else {
				*queueHead = put_Val(*queueHead, toPut);
			}
		}
	}
}



void printQueue(Queue** queueHead)
{
	Queue* altQ = NULL;
	if (*queueHead) {
		printf("\n// Head/Front\n\n");
		while (*queueHead)
		{
			NodeInfo* toPut = get(&(*queueHead));
			altQ = put_Val(altQ, toPut);
			printInfo(toPut);
		}
		printf("\n// Tail/Back\n");
		while (altQ)
		{
			NodeInfo* toPut = get(&altQ);
			*queueHead = put_Val(*queueHead, toPut);
		}
	}
	else
	{
		printf("\nQueue is empty!\n");
	}
}