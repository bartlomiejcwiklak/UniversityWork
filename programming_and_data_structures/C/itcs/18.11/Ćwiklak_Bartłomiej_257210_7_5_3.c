#include <stdio.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) { if (num % i == 0) return 0; }
    return 1;
}

int checkGoldbach(int n, int* one, int* two) {
    if (n < 4) return 0;
    for (int i = 2; i <= n / 2; i++) {
        if (isPrime(i) && isPrime(n - i)) {
            *one = i;
            *two = n-i;
        }
    }
    return 0;
}

int main() {
    int a = 0, x = 0, y = 0, size = 0, count = 0;
    printf("Actions for a specified range (x1, x2)\n1. Designate prime numbers\n2. Designate prime twins\n3. Verify Goldbach's conjecture\n\nPlease enter integers in the following order: choice x1 x2\n");
    scanf("\n%d %d %d", &a, &x, &y);
    if (x > y) { int t = x; x = y; y = t; }
    size = y - x;
    int arr[size+1];
    while (count <= size) {
        arr[count++] = x;
        x++;
    }

    switch (a) {
        case 1:
            for (int j = 0; j <= size; j++) {
                if (isPrime(arr[j])) printf("%d ", arr[j]);
            }
            break;
        case 2:
            for (int j = 0; j <= size; j++) {
                if (isPrime(arr[j]) && isPrime(arr[j + 2])) printf("%d %d\n", arr[j], arr[j]+2);
            }
            break;
        case 3:
            for (int j = 0; j <= size; j++) {
                if (arr[j] < 4 || arr[j] % 2 != 0) continue;
                checkGoldbach(arr[j], &x, &y);
                printf("%d = %d + %d\n", arr[j], x, y);
            }
            break;
    }
}
