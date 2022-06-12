
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Simple Linked List - Circular --------------*/

// data structure definition
typedef struct Node {
	Employee* info;
	struct Node* pNext;
} Node, SimpleListC;

/*simple list specific methods*/
Node* createNode(Employee*);

SimpleListC* insertHead_Val(SimpleListC*, Employee*);	// done
void insertHead_Ref(SimpleListC**, Employee*);

SimpleListC* insertTail_Val(SimpleListC*, Employee*);
void insertTail_Ref(SimpleListC**, Employee*);

SimpleListC* insertListOnPos_Val(SimpleListC*, Employee*, int);
void insertListOnPos_Ref(SimpleListC**, Employee*, int);
SimpleListC* insertListBeforePos_Val(SimpleListC*, Employee*, int);
void insertListBeforePos_Ref(SimpleListC**, Employee*, int);
SimpleListC* insertListAfterPos_Val(SimpleListC*, Employee*, int);
void insertListAfterPos_Ref(SimpleListC**, Employee*, int);

SimpleListC* deleteListPos_Val(SimpleListC*, int);
void deleteListPos_Ref(SimpleListC**, int);

SimpleListC* deleteAllCond_Val(SimpleListC*, int);
void deleteAllCond_Ref(SimpleListC**, int);

void printList(SimpleListC*);

// implementation

Node* createNode(Employee* info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->info = info;
		newNode->pNext = NULL;
	}
	return newNode;
}



SimpleListC* insertHead_Val(SimpleListC* head, Employee* info) {
	Node* newHead = createNode(info);
	if (head)
	{
		Node* aux = head;
		while (aux->pNext != head)
			aux = aux->pNext;
		aux->pNext = newHead;
		newHead->pNext = head;
	}
	else
	{
		newHead->pNext = newHead;
	}	
	head = newHead;
	return head;
}
void insertHead_Ref(SimpleListC** head, Employee* info) {
	Node* newHead = createNode(info);
	if (*head)
	{
		Node* aux = *head;
		while (aux->pNext != *head)
			aux = aux->pNext;
		aux->pNext = newHead;
		newHead->pNext = *head;
	}
	else
	{
		newHead->pNext = newHead;
	}
	*head = newHead;
}



SimpleListC* insertTail_Val(SimpleListC* head, Employee* info)
{
	Node* newTail = createNode(info);
	// 1. connect node to the structure
	if (head == NULL) {
		head = newTail;
		newTail->pNext = newTail;
	}
	// 2. connect the structure to the node
	else {
		Node* tmp = head;
		while (tmp->pNext != head) {
			tmp = tmp->pNext;
		}
		tmp->pNext = newTail;
		newTail->pNext = head;
	}
	return head;
}
void insertTail_Ref(SimpleListC** head, Employee* info)
{
	Node* newTail = createNode(info);
	// 1. connect node to the structure
	if (*head == NULL) {
		*head = newTail;
		newTail->pNext = newTail;
	}
	// 2. connect the structure to the node
	else {
		Node* tmp = *head;
		while (tmp->pNext != *head) {
			tmp = tmp->pNext;
		}
		tmp->pNext = newTail;
		newTail->pNext = *head;
	}
}



// if pos = length of list + 1 -> inserting at the end
SimpleListC* insertListOnPos_Val(SimpleListC* head, Employee* emp, int pos) {
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
		while (index++ < (pos - 1) && aux->pNext != head) {
			aux = aux->pNext;
		}
		if (index == pos)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length + 1 of the list. Insertion canceling...\n");

	}
	return head;
}
void insertListOnPos_Ref(SimpleListC** head, Employee* emp, int pos) {
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
		while (index++ < (pos - 1) && aux->pNext != *head) {
			aux = aux->pNext;
		}
		if (index == pos)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length + 1 of the list. Insertion canceling...\n");

	}
}
// if pos = length + 1 -> inserting at the tail
SimpleListC* insertListBeforePos_Val(SimpleListC* head, Employee* emp, int pos) {
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
		pos--;
		// insert at the position
		Node* aux = head;
		int index = 0;
		while (index < (pos - 1) && aux->pNext != head) {
			index++;
			aux = aux->pNext;
		}
		if (index == pos - 1)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");

	}
	return head;
}
void insertListBeforePos_Ref(SimpleListC** head, Employee* emp, int pos) {
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
		pos--;
		// insert at the position
		Node* aux = *head;
		int index = 0;
		while (index < (pos - 1) && aux->pNext != *head) {
			index++;
			aux = aux->pNext;
		}
		if (index == pos - 1)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");

	}
}
// if pos = 0 -> insert at head
SimpleListC* insertListAfterPos_Val(SimpleListC* head, Employee* emp, int pos) {
	if (pos < 0)
	{
		printf("\nPosition cannot be negative. Insertion canceling...\n");
		return head;
	}

	Node* newNode = createNode(emp);
	if (pos == 0) {
		// insert at the head	
		head = insertHead_Val(head, emp);
		//insertHead_Ref(&head, emp);
	}
	else {
		// insert at the position
		Node* aux = head;
		int index = 0;
		while (index < (pos - 1) && aux->pNext != head) {
			index++;
			aux = aux->pNext;
		}
		if (index == pos - 1)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");

	}
	return head;
}
void insertListAfterPos_Ref(SimpleListC** head, Employee* emp, int pos) {
	if (pos < 0)
	{
		printf("\nPosition cannot be negative. Insertion canceling...\n");
		return;
	}

	Node* newNode = createNode(emp);
	if (pos == 0) {
		// insert at the head	
		*head = insertHead_Val(*head, emp);
		//insertHead_Ref(&(*head), emp);
	}
	else {
		// insert at the position
		Node* aux = *head;
		int index = 0;
		while (index < (pos - 1) && aux->pNext != *head) {
			index++;
			aux = aux->pNext;
		}
		if (index == pos - 1)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");

	}
}



