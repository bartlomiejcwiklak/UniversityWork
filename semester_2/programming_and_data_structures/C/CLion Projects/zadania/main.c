#include "header.h"

#define MAX_STUDENTS 100

int main() {
    int n, i = 0;
    Student students[MAX_STUDENTS];

    printf("Enter the number of students: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter name and surname of student %d: ", i + 1);
        scanf("%s %s", students[i].name, students[i].surname);
    }

    bubbleSort(students, n);

    printf("\nSorted list of students by surname:\n");
    for (i = 0; i < n; i++) {
        printf("%s %s\n", students[i].name, students[i].surname);
    }

    return 0;
}