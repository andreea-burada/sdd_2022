#define LINE_BUFFEER 1024
#define FILE_NAME "Rooms.txt"
#define _CRT_SECURE_NO_WARNINGS

//		requirements
/*Write the source code sequence to create a Binary Search Tree structure that represents a hotel with different
types of rooms. The insertion key is a composite key made of two fields: floor and room number. The insertion of
a room is implemented in the main function for at least 10 elements taken from an input file. 

Write and call the function for extracting the subtree whose root is received as a parameter by specifying the
composite insertion key. After extraction, the initially remaining tree will be displayed, as well as the extracted
one.

Write and call the function for determining the total income for a certain type of room on a certain floor of the
hotel, values received as parameters, assuming that the hotel is fully booked.

Write and call the function to display all the elements in the tree structure grouped by each level in the tree.

Write and call the function to display all the rooms grouped by each floor of the hotel, having O(n) complexity for
the binary search tree structure
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>
#include "minmax.h"

typedef enum FloorNo { XO = 0, I = 1, II = 2, III = 3, IV = 4, V = 5, VI = 6, VII = 7, VIII = 8, IX = 9, X = 10 } FloorNo;

typedef struct Room
{
	FloorNo floorNo;
	int roomNo;
	char* roomType;
	float price;
} Room, NodeInfo;

typedef struct BST
{
	struct BST* leftChild;
	NodeInfo* info;
	struct BST* rightChild;
}BinarySearchTree, BinaryNode;

typedef struct TotalCost
{
	char* clientName;
	float totalCost;
} TotalCost;

NodeInfo* createNodeInfo(FloorNo, int, char*, float);
void printInfo(NodeInfo*);
int calcKey(FloorNo, int);	// floor no * 1000 + room no

BinaryNode* createNode(NodeInfo*);

void printInfo(NodeInfo*);

void insertBST(BinarySearchTree**, NodeInfo*);

void deleteBST(BinarySearchTree**, int);
void logicalDeletion(BinarySearchTree**, BinarySearchTree**);

void inorder_LPR(BinarySearchTree*);
void inorder_PLR(BinarySearchTree*);
void inorder_LRP(BinarySearchTree*);

void extractSubtree(BinarySearchTree**, BinarySearchTree**, int);
void totalIncome(float*, FloorNo, char*, BinarySearchTree*);

void printTreeByLevel(BinarySearchTree*);
void printLevel(BinarySearchTree*, int);
short height(BinarySearchTree*);

void printByFloor(BinarySearchTree*, FloorNo*, FloorNo*);

void main()
{
	// define data structure
	BinarySearchTree* bTree = NULL;
	// floor(roman),roomNo,roomType,price
	FILE* pFile = fopen(FILE_NAME, "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	FloorNo fNo; int rNo; char* rType; float price;
	int size = 0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			//floor no
			token = strtok(lineBuffer, sepList);
			// case for 
			if (strcmp(token, "I") == 0)
				fNo = (FloorNo)I;
			else if (strcmp(token, "II") == 0)
				fNo = (FloorNo)II;
			else if (strcmp(token, "III") == 0)
				fNo = (FloorNo)III;
			else if (strcmp(token, "IV") == 0)
				fNo = (FloorNo)IV;
			else if (strcmp(token, "V") == 0)
				fNo = (FloorNo)V;
			else if (strcmp(token, "VI") == 0)
				fNo = (FloorNo)VI;
			else if (strcmp(token, "VII") == 0)
				fNo = (FloorNo)VII;
			else if (strcmp(token, "VIII") == 0)
				fNo = (FloorNo)VIII;
			else if (strcmp(token, "IX") == 0)
				fNo = (FloorNo)IX;
			else if (strcmp(token, "X") == 0)
				fNo = (FloorNo)X;
			//fNo = (FloorNo)token;
			
			//roomNo
			token = strtok(NULL, sepList);
			rNo = atoi(token);

			//roomType
			rType = strtok(NULL, sepList);
		
			//price
			token = strtok(NULL, sepList);
			price = atof(token);

			NodeInfo* info = createNodeInfo(fNo, rNo, rType, price);

			// insert into data structure
			insertBST(&bTree, info);

			size++;
		}
		// print data structure
		printf("\n\tIn-order: left / root / right\n");
		inorder_LPR(bTree);

		/*printf("\n\tPre-order: root / left / right\n");
		inorder_PLR(bTree);*/

		/*printf("\n\tPost-order: left / right / root\n");
		inorder_LRP(bTree);*/

		/*BinarySearchTree* subTree = NULL;
		int subTKey = calcKey(II, 4);
		extractSubtree(&subTree, &bTree, subTKey);

		printf("\n---\n");

		printf("\n\tIn-order: left / root / right\n");
		inorder_LPR(bTree);

		printf("\n\tIn-order: left / root / right\n");
		inorder_LPR(subTree);*/

		/*float cost = 0.0;
		FloorNo findFloor = III;
		char* findRoom = "Deluxe";
		totalIncome(&cost, findFloor, findRoom, bTree);
		printf("\n\nTotal cost of floor %2d, room %-15s: %.3f\n", findFloor, findRoom, cost);

		printf("\n---\n\n");
		printTreeByLevel(bTree);*/
		printf("\n---\n");
		FloorNo f1 = XO, f2 = XO;
		printByFloor(bTree, &f1, &f2);
	}
	else
	{
		printf("File \"%s\" could not be opened.\n", FILE_NAME);
	}
	int a = 2;
}


