#pragma once

struct FigureInfo {
    double Xcord;
    double Ycord;
    double radius;
    struct FigureInfo* next;
    struct FigureInfo* prev;
    char* circle;
};

double perimeter(char* str, struct FigureInfo* current);

double area(char* str, struct FigureInfo* current);

int intersections(char* str, struct FigureInfo* current);
