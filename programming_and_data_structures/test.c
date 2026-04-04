#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *readLine(FILE *fp){
    int c;
    size_t size = 16; // initial buffer size
    size_t len = 0;
    char *buffer = malloc(size);
    if (!buffer){
        fprintf(stderr, "Memory allocation failed!");
        exit(1);
    }

    while((c = fgetc(fp)) != EOF && isspace(c))
        ;

    if (c == EOF){
        free(buffer);
        return NULL; // return null if no line has been found
    }

    // read characters until we hit whitespace or EOF
    do {
        if (len + 1 >= size) { // check if we allocated enough space for the first line
            size *= 2;
            char *tmp = realloc(buffer, size); // if no, then we double the amount of allocated space
            if (!tmp){ // check if allocation was not successful
                free(buffer);
                fprintf(stderr, "Memory allocation failed.");
                exit(1);
            }
            buffer = tmp; // finally resize the buffer
        }
        buffer[len++] = (char)c; // input the character into the buffer
        c = fgetc(fp); // read next character from the file
    } while (c != EOF && !isspace(c)); // until we hit end of file or space

    buffer[len] = '\0'; // add an empty character at the end;
    return buffer;
}

char *stripLeadingZeroes(char *str){
    while (*str == '0' && *(str + 1) != '\0') str++; // str++ means moving the pointer one space next, thus leaving behind a 0
    return str;
}

int isValidNumber(const char *str){
    if (*str == '\0') return 0;
    for (int i = 0; str[i]; i++){ // str[i] as a condition checks if current character is not '\0'
        if (!isdigit((unsigned char)str[i])) return 0; // if is not a digit, return 0
    }
    return 1;
}

char *addBigNumbers(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = (len_a > len_b ? len_a : len_b) + 1; // check if len_a is bigger than len_b and pick the greater one

    char *result = malloc(max_len + 1);
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    result[max_len] = '\0';

    int carry = 0;
    int i = len_a - 1;
    int j = len_b - 1;
    int k = max_len - 1;

    while (i >= 0 || j >= 0 || carry) { // carry meaning carry != 0
        int digit_a = (i >= 0) ? a[i--] - '0' : 0; // subtract zero to get an integer value from its ASCII code
        int digit_b = (j >= 0) ? b[j--] - '0' : 0;
        int sum = digit_a + digit_b + carry;
        result[k--] = sum % 10 + '0';
        carry = sum / 10;
    }

    char *resStart = stripLeadingZeroes(result + k + 1);
    char *final = strdup(resStart);

    free(result);
    return final;
}

int main(int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr, "Incorrect amount of arguments.");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error opening the file.");
        return 1;
    }

    char *num1 = readLine(fp);
    char *num2 = readLine(fp);
    char *numExtra = readLine(fp);

    fclose(fp);

    if (!num1 || !num2 || numExtra){
        fprintf(stderr, "Invalid input file.");
        free(num1);
        free(num2);
        return 1;
    }

    char *sum = addBigNumbers(num1, num2);
    printf("%s\n", sum);

    free(num1);
    free(num2);
    free(sum);
    return 0;

}
