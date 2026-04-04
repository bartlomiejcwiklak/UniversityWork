#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int matrix[20][20];
    int horizSum[20];
    int n=0, o;
    while(n > 20 || n < 1) {
        printf("Enter number of rows and columns of the matrix: ");
        scanf("%d", &n);
    }
    srand(time(0));
    o = n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < o; j++) {
            matrix[i][j] = 1 + rand() % 10;
        }
    }

    printf("The matrix is:\n");
    for(int i = 0; i < n; i++) {
        int sum = 0;
        int sum2 = 0;
        for (int j = 0; j < o; j++) {
            printf("%d\t", matrix[i][j]);
            sum += matrix[i][j];
        }
        for(int j = 0; j < n; j++) {
            sum2 += matrix[j][i];
            horizSum[i] = sum2;
        }
        printf("%d\n", sum);
    }
    for(int j = 0; j < o; j++) {
        printf("%d\t", horizSum[j]);
    }

    int counter = 0;
    float sum3 = 0;

    if(n == o) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= i; j++) {
                sum3 += matrix[i][j];
                counter += 1;
            }
        }
        printf("\nAverage of the values below and on the diagonal: %.2f\n", sum3/counter);
    }
}
