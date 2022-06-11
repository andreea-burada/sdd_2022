#include "z.NodeInfo.c"

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

void printList(const SimpleListNonC*);

// implementation

Node* createNode(Employee* emp) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->info = emp;
		newNode->pNext = NULL;
	}
	return newNode;
}



SimpleListNonC* insertHead_Val(SimpleListNonC* head, Employee* emp) {
	Node* newHead = createNode(emp);
	newHead->pNext = head;
	head = newHead;
	return head;
}

void insertHead_Ref(SimpleListNonC** head, Employee* emp) {
	Node* newHead = createNode(emp);
	newHead->pNext = *head;
	*head = newHead;
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


void printList(const SimpleListNonC* head) {
	printf("\n");
	int pos = 1;
	while (head) {
		printf("%2d - ", pos++);
		printInfo(head->info);
		head = head->pNext;
	}
}