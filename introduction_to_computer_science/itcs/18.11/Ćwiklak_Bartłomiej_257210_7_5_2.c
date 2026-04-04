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
    int arr[20];
    int count = 0, a = 2, x = 0, y = 0;

    while (count < 20) {
        if (a % 2 == 0) arr[count++] = a;
        a++;
    }
    for (int j = 0; j < 20; j++) {
        if (arr[j] < 4) continue;
        checkGoldbach(arr[j], &x, &y);
        printf("%d = %d + %d\n", arr[j], x, y);
    }
}