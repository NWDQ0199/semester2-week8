
#include <stdio.h>
#include "shapes.h"

int main(void)
{

    // complete the structure definition in the header file first
    // code in main to test the structures and functions
	Point p={.x=5,.y=2};
    Rectangle r=makeRectangle(p,3,6);
	printf("Area: %f\n",area(r));
    return 0;
}

Rectangle makeRectangle(Point p, float width, float height)
{
	Rectangle r;
	r.point=p;
	r.width=width;
	r.height=height;
    return r;
}

float area(Rectangle r)
{
    float a=r.width*r.height;
    return a;
}

void shiftRectangle(Rectangle* r, Point dp)
{
	r->point.x+=dp.x;
	r->point.y+=dp.y;
    return;
}

void scaleRectangle(Rectangle* r, float scale)
{
	r->point.x*=scale;
	r->point.y*=scale;
    return;
}
