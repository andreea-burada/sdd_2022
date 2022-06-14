#define LINE_BUFFEER 1024
#define FILE_NAME "Reservations.txt"
#define _CRT_SECURE_NO_WARNINGS

//		requirements
/*Write the source code sequence to create a Binary Search Tree, refered as BST, that shall store clients’ reservations
as items of type Event*. Insertion key into the BST structure should be idEvent, next to other mandatory attributes like
ticketPrice(float), clientName(char*), eventDate(char[10]), and 2 other attributes at your choice. Inserting an event
into the BST structure is made in a function which is called when creating the tree. The structure will be populated with
at least 10 records read from an input file. (2p)

Write and call the function for retrieving the reservations from the BST structure created above, which have the event
date equal with a specified parameter of the function. Reservations are saved in an array and DO NOT share heap
memory areas with the ones from the BST structure. The array is returned in main() by using the return type or the list
of paramaters from the function.

Write and call the function for calculating the total cost per each client for all the reservations found in the BST structure.
The values that are calculated are saved in an array as pairs of two attributes (clientName, totalCost). The array and
its size are returned in main() by using the return type or the list of paramaters from the function.

Write and call the function for transforming the BST structure from the 1) requirement, into two complementary BST
structures, based on one of the optional attributes defined by you. The chosen attribute should have binary significance
in order to be able to split the main tree into two complementary structures. The resulted structures are to be returned in
main() and their content displayed at the console.

Write and call the function for transforming the BST structure from the 1) requirement, into two complementary BST
structures, based on one of the optional attributes defined by you. The chosen attribute should have binary significance
in order to be able to split the main tree into two complementary structures. The resulted structures are to be returned in
main() and their content displayed at the console.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>

typedef struct Event
{
	short idEvent;
	float ticketPrice;
	char* clientName;
	char eventDate[10];
	char* eventName;
	int noPeople;
} Event, NodeInfo;

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

NodeInfo* createNodeInfo(short, float, char*, char[10], char*, int);
void printInfo(NodeInfo*);

BinaryNode* createNode(NodeInfo*);

void printInfo(NodeInfo*);

void insertBST(BinarySearchTree**, NodeInfo*);

void deleteBST(BinarySearchTree**, int);
void logicalDeletion(BinarySearchTree**, BinarySearchTree**);

void inorder_LPR(BinarySearchTree*);
void inorder_PLR(BinarySearchTree*);
void inorder_LRP(BinarySearchTree*);

void arrayReservations(NodeInfo***, BinarySearchTree*, char*, int*);
void arrayTotalCost(TotalCost**, BinarySearchTree*, int*);
void arrayCalculateCost4Client(float*, BinarySearchTree*, char*);

void splitBST(BinarySearchTree**, BinarySearchTree**, BinarySearchTree**);
void saveNodes(BinaryNode***, BinarySearchTree*, int*);
void insertSubTree(BinarySearchTree**, BinaryNode*);


void main()
{
	// define data structure
	BinarySearchTree* bTree = NULL;
	// id,price,clientName,eventDate,eventName,noPeople
	FILE* pFile = fopen(FILE_NAME, "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	short id; int noP; float price; char* cName = NULL, eDate[10] = {0}, * eName = NULL;
	int size = 0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{	
			//id
			token = strtok(lineBuffer, sepList);
			id = atoi(token);
			//price
			token = strtok(NULL, sepList);
			price = atof(token);
			//clientNmae
			cName = strtok(NULL, sepList);
			//eventDate
			//token = strtok(NULL, sepList);
			token = strtok(NULL, sepList);
			for (int i = 0; i < 10; i++)
				eDate[i] = token[i];
			//eDate[10] = '\0';
			//strcpy(eDate, token);
			//eventName
			eName = strtok(NULL, sepList);
			//noPeople
			token = strtok(NULL, sepList);
			noP = atoi(token);

			NodeInfo* info = createNodeInfo(id, price, cName, eDate, eName, noP);

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

		int arraySize = 0;
		char* dateCriterion = "17/09/2022";
		NodeInfo** arrayOfReservations = NULL;
		arrayReservations(&arrayOfReservations, bTree, dateCriterion, &arraySize);

		printf("\n---\n\nEvents with date \"%s\"\n\n", dateCriterion);

		for (int i = 0; i < arraySize; i++)
			printInfo(arrayOfReservations[i]);



		int arrayCostSize = 0;
		TotalCost* arrayOfCosts = NULL;
		arrayTotalCost(&arrayOfCosts, bTree, &arrayCostSize);

		printf("\n---\n\n");

		for (int i = 0; i < arrayCostSize; i++)
		{
			printf("Client Name: %-20s; Total Cost: %.3f\n", arrayOfCosts[i].clientName, arrayOfCosts[i].totalCost);
		}

		BinarySearchTree* evenTree = NULL, * oddTree = NULL;
		splitBST(&bTree, &evenTree, &oddTree);

		printf("\n\tIn-order: left / root / right\n");
		inorder_LPR(evenTree);

		printf("\n\tIn-order: left / root / right\n");
		inorder_LPR(oddTree);

		// free-ing memory if necessarry
		while (bTree)
		{
			deleteBST(&bTree, bTree->info->idEvent);
		}
		if (bTree == NULL)
			printf("\nbTree BST is empty\n");

		while (evenTree)
		{
			deleteBST(&evenTree, evenTree->info->idEvent);
		}
		if (evenTree == NULL)
			printf("\nevenTree BST is empty\n");

		while (oddTree)
		{
			deleteBST(&oddTree, oddTree->info->idEvent);
		}
		if (oddTree == NULL)
			printf("\noddTree BST is empty\n");

		//freeing the two arrays
		if (arrayOfReservations)
		{
			for (int i = 0; i < arraySize; i++)
			{
				free(arrayOfReservations[i]->clientName);
				free(arrayOfReservations[i]->eventName);
				free(arrayOfReservations[i]);
			}
			free(arrayOfReservations);
			arrayOfReservations = NULL;
		}

		if (arrayOfCosts)
		{
			for (int i = 0; i < arrayCostSize; i++)
			{
				free(arrayOfCosts[i].clientName);
			}
			free(arrayOfCosts);
			arrayOfCosts = NULL;
		}
	}
	int a = 2;
}


// splitting the bst based on even and odd no. of guests
void splitBST(BinarySearchTree** root, BinarySearchTree** evenTree, BinarySearchTree** oddTree)
{
	
	// save all nodes in an array
	BinaryNode** arrayOfNodes = NULL;
	int arrayNodesSize = 0;
	saveNodes(&arrayOfNodes, *root, &arrayNodesSize);
	// reset children of nodes
	for (int i = 0; i < arrayNodesSize; i++)
	{
		arrayOfNodes[i]->leftChild = NULL;
		arrayOfNodes[i]->rightChild = NULL;
		// insert it in either even or odd tree
		if (arrayOfNodes[i]->info->noPeople % 2 == 0)
		{
			insertSubTree(&(*evenTree), arrayOfNodes[i]);
		}
		else
		{
			insertSubTree(&(*oddTree), arrayOfNodes[i]);
		}
	}
	free(arrayOfNodes);
	*root = NULL;
}
void saveNodes(BinaryNode*** arrayOfNodes, BinarySearchTree* root, int* size)
{
	if (root)
	{
		// if the condition is met -> add it to the array
		if (*arrayOfNodes == NULL)
		{
			*arrayOfNodes = (BinaryNode**)malloc(sizeof(BinaryNode*));
			//memset(arrayRes, NULL, sizeof(NodeInfo**) * (*size + 1));
			(*arrayOfNodes)[0] = root;
			*size = 1;
		}
		else
		{
			// resizing the array
			NodeInfo** newArray;
			newArray = (BinaryNode**)malloc(sizeof(BinaryNode*) * (*size + 1));
			if (newArray) {
				memset(newArray, NULL, sizeof(BinaryNode*) * (*size + 1));
				memcpy(newArray, *arrayOfNodes, sizeof(BinaryNode*) * (*size));
				free(*arrayOfNodes);
				*arrayOfNodes = newArray;
				(*arrayOfNodes)[*size] = root;
				*size += 1;
			}
		}
		saveNodes(&(*arrayOfNodes), root->leftChild, &(*size));
		saveNodes(&(*arrayOfNodes), root->rightChild, &(*size));
	}
}

void insertSubTree(BinarySearchTree** root, BinaryNode* toAdd)
{
	if (*root == NULL)
	{
		*root = toAdd;
	}
	else
	{
		if ((*root)->info->idEvent > toAdd->info->idEvent)
			insertSubTree(&(*root)->leftChild, toAdd);
		else if ((*root)->info->idEvent < toAdd->info->idEvent)
			insertSubTree(&(*root)->rightChild, toAdd);
		else
			(*root) = toAdd;
	}
}

void arrayTotalCost(TotalCost** totalCostArray, BinarySearchTree* root, int* size)
{
	if (root)
	{
		// we check if the client was added or not yet
		bool added = false;
		if (*totalCostArray)
		{
			for (int i = 0; i < *size && added == false; i++)
			{
				if (strcmp((*totalCostArray)[i].clientName, root->info->clientName) == 0)
					added = true;
			}
		}
			// if the client has not been added before -> calculate its total cost
			if (added == false) {
				float currentTotalCost = 0.0;
				arrayCalculateCost4Client(&currentTotalCost, root, root->info->clientName);

				// add it to the array
				if (*totalCostArray == NULL)
				{
					*totalCostArray = (TotalCost*)malloc(sizeof(TotalCost));
					//memset(arrayRes, NULL, sizeof(NodeInfo**) * (*size + 1));
					if (*totalCostArray) {
						(*totalCostArray)[0].clientName = (char*)malloc(strlen(root->info->clientName) + 1);
						strcpy((*totalCostArray)[0].clientName, root->info->clientName);
						(*totalCostArray)[0].totalCost = currentTotalCost;
						*size = 1;
					}	
				}
				else
				{
					// resizing the array
					TotalCost* newArray;
					newArray = (TotalCost*)malloc(sizeof(TotalCost) * (*size + 1));
					if (newArray) {
						memset(newArray, NULL, sizeof(TotalCost) * (*size + 1));
						memcpy(newArray, *totalCostArray, sizeof(TotalCost) * (*size));
						free(*totalCostArray);
						*totalCostArray = newArray;
						(*totalCostArray)[*size].clientName = (char*)malloc(strlen(root->info->clientName) + 1);
						strcpy((*totalCostArray)[*size].clientName, root->info->clientName);
						(*totalCostArray)[*size].totalCost = currentTotalCost;
						*size += 1;
					}
				}
			}
		arrayTotalCost(&(*totalCostArray), root->leftChild, &(*size));
		arrayTotalCost(&(*totalCostArray), root->rightChild, &(*size));
	}
}

// calculates the cost of a client
void arrayCalculateCost4Client(float* totalC, BinarySearchTree* root, char* cName)
{
	if (root)
	{
		if (strcmp(root->info->clientName, cName) == 0)
			*totalC += root->info->ticketPrice;

		arrayCalculateCost4Client(&(*totalC), root->leftChild, cName);
		arrayCalculateCost4Client(&(*totalC), root->rightChild, cName);
	}
}


void arrayReservations(NodeInfo*** arrayRes, BinarySearchTree* root, char* condition, int* size)
{
	if (root)
	{
		// if the condition is met -> add it to the array
		if (strcmp(root->info->eventDate, condition) == 0) {
			NodeInfo* deepCopy = createNodeInfo(root->info->idEvent,
				root->info->ticketPrice,
				root->info->clientName,
				root->info->eventDate,
				root->info->eventName,
				root->info->noPeople);
			if (*arrayRes == NULL)
			{
				*arrayRes = (NodeInfo**)malloc(sizeof(NodeInfo*));
				//memset(arrayRes, NULL, sizeof(NodeInfo**) * (*size + 1));
				(*arrayRes)[0] = deepCopy;
				*size = 1;
			}
			else
			{
				// resizing the array
				NodeInfo** newArray;
				newArray = (NodeInfo**)malloc(sizeof(NodeInfo*) * (*size + 1));
				if (newArray) {
					memset(newArray, NULL, sizeof(NodeInfo*) * (*size + 1));
					memcpy(newArray, *arrayRes, sizeof(NodeInfo*) * (*size));
					free(*arrayRes);
					*arrayRes = newArray;
					(*arrayRes)[*size] = deepCopy;
					*size += 1;
				}		
			}
		}
		arrayReservations(&(*arrayRes), root->leftChild, condition, &(*size));
		arrayReservations(&(*arrayRes), root->rightChild, condition, &(*size));
	}
}


BinarySearchTree* createNode(NodeInfo* info)
{
	BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	node->info = info;
	node->leftChild = node->rightChild = NULL;
	return node;
}



void insertBST(BinarySearchTree** root, NodeInfo* info)
{
	if (*root == NULL)
	{
		*root = createNode(info);
	}
	else
	{
		if ((*root)->info->idEvent > info->idEvent)
			insertBST(&(*root)->leftChild, info);
		else if ((*root)->info->idEvent < info->idEvent)
			insertBST(&(*root)->rightChild, info);
		else
			(*root)->info = info;
	}
}



void deleteBST(BinarySearchTree** root, int key)
{
	if (*root != NULL)
	{
		if ((*root)->info->idEvent > key)
			deleteBST(&(*root)->leftChild, key);
		else if ((*root)->info->idEvent < key)
			deleteBST(&(*root)->rightChild, key);
		else
		{
			if ((*root)->leftChild == NULL && (*root)->rightChild == NULL)
			{
				//free((*root)->info->eventDate);
				free((*root)->info->eventName);
				free((*root)->info->clientName);
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
				//free((*root)->info->eventDate);
				free((*root)->info->eventName);
				free((*root)->info->clientName);
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
		//free(tmp->eventDate);
		free(tmp->eventName);
		free(tmp->clientName);
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

NodeInfo* createNodeInfo(short id, float price, char* cName, char eDate[10], char* eName, int no)
{
	NodeInfo* toReturn = (NodeInfo*)malloc(sizeof(NodeInfo));
	if (toReturn != NULL)
	{
		toReturn->idEvent = id;
		toReturn->ticketPrice = price;

		toReturn->clientName = (char*)malloc(strlen(cName) + 1);
		if (toReturn->clientName) {
			strcpy(toReturn->clientName, cName);
		}

		//strcpy(toReturn->eventDate, eDate);
		for (int i = 0; i < 10; i++)
			toReturn->eventDate[i] = eDate[i];
		toReturn->eventDate[10] = '\0';

		toReturn->eventName = (char*)malloc(strlen(eName) + 1);
		if (toReturn->eventName) {
			strcpy(toReturn->eventName, eName);
		}

		toReturn->noPeople = no;

	}
	return toReturn;
}

// printing a NodeInfo
void printInfo(NodeInfo* info)
{
	if (info)
		printf("ID: %3d | Name: %-15s - Price: %4.3f, Client Name: %-20s, Date: %s, No. Pers.: %3d\n", info->idEvent, 
			info->eventName,
			info->ticketPrice,
			info->clientName, 
			info->eventDate,
			info->noPeople);
	else
		printf("No data to print!");
}