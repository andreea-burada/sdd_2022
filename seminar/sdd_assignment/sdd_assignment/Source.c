#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#define FILE_NAME "data.txt"
#define LINE_BUFFEER 1024

//							----------------------- RED-BLACK TREE -----------------------
/*
	For this assignment I chose the Red-Black Tree. The reason why I chose this data structure is because it is similar to
the AVL tree but it is used in different cases. The main difference is that the AVL Tree is more balanced but it may cause 
more rotations during the insertion and deletion. Consequently, if our problem involved a lot of insertions and deletions, 
a Red-Black Tree is a better choice. On the other hand, if our problem has more frequent searches then the AVL Tree is better
(I will use implementations from the AVL tree because there are a lot of similarities between the two)

Properties:
	- the root is always BLACK
	- the leaves are always BLACK
	- there are no adjacent RED nodes (a red node cannot have a red parent/child)
	- the height of an Red-Black Tree is always O(log n); n - no. of nodes
*/

typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} Employee, NodeInfo;

// black - 0 ; red - 1
typedef enum Colour { BLACK = 0, RED = 1 };




/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
void printInfo(NodeInfo* info);

/*functions signatures for Red-Black Tree operations*/


void main()
{
	FILE* pFile = fopen(FILE_NAME, "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
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

			NodeInfo* info = createInfo(code, name, dept, salary);
			// insert call

		}
		// print/traverse call
		
		// delete call

	}
}

void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s, Salary: %f\n", info->code, info->name, info->salary);
	else
		printf("No data to print!");
}

NodeInfo* createInfo(short code, char* name, char* dept, double salary)
{
	struct Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->dept = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->dept, dept);
	emp->salary = salary;
	return emp;
}