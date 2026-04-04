#include <stdio.h>

int calculateFunction(int n){
    if (n % 2 == 0) return (0.5*n)+(n*n);
    else return n*(n-5);
}

int main(){
    int x, y, tab[100];
    scanf("%d%d", &x, &y);
    if (x > y) { int t = x; x = y; y = t; }
    for (int i = x; i <= y; i++) tab[i] = calculateFunction(i);
    const int len = sizeof(tab) / sizeof(tab[0]);
    for (int i = 1; i <= len; i++) printf("\t%d\t\t%d\t\n", i, tab[i]);
}