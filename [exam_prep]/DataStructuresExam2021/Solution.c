#define LINE_BUFFEER 1024
#define FILE_NAME "Evaluations.txt"
#define _CRT_SECURE_NO_WARNINGS

//		requirements
/*Write the source code sequence to create a circular simple linked list that shall store students' evaluations for different
exams. The structure will be populated with at least 15 records read from the file. The Evaluation structure will be
defined so that it should contain 5 attributes: int (evaluationId), int (noCredits), pointer to type char (examName),
int (student id), double (grade)

Write and call the function for creating one dimensional array containing the total number of students' evaluations per
each exam found in the list. The array, returned in main() by return type of the function should be used to display
the number of evaluations per exam

Write and call the function to delete all students evaluations from the available circular simple linked list based
on the student id, given as a parameter

Write and call the function to transform the list structure into a binary search tree using the evaluation id field.
The function will return in main() the root of the tree. The content of the tree must be displayed using the inorder
traversal.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>

typedef struct Evaluation
{
	int evaluationId;
	int noCredits;
	char* examName;
	int studentId;
	double grade;
} Evaluation, NodeInfo;

typedef struct Node {
	NodeInfo* info;
	struct Node* pNext;
} Node, SimpleListC_Tail;

typedef struct BST
{
	struct BST* leftChild;
	NodeInfo* info;
	struct BST* rightChild;
}BinarySearchTree, BinaryNode;

typedef struct EvalNoArray
{
	char* examName;
	int noEvals;
} EvalNoArray;

NodeInfo* createNodeInfo(int, int, char*, int, double);
void printInfo(NodeInfo*);

SimpleListC_Tail* insertHead_Val(SimpleListC_Tail*, NodeInfo*);


SimpleListC_Tail* insertTail_Val(SimpleListC_Tail*, NodeInfo*);


SimpleListC_Tail* insertListOnPos_Val(SimpleListC_Tail*, NodeInfo*, int);

SimpleListC_Tail* insertListAfterPos_Val(SimpleListC_Tail*, NodeInfo*, int);


SimpleListC_Tail* deleteListPos_Val(SimpleListC_Tail*, int);


SimpleListC_Tail* deleteAllCond_Val(SimpleListC_Tail*, int, int);


void printList(SimpleListC_Tail*);

EvalNoArray* arrayTotalEvals(SimpleListC_Tail*, int*);

void main()
{
	// define data structure
	SimpleListC_Tail* tail = NULL;

	// evalId,noCredits,examName,studentId,grade
	FILE* pFile = fopen(FILE_NAME, "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	int evalId, noCred, stdId; char* exName; double grade;
	int size = 0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			//evalId
			token = strtok(lineBuffer, sepList);
			evalId = atoi(token);
			//noCredits
			token = strtok(NULL, sepList);
			noCred = atoi(token);
			//examName
			exName = strtok(NULL, sepList);
			//stdId
			token = strtok(NULL, sepList);
			stdId = atoi(token);
			//noPeople
			token = strtok(NULL, sepList);
			grade = atof(token);

			NodeInfo* info = createNodeInfo(evalId, noCred, exName, stdId, grade);

			// insert into data structure
			tail = insertTail_Val(tail, info);

			size++;
		}
		// print data structure
		printList(tail);

		int arraySize = 0;
		EvalNoArray* arrayEvals = arrayTotalEvals(tail, &arraySize);

		for (int i = 0; i < arraySize; i++)
			printf("\nEval name: %13s, No Evals.: %2d\n", arrayEvals[i].examName, arrayEvals[i].noEvals);

		int studIdCrit = 10023;
		tail = deleteAllCond_Val(tail, size, studIdCrit);

		printf("\n---\n");
		printList(tail);
	}
	else
	{
		printf("File \"%s\" could not be opened.\n", FILE_NAME);
	}
	int a = 2;
}


EvalNoArray* arrayTotalEvals(SimpleListC_Tail* tail, int* size)
{
	EvalNoArray* evalArray = NULL;
	// we go through the list
	if (tail) {
		if (tail == tail->pNext)
		{
			// only one element
			evalArray = (EvalNoArray*)malloc(sizeof(EvalNoArray));
			evalArray[0].examName = (char*)malloc(strlen(tail->info->examName) + 1);
			strcpy(evalArray[0].examName, tail->info->examName);
			evalArray[0].noEvals = 1;
			*size = 1;
			return evalArray;
		}
		else
		{
			// more than one element in the array
			SimpleListC_Tail* rememberTail = tail;
			evalArray = (EvalNoArray*)malloc(sizeof(EvalNoArray));
			evalArray[0].examName = (char*)malloc(strlen(tail->info->examName) + 1);
			strcpy(evalArray[0].examName, tail->info->examName);
			evalArray[0].noEvals = 1;
			*size = 1;
			tail = tail->pNext;
			while (tail != rememberTail)
			{
				bool found = false;
				// check if the eval is already in the list
				for (int i = 0; i < *size; i++)
				{
					if (strcmp(evalArray[i].examName, tail->info->examName) == 0)
					{
						evalArray[i].noEvals += 1;
						found = true;
					}
				}
				if (found == false)
				{
					// resize array and add evaluation
					EvalNoArray* newArray;
					newArray = (EvalNoArray*)malloc(sizeof(EvalNoArray) * (*size + 1));
					if (newArray) {
						memset(newArray, NULL, sizeof(EvalNoArray) * (*size + 1));
						memcpy(newArray, evalArray, sizeof(EvalNoArray) * (*size));
						free(evalArray);
						evalArray = newArray;
						evalArray[*size].examName = (char*)malloc(strlen(tail->info->examName) + 1);
						strcpy(evalArray[*size].examName, tail->info->examName);
						evalArray[*size].noEvals = 1;
						*size += 1;
					}
				}
				tail = tail->pNext;
			}
			return evalArray;
		}
	}
	else
		return NULL;
}


Node* createNode(NodeInfo* info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->info = info;
		newNode->pNext = NULL;
	}
	return newNode;
}



SimpleListC_Tail* insertHead_Val(SimpleListC_Tail* tail, NodeInfo* info) {
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



SimpleListC_Tail* insertTail_Val(SimpleListC_Tail* tail, NodeInfo* info)
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



// if pos = length of list + 1 -> inserting at the end
SimpleListC_Tail* insertListOnPos_Val(SimpleListC_Tail* tail, NodeInfo* info, int pos) {
	if (pos <= 0)
	{
		printf("\nPosition cannot be 0 or negative. Insertion canceling...\n");
		return tail;
	}

	Node* newNode = createNode(info);
	if (pos == 1) {
		// insert at the head	
		tail = insertHead_Val(tail, info);
		//insertHead_Ref(&head, info);
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
			aux->pNext = insertHead_Val(aux->pNext, info);
			//insertHead_Ref(&(aux->pNext), info);
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");

	}
	return tail;
}

// if pos = 0 -> insert at head
SimpleListC_Tail* insertListAfterPos_Val(SimpleListC_Tail* tail, NodeInfo* info, int pos) {
	if (pos < 0)
	{
		printf("\nPosition cannot be negative. Insertion canceling...\n");
		return tail;
	}

	Node* newNode = createNode(info);
	if (pos == 0) {
		// insert at the head	
		tail = insertHead_Val(tail, info);
		//insertHead_Ref(&head, info);
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
				tail = insertTail_Val(tail, info);
				//insertTail_REf(&tail, info);
			}
			else
			{
				aux->pNext = insertHead_Val(aux->pNext, info);
				//insertHead_Ref(&(aux->pNext), info);
			}
		}
		else
			printf("\nPosition is greater than the length of the list. Insertion canceling...\n");
	}
	return tail;
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
		free(aux->info->examName);
		free(aux->info);
		free(aux);
		aux = NULL;
	}
	return tail;
}



SimpleListC_Tail* deleteAllCond_Val(SimpleListC_Tail* tail, int size, int studId)
{
	Node* savedTail = tail;
	bool deleteConfirm;
	// we treat the tail outside the loop
	while (savedTail == tail && savedTail->pNext != tail)
	{
		if (savedTail->info->studentId == studId)
		{
			Node* toDelete = savedTail;
			// redoing the circular link
			Node* tmp = tail->pNext;
			while (tmp->pNext != tail)
				tmp = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;

			tail = tmp;
			savedTail = tail;

			free(toDelete->info->examName);
			free(toDelete->info);
			free(toDelete);
			toDelete = NULL;
			size--;
		}
		else
			break;
	}
	// we check if we only have one node in the structure
	if (tail == tail->pNext && tail->info->studentId == studId)
	{
		// delete the head and make the list null
		free(tail->info->examName);
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
			if (savedTail->pNext->info->studentId == studId) {
				Node* toDelete = savedTail->pNext;
				deleteConfirm = true;

				savedTail->pNext = savedTail->pNext->pNext;

				if (toDelete)
				{
					free(toDelete->info->examName);
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

NodeInfo* createNodeInfo(int eId, int noC, char* eName, int sId, double g)
{
	NodeInfo* toReturn = (NodeInfo*)malloc(sizeof(NodeInfo));
	if (toReturn != NULL)
	{
		toReturn->evaluationId = eId;
		toReturn->noCredits = noC;
		toReturn->examName = (char*)malloc(strlen(eName) + 1);
		strcpy(toReturn->examName, eName);
		toReturn->studentId = sId;
		toReturn->grade = g;

	}
	return toReturn;
}

// printing a NodeInfo
void printInfo(NodeInfo* info)
{
	if (info)
		printf("Eval. Id: %4d, No. Credits: %2d, Exam Name: %13s, \tStudent ID: %5d, Grade: %2.2f\n",
			info->evaluationId,
			info->noCredits,
			info->examName,
			info->studentId,
			info->grade);
	else
		printf("No data to print!");
}

