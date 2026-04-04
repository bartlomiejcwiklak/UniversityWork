#ifndef SORT_STUDENTS_H
#define SORT_STUDENTS_H

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
} Student;

void bubbleSort(Student arr[], int n);

#endif