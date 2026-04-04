#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 10;
const int SIZE = 25;

int main(){
    char names[N][3][SIZE];
    int i, n, o;
    printf("How many students? ");

    do {
        o = scanf("%d", &n);
        while (getchar() != '\n');
    } while(o==0 || n<1 || n>N);

    for(i=0;i<n;++i) {
        printf("Enter the %d student's name: ", i+1);
        o = scanf("%25[^\n]s", names[i][0]);
        while (getchar() != '\n');
        printf("Enter the %d student's surname: ", i+1);
        o = scanf("%25[^\n]s", names[i][1]);
        while (getchar() != '\n');
        printf("Enter the %d student's address: ", i+1);
        o = scanf("%25[^\n]s", names[i][2]);
        while (getchar() != '\n');
    }

    printf("ID%5sNAME%23sSURNAME%20sADDRESS\n--------------------------------------------------------------------------------------", " ", " ", " ");
    for(i=0;i<n;++i) {
        printf("\n%-7d%-27s", i, names[i][0]);
        printf("%-27s", names[i][1]);
        printf("%-27s", names[i][2]);
    }
}
