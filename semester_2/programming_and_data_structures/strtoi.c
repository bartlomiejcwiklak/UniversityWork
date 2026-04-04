#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

long int strtol(const char *nptr, char **endptr, int base) {
    const char *s = nptr;
    int neg = 0;
    long acc = 0;
    int any = 0;
    int overflow = 0;
    
    while (isspace((unsigned char)*s)) s++;

    if (*s == '+' || *s == '-') {
        if (*s == '-')
            neg = 1;
        s++;
    }

    if (base == 0) {
        if (*s == '0') {
            if ((s[1] == 'x' || s[1] == 'X') && isxdigit((unsigned char)s[2])) {
                base = 16;
                s += 2;
            } else {
                base = 8;
                s++;
            }
        } else {
            base = 10;
        }
    } else if (base == 16) {
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X') && isxdigit((unsigned char)s[2]))
            s += 2;
    }

    for (; *s; s++) {
        int digit;
        char c = *s;
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (c >= 'A' && c <= 'Z')
            digit = c - 'A' + 10;
        else if (c >= 'a' && c <= 'z')
            digit = c - 'a' + 10;
        else
            break;
        if (digit >= base)
            break;

        if (!overflow) {
            if (neg) {
                if (acc < (LONG_MIN + digit) / base) {
                    overflow = 1;
                    acc = LONG_MIN;
                } else {
                    acc = acc * base - digit;
                }
            } else {
                if (acc > (LONG_MAX - digit) / base) {
                    overflow = 1;
                    acc = LONG_MAX;
                } else {
                    acc = acc * base + digit;
                }
            }
        }
        any = 1;
    }

    if (!any) {
        if (endptr)
            *endptr = (char *)nptr;
        return 0;
    }

    if (overflow) errno = ERANGE;

    if (endptr) *endptr = (char *)s;

    return acc;
}
