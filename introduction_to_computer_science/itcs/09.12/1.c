#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[100];
    srand(time(0));
    for (int i = 0; i < 100; i++) arr[i] = rand() % 1001;

    for (int i = 0; i < 100; i++) printf("%d ", arr[i]);

    printf("\n");
    bubbleSort(arr, 100);

    for (int i = 0; i < 100; i++) printf("%d ", arr[i]);
}

