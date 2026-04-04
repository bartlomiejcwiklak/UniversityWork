#include <stdio.h>

int main() {

    double x, result;

    printf("Please enter a number: ");
    scanf("%lf", &x);

    if (x >= -5 && x <= 5) {
        result = (2 * x * x) + (3 * x) - 1;
        printf("Result = %.2lf\n", result);
    } else {
        result = (x + 5) * (x - 5) - 10;
        printf("Result = %.2lf\n", result);
    }

    return 0;
}