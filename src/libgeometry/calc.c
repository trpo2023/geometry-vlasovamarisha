
#include <ctype.h>

#include <math.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>



double FindRadius(char* str)

{

    int length = strlen(str);

    char radius[10];

    while (str[length] != ',') {

        length--;

    }



    length++;



    while (str[length] == ' ') {

        length++;

    }



    int current = 0;

    while (str[length] != ' ' && str[length] != ')') {

        radius[current] = str[length];

        current++;

        length--;

    }

    radius[current + 1] = '\0';

    double a = atof(radius);

    return a;

}



double perimeter(char str[])

{

    double radius = FindRadius(str);

    double a = M_PI * radius * 2;

    return a;

}



double area(char str[])

{

    double radius = FindRadius(str);

    double a = M_PI * radius * radius;

    return a;

}
