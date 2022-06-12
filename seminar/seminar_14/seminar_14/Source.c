#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"

/*
	- adjacency lists or storing the neighbours of a node
	- directed and undirected nodes
	- (array of lists -> chained hash tables)
*/
typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} Employee, NodeInfo;

typedef struct MainList
{
	NodeInfo* info;
	struct MainList* nextNode;
	struct Neighbour* neighbours;
} MainList, Vertex;

typedef struct Neighbour
{
	Vertex* vertex;
	struct Neighbour* nextAdj;
} Neighbour;

typedef struct Employee NodeInfo;


#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
void printInfo(NodeInfo* info);
/*functions signatures for graphs structure's operations*/
Vertex* createVertex(NodeInfo*);
Neighbour* createNeighbour(Vertex*);
void addNode(Vertex**, NodeInfo*);
void addConnection(Vertex*, short, short);
Neighbour* addNeighbour(Vertex*, Vertex*);
void displayGraph(Vertex*);

void main()
{
	Vertex* graph = NULL;	// main list of nodes
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
			//insert call
			addNode(&graph, info);
		}

		addConnection(graph, 10001, 10010);
		addConnection(graph, 10001, 10009);
		addConnection(graph, 10002, 10005);
		addConnection(graph, 10003, 10004);
		addConnection(graph, 10003, 10010);
		addConnection(graph, 10004, 10006);
		addConnection(graph, 10005, 10006);
		addConnection(graph, 10007, 10010);
		addConnection(graph, 10008, 10009);

		displayGraph(graph);
	}
	int a = 2;
}



void addNode(Vertex** graph, NodeInfo* info)
{
	Vertex* node = createVertex(info);

	// insertion at the beginning of the list of vertices
	/*node->nextNode = *graph;
	*graph = node;*/

	// insertion at the end of the list of vertices
	// CHECK IF THE LIST OF LISTS IS NULL (EMPTY AT THE BEGINNING)
	if (*graph == NULL)
	{
		*graph = node;
	}
	else {
		Vertex* aux = *graph;
		while (aux->nextNode)
		{
			aux = aux->nextNode;
		}
		aux->nextNode = node;
	}

}


Neighbour* addNeighbour(Vertex* src, Vertex* dst)
{
	// adding at the head of the list
	Neighbour* newNeighbour = createNeighbour(dst);
	newNeighbour->nextAdj = src->neighbours;

	return newNeighbour;
}

// adding the connection -> V1 with V2 and V2 with V1 (non-directed graph)
// we pass the keys of the vertices to find V1 and V2 in the MainList
void addConnection(Vertex* graph, short src, short dst)
{
	Vertex* srcNode = NULL, * dstNode = NULL;
	while (graph && (srcNode == NULL || dstNode == NULL))
	{
		if (graph->info->code == src)
			srcNode = graph;
		if (graph->info->code == dst)
			dstNode = graph;

		graph = graph->nextNode;
	}

	if (srcNode != NULL && dstNode != NULL) {
		// V1 with V2
		srcNode->neighbours = addNeighbour(srcNode, dstNode);
		// V2 with V1
		if (src != dst)
			dstNode->neighbours = addNeighbour(dstNode, srcNode);
	}
}

Vertex* createVertex(NodeInfo* info)
{
	Vertex* toReturn = (Vertex*)malloc(sizeof(Vertex));
	toReturn->info = info;
	toReturn->neighbours = NULL;
	toReturn->nextNode = NULL;

	return toReturn;
}

Neighbour* createNeighbour(Vertex* info)
{
	Neighbour* toReturn = (Neighbour*)malloc(sizeof(Neighbour));
	toReturn->nextAdj = NULL;
	toReturn->vertex = info;

	return toReturn;
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

void displayGraph(Vertex* graph)
{
	while (graph)
	{
		printf("%d - neighbours:\n", graph->info->code);
		Neighbour* listNeighbours = graph->neighbours;
		while (listNeighbours)
		{
			printInfo(listNeighbours->vertex->info);
			listNeighbours = listNeighbours->nextAdj;
		}
		printf("\n");
		graph = graph->nextNode;
	}
}

void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s, Salary: %f\n", info->code, info->name, info->salary);
	else
		printf("No data to print!");
}

