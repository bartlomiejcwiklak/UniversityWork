#include <math.h>
#include <stdio.h>

float calculateFunction(int a, int b, int c, int x, int delta){
    return (pow(a*2.718281,-1*delta*x))/(b * x * x + c);
}

int main(){
    int a = 2, b = 2, c = 2;
    float x = 0, delta = 0.5, epsilon = 0.001, result = 1;

    while (result > epsilon) {
        result = calculateFunction(a,b,c,x,delta);
        printf("\t%.1f\t%f\n",x, result);
        x = x + delta;
    }
}