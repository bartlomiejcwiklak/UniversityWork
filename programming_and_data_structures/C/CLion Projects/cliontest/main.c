#include <stdio.h>

int main() {

    int x, result;

    printf("Please enter a number: ");
    scanf("%d", &x);

    if (x >= -5 && x <= 5) {
        result = (2 * x * x) + (3 * x) - 1;
        printf("Result = %d\n", result);
    } else {
        result = (x + 5) * (x - 5) - 10;
        printf("Result = %d\n", result);
    }

    return 0;
}