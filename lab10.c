#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "defs.h"

int main(int argc, char const *argv[])
{
    Node *pHead = NULL;
    char *nameOfFile = NULL;

    createList(&pHead);
    getNameOfFile(&nameOfFile);
    readMembers(&pHead, nameOfFile);

    printRes(pHead);
    delStudents(&pHead);
    printf("\nTable without students that reached 3 on first and third exams: \n");
    printRes(pHead);

    deleteList(&pHead);

    return 0;
}
