#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"

void printChars(char character, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        printf("%c", character);
    }
}
//--------------------------------------------------------------------------------
void freeInfo(Node *el)
{
    if (!el || !(el->info) || !(el->info->mName) || !(el->info->mSurname) \
        || !(el->info->listOfMarks) || !(el->info->age))
        return;
    free(el->info->mName);
    free(el->info->mSurname);
    free(el->info->listOfMarks);
    free(el->info->age);
    el->info = NULL;
}
//--------------------------------------------------------------------------------
void deleteList(Node ** pHead)
{
    if (!pHead || !(*pHead))
        return;

    Node *tmp = *pHead;
    Node *tmpPrev = tmp;

    while (tmp->pNext)
    {
        tmpPrev = tmp;
        tmp = tmp->pNext;
        freeInfo(tmpPrev);
        free(tmpPrev);
    }
    
    freeInfo(tmp);
    *pHead = NULL;
}
//--------------------------------------------------------------------------------
void freeParts(char **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }
}
//--------------------------------------------------------------------------------
int tokInput(char *arr[], int arrSize, char str[], char delimeters[])
{
    char *p = NULL;

    p = strtok(str, delimeters);

    if (arr == NULL)
        return -1;

    int i = 0;
    while (p && i != arrSize)
    {
        arr[i] = (char *)calloc(strlen(p), sizeof(char));
        strncpy(arr[i], p, strlen(p));

        p = strtok(NULL, delimeters);
        i++;
    }
    return (i+1);
}
//--------------------------------------------------------------------------------
void createList(Node ** pHead)
{
    *pHead = (Node*)calloc(1, sizeof(Node));
    (*pHead)->info = NULL;
    (*pHead)->pNext = NULL;
}
//--------------------------------------------------------------------------------
int amountOfElements(Node *pHead)
{
    Node *tmp = pHead;
    int amountOfElements = 0;
    if (tmp != NULL)
    {
        amountOfElements++;
        while (tmp->pNext)
        {
            tmp = tmp->pNext;
            amountOfElements++;
        }
    }

    return amountOfElements;
}
//--------------------------------------------------------------------------------
void addNodeInEnd(Node * pHead)
{
    Node *tmp = pHead;
    while (tmp->pNext)
        tmp = tmp->pNext;

    tmp->pNext = NULL;
}
//--------------------------------------------------------------------------------
void insertInSortedList(Node **pHead, Node *element)
{
    Node *tmp2 = *pHead;
    Node *tmp1 = tmp2;
    if (!(*pHead) || !((*pHead)->info) || !((*pHead)->info->mName) || \
        !((*pHead)->info->mSurname) || !((*pHead)->info->listOfMarks) || \
        !((*pHead)->info->age))
    {
        (*pHead) = element;
        return;
    }
    

    if ((*pHead)->pNext == NULL)
    {
        if (strcmp((*pHead)->info->mName, element->info->mName) > 0)
        {
            element->pNext = *pHead;
            *pHead = element;
        }
        else
        {
            element->pNext = (*pHead)->pNext;
            (*pHead)->pNext = element;
        }
    }
    else
    {
        if (strcmp((*pHead)->info->mName, element->info->mName) > 0)
        {
            element->pNext = *pHead;
            *pHead = element;
            return ;
        }
        else
        {
            while(tmp2->pNext)
            {
                tmp1 = tmp2->pNext;
                if (strcmp(tmp1->info->mName, element->info->mName) > 0)
                {
                    element->pNext = tmp2->pNext;
                    tmp2->pNext = element;
                    return ;
                }
                else
                {
                    tmp2 = tmp2->pNext;
                }
            }
            if (tmp2->pNext == NULL)
            {
                tmp2->pNext = element;
            }
        }
    }
}
//--------------------------------------------------------------------------------
int createNode(Node ** element)
{
    if (element == NULL)
        return -1;

    *element = (Node*)calloc(1, sizeof(Node));

    if (*element == NULL)
        return -1;
    
    (*element)->pNext = NULL;
    (*element)->info = NULL;

    return 0;
}
//--------------------------------------------------------------------------------
int isCorrectDate(char *str)
{
    int res = 0;
    int day = 0, month = 0, year = 0;
    FILE *dateOfBirth = NULL;
    dateOfBirth = fmemopen(str, strlen(str), "rt");
    res = fscanf(dateOfBirth, "%d.%d.%d", &day, &month, &year);
    fclose(dateOfBirth);

    if (res != 3)
        return 0;

    if ((month == 2 && day > 29 && year % 4 == 0) || 
        (month == 2 && day > 28 && year % 4 != 0) || \
        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || \
        ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || 
          month == 10 || month == 12) && day > 31))
    {
        return 0;
    }

    return 1;
}
//--------------------------------------------------------------------------------
int fillStudent(Node *pNode, char *partsOfStr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (!partsOfStr[i])
        {
            return -1;
        }
    }

    pNode->info = (Info*)calloc(1, sizeof(Info));
    if (pNode->info == NULL)
    {
        return -1;
    }

    if (partsOfStr[INDEX_OF_NAME] != NULL)
    {
        pNode->info->mName = (char *)calloc(strlen(partsOfStr[INDEX_OF_NAME]), 
                                            sizeof(char));
        strncpy(pNode->info->mName, 
                partsOfStr[INDEX_OF_NAME], 
                strlen(partsOfStr[INDEX_OF_NAME]));
    }
    else
        return -1;
    if (partsOfStr[INDEX_OF_SURNAME] != NULL)
    {
        pNode->info->mSurname = (char *)calloc(strlen(partsOfStr[INDEX_OF_SURNAME]), 
                                               sizeof(char));
        strncpy(pNode->info->mSurname, 
                partsOfStr[INDEX_OF_SURNAME], 
                strlen(partsOfStr[INDEX_OF_SURNAME]));
    }
    else
        return -1;
    int day, month;
    if (partsOfStr[INDEX_OF_DATE_OF_BIRTH] != NULL && 
        isCorrectDate(partsOfStr[INDEX_OF_DATE_OF_BIRTH]))
    {
        pNode->info->age = (char *)calloc(strlen(partsOfStr[INDEX_OF_DATE_OF_BIRTH]) + 1, 
                                          sizeof(char));
        strncpy(pNode->info->age, 
                partsOfStr[INDEX_OF_DATE_OF_BIRTH], 
                strlen(partsOfStr[INDEX_OF_DATE_OF_BIRTH]));
    }
    else
        return -1;

    pNode->info->listOfMarks = (int *)calloc(AMOUNT_OF_MARKS, sizeof(int));
    for (int i = 0; i < AMOUNT_OF_MARKS; i++)
    {
        if (partsOfStr[i + 3] != NULL)
            pNode->info->listOfMarks[i] = atoi(partsOfStr[i + 3]);
        else
            return -1;
    }
    return 0;
}
//--------------------------------------------------------------------------------
void clearArr(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = '\0';
    }
}
//--------------------------------------------------------------------------------
void getNameOfFile(char **nameOfFile)
{
    char buf[BUFSIZ] = "";
    char *name = NULL;
    FILE *list = NULL;
    while (1)
    {
        printf("Enter name of file with information about students: ");
        if (scanf("%s", buf))
        {
            list = fopen(buf, "rt");
            if (!list)
                printf("Cannot open file! Please, try again!\n");
            else
            {
                fclose(list);
                list = NULL;
                break;
            }
        }
        else
            printf("Invalid name of file! Please, try again!\n");
        clearArr(buf, strlen(buf));
    }
    name = (char *)calloc(strlen(buf), sizeof(char));
    strncpy(name, buf, strlen(buf));
    *nameOfFile = name;
}
//--------------------------------------------------------------------------------
int readMembers(Node **pHead, const char * const nameOfFile)
{
    char ch = '\0';
    char buff[SIZE_OF_BUFF] = "";
    int k = 0,
        j = 0,
        i = 0;
    Node * element = NULL;
    int res;

    printf("%s\n", nameOfFile);

    FILE *list = fopen(nameOfFile, "rt");

    char** partsOfStr = NULL;
    
    while (ch != EOF)
    {
        element = (Node *)calloc(1, sizeof(Node));
        ch = '\0';
        partsOfStr = (char**)calloc(AMOUNT_OF_PARTS, sizeof(char*));
        while ((ch = getc(list)) != EOF && ch != '\n')
        {
            buff[k] = ch;
            k++;
        }

        k = 0;
        res = tokInput(partsOfStr, AMOUNT_OF_PARTS, buff, " ");
        clearArr(buff, SIZE_OF_BUFF);

        res = fillStudent(element, partsOfStr, AMOUNT_OF_PARTS);

        if (res != -1)
        {
            freeParts(partsOfStr, AMOUNT_OF_PARTS);
            free(partsOfStr);
            i++;
        }
        else
        {
            while(partsOfStr[j] != NULL && j < AMOUNT_OF_PARTS)
            {
                free(partsOfStr[j]);
                j++;
            }
            j = 0;
            free(partsOfStr);
            continue;
        }

        if ((i-1) == 0)
            *pHead = element;
        else
            insertInSortedList(pHead, element);
    }

    fclose(list);
    return 0;
}
//--------------------------------------------------------------------------------
void delStudents(Node ** pHead)
{
    Node *tmp1 = *pHead;
    Node *tmp2 = tmp1;

    while (tmp1->pNext)
    {
        tmp2 = tmp1->pNext;
        if (tmp2->info->listOfMarks[INDEX_OF_SUBJ1] == MARK_3 && 
            tmp2->info->listOfMarks[INDEX_OF_SUBJ3] == MARK_3)
        {
            tmp1->pNext = tmp2->pNext;
            freeInfo(tmp2);
            free(tmp2);
            // continue;
        }
        else
            tmp1 = tmp1->pNext;
    }

    if ((*pHead)->info->listOfMarks[INDEX_OF_SUBJ1] == MARK_3 && 
        (*pHead)->info->listOfMarks[INDEX_OF_SUBJ3] == MARK_3 && ((*pHead)->pNext))
    {
        tmp2 = (*pHead)->pNext;
        freeInfo((*pHead));
        free((*pHead));
        (*pHead) = tmp2;
        tmp2 = (*pHead);
        tmp1 = (*pHead);
    }

    if (tmp1->info->listOfMarks[INDEX_OF_SUBJ1] == MARK_3 && 
        tmp1->info->listOfMarks[INDEX_OF_SUBJ3] == MARK_3)
    {
        freeInfo(tmp1);
        free(tmp1);
        tmp1 = NULL;
        (*pHead) = tmp1;
    }
}
//--------------------------------------------------------------------------------
void printStudentTable(Node * pHead, int maxLenOfName, int maxLenOfSurname)
{
    Node *tmp = pHead;

    if (!tmp || !(tmp->info) || !(tmp->info->mName) || \
        !(tmp->info->mSurname) || !(tmp->info->listOfMarks) || \
        !(tmp->info->age))
    {
        return;
    }


    while (tmp)
    {
        printf("| %s ", tmp->info->mName);
        printChars(' ', maxLenOfName-strlen(tmp->info->mName));
        printf("| %s ", tmp->info->mSurname);
        printChars(' ', maxLenOfSurname-strlen(tmp->info->mSurname));
        printf("| %s    ", tmp->info->age);
        for (int i = 0; i < AMOUNT_OF_MARKS; i++)
        {
            printf("|  %d  ", tmp->info->listOfMarks[i]);
        }
        printf("|\n");
        tmp = tmp->pNext;
    }
}
//--------------------------------------------------------------------------------
int maxLenOfNameAndSurname(Node *pHead, int *pMaxLenOfName, int *pMaxLenOfSurname)
{
    if (!pHead)
        return -1;

    Node *tmp = pHead;
    *pMaxLenOfName = LEN_OF_NAME;
    *pMaxLenOfSurname = LEN_OF_SURNAME;
    int i = 1;
    while (tmp->pNext)
    {
        if (strlen(tmp->info->mName) > *pMaxLenOfName)
            *pMaxLenOfName = strlen(tmp->info->mName);
        if (strlen(tmp->info->mSurname) > *pMaxLenOfSurname)
            *pMaxLenOfSurname = strlen(tmp->info->mSurname);
        tmp = tmp->pNext;
        i++;
    }
    if (strlen(tmp->info->mName) > *pMaxLenOfName)
        *pMaxLenOfName = strlen(tmp->info->mName);
    if (strlen(tmp->info->mSurname) > *pMaxLenOfSurname)
        *pMaxLenOfSurname = strlen(tmp->info->mSurname);

    return 0;
}
//--------------------------------------------------------------------------------
void printRes(Node* pHead)
{
    int maxLenOfName = 0,
        maxLenOfSurname = 0;

    if (!pHead || !(pHead->info) || !(pHead->info->mName) || \
        !(pHead->info->mSurname) || !(pHead->info->listOfMarks) || \
        !(pHead->info->age))
    {
        printf("There are no elements in list!\n");
        return;
    }

    if (maxLenOfNameAndSurname(pHead, &maxLenOfName, &maxLenOfSurname) == -1)
    {
        printf("There are no students in list!\n");
        return;
    }

    printf("\n| Name");
    printChars(' ', maxLenOfName-LEN_OF_NAME);
    printf(" | Surname");
    printChars(' ', maxLenOfSurname-LEN_OF_SURNAME);
    printf(" | Date of Birth |               Marks               |\n");
    printf("|");
    printChars(' ', maxLenOfName+2);
    printf("|");
    printChars(' ', maxLenOfSurname+2);
    printf("|");
    printChars(' ', 13+2);
    printf("|");
    printf("Subj1|Subj2|Subj3|Subj4|Subj5|Subj6|\n");

    printStudentTable(pHead, maxLenOfName, maxLenOfSurname);
}
