#include <stdio.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main(){
    int x, y, tab[100], n=0;
    scanf("%d%d", &x, &y);
    if (x > y) { int t = x; x = y; y = t; }
    for (int i = 0; i < 100; i++) {
        if (isPrime(i) || i % 23 == 0) {
            tab[n] = i;
            n++;
        }
    }
    for (int i = 1; i <= y-1; i++) printf("%d, ", tab[i]);
    printf("%d\n", tab[y]);
}