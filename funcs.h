#ifndef FUNCS_H
#define FUNCS_H

#include "defs.h"

int readMembers(Node **pHead, const char * const nameOfFile);
void printRes(Node* pHead);
void createList(Node ** pHead);
void addNodeInEnd(Node * pHead);
void delStudents(Node ** pHead);
void deleteList(Node ** pHead);

// void getUserInput();
void getNameOfFile(char **nameOfFile);

int createNode(Node ** element);
void insertInSortedList(Node **pHead, Node *element);
int fillStudent(Node *pNode, char *partsOfStr[], int arrSize);
int tokInput(char *arr[], int arrSize, char str[], char delimeters[]);

#endif