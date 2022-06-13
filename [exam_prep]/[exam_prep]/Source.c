#define LINE_BUFFEER 1024
#define FILE_NAME "Data.txt"
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
// include all DS .h files
// careful about ambiguity
//#include "zNodeInfo/z.NodeInfo.h"
//#include "List_Simple/List_Simple_NonC.h"
//#include "List_Simple/List_Simple_C.h"
//#include "List_Simple/List_Simple_C_Tail.h"
//#include "List_Double/List_Double_NonC_HeadTail.h"
//#include "Stack/Stack.h"
//#include "Queue/Queue.h"
#include "PriorityQueue/PriorityQueue.h"

void main()
{
	// define data structure
	//SimpleListNonC* head = NULL;
	//SimpleListC* head = NULL;
	//SimpleListC_Tail* tail = NULL;
	//DoubleListNonC doubleList = { .head = NULL, .tail = NULL };
	//Stack *topStack = NULL;
	//Queue* queueHead = NULL;
	PriorityQueue pQueue = { .items = NULL, .size = 0, .nextIndex = 0 };

	FILE* pFile = fopen(FILE_NAME, "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	int size = 0;
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

			NodeInfo* info = createNodeInfo(code, name, dept, salary);

			// insert into data structure
			#pragma region SimpleListNonC
			//head = insertHead_Val(head, info);
			//insertHead_Ref(&head, info);
			//head = insertTail_Val(head, info);
			//insertTail_Ref(&head, info);
			#pragma endregion

			#pragma region SimpleListC
			//head = insertHead_Val(head, info);
			//insertHead_Ref(&head, info);

			//head = insertTail_Val(head, info);
			//insertTail_Ref(&head, info);
			#pragma endregion

			#pragma region SimpleListC_Tail
			//tail = insertHead_Val(tail, info);
			//insertHead_Ref(&tail, info);

			//tail = insertTail_Val(tail, info);
			//insertTail_Ref(&tail, info);
			#pragma endregion

			#pragma region DoubleListNonC
			//doubleList = insertHead_Val(doubleList, info);
			//insertHead_Ref(&doubleList, info);
			//doubleList = insertTail_Val(doubleList, info);
			//insertTail_Ref(&doubleList, info);
			#pragma endregion

			#pragma region Stack
			//topStack = push_Val(topStack, info);
			//push_Ref(&topStack, info);
			#pragma endregion

			#pragma region Queue
			//queueHead = put_Val(queueHead, info);
			//push_Ref(&topStack, info);
			#pragma endregion

			#pragma region PriorityQueue
			//pQueue = putPQ_Val(pQueue, info);
			//putPQ_Ref(&pQueue, info);

			//printf("\n---\n");
			//printPQ(pQueue);
			#pragma endregion

			size++;
		}
		// print data structure
		//printList(head);
		//printList(tail);
		//printList(doubleList);
		
		// do other data structure specific actions and test
		int insPos = 11;
		int delPos = 7;
		NodeInfo* dummyInfo = createNodeInfo(10013, "Margaret Sinclair", "Cybersecurity", 23043.12);

		#pragma region SimpleListNonC
		/*printf("\n---\n");*/
		
		//head = insertListOnPos_Val(head, dummyInfo, insPos);
		//insertListOnPos_Ref(&head, dummyInfo, insPos);

		//head = insertListBeforePos_Val(head, dummyInfo, insPos);
		//insertListBeforePos_Ref(&head, dummyInfo, insPos);

		//head = insertListAfterPos_Val(head, dummyInfo, insPos);
		//insertListAfterPos_Ref(&head, dummyInfo, insPos);
		//printList(head);

		//printf("\n---\n");
		
		////head = deleteListPos_Val(head, delPos);
		//deleteListPos_Ref(&head, delPos);
		//printList(head);

		//printf("\n---\n");
		//head = deleteAllCond_Val(head, size);
		////deleteAllCond_Ref(&head, size);
		//printList(head);
		#pragma endregion

		#pragma region SimpleListC
		// checking the circularity
		/*printf("\n---\n");
		SimpleListC* headAux = head;
		if (headAux)
		{
			while (headAux->pNext != head)
				headAux = headAux->pNext;
			printf("\nHead - ");
			printInfo(headAux->pNext->info);
		}*/

		//printf("\n---\n");

		//head = insertListOnPos_Val(head, dummyInfo, insPos);
		//insertListOnPos_Ref(&head, dummyInfo, insPos);

		//head = insertListBeforePos_Val(head, dummyInfo, insPos);
		//insertListBeforePos_Ref(&head, dummyInfo, insPos);

		//head = insertListAfterPos_Val(head, dummyInfo, insPos);
		//insertListAfterPos_Ref(&head, dummyInfo, insPos);
		//printList(head);

		//printf("\n---\n");

		//head = deleteListPos_Val(head, delPos);
		//deleteListPos_Ref(&head, delPos);
		//printList(head);

		//printf("\n---\n");
		//head = deleteAllCond_Val(head, size);
		//deleteAllCond_Ref(&head, size);
		//printList(head);

		/*printf("\n---\n");
		headAux = head;
		if (headAux)
		{
			while (headAux->pNext != head)
				headAux = headAux->pNext;
			printf("\nHead - ");
			printInfo(headAux->pNext->info);
		}*/
		#pragma endregion

		#pragma region SimpleListC_Tail
		//printf("\n---\n");
		//printf("\nHead - ");
		//if (tail)
			//printInfo(tail->pNext->info);

		//printf("\n---\n");

		//tail = insertListOnPos_Val(tail, dummyInfo, insPos);
		//insertListOnPos_Ref(&tail, dummyInfo, insPos);

		//tail = insertListAfterPos_Val(tail, dummyInfo, insPos);
		//insertListAfterPos_Ref(&tail, dummyInfo, insPos);
		//printList(tail);

		//printf("\n---\n");

		//tail = deleteListPos_Val(tail, delPos);
		//deleteListPos_Ref(&tail, delPos);
		//printList(head);

		//tail = deleteAllCond_Val(tail, size);
		//deleteAllCond_Ref(&tail, size);
		//printList(tail);

		//printf("\n---\n");
		//printf("\nHead - ");
		//if (tail)
			//printInfo(tail->pNext->info);
		#pragma endregion

		#pragma region DoubleListNonC
		/*printf("\n---\n");
		printf("\nTail - ");
		if (doubleList.tail)
		printInfo(doubleList.tail->info);
		printf("\nPrev Tail - ");
		if (doubleList.tail->pPrev)
		printInfo(doubleList.tail->pPrev->info);*/

		//printf("\n---\n");

		//doubleList = insertListOnPos_Val(doubleList, dummyInfo, insPos);
		//insertListOnPos_Ref(&doubleList, dummyInfo, insPos);

		//doubleList = insertListAfterPos_Val(doubleList, dummyInfo, insPos);
		//insertListAfterPos_Ref(&doubleList, dummyInfo, insPos);
		//printList(doubleList);

		//printf("\n---\n");

		//doubleList = deleteListPos_Val(doubleList, delPos);
		//deleteListPos_Ref(&doubleList, delPos);
		//printList(doubleList);

		//doubleList = deleteAllCond_Val(doubleList, size);
		//deleteAllCond_Ref(&doubleList, size);
		//printList(doubleList);

		/*printf("\n---\n");
		printf("\nTail - ");
		if (doubleList.tail) {
			printInfo(doubleList.tail->info);
			printf("\nPrev Tail - ");
			if (doubleList.tail->pPrev)
				printInfo(doubleList.tail->pPrev->info);
			else
				printf(" No Prev of Tail");
		}
		else
			printf(" No Tail");*/
		#pragma endregion

		#pragma region Stack
		//printStack(&topStack);

		//printf("\n---\n");

		//topStack = deleteStack_Val(topStack);
		//deleteStack_Ref(&topStack);
		//printStack(&topStack);

		//printf("\n---\n");

		//topStack = deleteStackCond_Val(topStack);
		//deleteStackCond_Ref(&topStack);
		//printStack(&topStack);
		#pragma endregion

		#pragma region Queue
		//printQueue(&queueHead);

		//printf("\n---\n");

		//queueHead = deleteQueue_Val(queueHead);
		//deleteQueue_Ref(&queueHead);
		//printQueue(&queueHead);

		//printf("\n---\n");

		//queueHead = deleteQueueCond_Val(queueHead);
		//deleteQueueCond_Ref(&queueHead);
		//printQueue(&queueHead);
		#pragma endregion

		#pragma region PriorityQueue
		//printf("\n---\n");
		//printPQ(pQueue);

		/*NodeInfo* peeked = peekPQ(pQueue);
		printf("\nMax Priority: ");
		printInfo(peeked);*/

		//NodeInfo* gotten = getPQ(&pQueue);
		//printf("\nMax Priority: ");
		//printInfo(gotten);

		//printf("\n---\n");
		//printPQ(pQueue);
		#pragma endregion

	}
	int a = 2;
}