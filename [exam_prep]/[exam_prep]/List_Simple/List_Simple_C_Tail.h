
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Simple Linked List - Circular (Tail repr.) --------------*/

// data structure definition
typedef struct Node {
	Employee* info;
	struct Node* pNext;
} Node, SimpleListC_Tail;

/*simple list specific methods*/
Node* createNode(Employee*);

SimpleListC_Tail* insertHead_Val(SimpleListC_Tail*, Employee*);
void insertHead_Ref(SimpleListC_Tail**, Employee*);

SimpleListC_Tail* insertTail_Val(SimpleListC_Tail*, Employee*);
void insertTail_Ref(SimpleListC_Tail**, Employee*);

SimpleListC_Tail* insertListOnPos_Val(SimpleListC_Tail*, Employee*, int);
void insertListOnPos_Ref(SimpleListC_Tail**, Employee*, int);
SimpleListC_Tail* insertListAfterPos_Val(SimpleListC_Tail*, Employee*, int);
void insertListAfterPos_Ref(SimpleListC_Tail**, Employee*, int);

SimpleListC_Tail* deleteListPos_Val(SimpleListC_Tail*, int);
void deleteListPos_Ref(SimpleListC_Tail**, int);

SimpleListC_Tail* deleteAllCond_Val(SimpleListC_Tail*, int);
void deleteAllCond_Ref(SimpleListC_Tail**, int);

void printList(SimpleListC_Tail*);

// implementation

Node* createNode(Employee* info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->info = info;
		newNode->pNext = NULL;
	}
	return newNode;
}



SimpleListC_Tail* insertHead_Val(SimpleListC_Tail* tail, Employee* info) {
	Node* newHead = createNode(info);
	if (tail)
	{	
		newHead->pNext = tail->pNext;
		tail->pNext = newHead;
	}
	else
	{
		// if tail doesn't exist
		newHead->pNext = newHead; // circular
		tail = newHead;
	}
	return tail;
}
void insertHead_Ref(SimpleListC_Tail** tail, Employee* info) {
	Node* newHead = createNode(info);
	if (*tail)
	{
		newHead->pNext = (*tail)->pNext;
		(*tail)->pNext = newHead;
	}
	else
	{
		// if tail doesn't exist
		newHead->pNext = newHead; // circular
		*tail = newHead;
	}
}



SimpleListC_Tail* insertTail_Val(SimpleListC_Tail* tail, Employee* info)
{
	Node* toAdd = createNode(info);
	// if the list is empty
	if (tail == NULL) {
		// when we have only one element the circularity with be with itself
		tail = toAdd;
		tail->pNext = tail;
	}
	else {	// we have elements in the list
		// if we have only one element
		if (tail == tail->pNext) {
			tail->pNext = toAdd;
			toAdd->pNext = tail;
			tail = toAdd;	// we move the tail
		}
		else {
			// we have more than one element
			toAdd->pNext = tail->pNext;
			tail->pNext = toAdd;
			tail = toAdd;
		}
	}
	return tail;
}
void insertTail_Ref(SimpleListC_Tail** tail, Employee* info)
{
	Node* toAdd = createNode(info);
	// if the list is empty
	if (*tail == NULL) {
		// when we have only one element the circularity with be with itself
		*tail = toAdd;
		(*tail)->pNext = *tail;
	}
	else {	// we have elements in the list
		// if we have only one element
		if ((*tail) == (*tail)->pNext) {
			(*tail)->pNext = toAdd;
			toAdd->pNext = *tail;
			*tail = toAdd;	// we move the tail
		}
		else {
			// we have more than one element
			toAdd->pNext = (*tail)->pNext;
			(*tail)->pNext = toAdd;
			*tail = toAdd;
		}
	}
}



