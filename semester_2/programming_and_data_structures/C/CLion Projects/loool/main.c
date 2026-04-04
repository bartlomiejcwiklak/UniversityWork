#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 100

void sort_students(int *ids, float *num_subjects, float *grades, int n);

int main() {
    char input[256];
    int ids[MAX_STUDENTS];
    float num_subjects[MAX_STUDENTS];
    float grades[MAX_STUDENTS];
    int n = 0;

    printf("Podaj numery indeksów studentów oddzielone spacjami:\n");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    while (token != NULL) {
        *(ids + n) = atoi(token);
        n++;
        token = strtok(NULL, " ");
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        *(num_subjects + i) = rand() % 5 + 6; // liczba przedmiotów 6-10
        *(grades + i) = (rand() % 4 + 2) + (rand() % 10) / 10.0; // średnia ocen 2-5
    }

    printf("Przed sortowaniem:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %.1f\n", *(ids + i), (int)*(num_subjects + i), *(grades + i));
    }

    sort_students(ids, num_subjects, grades, n);

    printf("Po sortowaniu:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %.1f\n", *(ids + i), (int)*(num_subjects + i), *(grades + i));
    }

    return 0;
}

void sort_students(int *ids, float *num_subjects, float *grades, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(grades + j) > *(grades + j + 1) ||
                (*(grades + j) == *(grades + j + 1) && *(num_subjects + j) < *(num_subjects + j + 1))) {
                // Swap IDs
                int temp_id = *(ids + j);
                *(ids + j) = *(ids + j + 1);
                *(ids + j + 1) = temp_id;

                // Swap subjects
                float temp_subjects = *(num_subjects + j);
                *(num_subjects + j) = *(num_subjects + j + 1);
                *(num_subjects + j + 1) = temp_subjects;

                // Swap grades
                float temp_grades = *(grades + j);
                *(grades + j) = *(grades + j + 1);
                *(grades + j + 1) = temp_grades;
            }
        }
    }
}