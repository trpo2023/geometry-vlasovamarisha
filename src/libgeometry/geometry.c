#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/geometry.h>

int print_error(int errcode, int current_el, char* strerr)
{
    switch (errcode) {
    case 1:
        printf("Error at column 0: expected 'circle' instead of %s\n", strerr);
        return errcode;

    case 2:
        printf("Error at column %d: expected '.' \n", current_el);
        return errcode;
    case 3:
        printf("Error at column %d: unexpected character\n", current_el);
        return errcode;
    case 4:
        printf("Error at column %d: expected number\n", current_el);
        return errcode;

    case 5:
        printf("Error at column %d: expected ' '\n", current_el);
        return errcode;
    case 6:
        printf("Error at column %d: expected '('\n", current_el);
        return errcode;

    case 7:
        printf("Error at column %d: expected ','\n", current_el);
        return errcode;
    case 8:
        printf("Error at column %d: expected ')'\n", current_el);
        return errcode;
    }
    return 0;
}

int check_num(char figure[], int* ptr)
{
    int current_el = *ptr;

    char str2[13] = "-.0123456789";

    int errcode;

    while (figure[current_el] == ' ') {
        current_el++;
    }

    if (figure[current_el] == '0') {
        if (figure[current_el + 1] != '.'
            && strchr(str2, figure[current_el + 1]) != NULL) {
            return print_error(errcode = 2, current_el, 0);
        }
    }

    if (strchr(str2, figure[current_el]) == NULL) {
        return print_error(errcode = 3, current_el, 0);
    }

    while (strchr(str2, figure[current_el]) != NULL) {
        current_el++;
    }

    if (figure[current_el] == ',' || figure[current_el] == ')') {
        return print_error(errcode = 4, current_el, 0);
    }

    if (figure[current_el] != ' ') {
        return print_error(errcode = 5, current_el, 0);
    }

    while (figure[current_el] == ' ') {
        current_el++;
    }

    if (figure[current_el] == '0') {
        if (figure[current_el + 1] != '.'
            && strchr(str2, figure[current_el + 1]) != NULL) {
            return print_error(errcode = 2, current_el, 0);
        }
    }

    if (strchr(str2, figure[current_el]) == NULL) {
        return print_error(errcode = 3, current_el, 0);
    }

    while (strchr(str2, figure[current_el]) != NULL) {
        current_el++;
    }

    while (figure[current_el] == ' ') {
        current_el++;
    }

    current_el++;
    *ptr = current_el;
    return 0;
}

int circle(char* figure)
{
    int errcode;
    char str[6] = "circle";
    char substr[13] = "-.0123456789";

    for (int i = 0; i < 5; i++) {
        figure[i] = tolower(figure[i]);

        if (figure[i] != str[i]) {
            char strerr[6];
            strncpy(strerr, figure, 6);
            strerr[6] = '\0';
            return print_error(errcode = 1, 0, strerr);
        }
    }

    int current_el = 7;

    if (figure[6] != '(') {
        return print_error(errcode = 6, current_el, 0);
    }

    if (check_num(figure, &current_el) != 0) {
        return -1;
    }

    if (figure[current_el - 1] != ',') {
        return print_error(errcode = 7, current_el, 0);
    }

    while (figure[current_el] == ' ') {
        current_el++;
    }

    if (figure[current_el] == '0') {
        if (figure[current_el + 1] != '.'
            && strchr(substr, figure[current_el + 1]) != NULL) {
            return print_error(errcode = 2, current_el, 0);
        }
    }

    if (strchr(substr, figure[current_el]) == NULL) {
        return print_error(errcode = 3, current_el, 0);
    }

    while (strchr(substr, figure[current_el]) != NULL) {
        current_el++;
    }

    if (figure[current_el] != ')') {
        return print_error(errcode = 8, current_el, 0);
    }
    return 0;
}
