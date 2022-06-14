#include "z.NodeInfo.h"

// creating a NodeInfo*
NodeInfo* createNodeInfo(short code, char* name, char* dept, double salary)
{
	Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
	if (emp != NULL)
	{
		emp->code = code;
		emp->name = (char*)malloc(strlen(name) + 1);
		if (emp->name) {
			strcpy(emp->name, name);
		}
		emp->dept = (char*)malloc(strlen(dept) + 1);
		if (emp->dept) {
			strcpy(emp->dept, dept);
		}
		emp->salary = salary;

	}
	return emp;
}

// printing a NodeInfo
void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %-25s, Dept: %-15s\tSalary: %.2f\n", info->code, info->name,
			info->dept, info->salary);
	else
		printf("No data to print!");
}