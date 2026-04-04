#include <stdio.h>

int main(){
    float result = 0;
    for (int i = 1 ; i < 10000; i++) {
        result += (1 / i * (i + 1));
    }
    printf("result = %.4f\n", result);
}
