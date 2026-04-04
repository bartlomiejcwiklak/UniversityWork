#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 0;
    float x, sum = 0, avg = 0, howManyAbs = 0;

    while (x != 0) {
        scanf("%f", &x);
        n++;
        sum += x;
        if (abs(x) < 100) { howManyAbs++; }
    }
    n--;
    avg = sum / n;
    printf("Average is %.2f\n", avg);
    printf("Number of absolute values greater than 100 is : %d\n", n);
}
