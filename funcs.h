#ifndef FUNCS_H
#define FUNCS_H

#include "defs.h"

// Reads students from file nameOfFile to linked list pHead.
// Returns 0 in case of successful function exit.
int readMembers(Node **pHead, const char * const nameOfFile);

// Prints list pHead of students.
void printRes(Node* pHead);

// Initialises first element of linked list pHead.
void createList(Node ** pHead);

// Adds empty node in end of list pHead.
void addNodeInEnd(Node * pHead);

// Removes nodes with information about students, that have marks 3 in subjects 1 and 3 from list pHead.
void delStudents(Node ** pHead);

// Deallocates list pHead.
void deleteList(Node ** pHead);

// Prompts user to enter name of file with information about students.
void getNameOfFile(char **nameOfFile);

// Initialises separate node element.
// Returns 0 in case of successful function exit.
int createNode(Node ** element);

// Adds node element in sorted list pHead.
void insertInSortedList(Node **pHead, Node *element);

// Adds node with information about student in partsOfStr in list pNode.
// Returns 0 in case of successful function exit.
int fillStudent(Node *pNode, char *partsOfStr[], int arrSize);

// Divides string str with information about students in array arr with arrSize elements.
// Divides by characters in delimeters.
// Returns amount of elements, inserted in array arr.
int tokInput(char *arr[], int arrSize, char str[], char delimeters[]);

#endif