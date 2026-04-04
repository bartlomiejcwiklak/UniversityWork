#include <stdio.h>

int main(){
    const int n = 3;
    float x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        scanf("%f", &y);
        x += y;
    }
    printf("%.2f\n", x);
}