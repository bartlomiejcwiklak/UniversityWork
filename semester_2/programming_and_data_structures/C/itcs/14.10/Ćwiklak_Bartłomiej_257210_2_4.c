#include <stdio.h>

int main(){
    int a, b, temp;
    float valL, valR;
    scanf("%d %d", &a, &b);

    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }

    for (int i = a; i <= b; i++) {
        valL = (i * i * i) + 20 * i;
        valR = (3 * i * i) + 370;
        if (valL >= valR) { printf("Value %d does not satisfy the function.\n", i); }
        // printf("%f\n%f\n\n", valL, valR);
    }
}
