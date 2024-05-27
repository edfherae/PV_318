#include <iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"


//#define STRUCT_POINT // CTRL + SPACE
//#define DISTANCE_CHECK
//#define CONSTRUCTORS_CHECK
#define ASSINGMENT_CHECK

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

	//		Constructors

	Point()
	{
		x = y = 0;
		cout << "Default constructor:\t" << this << endl;
	}
	Point(double x)
	{
		this->x = x;
		this->y = 0;
		cout << "1Argconstructor:\t" << this << endl;
	}
	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//		Operators:
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	//		Methods
	double distance(const Point& other)const //константный объект нельзя изменить, this и other теперь константные
	{
		return sqrt(pow((other.x - this->x), 2) + pow((other.y - this->y), 2));
	}
	void print()const
	{
		cout << this << ": X = " << x << tab << "Y = " << y << endl;
	}
};

double distance(const Point& A, const Point& B);

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
#endif // STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);

	Point B;
	B.set_x(7);
	B.set_y(8);
	cout << A.get_x() << tab << A.get_y() << endl;
	cout << B.get_x() << tab << B.get_y() << delimiter;

	cout << distance(A, B) << delimiter;
	cout << distance(B, A) << delimiter;
	cout << A.distance(B) << delimiter;
	cout << B.distance(A) << delimiter;
#endif // DISTANCE_CHECK

#ifdef CONSTRUCTORS_CHECK
	Point A; //Default constructor
	A.print();

	Point B = 5;
	B.print();

	Point C(2, 3);
	C.print();

	Point D = C;
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ASSINGMENT_CHECK
	//Point A(2, 3); //Constructor
	//Point B;	   //Default constructor
	//B = A;		   //Copy assignment
	//B.print();
	//Point C = B;   //CopyConstructor

	int a, b, c;
	a = b = c = 0; // c = 0, b = c, a = b // Ассоциативность справа налево
	cout << a << tab << b << tab << c << endl;

	Point A, B, C;
	cout << delimiter << endl;
	A = B = C = Point(2, 3);
	cout << delimiter << endl;
	A.print();
	B.print();
	C.print();
#endif // ASSINGMENT_CHECK

}

double distance(const Point& A, const Point& B)
{
	//A(xa, ya), B(xb, yb): AB = √((xb - xa)^2 + (yb - ya)^2)
	return sqrt(pow((B.get_x() - A.get_x()), 2) + pow((B.get_y() - A.get_y()), 2));
}