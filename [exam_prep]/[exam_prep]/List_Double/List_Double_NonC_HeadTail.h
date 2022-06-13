
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Double Linked List - Non-Circular --------------*/

// data structure definition
typedef struct Node {
	Employee* info;
	struct Node* pNext;
	struct Node* pPrev;
} Node;

typedef struct DoubleList {
	Node* head;
	Node* tail;
} DoubleListNonC;

/*double list specific methods*/
Node* createNode(Employee*);
bool isEmpty(DoubleListNonC);

DoubleListNonC insertHead_Val(DoubleListNonC, Employee*);	// done
void insertHead_Ref(DoubleListNonC*, Employee*);			// done

DoubleListNonC insertTail_Val(DoubleListNonC, Employee*);	// done
void insertTail_Ref(DoubleListNonC*, Employee*);			// done

DoubleListNonC insertListOnPos_Val(DoubleListNonC, Employee*, int);		// done
void insertListOnPos_Ref(DoubleListNonC*, Employee*, int);				// done
DoubleListNonC insertListAfterPos_Val(DoubleListNonC, Employee*, int);	// done
void insertListAfterPos_Ref(DoubleListNonC*, Employee*, int);			// done

DoubleListNonC deleteListPos_Val(DoubleListNonC, int);		// done
void deleteListPos_Ref(DoubleListNonC*, int);				// done

DoubleListNonC deleteAllCond_Val(DoubleListNonC, int);
void deleteAllCond_Ref(DoubleListNonC**, int);

void printList(DoubleListNonC);

// implementation

Node* createNode(Employee* info) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node) {
		node->info = info;
		node->pNext = NULL;
		node->pPrev = NULL;
	}
	return node;
}
bool isEmpty(DoubleListNonC doubleList)
{
	return (doubleList.head == NULL && doubleList.tail == NULL);
}


DoubleListNonC insertHead_Val(DoubleListNonC doubleList, Employee* info) {
	Node* newNode = createNode(info);
	if (isEmpty(doubleList))
		doubleList.head = doubleList.tail = newNode;
	else
	{
		newNode->pNext = doubleList.head;
		doubleList.head->pPrev = newNode;
		doubleList.head = newNode;
	}
	return doubleList;
}
void insertHead_Ref(DoubleListNonC* doubleList, Employee* info) {
	Node* newNode = createNode(info);
	if (isEmpty(*doubleList))
		doubleList->head = doubleList->tail = newNode;
	else
	{
		newNode->pNext = doubleList->head;
		doubleList->head->pPrev = newNode;
		doubleList->head = newNode;
	}
}



DoubleListNonC insertTail_Val(DoubleListNonC doubleList, Employee* info)
{
	Node* newNode = createNode(info);
	if (isEmpty(doubleList))
		doubleList.head = doubleList.tail = newNode;
	else
	{
		doubleList.tail->pNext = newNode;
		newNode->pPrev = doubleList.tail;
		doubleList.tail = newNode;
	}
	return doubleList;
}
void insertTail_Ref(DoubleListNonC* doubleList, Employee* info)
{
	Node* newNode = createNode(info);
	if (isEmpty(*doubleList))
		doubleList->head = doubleList->tail = newNode;
	else
	{
		doubleList->tail->pNext = newNode;
		newNode->pPrev = doubleList->tail;
		doubleList->tail = newNode;
	}
}



