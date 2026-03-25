#include <stdio.h>
#include <stdbool.h>
#include "shapes.h"

void testLine(void);
void testTriangle(void);
void testLine2(void);
bool sameFloat(float a, float b);

int main(void)
{
	/*
	a line (1,1),(2,1) will have length 1.0
	a triangle (0,0),(1,0),(0,1) will have area 0.5
	a point (1,1) is not part of the previous triangle (false/0)
	a point (2,2) is part of the line (3,2),(2,2) (true/1)
	*/
	// test your code by calling the functions and printing the output 
	testLine();
	testTriangle();
	testLine2();

	return 0;
}

void testLine(void)
{
	//a line (1,1),(2,1) will have length 1.0
	Point p1=makePoint(1.f,1.f);
	Point p2=makePoint(2.f,1.f);
	Line l=makeLine(p1,p2);
	float length=lineLength(l);
	printf("|l|=%f\n",length);
	printf("testLine: %s\n",sameFloat(length,1.f)?"pass":"fail");
}

void testTriangle(void)
{
	//a triangle (0,0),(1,0),(0,1) will have area 0.5
	Point p1=makePoint(0.f,0.f);
	Point p2=makePoint(1.f,0.f);
	Point p3=makePoint(0.f,1.f);
	Triangle t=makeTriangle(p1,p2,p3);
	float area=triangleArea(t);
	printf("area(t)=%f\n",area);
	printf("testTriangle (a): %s\n",sameFloat(area,0.5f)?"pass":"fail");

	//a point (1,1) is not part of the previous triangle (false/0)
	Point p4=makePoint(1.f,1.f);
	printf("testTriangle (b): %s\n",pointInTriangle(p4,t)?"fail":"pass");
}

void testLine2(void)
{
	//a point (2,2) is part of the line (3,2),(2,2) (true/1)
	Point p1=makePoint(3.f,2.f);
	Point p2=makePoint(2.f,2.f);
	Line l=makeLine(p1,p2);
	Point p3=makePoint(2.f,2.f);
	printf("testLine2: %s\n",pointInLine(p3,l)?"pass":"fail");
}