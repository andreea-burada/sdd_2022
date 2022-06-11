#define LINE_BUFFEER 1024
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
// include all DS .h files
// careful about ambiguity
#include "List_Simple/List_Simple_NonC.h"

void main()
{
	// define data structure
	SimpleListNonC* head = NULL;

	FILE* pFile = fopen("Data.txt", "r");
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
			//head = insertHead_Val(head, info);
			//insertHead_Ref(&head, info);
			//head = insertTail_Val(head, info);
			insertTail_Ref(&head, info);
			size++;
		}
		// print data structure
		printList(head);

		// do other data structure specific actions and test

		///*printf("\n---\n");*/
		//int insPos = 10;
		//NodeInfo* dummyInfo = createNodeInfo(10013, "Margaret Sinclair", "Cybersecurity", 23043.12);
		////head = insertListPos_Val(head, dummyInfo, pos);
		//insertListOnPos_Ref(&head, dummyInfo, insPos);
		//printList(head);

		//printf("\n---\n");
		//int delPos = 8;
		////head = deleteListPos_Val(head, delPos);
		//deleteListPos_Ref(&head, delPos);
		//printList(head);

		printf("\n---\n");
		head = deleteAllCond_Val(head, size);
		//deleteAllCond_Ref(&head, size);
		printList(head);
	}
	int a = 2;
}