#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int matrix[20][20];
    int horizSum[20];
    int n, o;
    printf("Enter number of rows of matrix: ");
    scanf("%d", &n);
    printf("Enter number of columns of matrix: ");
    scanf("%d", &o);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < o; j++) {
            printf("Enter matrix[%d][%d]: ", j, i);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("The matrix is:\n");
    for(int i = 0; i < n; i++) {
        int sum = 0;
        int sum2 = 0;
        for (int j = 0; j < o; j++) {
            printf("%d\t", matrix[i][j]);
            sum += matrix[i][j];
            sum2 += matrix[j][i];
            horizSum[i] = sum2;
        }
        printf("%d\n", sum);
    }
    for(int j = 0; j < o; j++) {
        printf("%d\t", horizSum[j]);
    }

}