// if pos = length of list + 1 -> inserting at the end
SimpleListC_Tail* insertListOnPos_Val(SimpleListC_Tail* tail, Employee* emp, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return tail;
	}

	Node* newNode = createNode(emp);
	if (pos == 1) {
		// insert at the head	
		tail = insertHead_Val(tail, emp);
		//insertHead_Ref(&head, emp);
	}
	else {
		// insert at the position
		Node* aux = tail;
		int index = 1;
		while (index < (pos - 1) && aux->pNext != tail) {
			aux = aux->pNext;
			index++;
		}
		if (index == pos)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");

	}
	return tail;
}
void insertListOnPos_Ref(SimpleListC_Tail** tail, Employee* emp, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return *tail;
	}

	Node* newNode = createNode(emp);
	if (pos == 1) {
		// insert at the head	
		*tail = insertHead_Val(tail, emp);
		//insertHead_Ref(&head, emp);
	}
	else {
		// insert at the position
		Node* aux = *tail;
		int index = 1;
		while (index < (pos) && aux->pNext != *tail) {
			aux = aux->pNext;
			index++;
		}
		if (index == pos)
		{
			aux->pNext = insertHead_Val(aux->pNext, emp);
			//insertHead_Ref(&(aux->pNext), emp);
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");

	}
}
// if pos = 0 -> insert at head
SimpleListC_Tail* insertListAfterPos_Val(SimpleListC_Tail* tail, Employee* emp, int pos) {
	if (pos < 0)
	{
		printf("\nPosition cannot be negative. Insertion canceling...\n");
		return tail;
	}

	Node* newNode = createNode(emp);
	if (pos == 0) {
		// insert at the head	
		tail = insertHead_Val(tail, emp);
		//insertHead_Ref(&head, emp);
	}
	else {
		// insert at the position
		Node* aux = tail;
		int index = 0;
		while (index < (pos - 1) && aux->pNext != tail) {
			index++;
			aux = aux->pNext;
		}
		if (index == pos - 1)
		{
			if (aux->pNext == tail)
			{
				tail = insertTail_Val(tail, emp);
				//insertTail_REf(&tail, emp);
			}
			else
			{
				aux->pNext = insertHead_Val(aux->pNext, emp);
				//insertHead_Ref(&(aux->pNext), emp);
			}
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");
	}
	return tail;
}
void insertListAfterPos_Ref(SimpleListC_Tail** tail, Employee* emp, int pos) {
	if (pos < 0)
	{
		printf("\nPosition cannot be negative. Insertion canceling...\n");
		return *tail;
	}

	Node* newNode = createNode(emp);
	if (pos == 0) {
		// insert at the head	
		*tail = insertHead_Val(&(*tail), emp);
		//insertHead_Ref(&head, emp);
	}
	else {
		// insert at the position
		Node* aux = *tail;
		int index = 0;
		while (index < (pos - 1) && aux->pNext != *tail) {
			index++;
			aux = aux->pNext;
		}
		if (index == pos - 1)
		{
			if (aux->pNext == *tail)
			{
				*tail = insertTail_Val(*tail, emp);
				//insertTail_REf(&(*tail), emp);
			}
			else
			{
				aux->pNext = insertHead_Val(aux->pNext, emp);
				//insertHead_Ref(&(aux->pNext), emp);
			}
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");
	}
}



SimpleListC_Tail* deleteListPos_Val(SimpleListC_Tail* tail, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Canceling deletion...\n");
		return tail;
	}

	Node* aux = NULL;
	if (pos == 1) {
		// head deletion
		aux = tail->pNext;
		tail->pNext = tail->pNext->pNext;
	}
	else {
		int index = 1;
		Node* tmp = tail;
		while (index < (pos) && tmp->pNext->pNext != tail) {
			tmp = tmp->pNext;
			index++;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp->pNext->pNext != tail) {
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
		}
		else if (tmp->pNext->pNext == tail && index == pos - 1) {
			// deleting the tail
			aux = tmp->pNext->pNext;
			tail = tmp->pNext;
			tmp->pNext->pNext = tmp->pNext->pNext->pNext;
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
	return tail;
}
void deleteListPos_Ref(SimpleListC_Tail** tail, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Canceling deletion...\n");
		return *tail;
	}

	Node* aux = NULL;
	if (pos == 1) {
		// head deletion
		aux = (*tail)->pNext;
		(*tail)->pNext = (*tail)->pNext->pNext;
	}
	else {
		int index = 1;
		Node* tmp = *tail;
		while (index < (pos) && tmp->pNext->pNext != *tail) {
			tmp = tmp->pNext;
			index++;
		}
		// redoing the links so that the node that
		// we want to delete is skipped over
		if (tmp->pNext->pNext != *tail) {
			aux = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
		}
		else if (tmp->pNext->pNext == *tail && index == pos - 1) {
			// deleting the tail
			aux = tmp->pNext->pNext;
			*tail = tmp->pNext;
			tmp->pNext->pNext = tmp->pNext->pNext->pNext;
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

SimpleListC_Tail* deleteAllCond_Val(SimpleListC_Tail* tail, int size)
{
	Node* savedTail = tail;
	bool deleteConfirm;
	// we treat the tail outside the loop
	while (savedTail == tail && savedTail->pNext != tail)
	{
		if (savedTail->info->code % 2 == 0)
		{
			Node* toDelete = savedTail;
			// redoing the circular link
			Node* tmp = tail->pNext;
			while (tmp->pNext != tail)
				tmp = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;

			tail = tmp;
			savedTail = tail;

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
	if (tail == tail->pNext && tail->info->code % 2 == 0)
	{
		// delete the head and make the list null
		free(tail->info->name);
		free(tail->info->dept);
		free(tail->info);
		free(tail);
		tail = NULL;
		return tail;
	}
	for (int i = 0; i < size - 1; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedTail && savedTail->pNext) {
			if (savedTail->pNext->info->code % 2 == 0) {
				Node* toDelete = savedTail->pNext;
				deleteConfirm = true;

				savedTail->pNext = savedTail->pNext->pNext;

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
		if (savedTail && deleteConfirm == false)
			savedTail = savedTail->pNext;
	}
	return tail;
}
void deleteAllCond_Ref(SimpleListC_Tail** tail, int size)
{
	Node* savedTail = *tail;
	bool deleteConfirm;
	// we treat the tail outside the loop
	while (savedTail == *tail && savedTail->pNext != *tail)
	{
		if (savedTail->info->code % 2 == 0)
		{
			Node* toDelete = savedTail;
			// redoing the circular link
			Node* tmp = (*tail)->pNext;
			while (tmp->pNext != *tail)
				tmp = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;

			*tail = tmp;
			savedTail = *tail;

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
	if (*tail == (*tail)->pNext && (*tail)->info->code % 2 == 0)
	{
		// delete the head and make the list null
		free((*tail)->info->name);
		free((*tail)->info->dept);
		free((*tail)->info);
		free(*tail);
		*tail = NULL;
		return;
	}
	for (int i = 0; i < size - 1; i++)
	{
		// we try to delete if the condition is met
		deleteConfirm = false;
		if (savedTail && savedTail->pNext) {
			if (savedTail->pNext->info->code % 2 == 0) {
				Node* toDelete = savedTail->pNext;
				deleteConfirm = true;

				savedTail->pNext = savedTail->pNext->pNext;

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
		if (savedTail && deleteConfirm == false)
			savedTail = savedTail->pNext;
	}
}


void printList(SimpleListC_Tail* tail) {
	printf("\n");
	if (tail == NULL) {
		printf("List is empty!\n");
		return;
	}
	int pos = 1;
	Node* aux = tail->pNext;
	tail = tail->pNext;
	printf("%2d - ", pos++);
	printInfo(tail->info);
	while (tail->pNext != aux) {
		tail = tail->pNext;
		printf("%2d - ", pos++);
		printInfo(tail->info);
	}
}

