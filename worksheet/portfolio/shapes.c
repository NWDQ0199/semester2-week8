
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#include "shapes.h"

bool sameFloat(float a, float b); //would put this in shapes.h but instructed not to modify

Point makePoint(float x, float y)
{
    Point new;
    new.x=x;
    new.y=y;
    return new;
}

// complete other functions below
// - start with stubs as above
// - compile regularly to test syntax
// - test functions by calling them from main()

Line makeLine(Point p1, Point p2)
{
    Line new;
    new.p[0]=p1;
    new.p[1]=p2;
    return new;
}

Triangle makeTriangle(Point p1, Point p2, Point p3)
{
    Triangle new;
    new.p[0]=p1;
    new.p[1]=p2;
    new.p[2]=p3;
    return new;
}

float lineLength(Line l)
{
    float x1x2=l.p[0].x-l.p[1].x;
    float y1y2=l.p[0].y-l.p[1].y;
    return sqrt(x1x2*x1x2+y1y2*y1y2);
}

float triangleArea(Triangle t)
{
    //using Heron's formula
    float a=lineLength(makeLine(t.p[0],t.p[1]));
    float b=lineLength(makeLine(t.p[0],t.p[2]));
    float c=lineLength(makeLine(t.p[1],t.p[2]));
    float s=(a+b+c)/2.f;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

bool samePoint(Point p1, Point p2)
{
    return abs(lineLength(makeLine(p1,p2)))<1.0e-6;
}

bool pointInLine(Point p, Line l)
{
    return samePoint(p,l.p[0])||samePoint(p,l.p[1]);
}

bool pointInTriangle(Point p, Triangle t)
{
    return samePoint(p,t.p[0])||samePoint(p,t.p[1])||samePoint(p,t.p[2]);
}

bool sameFloat(float a, float b)
{
	return abs(a-b)<1.0e-6;
}