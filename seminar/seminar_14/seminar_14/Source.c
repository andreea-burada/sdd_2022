//#define _CRT_SECURE_NO_WARNINGS
//#include "stdio.h"
//#include "stdlib.h"
//#include "memory.h"
//#include "string.h"
//
///*
//	- adjacency lists or storing the neighbours of a node
//	- directed and undirected nodes
//	- (array of lists -> chained hash tables)
//*/
//typedef struct Employee
//{
//	short code;
//	char* name;
//	char* dept;
//	double salary;
//} Employee, NodeInfo;
//
//typedef struct MainList
//{
//	NodeInfo* info;
//	struct MainList* nextNode;
//	struct Neighbour* neighbours;
//} MainList, Vertex;
//
//typedef struct Neighbour
//{
//	Vertex* vertex;
//	struct Neighbour* nextAdj;
//} Neighbour;
//
//typedef struct Employee NodeInfo;
//
//
//#define LINE_BUFFEER 1024
///*functions signatures for memory management*/
//NodeInfo* createInfo(short, char*, char*, double);
//void printInfo(NodeInfo* info);
///*functions signatures for graphs structure's operations*/
//Vertex* createVertex(NodeInfo*);
//Neighbour* createNeighbour(Vertex*);
//void addNode(Vertex**, NodeInfo*);
//void addConnection(Vertex*, short, short);
//Neighbour* addNeighbour(Vertex*, Vertex*);
//void displayGraph(Vertex*);
//
//void main()
//{
//	Vertex* graph = NULL;	// main list of nodes
//	FILE* pFile = fopen("Data.txt", "r");
//	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
//	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
//	if (pFile)
//	{
//		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
//		{
//			token = strtok(lineBuffer, sepList);
//			code = atoi(token);
//			name = strtok(NULL, sepList);
//			dept = strtok(NULL, sepList);
//			token = strtok(NULL, sepList);
//			salary = atof(token);
//
//			NodeInfo* info = createInfo(code, name, dept, salary);
//			//insert call
//			addNode(&graph, info);
//		}
//
//		addConnection(graph, 10001, 10010);
//		addConnection(graph, 10001, 10009);
//		addConnection(graph, 10002, 10005);
//		addConnection(graph, 10003, 10004);
//		addConnection(graph, 10003, 10010);
//		addConnection(graph, 10004, 10006);
//		addConnection(graph, 10005, 10006);
//		addConnection(graph, 10007, 10010);
//		addConnection(graph, 10008, 10009);
//
//		displayGraph(graph);
//	}
//}
//
//
//
//void addNode(Vertex** graph, NodeInfo* info)
//{
//	Vertex* node = createVertex(info);
//
//	// insertion at the beginning of the list of vertices
//	/*node->nextNode = *graph;
//	*graph = node;*/
//
//	// insertion at the end of the list of vertices
//	// CHECK IF THE LIST OF LISTS IS NULL (EMPTY AT THE BEGINNING)
//	if (*graph == NULL)
//	{
//		*graph = node;
//	}
//	else {
//		Vertex* aux = *graph;
//		while (aux->nextNode)
//		{
//			aux = aux->nextNode;
//		}
//		aux->nextNode = node;
//	}
//
//}
//
//
//Neighbour* addNeighbour(Vertex* src, Vertex* dst)
//{
//	// adding at the head of the list
//	Neighbour* newNeighbour = createNeighbour(dst);
//	newNeighbour->nextAdj = src->neighbours;
//
//	return newNeighbour;
//}
//
//// adding the connection -> V1 with V2 and V2 with V1 (non-directed graph)
//// we pass the keys of the vertices to find V1 and V2 in the MainList
//void addConnection(Vertex* graph, short src, short dst)
//{
//	Vertex* srcNode = NULL, * dstNode = NULL;
//	while (graph && (srcNode == NULL || dstNode == NULL))
//	{
//		if (graph->info->code == src)
//			srcNode = graph;
//		if (graph->info->code == dst)
//			dstNode = graph;
//
//		graph = graph->nextNode;
//	}
//
//	if (srcNode != NULL && dstNode != NULL) {
//		// V1 with V2
//		srcNode->neighbours = addNeighbour(srcNode, dstNode);
//		// V2 with V1
//		if (src != dst)
//			dstNode->neighbours = addNeighbour(dstNode, srcNode);
//	}
//}
//
//Vertex* createVertex(NodeInfo* info)
//{
//	Vertex* toReturn = (Vertex*)malloc(sizeof(Vertex));
//	toReturn->info = info;
//	toReturn->neighbours = NULL;
//	toReturn->nextNode = NULL;
//
//	return toReturn;
//}
//
//Neighbour* createNeighbour(Vertex* info)
//{
//	Neighbour* toReturn = (Neighbour*)malloc(sizeof(Neighbour));
//	toReturn->nextAdj = NULL;
//	toReturn->vertex = info;
//
//	return toReturn;
//}
//
//NodeInfo* createInfo(short code, char* name, char* dept, double salary)
//{
//	struct Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
//	emp->code = code;
//	emp->name = (char*)malloc(strlen(name) + 1);
//	strcpy(emp->name, name);
//	emp->dept = (char*)malloc(strlen(dept) + 1);
//	strcpy(emp->dept, dept);
//	emp->salary = salary;
//	return emp;
//}
//
//void displayGraph(Vertex* graph)
//{
//	while (graph)
//	{
//		printf("%d - neighbours:\n", graph->info->code);
//		Neighbour* listNeighbours = graph->neighbours;
//		while (listNeighbours)
//		{
//			printInfo(listNeighbours->vertex->info);
//			listNeighbours = listNeighbours->nextAdj;
//		}
//		printf("\n");
//		graph = graph->nextNode;
//	}
//}
//
//void printInfo(NodeInfo* info)
//{
//	if (info)
//		printf("Code: %d - Name: %s, Salary: %f\n", info->code, info->name, info->salary);
//	else
//		printf("No data to print!");
//}
//
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
};
typedef struct Employee NodeInfo;

