#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 20

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) { if (num % i == 0) return 0; }
    return 1;
}

int validate_input(char *input) {
    int i = 0;
    while (input[i]) { if (!isdigit(input[i])) return -1; i++; }
    int num = atoi(input);
    if (num < 0 || num >= 1000) return -1;
    return num;
}

int main() {
    char input[20];
    int a, count = 0, twin_primes[MAX_SIZE], current;

    printf("Enter a positive integer smaller than 1000: ");
    while (validate_input(input) == -1) {
        scanf("%s", input);
        printf("Invalid input. Please enter a positive integer smaller than 1000: ");
    }
    current = validate_input(input) + 1;
    while (count < MAX_SIZE) {
        if (is_prime(current) && is_prime(current + 2)) { twin_primes[count++] = current; }
        current++;
    }
    for (int i = 0; i < MAX_SIZE; i++) { printf("(%d, %d)\n", twin_primes[i], twin_primes[i] + 2); }
    return 0;
}