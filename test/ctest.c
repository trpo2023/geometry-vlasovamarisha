#include <ctest.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES // M_PI in math.h

#include <libgeometry/calc.h>
#include <libgeometry/geometry.h>

CTEST(calc, perimeter)
{
    struct FigureInfo* current
            = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    current->circle = (char*)malloc(sizeof(struct FigureInfo));
    struct FigureInfo* current_exp
            = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    char str[] = "circle(1 1, 1)";
    current_exp->circle = str;
    current_exp->radius = 1;
    current_exp->Xcord = 1;
    current_exp->Ycord = 1;
    current->circle = "circle(1 1, 1)";
    double result = perimeter(current->circle, current);
    double expected = 2 * M_PI * current_exp->radius;
    ASSERT_DBL_NEAR(expected, result);
    ASSERT_DBL_NEAR(current_exp->radius, current->radius);
    ASSERT_DBL_NEAR(current_exp->Xcord, current->Xcord);
    ASSERT_DBL_NEAR(current_exp->Ycord, current->Ycord);
    ASSERT_STR(current_exp->circle, current->circle);
}

CTEST(calc, area)
{
    struct FigureInfo* current
            = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    current->circle = (char*)malloc(sizeof(struct FigureInfo));
    struct FigureInfo* current_exp
            = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    char str[] = "circle(1 1, 1)";
    current_exp->circle = str;
    current_exp->radius = 1;
    current_exp->Xcord = 1;
    current_exp->Ycord = 1;
    current->circle = "circle(1 1, 1)";
    double result = area(current->circle, current);
    double expected = M_PI * current_exp->radius * current_exp->radius;
    ASSERT_DBL_NEAR(expected, result);
    ASSERT_DBL_NEAR(current_exp->radius, current->radius);
    ASSERT_DBL_NEAR(current_exp->Xcord, current->Xcord);
    ASSERT_DBL_NEAR(current_exp->Ycord, current->Ycord);
    ASSERT_STR(current_exp->circle, current->circle);
}

CTEST(calc, intersections)
{
    struct FigureInfo* current
            = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    struct FigureInfo* current_exp
            = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    current_exp->circle = "circle(1 1, 1)";
    current_exp->radius = 1;
    current_exp->Xcord = 1;
    current_exp->Ycord = 1;
    current->circle = "circle(1 1, 1)";

    // 1 случай, добавлена одна фигура
    current->next = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    int i = intersections(current->circle, current);
    int i_ex = -1;
    ASSERT_EQUAL(i_ex, i);
    ASSERT_DBL_NEAR(current_exp->radius, current->radius);
    ASSERT_DBL_NEAR(current_exp->Xcord, current->Xcord);
    ASSERT_DBL_NEAR(current_exp->Ycord, current->Ycord);
    ASSERT_STR(current_exp->circle, current->circle);

    // случай 2, введена вторая фигура
    struct FigureInfo* node = current;
    current = current->next;
    current->prev = node;
    current->circle = "circle(1 1.5, 1)";
    current_exp->radius = 1;
    current_exp->Xcord = 1;
    current_exp->Ycord = 1.5;
    current_exp->circle = "circle(1 1.5, 1)";
    i = intersections(current->circle, current);
    i_ex = 1;
    ASSERT_EQUAL(i_ex, i);
    ASSERT_DBL_NEAR(current_exp->radius, current->radius);
    ASSERT_DBL_NEAR(current_exp->Xcord, current->Xcord);
    ASSERT_DBL_NEAR(current_exp->Ycord, current->Ycord);
    ASSERT_STR(current_exp->circle, current->circle);

    // случай 3, фигуры не пересекаются
    current->next = (struct FigureInfo*)malloc(sizeof(struct FigureInfo));
    node = current;
    current = current->next;
    current->prev = node;
    current->circle = "circle(2 15, 9)";
    current->Xcord = 0;
    current_exp->radius = 9;
    current_exp->Xcord = 2;
    current_exp->Ycord = 15;
    current_exp->circle = "circle(2 15, 9)";
    i = intersections(current->circle, current);
    i_ex = 0;

    ASSERT_EQUAL(i_ex, i);
    ASSERT_DBL_NEAR(current_exp->radius, current->radius);
    ASSERT_DBL_NEAR(current_exp->Xcord, current->Xcord);
    ASSERT_DBL_NEAR(current_exp->Ycord, current->Ycord);
    ASSERT_STR(current_exp->circle, current->circle);
}

CTEST(geometry, circle)
{
    // Случай 1. Ошибка в названии фигуры
    printf("\n");
    char str1[20] = "circ";
    int errcode = circle(str1);
    int errcode_exp = 1;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 2. Ошибка написания десятичной дроби
    char str2[20] = "circle(05 1, 1)";
    errcode = circle(str2);
    errcode_exp = 2;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 3. Неожиданный символ
    char str3[20] = "circle(x y, r)";
    errcode = circle(str3);
    errcode_exp = 3;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 4. Отсутствует одно из чисел
    char str4[20] = "circle(1,1)";
    errcode = circle(str4);
    errcode_exp = 4;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 5. Отсутствует пробел между числами
    char str5[20] = "circle(1p1,1)";
    errcode = circle(str5);
    errcode_exp = 5;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 6. Скобка не рядом с названием фигуры
    char str6[20] = "circle (1 1, 1)";
    errcode = circle(str6);
    errcode_exp = 6;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 7. Ожидается запятая
    char str7[20] = "circle(1 1 3)";
    errcode = circle(str7);
    errcode_exp = 7;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 8. Ожидается закрывающая скобка
    char str8[20] = "circle(1 2, 3";
    errcode = circle(str8);
    errcode_exp = 8;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 9. Подаётся "е"
    char str9[20] = "e";
    errcode = circle(str9);
    errcode_exp = 9;
    ASSERT_EQUAL(errcode_exp, errcode);

    // Случай 10. Верно написанная строка
    char str10[20] = "circle(1 2, 3)";
    errcode = circle(str10);
    errcode_exp = 0;
    ASSERT_EQUAL(errcode_exp, errcode);
}
