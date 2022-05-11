// ------------------ course 10 -------------------

// general tree definition
typedef struct GeneralTreeNode {
	int into;
	struct GeneralTreeNode** descendants;
	int noDescendants;
} GeneralTreeNode;

// binary tree definition - generic tree with maximum 2 descendants
//typedef struct BinaryNode {
//	int info;
//	struct BinaryNode* leftChild;
//	struct BinaryNode* rightChild;
//} BinaryNode;

// balance tree - nodes are inserted so that the tree stays balanced on its left and right side of descendants

// taxonomy binary trees -> the yes/no trees with questions

// --- binary search trees implementation ---
// through recursivity you can pass the information from the child back to the parent
// for trees, recursive implementations are recommended (to simplify the problem)
// the keys in a binary tree should be unique -> inserting an element with the same key -> overriding that element

#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFEER 1024
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} Employee, NodeInfo;

typedef struct BinaryNode {
	NodeInfo* info;
	struct BinaryNode* leftChild;
	struct BinaryNode* rightChild;
} Node, BinaryNode, BinaryTree, BinarySearchTree;

/* functions signatures for memory management */
NodeInfo * createInfo(short, char*, char*, double);
BinaryNode* createNode(NodeInfo* info);
void printInfo(NodeInfo * info);

/* functions signatures for Binary Trees operations */
void insertBinaryTree(BinaryTree**, NodeInfo*);
void inorder_LPR(BinaryTree*);
void inorder_PLR(BinaryTree*);
void inorder_RPL(BinaryTree*);

void main()
{
	BinarySearchTree* binaryTree = NULL;
	FILE* pFile = fopen("Data.txt", "r");
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
			insertBinaryTree(&binaryTree, info);

			printf("****************************************\n\n");

			//inorder_LPR(binaryTree);
			//inorder_PLR(binaryTree);
			inorder_RPL(binaryTree);
		}

		// inorder_LPR(binaryTree);
		// inorder_PLR(binaryTree);
	}
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

BinaryNode* createNode(NodeInfo* info)
{
	BinaryNode* toReturn = (BinaryNode*)malloc(sizeof(BinaryNode));
	toReturn->info = info;
	toReturn->leftChild = NULL;
	toReturn->rightChild = NULL;

	return toReturn;
}

void insertBinaryTree(BinaryTree** root, NodeInfo* info)
{
	// BinaryTree* aux = *root;
	
	if (*root == NULL) {		// the end of the recursivity
		BinaryNode* newNode = createNode(info);
		//return newNode;
		*root = newNode;
	}
	
	else
	{
		if ((*root)->info->code > info->code)
			// insert on the left side of the root
			insertBinaryTree(&((*root)->leftChild), info);
		else {
			if ((*root)->info->code < info->code)
				// insert to the right
				insertBinaryTree(&((*root)->rightChild), info);
			else {
				(*root)->info = info;	
			}
		}
	}

}

void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s\n", info->code, info->name);
	else
		printf("No data to print!");
}


// printing in ascending order
void inorder_LPR(BinaryTree* root) {
	if (root)
	{
		inorder_LPR(root->leftChild);
		printInfo(root->info);
		inorder_LPR(root->rightChild);
	}
}

// printing the root first then in ascending order
void inorder_PLR(BinaryTree* root) {
	if (root)
	{
		printInfo(root->info);
		inorder_PLR(root->leftChild);
		inorder_PLR(root->rightChild);
	}
}

// printing in descending order
void inorder_RPL(BinaryTree* root) {
	if (root)
	{
		inorder_RPL(root->rightChild);
		printInfo(root->info);
		inorder_RPL(root->leftChild);	
	}
}

