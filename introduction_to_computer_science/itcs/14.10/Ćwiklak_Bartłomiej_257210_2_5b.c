#include <stdio.h>

int main(){
    float e, sum, x = 0;

    scanf("%f", &e);
    for (float n = 1; n < 10000; n++) {
        sum += (1 / n);
        if (sum > e) {
            printf("%.0f\n", n);
            return 0;
        }
    }
}