//void insertSubTree(BinarySearchTree** root, BinaryNode* toAdd)
//{
//	if (*root == NULL)
//	{
//		*root = toAdd;
//	}
//	else
//	{
//		if ((*root)->info->idEvent > toAdd->info->idEvent)
//			insertSubTree(&(*root)->leftChild, toAdd);
//		else if ((*root)->info->idEvent < toAdd->info->idEvent)
//			insertSubTree(&(*root)->rightChild, toAdd);
//		else
//			(*root) = toAdd;
//	}
//}


void extractSubtree(BinarySearchTree** subTreeRoot, BinarySearchTree** root, int newRootKey)
{
	// we traverse until one of the children is the root of the subtree
	// when we find it, we cut the link between root and child
	if (*root)
	{	
		if((*root)->rightChild)
			if (calcKey((*root)->rightChild->info->floorNo, (*root)->rightChild->info->roomNo) == newRootKey)
			{
				*subTreeRoot = (*root)->rightChild;
				// cut the link
				(*root)->rightChild = NULL;
				return;	// exit the function
			}
		if ((*root)->leftChild)
			if (calcKey((*root)->leftChild->info->floorNo, (*root)->leftChild->info->roomNo) == newRootKey)
			{
				*subTreeRoot = (*root)->leftChild;
				// cut the link
				(*root)->leftChild = NULL;
				return;	// exit the function
			}
		extractSubtree(&(*subTreeRoot), &((*root)->leftChild), newRootKey);
		extractSubtree(&(*subTreeRoot), &((*root)->rightChild), newRootKey);
	}
}
void totalIncome(float* totalI, FloorNo fNo, char* rType, BinarySearchTree* root)
{
	if (root)
	{	
		if (rType == NULL)
			return;
		// is the room on the floor and of the same type?
		if (root->info->floorNo == fNo && strcmp(root->info->roomType, rType) == 0)
		{
			*totalI += root->info->price;
		}
		totalIncome(&(*totalI), fNo, rType, root->leftChild);
		totalIncome(&(*totalI), fNo, rType, root->rightChild);
	}
}

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
short height(BinarySearchTree* root)
{
	if (root)
		return 1 + max(height(root->leftChild), height(root->rightChild));
	else
		return 0;
}

void printByFloor(BinarySearchTree* root, FloorNo* currentF, FloorNo* prevF)
{
	if (root)
	{
		printByFloor(root->leftChild, &(*currentF), &(*prevF));
		*currentF = root->info->floorNo;
		if (*currentF != *prevF)
		{
			printf("\n\nFloor %2d\n---\n", root->info->floorNo);
			*prevF = *currentF;
		}
		printInfo(root->info);
		printByFloor(root->rightChild, &(*currentF), &(*prevF));
	}
}

