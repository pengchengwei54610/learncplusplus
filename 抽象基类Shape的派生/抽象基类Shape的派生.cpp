#include <iostream>

using namespace std;

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
#include<math.h>
#define output_length 50
#define pi 3.14159
class Shape
{
public:
	virtual double area() = 0;
};
class Circle :public Shape
{
private:
	double radius;
public:
	Circle(int r)
	{
		radius = r;
	}
	double area()
	{
		return pi * radius * radius;
	}
};
class Square :public Shape
{
private:
	double side_length;
public:
	Square(double l)
	{
		side_length = l;
	}
	double area()
	{
		return side_length * side_length;
	}
};
class Rectangle :public Shape
{
private:
	double length;
	double width;
public:
	Rectangle(double l, double w)
	{
		length = l;
		width = w;
	}
	double area()
	{
		return length * width;
	}
};
class Trapezoid :public Shape
{
private:
	double upper_end;
	double bottom_end;
	double height;
public:
	Trapezoid(double u, double b, double h)
	{
		upper_end = u;
		bottom_end = b;
		height = h;
	}
	double area()
	{
		return (upper_end + bottom_end) * height / 2;
	}
};
class Triangle :public Shape
{
private:
	double end1;
	double end2;
	double end3;
public:
	Triangle(double e1, double e2, double e3)
	{
		end1 = e1;
		end2 = e2;
		end3 = e3;
	}
	double area()
	{
		double p = (end1 + end2 + end3) / 2;
		return sqrt(p * (p - end1) * (p - end2) * (p - end3));
	}
};
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main() {
	Circle c1(2);
	Square s1(3);
	Rectangle r1(4, 5);
	Trapezoid t1(6, 7, 8);
	Triangle t2(3, 4, 5);

	Shape* s[5] = { &c1,&s1,&r1,&t1,&t2 };

	for (int i = 0; i < 5; i++)
		cout << s[i]->area() << endl;

	return 0;
}