SimpleListC* deleteListPos_Val(SimpleListC* head, int pos) {
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
		Node* tmp = head;
		// redoing the circular link
		while (tmp->pNext != head)
			tmp = tmp->pNext;
		head = head->pNext;
		tmp->pNext = head;
	}
	else {
		int index = 1;
		Node* tmp = head;
		while (index < (pos - 1) && tmp->pNext->pNext != head) {
			tmp = tmp->pNext;
			index++;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp->pNext->pNext != head) {
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
		} else if (tmp->pNext->pNext == head && index == pos - 1) {
			// deleting the tail
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;	
		} else {
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
void deleteListPos_Ref(SimpleListC** head, int pos) {
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
		Node* tmp = *head;
		// redoing the circular link
		while (tmp->pNext != *head)
			tmp = tmp->pNext;
		*head = (*head)->pNext;
		tmp->pNext = *head;
	}
	else {
		int index = 1;
		Node* tmp = *head;
		while (index < (pos - 1) && tmp->pNext->pNext != *head) {
			tmp = tmp->pNext;
			index++;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp->pNext->pNext != *head) {
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
		}
		else if (tmp->pNext->pNext == *head && index == pos - 1) {
			// deleting the tail
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
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

SimpleListC* deleteAllCond_Val(SimpleListC* head, int size)
{
	Node* savedHead = head;
	bool deleteConfirm;
	// we treat the head outside the loop
	while (savedHead == head && savedHead->pNext != head)
	{
		if (savedHead->info->code % 2 == 0)
		{
			Node* toDelete = savedHead;
			// redoing the circular link
			Node* tmp = head;
			while (tmp->pNext != head)
				tmp = tmp->pNext;
			tmp->pNext = head->pNext;

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
	// we check if we only have one node in the structure
	if (head == head->pNext && head->info->code % 2 == 0)
	{
		// delete the head and make the list null
		free(head->info->name);
		free(head->info->dept);
		free(head->info);
		free(head);
		head = NULL;
		return head;
	}
	for (int i = 0; i < size - 1; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedHead && savedHead->pNext) {
			if (savedHead->pNext->info->code % 2 == 0) {
				Node* toDelete = savedHead->pNext;
				deleteConfirm = true;

				savedHead->pNext = savedHead->pNext->pNext;

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
void deleteAllCond_Ref(SimpleListC** head, int size)
{
	bool deleteConfirm;
	Node* savedHead = *head;
	// we treat the head outside the loop
	while (savedHead == *head && savedHead->pNext != *head)
	{
		if (savedHead->info->code % 2 == 0)
		{
			Node* toDelete = savedHead;
			// redoing the circular link
			Node* tmp = *head;
			while (tmp->pNext != *head)
				tmp = tmp->pNext;
			tmp->pNext = (*head)->pNext;

			*head = savedHead->pNext;
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
	// we check if we only have one node in the structure
	if (*head == (*head)->pNext && (*head)->info->code % 2 == 0)
	{
		// delete the head and make the list null
		free((*head)->info->name);
		free((*head)->info->dept);
		free((*head)->info);
		free(head);
		head = NULL;
		return;
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
}


void printList(SimpleListC* head) {
	printf("\n");
	if (head == NULL) {
		printf("List is empty!\n");
		return;
	}
	int pos = 1;
	Node* aux = head;
	while (head->pNext != aux) {
		printf("%2d - ", pos++);
		printInfo(head->info);
		head = head->pNext;
	}
	printf("%2d - ", pos++);
	printInfo(head->info);
}
