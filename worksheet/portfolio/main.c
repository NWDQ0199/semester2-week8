#include <stdio.h>
#include <stdbool.h>
#include "shapes.h"

#include <stdlib.h>

void testLine(void);
void testTriangle(void);
void testLine2(void);
bool sameFloat(float a, float b);

void testSameFloat(void)
{
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			if((i==j)!=(sameFloat((float)i,(float)j)))
			{
				printf("i: %i, j: %i\n",i,j);
			}
		}
	}
}
void testSamePoint(void)
{
	bool good1=true;
	bool good2=true;
	for(int i=0;i<100;i++)
	{
		if(rand()%2==0)
		{
			//points are same
			Point p1=makePoint((float)(rand()%2000-1000),(float)(rand()%2000-1000));
			bool same=samePoint(p1,p1);
			if(same!=1)
			{
				printf("p1: (%f,%f)\n\tp1==p1: %i\n",p1.x,p1.y,same);
				good1=false;
			}
		}
		else
		{
			//points are not same in general
			//technically they can be the same but it is unlikely
			Point p1=makePoint((float)(rand()%2000-1000),(float)(rand()%2000-1000));
			Point p2=makePoint((float)(rand()%2000-1000),(float)(rand()%2000-1000));
			bool same=samePoint(p1,p2);
			if(same==1)
			{
				printf("p1: (%f,%f), p2: (%f,%f)\n\tp1==p2: %i\n",p1.x,p1.y,p2.x,p2.y,same);
			}
		}
	}
	printf("good1: %i\n",good1);
	printf("good2: %i\n",good2);
}

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
	//testSameFloat();
	//testSamePoint();
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
	printf("testTriangle (b): %s\n",!pointInTriangle(p4,t)?"pass":"fail");
}

void testLine2(void)
{
	//a point (2,2) is part of the line (3,2),(2,2) (true/1)
	Point p1=makePoint(3.f,2.f);
	Point p2=makePoint(2.f,2.f);
	Line l=makeLine(p1,p2);
	Point p3=makePoint(2.f,2.f);
	Point p4=makePoint(7.f,10.f);
	bool p3in=pointInLine(p3,l);
	printf("testLine2 (a):\n\tpointInLine(p3,l): %i\n\tstatus: %s\n",p3in,p3in?"pass":"fail");
	bool p4in=pointInLine(p4,l);
	printf("testLine2 (b):\n\tpointInLine(p4,l): %i\n\tstatus: %s\n",p4in,!p4in?"pass":"fail");
}