struct Node
{
	NodeInfo* info;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	char color;
};
typedef struct Node RedBlackNode;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
void printInfo(NodeInfo* info);
/*functions signatures for ......... structure's operations*/
RedBlackNode* createNode(NodeInfo*);
void insertNode(RedBlackNode**, NodeInfo*);
RedBlackNode* fixTree(RedBlackNode*);
void leftRotate(RedBlackNode*);
void rightRotate(RedBlackNode*);
void printTree(RedBlackNode*);
RedBlackNode* searchNode(RedBlackNode*, short);
void deleteNode(RedBlackNode*, short);
void printTree(RedBlackNode*);


void main()
{
	RedBlackNode* root = NULL;
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
			//insert into the tree	
			insertNode(&root, info);
			//print the tree
			int a = 2;


		}

		//delete info from the tree structure
		//deleteNode(root, root);

		//print out the tree structure
		printTree(root);
	}
	int a = 2;
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

//function to create a new node with the given NodeInfo structure
RedBlackNode* createNode(NodeInfo* info)
{
	RedBlackNode* node = (RedBlackNode*)malloc(sizeof(RedBlackNode));
	node->info = info;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->color = 'R';
	return node;
}

//function to insert a NodeInfo into the tree structure
void insertNode(RedBlackNode** root, NodeInfo* info)
{
	RedBlackNode* node = createNode(info);
	if (*root == NULL)
	{
		*root = node;
		node->color = 'B';
	}
	else
	{
		RedBlackNode* current = *root;
		RedBlackNode* parent = NULL;
		while (current != NULL)
		{
			parent = current;
			if (current->info->code > info->code)
				current = current->left;
			else
				current = current->right;
		}
		if (parent->info->code > info->code)
		{
			parent->left = node;
			node->parent = parent;
		}
		else
		{
			parent->right = node;
			node->parent = parent;
		}
		fixTree(node);
	}
}

//function to rebalance the red-black tree after inserting a node
RedBlackNode* fixTree(RedBlackNode* node)
{
	RedBlackNode* parent = node->parent;
	RedBlackNode* grandParent = parent->parent;
	if (parent->color == 'R')
	{
		if (node == parent->left)
		{
			RedBlackNode* uncle = parent->right;
			if (uncle->color == 'R')
			{
				parent->color = 'B';
				uncle->color = 'B';
				grandParent->color = 'R';
				return fixTree(grandParent);
			}
			else
			{
				if (node == parent->right)
				{
					leftRotate(parent);
					node = parent;
					parent = node->parent;
				}
				rightRotate(grandParent);
				parent->color = 'B';
				grandParent->color = 'R';
			}
		}
		else
		{
			RedBlackNode* uncle = parent->left;
			if (uncle->color == 'R')
			{
				parent->color = 'B';
				uncle->color = 'B';
				grandParent->color = 'R';
				return fixTree(grandParent);
			}
			else
			{
				if (node == parent->left)
				{
					rightRotate(parent);
					node = parent;
					parent = node->parent;
				}
				leftRotate(grandParent);
				parent->color = 'B';
				grandParent->color = 'R';
			}
		}
	}
	return node;
}

//function to perform a left rotation
void leftRotate(RedBlackNode* root)
{
	RedBlackNode* rightChild = root->right;
	RedBlackNode* rightLeftChild = rightChild->left;
	root->right = rightLeftChild;
	if (rightLeftChild != NULL)
		rightLeftChild->parent = root;
	rightChild->parent = root->parent;
	if (root->parent == NULL)
		root->parent = rightChild;
	else if (root == root->parent->left)
		root->parent->left = rightChild;
	else
		root->parent->right = rightChild;
	rightChild->left = root;
	root->parent = rightChild;
}

//function to perform a right rotation
void rightRotate(RedBlackNode* root)
{
	RedBlackNode* leftChild = root->left;
	RedBlackNode* leftRightChild = leftChild->right;
	root->left = leftRightChild;
	if (leftRightChild != NULL)
		leftRightChild->parent = root;
	leftChild->parent = root->parent;
	if (root->parent == NULL)
		root->parent = leftChild;
	else if (root == root->parent->left)
		root->parent->left = leftChild;
	else
		root->parent->right = leftChild;
	leftChild->right = root;
	root->parent = leftChild;
}

//function to search for a NodeInfo in the tree structure
RedBlackNode* searchNode(RedBlackNode* root, short code)
{
	if (root == NULL)
		return NULL;
	else if (root->info->code == code)
		return root;
	else if (root->info->code > code)
		return searchNode(root->left, code);
	else
		return searchNode(root->right, code);
}

//function to printTree in pre-order	
void printTree(RedBlackNode* root)
{
	if (root != NULL)
	{
		printInfo(root->info);
		printTree(root->left);
		printTree(root->right);
	}
}