// if pos = length of list + 1 -> inserting at the end
DoubleListNonC insertListOnPos_Val(DoubleListNonC doubleList, Employee* emp, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return doubleList;
	}

	Node* newNode = createNode(emp);
	if (pos == 1) {
		// insert at the head	
		doubleList = insertHead_Val(doubleList, emp);
		//insertHead_Ref(&doubleList, emp);
	}
	else {
		// insert at the position
		Node* aux = doubleList.head;
		int index = 1;
		while (index < (pos - 1) && aux != NULL) {
			aux = aux->pNext;
			index++;
		}
		if (index == pos - 1 && aux)
		{
			if (aux == doubleList.tail)
				doubleList.tail = newNode;
			if (aux->pNext)
			{
				newNode->pNext = aux->pNext;
				aux->pNext->pPrev = newNode;
			}
			newNode->pPrev = aux;
			aux->pNext = newNode;
		}
		else
			printf("\nPosition %d is greater than the length + 1 of the list. Insertion canceling...\n", pos);

	}
	return doubleList;
}
void insertListOnPos_Ref(DoubleListNonC* doubleList, Employee* emp, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return;
	}

	Node* newNode = createNode(emp);
	if (pos == 1) {
		// insert at the head	
		*doubleList = insertHead_Val(*doubleList, emp);
		//insertHead_Ref(&(*doubleList), emp);
	}
	else {
		// insert at the position
		Node* aux = doubleList->head;
		int index = 1;
		while (index < (pos - 1) && aux != NULL) {
			aux = aux->pNext;
			index++;
		}
		if (index == pos - 1 && aux)
		{
			if (aux == doubleList->tail)
				doubleList->tail = newNode;
			if (aux->pNext)
			{
				newNode->pNext = aux->pNext;
				aux->pNext->pPrev = newNode;
			}
			newNode->pPrev = aux;
			aux->pNext = newNode;
		}
		else
			printf("\nPosition %d is greater than the length + 1 of the list. Insertion canceling...\n", pos);

	}
}
// if pos = 0 -> insert at head
DoubleListNonC insertListAfterPos_Val(DoubleListNonC doubleList, Employee* emp, int pos) {
	if (pos < 0)
	{
		printf("\nPosition cannot be negative. Insertion canceling...\n");
		return doubleList;
	}

	Node* newNode = createNode(emp);
	if (pos == 0) {
		// insert at the head	
		doubleList = insertHead_Val(doubleList, emp);
		//insertHead_Ref(&doubleList, emp);
	}
	else {
		// insert at the position
		Node* aux = doubleList.head;
		int index = 0;
		while (index < (pos - 1) && aux != NULL) {
			aux = aux->pNext;
			index++;
		}
		if (index == pos - 1 && aux)
		{
			if (aux == doubleList.tail)
				doubleList.tail = newNode;
			if (aux->pNext)
			{
				newNode->pNext = aux->pNext;
				aux->pNext->pPrev = newNode;
			}
			newNode->pPrev = aux;
			aux->pNext = newNode;
		}
		else
			printf("\nPosition %d is greater than the length of the list. Insertion canceling...\n", pos);

	}
	return doubleList;
}
void insertListAfterPos_Ref(DoubleListNonC* doubleList, Employee* emp, int pos) {
	if (pos < 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return;
	}

	Node* newNode = createNode(emp);
	if (pos == 0) {
		// insert at the head	
		*doubleList = insertHead_Val(*doubleList, emp);
		//insertHead_Ref(&(*doubleList), emp);
	}
	else {
		// insert at the position
		Node* aux = doubleList->head;
		int index = 0;
		while (index < (pos - 1) && aux != NULL) {
			aux = aux->pNext;
			index++;
		}
		if (index == pos - 1 && aux)
		{
			if (aux == doubleList->tail)
				doubleList->tail = newNode;
			if (aux->pNext)
			{
				newNode->pNext = aux->pNext;
				aux->pNext->pPrev = newNode;
			}
			newNode->pPrev = aux;
			aux->pNext = newNode;
		}
		else
			printf("\nPosition %d is greater than the length of the list. Insertion canceling...\n", pos);

	}
}



