#include <iostream>
#include <math.h>
using namespace std;
#define tab "\t"
//#define STRUCT_POINT

//Создавая структуру или класс, мы создаем новый тип данных
class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	double distance()const
	{
		return sqrt((x * x) + (y * y));
	}
};

double distance(Point dot1, Point dot2);

int main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	Point A; //Объявление переменной А типа Point 
			//Создание объекта A структуры Point
			//Создание экземпляра A структуры Point

	cout << sizeof(A) << endl;
	cout << sizeof(Point) << endl; // 2 double

	A.x = 2;
	A.y = 3;
	cout << A.x << tab << A.y << endl;
	Point* pA = &A; //Pointer to A
	cout << pA->x << tab << pA->y << endl;
#endif
	Point A, B;
	A.set_x(2);
	A.set_y(3);
	B.set_x(3.14);
	B.set_y(1.1);
	cout << A.get_x() << tab << A.get_y() << endl;
	cout << B.get_x() << tab << B.get_y() << endl;
	cout << A.distance() << tab << B.distance() << endl;
	cout << distance(A, B) << endl;
}

double distance(Point dot1, Point dot2)
{
	//A(xa, ya), B(xb, yb): AB = √((xb - xa)^2 + (yb - ya)^2)
	return sqrt(pow((dot2.get_x() - dot1.get_x()), 2) + pow((dot2.get_x() - dot1.get_x()), 2));
}