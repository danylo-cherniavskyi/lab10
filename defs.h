#ifndef DEFS_H
#define DEFS_H

#define SIZE_OF_BUFF 100
#define AMOUNT_OF_MARKS 6
#define AMOUNT_OF_PARTS 9
#define LEN_OF_NAME 4
#define LEN_OF_SURNAME 7
#define LEN_OF_AGE 3
#define INDEX_OF_DATE_OF_BIRTH 2
#define INDEX_OF_NAME 1
#define INDEX_OF_SURNAME 0
#define AMOUNT_OF_STUDENTS 25
#define INDEX_OF_SUBJ1 0
#define INDEX_OF_SUBJ3 2
#define MARK_3 3

#define SURPRISE "Hello from sasha-sush"

typedef struct SInfo
{
    char *mName;
    char *mSurname;
    char *age;
    int *listOfMarks;
} Info;

typedef struct SNode
{
    struct SInfo * info;
    struct SNode * pNext;
} Node;

#endif