// ------------------ seminar 13 -------------------
#define _CRT_SECURE_NO_WARNINGS
#define LINE_BUFFEER 1024
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"

/*
	- AVL Tree
	- if we want a balanced binary tree, we have to start with balanced and keep it that way
	- because the rotations only apply to was before an insertion/deletion
		-> when we insert we need to check the balance (equilibrium factor ?) and rebalance if needed
		( balance factor -> increases when we lean on one side -> we search for nodes with a balance factor 
		outside a certain set: {-1, 0, 1})
		-> -1 for left side; 1 for right side
		-> when we do a rotation and the signs of the pivot and the descendant are different -> DOUBLE ROTATION
		-> first rotation is on the descendent then on the pivot (the incorrect node)
			-> positive balance factor out of the set -> ROTATION TO THE LEFT
			-> negative balance factor out of the set -> ROTATION TO THE RIGHT

	- BALANCE FACTOR CALCULATION: height[right_subtree] - height[left_subtree]

						pivot ->
	desc/pivot		-	  |	    +
   _______________________|____________
  d		-		RR(pivot) | RR(desc)
  e						  | LR(pivot)
  s
  c		+		LR(desc)	LR(pivot)
  |				RR(pivot)
 \ / 
*/

// general tree definition
typedef struct GeneralTreeNode {
	int into;
	struct GeneralTreeNode** descendants;
	int noDescendants;
} GeneralTreeNode;

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
	short bFactor;	// balance factor for a node -> 0 by default
} Node, BinaryNode, BinaryTree, BinarySearchTree;

/* functions signatures for memory management */
NodeInfo* createInfo(short, char*, char*, double);
BinaryNode* createNode(NodeInfo* info);
void printInfo(NodeInfo* info);

/* functions signatures for Binary Search Trees AVL operations */
void insertBinaryTree(BinaryTree**, NodeInfo*);
BinarySearchTree* leftRotation(BinarySearchTree*);
BinarySearchTree* rightRotation(BinarySearchTree*);
BinarySearchTree* rebalance(BinarySearchTree*);
void printTreeByLevel(BinarySearchTree*);
void printLevel(BinarySearchTree*, int);
short height(BinaryTree*);
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
			inorder_PLR(binaryTree);
			//inorder_RPL(binaryTree);
		}

		// inorder_LPR(binaryTree);
		// inorder_PLR(binaryTree);
		printf("\n\n");
		printTreeByLevel(binaryTree);

	}
	int a = 2;
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
	toReturn->bFactor = 0;

	return toReturn;
}

void insertBinaryTree(BinarySearchTree** root, NodeInfo* info)
{
	// BinaryTree* aux = *root;

	if (*root == NULL) {		// the end of the recursivity
		BinaryNode* newNode = createNode(info);
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
	// rebalancing the BST
	*root = rebalance(*root);

}

BinarySearchTree* leftRotation(BinarySearchTree* pivot)
{
	BinarySearchTree* desc = pivot->rightChild;
	pivot->rightChild = desc->leftChild;
	desc->leftChild = pivot;

	return desc;
}

BinarySearchTree* rightRotation(BinarySearchTree* pivot)
{
	BinarySearchTree* desc = pivot->leftChild;
	pivot->leftChild = desc->rightChild;
	desc->rightChild = pivot;

	return desc;
}

// rebalancing the BST
BinarySearchTree* rebalance(BinarySearchTree* root)
{
	BinarySearchTree* desc = NULL;
	// recalculating the balance factor
	root->bFactor = height(root->rightChild) - height(root->leftChild);
	if (root->bFactor == -2)
	{
		desc = root->leftChild;
		if (desc->bFactor == -1)
		{
			// single rotation
			// RIGHT ROTATION on pivot
			root = rightRotation(root);
		}
		else
		{
			// double rotation
			// LEFT ROTATION on desc -> RIGHT ROTATION on pivot
			root->leftChild = leftRotation(desc);
			root = rightRotation(root);
		}
	}
	else if (root->bFactor == 2)
	{
		desc = root->rightChild;
		if (desc->bFactor == -1)
			root->rightChild = rightRotation(desc);
		root = leftRotation(root);
	}

	return root;
}

short height(BinaryTree* root)
{
	if (root)
		return 1 + max(height(root->leftChild), height(root->rightChild));
	else
		return 0;
}


void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s\n", info->code, info->name);
	else
		printf("No data to print!");
}


// printing in ascending order
void inorder_LPR(BinarySearchTree* root) {
	if (root)
	{
		inorder_LPR(root->leftChild);
		printInfo(root->info);
		inorder_LPR(root->rightChild);
	}
}

// printing the root first then in ascending order
void inorder_PLR(BinarySearchTree* root) {
	if (root)
	{
		printInfo(root->info);
		inorder_PLR(root->leftChild);
		inorder_PLR(root->rightChild);
	}
}

// printing in descending order
void inorder_RPL(BinarySearchTree* root) {
	if (root)
	{
		inorder_RPL(root->rightChild);
		printInfo(root->info);
		inorder_RPL(root->leftChild);
	}
}

void printLeaves(BinarySearchTree* root)
{
	if (root)
	{
		if (root->leftChild == NULL && root->rightChild == NULL)
			printInfo(root->info);
		printLeaves(root->leftChild);
		printLeaves(root->rightChild);
	}
}

// print tree level by level - O(n*h); h - height
void printTreeByLevel(BinarySearchTree* root)
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

void printLevel(BinarySearchTree* root, int lvl)
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
	}
}
