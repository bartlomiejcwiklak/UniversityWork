#include <stdio.h>

int factorial_iter(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) result *= i;
    return result;
}

int factorial_rec(int n) {
    if (n == 0) return 1;
    return n * factorial_rec(n - 1);
}

int main () {
    int choice, number;

    printf("Choose factorial calculation method:\n");
    printf("1. Iterative\n");
    printf("2. Recursive\n");
    scanf("%d", &choice);

    printf("Enter a number: ");
    scanf("%d", &number);

    if (choice == 1) { printf("Factorial of %d (iterative) is %d\n", number, factorial_iter(number)); }
    else if (choice == 2) { printf("Factorial of %d (recursive) is %d\n", number, factorial_rec(number)); }
    else { printf("Invalid choice\n"); }

    return 0;
}