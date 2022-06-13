#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include <stdbool.h>

// change this to fit the problem
typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
} Employee, NodeInfo;

NodeInfo* createNodeInfo(short, char*, char*, double);
void printInfo(NodeInfo*);