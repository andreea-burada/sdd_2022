#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Simple Linked List - Non-Circular --------------*/

// data structure definition
typedef struct Node {
	Employee* info;
	struct Node* pNext;
} Node, SimpleListNonC;

/*simple list specific methods*/
Node* createNode(Employee*);

SimpleListNonC* insertHead_Val(SimpleListNonC*, Employee*);
void insertHead_Ref(SimpleListNonC**, Employee*);

SimpleListNonC* insertTail_Val(SimpleListNonC*, Employee*);
void insertTail_Ref(SimpleListNonC**, Employee*);

SimpleListNonC* insertListOnPos_Val(SimpleListNonC*, Employee*, int);
void insertListOnPos_Ref(SimpleListNonC**, Employee*, int);

SimpleListNonC* deleteListPos_Val(SimpleListNonC*, int);
void deleteListPos_Ref(SimpleListNonC**, int);

SimpleListNonC* deleteAllCond_Val(SimpleListNonC*, int);
void deleteAllCond_Ref(SimpleListNonC**, int);

void printList(const SimpleListNonC*);

// implementation

Node* createNode(Employee* info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->info = info;
		newNode->pNext = NULL;
	}
	return newNode;
}



SimpleListNonC* insertHead_Val(SimpleListNonC* head, Employee* info) {
	Node* newHead = createNode(info);
	newHead->pNext = head;
	head = newHead;
	return head;
}
void insertHead_Ref(SimpleListNonC** head, Employee* info) {
	Node* newHead = createNode(info);
	newHead->pNext = *head;
	*head = newHead;
}



SimpleListNonC* insertTail_Val(SimpleListNonC* head, Employee* info)
{
	Node* newTail = createNode(info);
	// 1. connect node to the structure
	if (head == NULL) {
		head = newTail;
	}
	// 2. connect the structure to the node
	else {
		Node* tmp = head;
		while (tmp->pNext) {
			tmp = tmp->pNext;
		}
		tmp->pNext = newTail;
	}
	return head;
}
void insertTail_Ref(SimpleListNonC** head, Employee* info)
{
	Node* newTail = createNode(info);
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



// if pos = length of list + 1 -> inserting at the end
SimpleListNonC* insertListOnPos_Val(SimpleListNonC* head, Employee* emp, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return head;
	}

	Node* newNode = createNode(emp);
	if (pos == 1) {
		// insert at the head	
		head = insertHead_Val(head, emp);
		//insertHead_Ref(&head, emp);
	}
	else {
		// insert at the position
		Node* aux = head;
		int index = 1;
		while (index++ < (pos - 1) && aux->pNext) {
			aux = aux->pNext;
		}
		if ((aux->pNext) || (index == pos && aux->pNext == NULL))	// i do not want to insert if the pos is greater than the length
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length + 1 of the list. Insertion canceling...\n");
		
	}
	return head;
}
void insertListOnPos_Ref(SimpleListNonC** head, Employee* emp, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return;
	}

	Node* newNode = createNode(emp);
	if (pos == 1) {
		// insert at the head	
		*head = insertHead_Val(*head, emp);
		//insertHead_Ref(&(*head), emp);
	}
	else {
		// insert at the position
		Node* aux = *head;
		int index = 1;
		while (index++ < (pos - 1) && aux->pNext) {
			aux = aux->pNext;
		}
		if ((aux->pNext) || (index == pos && aux->pNext == NULL))	// i do not want to insert if the pos is greater than the length
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length + 1 of the list. Insertion canceling...\n");
		
	}
}



SimpleListNonC* deleteListPos_Val(SimpleListNonC* head, int pos) {
	// we need to save the node we want to delete in order to deallocate memory
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Canceling deletion...\n");
		return head;
	}

	Node* aux = NULL;
	if (pos == 1) {
		// head deletion
		aux = head;
		head = head->pNext;
	}
	else {
		int index = 1;
		Node* tmp = head;
		while (index++ < (pos - 1) && tmp->pNext) {
			tmp = tmp->pNext;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp->pNext) {
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
		}
		if ((index < pos) || (index == pos && aux == NULL))
		{
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
	return head;
}
void deleteListPos_Ref(SimpleListNonC** head, int pos) {
	// we need to save the node we want to delete in order to deallocate memory
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Canceling deletion...\n");
		return;
	}

	Node* aux = NULL;
	if (pos == 1) {
		// head deletion
		aux = *head;
		*head = (*head)->pNext;
	}
	else {
		int index = 1;
		Node* tmp = *head;
		while (index++ < (pos - 1) && tmp->pNext) {
			tmp = tmp->pNext;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp->pNext) {
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
		}
		if ((index < pos) || (index == pos && aux == NULL))
		{
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

SimpleListNonC* deleteAllCond_Val(SimpleListNonC* head, int size)
{
	Node* savedHead = head;
	bool deleteConfirm;
	// we treat the head outside the loop
	while (savedHead == head && savedHead)
	{
		if (savedHead->info->code % 2 == 0)
		{
			Node* toDelete = savedHead;
			head = savedHead->pNext;
			savedHead = savedHead->pNext;

			free(toDelete->info->name);
			free(toDelete->info->dept);
			free(toDelete->info);
			free(toDelete);
			toDelete = NULL;
			size--;
		}
		else
			break;
	}
	for (int i = 0; i < size - 1 && savedHead != NULL; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedHead && savedHead->pNext) {
			if (savedHead->pNext->info->code % 2 == 0) {
				Node* toDelete = savedHead->pNext;
				deleteConfirm = true;
				// if the node is the tail of the list
				if (savedHead->pNext->pNext == NULL) {
					savedHead->pNext = NULL;
				}
				else {
					savedHead->pNext = savedHead->pNext->pNext;
				}
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
		if (savedHead && deleteConfirm == false)
			savedHead = savedHead->pNext;
	}
	return head;
}
void deleteAllCond_Ref(SimpleListNonC** head, int size)
{
	bool deleteConfirm;
	// we treat the head outside the loop
	while (*head)
	{
		if ((*head)->info->code % 2 == 0)
		{
			Node* toDelete = *head;
			*head = (*head)->pNext;

			free(toDelete->info->name);
			free(toDelete->info->dept);
			free(toDelete->info);
			free(toDelete);
			size--;
		}
		else
			break;
	}

	if (*head == NULL)
		return;

	Node* savedHead = *head;
	for (int i = 0; i < size - 1 && savedHead != NULL; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedHead && savedHead->pNext) {
			if (savedHead->pNext->info->code % 2 == 0) {
				Node* toDelete = savedHead->pNext;
				deleteConfirm = true;
				// if the node is the tail of the list
				if (savedHead->pNext->pNext == NULL) {
					savedHead->pNext = NULL;
				}
				else {
					savedHead->pNext = savedHead->pNext->pNext;
				}
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
		if (savedHead && deleteConfirm == false)
			savedHead = savedHead->pNext;
	}
}


void printList(const SimpleListNonC* head) {
	printf("\n");
	int pos = 1;
	while (head) {
		printf("%2d - ", pos++);
		printInfo(head->info);
		head = head->pNext;
	}
	if (pos == 1)
		printf("List is empty\n");
}