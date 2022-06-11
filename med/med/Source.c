//#define _CRT_SECURE_NO_WARNINGS
//#include "stdlib.h"
//#include "stdio.h"
//#include "string.h"
//#include "memory.h"
//
////Structura cu informatia
//typedef struct Employee
//{
//    short code;
//    char* name;
//    char* department;
//    double salary;
//}Employee;
////Structura cu lista
//typedef struct Node
//{
//    Employee* info;
//    struct Node* next;
//}Node;
//
///* functions' signatures for memory management */
//Employee* createInfo(short code, const char* name, const char* department, double salary);
//Node* createNode(Employee* info);
///* functions' signatures for list operations */
//Node* insertHead(Node* head, Employee* info);
//Node* insertTail(Node* head, Employee* info);
//Node* insertNthPos(Node* head, Employee* info, int pos);
//void printInfo(Employee* info);
//void printNode(Node* head);
//int main()
//{
//    FILE* pfile = fopen("Data.txt", "r");
//    char buffer[128];
//    char* token;
//    char sep_list[] = ",\n";
//    Employee* emp = NULL;
//    Node* list = NULL;
//
//    if (pfile)
//    {
//        while (fgets(buffer, sizeof(buffer), pfile))
//        {
//            emp = (Employee*)malloc(sizeof(Employee));
//
//            //parsing the code
//            token = strtok(buffer, sep_list);
//            emp->code = atoi(token);
//
//            //parsing the name
//            token = strtok(NULL, sep_list);
//            emp->name = (char*)malloc(strlen(token) + 1);
//            strcpy(emp->name, token);
//
//            //parsing the department
//            token = strtok(NULL, sep_list);
//            emp->department = (char*)malloc(strlen(token) + 1);
//            strcpy(emp->department, token);
//
//            //parsing the salary
//            token = strtok(NULL, sep_list);
//            emp->salary = atof(token);
//
//            //alegem cum vrem sa inseram
//            //insertHead(&list, emp);
//            list = insertTail(list, emp);
//        }
//
//        //se printeaza lista
//        printf("%s", "Before insertion\n");
//        printNode(list);
//
//        printf("%s", "After insertion\n");
//        Employee* e1 = createInfo(20001, "Badulescu Cristian", "Cybersecurity", 2100.2);
//        int pos = 3;
//
//        list = insertNthPos(list, e1, pos);
//        printNode(list);
//
//    }
//
//    int a = 2;
//}
//Node* insertNthPos(Node* head, Employee* info, int pos)
//{
//    Node* newNode = createNode(info);
//    if (pos <= 1) {
//
//        head = insertHead(head, info);
//    }
//    else
//    {
//        Node* aux = head;
//        for (int i = 1; i < pos - 1; i++)
//        {
//            aux = aux->next;
//        }
//        aux->next = newNode;
//    }
//    return head;
//}
//
//
//Node* insertTail(Node* head, Employee* info)
//{
//    Node* node = createNode(info);
//    //connect node to the structure
//    //only when head == null
//    if (head == NULL)
//    {
//        head = node;
//    }
//    //connect the structure to the node
//    else
//    {
//        Node* tmp = head;
//        while (tmp->next)
//        {
//            tmp = tmp->next;
//        }
//        tmp->next = node;
//    }
//    return head;
//}
//
//Node* insertHead(Node* head, Employee* info)
//{
//    Node* node = createNode(info);
//    //connect the node to the structure
//    node->next = head;
//    //connect the structure to the node
//    head = node;
//    return head;
//}
//
//Node* createNode(Employee* info)
//{
//    Node* node = (Node*)malloc(sizeof(Node));
//    node->info = info;
//    node->next = NULL;
//    return node;
//}
//
//Employee* createInfo(short code, const char* name, const char* department, double salary)
//{
//    Employee* emp = (Employee*)malloc(sizeof(Employee));
//    emp->code = code;
//    emp->name = (char*)malloc(strlen(name) + 1);
//    strcpy(emp->name, name);
//    emp->department = (char*)malloc(strlen(department) + 1);
//    strcpy(emp->department, department);
//    emp->salary = salary;
//    return emp;
//}
//
//void printInfo(Employee* info)
//{
//    printf(" Code: %d; Name: %s; Department: %s; Salary: %f\n", info->code, info->name, info->department, info->salary);
//}
//
//// print list
//void printNode(Node* head)
//{
//    while (head)
//    {
//        printInfo(head->info);
//        head = head->next;
//    }
//}