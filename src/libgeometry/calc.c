#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgeometry/calc.h"

void FindInfo(struct FigureInfo* current, char* str)
{
    current->circle = str;
    int length = 0;
    char xcord[10];
    char ycord[10];
    char Radius[10];
    while (str[length] != '(') {
        length++;
    }
    length++;
    while (str[length] == ' ') {
        length++;
    }
    int cur = 0;
    while (str[length] != ' ') {
        xcord[cur] = str[length];
        length++;
        cur++;
    }
    current->Xcord = atof(xcord);

    while (str[length] == ' ') {
        length++;
    }
    cur = 0;
    while (str[length] != ',') {
        ycord[cur] = str[length];
        length++;
        cur++;
    }
    current->Ycord = atof(ycord);
    length++;

    while (str[length] == ' ') {
        length++;
    }

    cur = 0;
    while (str[length] != ')') {
        Radius[cur] = str[length];
        length++;
        cur++;
    }
    current->radius = atof(Radius);
}

double perimeter(char* str, struct FigureInfo* current)
{
    if (current->radius == 0)
        FindInfo(current, str);
    double result = M_PI * current->radius * 2;
    return result;
}

double area(char* str, struct FigureInfo* current)
{
    if (current->radius == 0)
        FindInfo(current, str);
    double result = M_PI * current->radius * current->radius;
    return result;
}

int intersections(char* str, struct FigureInfo* current)
{
    if (current->radius == 0)
        FindInfo(current, str);
    printf("Intersections:\n");
    if (current->prev == NULL) {
        printf("Это первый круг, и он ни с чем не может пересекаться\n\n");
        struct FigureInfo* node = current;
        current = current->next;
        current->prev = node;
        return -1;
    }

    struct FigureInfo* tail = current;
    current = current->prev;
    int a = 0;
    while (current != NULL) {
        double dist
                = sqrt(pow((tail->Xcord - current->Xcord), 2)
                       + pow((tail->Ycord - current->Ycord), 2));
        double condition = tail->radius + current->radius;
        if (condition > dist) {
            printf("%s\n", current->circle);
            a++;
        }
        current = current->prev;
    }
    if (a == 0) {
        printf("No intersects\n");
        return 0;
    }
    return a;
}
