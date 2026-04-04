#include "header.h"

void bubbleSort(Student arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcasecmp(arr[j].surname, arr[j+1].surname) > 0) {
                Student temp;
                strcpy(temp.name, arr[j].name);
                strcpy(temp.surname, arr[j].surname);
                strcpy(arr[j].name, arr[j+1].name);
                strcpy(arr[j].surname, arr[j+1].surname);
                strcpy(arr[j+1].name, temp.name);
                strcpy(arr[j+1].surname, temp.surname);
            }
        }
    }
}