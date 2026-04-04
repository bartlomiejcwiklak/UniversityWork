#include <stdio.h>

int main(){
    float x, sum, avg, variance, dashx, sum_t, sum_even, sum_div3, min, max;
    int i = 0, n = 0, d = 0, evenIndex = 0, div3Index = 0;
    float a[199];

    do {
        printf("Enter the number of measurements: ");
        d = scanf("%d", &n);
        while (getchar() != '\n');
    } while (d == 0 || n < 1 || n >= 200);

    for (i = 0; i < n; i++) {
        do {
            printf("m[%d]=", i);
            d = scanf("%f", &a[i]);
            while (getchar() != '\n');
        } while (d==0);
        sum += a[i];
    }
    avg = sum / n;
    printf("Sum is %.2f\n", sum);
    printf("Average is %.2f\n", avg);

    min = a[0];

    for (i = 0; i < n; i++) {
        if (i % 2 == 0) { sum_even += a[i]; }
        if (i % 3 == 0) { sum_div3 += a[i]; }
        if (a[i] < min) { min = a[i]; }
        if (a[i] > max) { max = a[i]; }
    }

    printf("Sum of even indexes: %.2f\n", sum_even);
    printf("Sum of indexes divisible by 3: %.2f\n", sum_div3);
    printf("Minimum: %.2f\n", min);
    printf("Maximum: %.2f\n", max);
}