DoubleListNonC deleteListPos_Val(DoubleListNonC doubleList, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Canceling deletion...\n");
		return doubleList;
	}

	Node* aux = NULL;
	if (pos == 1) {
		 // head deletion
		aux = doubleList.head;
		if (doubleList.head->pNext)
			doubleList.head->pNext->pPrev = NULL;
		else
			doubleList.tail = NULL;
		doubleList.head = doubleList.head->pNext;
	}
	else {
		int index = 1;
		Node* tmp = doubleList.head;
		while (index < (pos) && tmp->pNext != NULL) {
			tmp = tmp->pNext;
			index++;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp != doubleList.tail) {
			// deleting a non tail
			tmp->pPrev->pNext = tmp->pNext;
			if (tmp->pNext)
				tmp->pNext->pPrev = tmp->pPrev;
			aux = tmp;
		}
		else if (tmp == doubleList.tail && index == pos) {
			// deleting the tail
			tmp->pPrev->pNext = NULL;
			doubleList.tail = tmp->pPrev;
			aux = tmp;
		}
		else {
			printf("\nPosition %2d is out of the list. Canceling deletion...\n", pos);
		}
	}
	if (aux) {
		free(aux->info->name);
		free(aux->info->dept);
		free(aux->info);
		free(aux);
		aux = NULL;
	}
	return doubleList;
}
void deleteListPos_Ref(DoubleListNonC* doubleList, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Canceling deletion...\n");
		return;
	}

	Node* aux = NULL;
	if (pos == 1) {
		// head deletion
		aux = doubleList->head;
		if (doubleList->head->pNext)
			doubleList->head->pNext->pPrev = NULL;
		else
			doubleList->tail = NULL;
		doubleList->head = doubleList->head->pNext;
	}
	else {
		int index = 1;
		Node* tmp = doubleList->head;
		while (index < (pos) && tmp->pNext != NULL) {
			tmp = tmp->pNext;
			index++;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp != doubleList->tail) {
			// deleting a non tail
			tmp->pPrev->pNext = tmp->pNext;
			if (tmp->pNext)
				tmp->pNext->pPrev = tmp->pPrev;
			aux = tmp;
		}
		else if (tmp == doubleList->tail && index == pos) {
			// deleting the tail
			tmp->pPrev->pNext = NULL;
			doubleList->tail = tmp->pPrev;
			aux = tmp;
		}
		else {
			printf("\nPosition %2d is out of the list. Canceling deletion...\n", pos);
		}
	}
	if (aux) {
		free(aux->info->name);
		free(aux->info->dept);
		free(aux->info);
		free(aux);
		aux = NULL;
	}
}

DoubleListNonC deleteAllCond_Val(DoubleListNonC doubleList, int size)
{
	Node* savedNode = doubleList.head;
	bool deleteConfirm;
	int loopNo = size;

	for (int i = 1; i <= loopNo; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedNode) {
			if (savedNode->info->code % 2 == 0) {
				if (savedNode == doubleList.head)
				{
					savedNode = savedNode->pNext;
					doubleList = deleteListPos_Val(doubleList, 1);
					size--;
					deleteConfirm = true;
				}
				else if (savedNode == doubleList.tail)
				{
					doubleList = deleteListPos_Val(doubleList, size);
					size--;
					deleteConfirm = true;
				}
				else 
				{
					Node* toDelete = savedNode;
					size--;
					deleteConfirm = true;
					savedNode = toDelete->pNext;
					// redo links
					toDelete->pPrev->pNext = toDelete->pNext;
					if (toDelete->pNext)
						toDelete->pNext->pPrev = toDelete->pPrev;
					
					if (toDelete)
					{
						free(toDelete->info->name);
						free(toDelete->info->dept);
						free(toDelete->info);
						free(toDelete);
					}
					toDelete = NULL;
				}
				
			}
		}
		if (savedNode && deleteConfirm == false)
			savedNode = savedNode->pNext;
	}
	return doubleList;
}
void deleteAllCond_Ref(DoubleListNonC* doubleList, int size)
{
	Node* savedNode = doubleList->head;
	bool deleteConfirm;
	int loopNo = size;

	for (int i = 1; i <= loopNo; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedNode) {
			if (savedNode->info->code % 2 == 0) {
				if (savedNode == doubleList->head)
				{
					savedNode = savedNode->pNext;
					*doubleList = deleteListPos_Val(*doubleList, 1);
					size--;
					deleteConfirm = true;
				}
				else if (savedNode == doubleList->tail)
				{
					*doubleList = deleteListPos_Val(*doubleList, size);
					size--;
					deleteConfirm = true;
				}
				else
				{
					Node* toDelete = savedNode;
					size--;
					deleteConfirm = true;
					savedNode = toDelete->pNext;
					// redo links
					toDelete->pPrev->pNext = toDelete->pNext;
					if (toDelete->pNext)
						toDelete->pNext->pPrev = toDelete->pPrev;

					if (toDelete)
					{
						free(toDelete->info->name);
						free(toDelete->info->dept);
						free(toDelete->info);
						free(toDelete);
					}
					toDelete = NULL;
				}

			}
		}
		if (savedNode && deleteConfirm == false)
			savedNode = savedNode->pNext;
	}
}


void printList(DoubleListNonC doubleList) {
	printf("\n");
	if (doubleList.head == NULL) {
		printf("List is empty!\n");
		return;
	}
	int pos = 1;
	Node* aux = doubleList.head;
	while (aux) {
		printf("%2d - ", pos++);
		printInfo(aux->info);
		aux = aux->pNext;
	}
}

