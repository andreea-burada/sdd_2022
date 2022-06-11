#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#define LINE_BUFFEER 1024
#define FILE_NAME "data.txt"

//		----------------------- Treap - Randomized Binary Search Tree -----------------------
/*
	For this assignment I chose the Randomized Binary Search Tree. The reason why
 I chose this data structure is that I found it interestince since it combines
 binary trees and binary heaps

 (I will use similar implementations from the AVL tree)

 The keys of nodes are employee ids and the proprities are randomized

 Rotations on the tree are performed in order to retain the priority property

 Using a Treap we can get the maximum priority node with O(1) complexity
*/

typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} Employee, NodeInfo;

typedef struct TreapNode
{
	NodeInfo* info;
	int priority;
	struct TreapNode* leftChild;
	struct TreapNode* rightChild;
} TreapNode, TreapTree;


/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
TreapNode* createNode(NodeInfo* info);
void printInfo(NodeInfo* info);
void printTreeByLevel(TreapNode*);
void printLevel(TreapNode*, int);
void inorder_LPR(TreapNode*);
void inorder_PLR(TreapNode*);
void inorder_RPL(TreapNode*);

/*functions signatures for Treap structure's operations*/
TreapNode* search(TreapNode*, int);
TreapNode* insertTreap(TreapNode*, NodeInfo*);
TreapNode* deleteNode(TreapNode*, int);
TreapNode* rightRotate(TreapNode* );
TreapNode* leftRotate(TreapNode* );



void main()
{
	TreapTree* root = NULL;
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
			//insert call
			root = insertTreap(root, info);
		}

		//print call
		//inorder_LPR(root);
		printTreeByLevel(root);

		//delete call
		root = deleteNode(root, 10002);
		printf("\n --- After deletion ---\n\n\n");
		printTreeByLevel(root);

		/*root = deleteNode(root, 10020);
		printf("\n ---After deletion ---\n\n");
		printTreeByLevel(root);*/

		printf("\nThe maximum priority node is: \n");
		printInfo(root->info);
	}
	int a = 2;
}

TreapNode* leftRotate(TreapNode* pivot)
{
	TreapNode* desc = pivot->rightChild;
	pivot->rightChild = desc->leftChild;
	desc->leftChild = pivot;

	return desc;
}

TreapNode* rightRotate(TreapNode* pivot)
{
	TreapNode* desc = pivot->leftChild;
	pivot->leftChild = desc->rightChild;
	desc->rightChild = pivot;

	return desc;
}

// search function
// key - employee code
TreapNode* search(TreapNode* root, int key)
{
	// check if the node we are searching for is the root
	if (root == NULL || root->info->code == key)
		return root;
	// if key is bigger than current key -> the node is in the right subtree
	if (root->info->code < key)
		return search(root->rightChild, key);
	// if key is smaller than current key -> the node is in the left subtree
	else 
		return search(root->leftChild, key);
}

TreapNode* insertTreap(TreapNode* root, NodeInfo* info)
{
	if (!root) {
		TreapNode* newNode = createNode(info);
		return newNode;
	}

	if (info->code <= root->info->code)
	{
		root->leftChild = insertTreap(root->leftChild, info);
		// fixing property
		if (root->leftChild->priority > root->priority)
			root = rightRotate(root);
	}
	else
	{
		root->rightChild = insertTreap(root->rightChild, info);
		if (root->rightChild->priority > root->priority)
			root = leftRotate(root);
	}
	return root;
}

TreapNode* deleteNode(TreapNode* root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->info->code)
		root->leftChild = deleteNode(root->leftChild, key);
	else if (key > root->info->code)
		root->rightChild = deleteNode(root->rightChild, key);

	// when we reach this code we found the node with our key
	// if left child is null -> the node to delete is the right one
	else if (root->leftChild == NULL)
	{
		TreapNode* toReplace = root->rightChild;
		free(root->info->name);
		free(root->info->dept);
		free(root->info);
		free(root);
		root = toReplace; 
	}
	else if (root->rightChild == NULL)
	{
		TreapNode* toReplace = root->leftChild;
		free(root->info->name);
		free(root->info->dept);
		free(root->info);
		free(root);
		root = toReplace; 
	}
	// if we have both children we readjust priorities
	else if (root->leftChild->priority < root->rightChild->priority)
	{
		root = leftRotate(root);
		root->leftChild = deleteNode(root->leftChild, key);
	}
	else
	{
		root = rightRotate(root);
		root->rightChild = deleteNode(root->rightChild, key);
	}

	return root;
}

// printing in ascending order
void inorder_LPR(TreapNode* root) {
	if (root)
	{
		inorder_LPR(root->leftChild);
		printInfo(root->info);
		inorder_LPR(root->rightChild);
	}
}

// printing the root first then in ascending order
void inorder_PLR(TreapNode* root) {
	if (root)
	{
		printInfo(root->info);
		inorder_PLR(root->leftChild);
		inorder_PLR(root->rightChild);
	}
}

// printing in descending order
void inorder_RPL(TreapNode* root) {
	if (root)
	{
		inorder_RPL(root->rightChild);
		printInfo(root->info);
		inorder_RPL(root->leftChild);
	}
}

void printLeaves(TreapNode* root)
{
	if (root)
	{
		if (root->leftChild == NULL && root->rightChild == NULL)
			printInfo(root->info);
		printLeaves(root->leftChild);
		printLeaves(root->rightChild);
	}
}

short height(TreapNode* root)
{
	if (root)
		return 1 + max(height(root->leftChild), height(root->rightChild));
	else
		return 0;
}

// print tree level by level - O(n*h); h - height
void printTreeByLevel(TreapNode* root)
{
	int treeHeight = height(root);
	for (int i = 1; i <= treeHeight; i++)
	{
		if (i == 1)
			printf("Root\n");
		else
			printf("Level %d\n", i);
		printLevel(root, i);
		printf("\n");
	}
}

void printLevel(TreapNode* root, int lvl)
{
	if (lvl != 1)
	{
		if (root->leftChild)
			printLevel(root->leftChild, lvl - 1);
		if (root->rightChild)
			printLevel(root->rightChild, lvl - 1);
	}
	else {
		printInfo(root->info);
		printf("\tPriority: %d", root->priority);
		if (root->leftChild)
			printf(" ; LeftC: %d", root->leftChild->info->code);
		if (root->rightChild)
			printf(" ; RightC: %d", root->rightChild->info->code);
		printf("\n");
	}
}

void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s, Salary: %.2f\n", info->code, info->name, info->salary);
	else
		printf("No data to print!");
}

TreapNode* createNode(NodeInfo* info)
{
	TreapNode* toReturn = (TreapNode*)malloc(sizeof(TreapNode));
	if (toReturn) {
		toReturn->info = info;
		toReturn->leftChild = NULL;
		toReturn->rightChild = NULL;
		toReturn->priority = rand() % 100;	// random priority value
	}
	return toReturn;
}

NodeInfo* createInfo(short code, char* name, char* dept, double salary)
{
	struct Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
	if (emp) {
		emp->code = code;
		emp->name = (char*)malloc(strlen(name) + 1);
		emp->dept = (char*)malloc(strlen(dept) + 1);
		if (emp->name && emp->dept) {
			strcpy(emp->name, name);
			strcpy(emp->dept, dept);
		}
		emp->salary = salary;
	}
	return emp;
}
