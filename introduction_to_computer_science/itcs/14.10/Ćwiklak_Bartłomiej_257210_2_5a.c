#include <stdio.h>
#include <math.h>

int main(){
    int n = 0;
    float valL, valR;
    for (n = 1; n < 10000; n++) {
        valL = pow(1.02, n);
        valR = 1000 * pow(n, 2);
        // printf("%f > %f\n", valL, valR);
        if (valL > valR) {
            printf("%d", n);
            break;
        }
    }
}