BinarySearchTree* createNode(NodeInfo* info)
{
	BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	node->info = info;
	node->leftChild = node->rightChild = NULL;
	return node;
}
int calcKey(FloorNo fNo, int rNo)
{
	return fNo * 1000 + rNo;
}


void insertBST(BinarySearchTree** root, NodeInfo* info)
{
	if (*root == NULL)
	{
		*root = createNode(info);
	}
	else
	{
		int rootKey = calcKey((*root)->info->floorNo, (*root)->info->roomNo);
		int infoKey = calcKey(info->floorNo, info->roomNo);
		if (rootKey > infoKey)
			insertBST(&(*root)->leftChild, info);
		else if (rootKey < infoKey)
			insertBST(&(*root)->rightChild, info);
		else
			(*root)->info = info;
	}
}



void deleteBST(BinarySearchTree** root, int key)
{
	if (*root != NULL)
	{
		int rootKey = calcKey((*root)->info->floorNo, (*root)->info->roomNo);
		if (rootKey > key)
			deleteBST(&(*root)->leftChild, key);
		else if (rootKey < key)
			deleteBST(&(*root)->rightChild, key);
		else
		{
			if ((*root)->leftChild == NULL && (*root)->rightChild == NULL)
			{
				free((*root)->info->roomType);
				free((*root)->info);
				free((*root));
				*root = NULL;
			}
			else if ((*root)->leftChild == NULL || (*root)->rightChild == NULL)
			{
				BinarySearchTree* desc = NULL;
				if ((*root)->leftChild)
					desc = (*root)->leftChild;
				else
					desc = (*root)->rightChild;
				free((*root)->info->roomType);
				free((*root)->info);
				free((*root));
				*root = desc;
			}
			else
				logicalDeletion(root, &(*root)->leftChild);
		}
	}
}
void logicalDeletion(BinarySearchTree** root, BinarySearchTree** leftSubTree)
{
	if ((*leftSubTree)->rightChild)
		logicalDeletion(root, &(*leftSubTree)->rightChild);
	else
	{
		NodeInfo* tmp = (*root)->info;
		(*root)->info = (*leftSubTree)->info;
		BinarySearchTree* aux = (*leftSubTree);
		(*leftSubTree) = (*leftSubTree)->leftChild;
		free(tmp->roomType);
		free(tmp);
		free(aux);
	}
}



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
void inorder_LRP(BinarySearchTree* root) {

	if (root)
	{
		inorder_LRP(root->leftChild);
		inorder_LRP(root->rightChild);
		printInfo(root->info);
	}
}

NodeInfo* createNodeInfo(FloorNo fNo, int roomNo, char* roomT, float price)
{
	NodeInfo* toReturn = (NodeInfo*)malloc(sizeof(NodeInfo));
	if (toReturn != NULL)
	{
		toReturn->floorNo = fNo;
		toReturn->roomNo = roomNo;

		toReturn->roomType = (char*)malloc(strlen(roomT) + 1);
		if (toReturn->roomType) {
			strcpy(toReturn->roomType, roomT);
		}

		toReturn->price = price;

	}
	return toReturn;
}

// printing a NodeInfo
void printInfo(NodeInfo* info)
{
	if (info)
	{
		char floorC[5] = {0};
		switch (info->floorNo) {
		case I: {
			strcpy(floorC, "I");
			break;
		}
		case II: {
			strcpy(floorC, "II");
			break;
		}
		case III: {
			strcpy(floorC, "III");
			break;
		}
		case IV: {
			strcpy(floorC, "IV");
			break;
		}
		case V: {
			strcpy(floorC, "V");
			break;
		}
		case VI: {
			strcpy(floorC, "VI");
			break;
		}
		case VII: {
			strcpy(floorC, "VII");
			break;
		}
		case VIII: {
			strcpy(floorC, "VIII");
			break;
		}
		case IX: {
			strcpy(floorC, "IX");
			break;
		}
		case X: {
			strcpy(floorC, "X");
			break;
		}
		}
		printf("Floor: %4s, Room: %4d, Type: %15s, Price: %.3f\n", floorC,
			info->roomNo,
			info->roomType,
			info->price);
	}
	else
		printf("No data to print!");
}