#define _USE_MATH_DEFINES	
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
using std::cin;
using std::cout;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"
#define double_delimiter "\n=====================================================================\n"

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction // m/n
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	Fraction& set_integer(int integer)
	{
		this->integer = integer;
		return *this;
	}
	Fraction& set_numerator(int numerator)
	{
		this->numerator = numerator;
		return *this;
	}
	Fraction& set_denominator(int denominator)
	{
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
		return *this;
	}

	//          Constructors:

	Fraction() //E0339: может быть вызван без параметров
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer) //explicit - €вный, implicit - не€вный
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1argConstructor:\t" << this << endl;
	}
	Fraction(double decimal)
	{
		decimal += 1e-10;
		integer = decimal;
		decimal -= integer;
		denominator = 1e+9; // 1 * 10^9
		numerator = decimal * denominator;
		reduce();
		cout << "1argConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator) //E0339: тоже может быть вызван без параметров, если есть знач. по умолч.
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//          Operators:

	Fraction& operator=(const Fraction& other) //возврат type&, чтобы реализовывалась ситуаци€ a = b = c
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	Fraction& operator+=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		if (this->denominator == other.denominator)
			this->numerator += other.numerator;
		else
		{
			this->numerator = this->numerator * other.denominator + other.numerator * this->denominator;
			this->denominator = this->denominator * other.denominator;
		}
		return this->to_proper();
	}
	Fraction& operator-=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		if (this->denominator == other.denominator)
			this->numerator -= other.numerator;
		else
		{
			this->numerator = this->numerator * other.denominator - other.numerator * this->denominator;
			this->denominator = this->denominator * other.denominator;
		}
		return this->to_proper();
	}
	//std::istream& operator>>(std::istream& os)
	//{
	//	int integer, numerator, denominator;
	//	os >> integer >> numerator >> denominator;
	//	this->set_integer(integer), this->set_numerator(numerator), this->set_denominator(denominator);
	//	return os;
	//}
	//std::istream& operator>>(std::istream& os)
	//{
	//	int integer, numerator, denominator;
	//	os >> integer >> numerator >> denominator;
	//	this->integer = integer, this->numerator = numerator, this->denominator = denominator;
	//	return os;
	//}

	//			Type-cast operators

	explicit operator int()const
	{
		return integer;
	}
	operator double()
	{
		return integer + (double)numerator / denominator; //приоритет: / принимает int и int, на выходе Int, дробна€ часть тер€етс€
	}

	//		  Methods:

	Fraction& reduce()
	{
		//https://www.webmath.ru/poleznoe/formules_12_7.php
		int more, less, rest;
		if (numerator > denominator) more = numerator, less = denominator;
		else more = denominator, less = numerator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //Greatest Common Divisor
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this; //чтобы не создавать внутри класса новый объект, а вернуть уже измененный объект
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	double fraction_result()
	{
		if (denominator != 0)
		{
			this->to_improper();
			return (double)numerator / denominator;
		}
		else
		{
			cout << "«наменатель не должен быть равен нулю\n";
			return 1;
		}
	}
	void print()const
	{
		if (integer) cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}
};
Fraction operator*(Fraction left, Fraction right) // & приводит к изменению данных, нарушение инкапсул€ции вроде
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted(); // cool
}
Fraction operator+(Fraction left, Fraction right)
{
	//left.to_common_denominator(right);
	//right.to_common_denominator(left);
	left.to_improper();
	right.to_improper();
	if (left.get_denominator() == right.get_denominator())
	{
		return left.set_numerator(left.get_numerator() + right.get_numerator()).to_proper();
	}
	return Fraction
	(
		(left.get_numerator() * right.get_denominator()) + (right.get_numerator() * left.get_denominator()),
		(left.get_denominator() * right.get_denominator())
		//left.get_numerator() + right.get_numerator(),
		//left.get_denominator()
	).to_proper();
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_denominator() == right.get_denominator())
	{
		return left.set_numerator(left.get_numerator() - right.get_numerator()).to_proper();
	}

	return Fraction
	(
		left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() ==
		right.get_numerator() * left.get_denominator();
	//if (left.get_denominator() == right.get_denominator())
	//	return left.get_numerator() == right.get_numerator();
	//else
	//	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}
bool operator<(const Fraction& left, const Fraction& right)
{
	return right > left;
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
	//return left > right || left == right;
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
	//return left < right || left == right;
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer()) os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer()) os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer()) os << ")";
	}
	else if (obj.get_integer() == 0) os << 0;
	return os;
}
std::istream& operator>>(std::istream& is, Fraction& obj)
{
	const int SIZE = 64;
	char buffer[SIZE]{};
	//is >> buffer;
	is.getline(buffer, SIZE);
	int number[3];
	int n = 0;
	const char delimiters[] = "(/) +";
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
		//функци€ strtok измен€ет входную строку
		number[n++] = atoi(pch);
	for (int i = 0; i < n; i++) cout << number[i] << tab; cout << endl;

	switch (n)
	{
	case 1: obj = Fraction(number[0]); break;
	case 2: obj = Fraction(number[0], number[1]); break;
	case 3: obj = Fraction(number[0], number[1], number[2]); break;
	}

	return is;

	//int integer, numerator, denominator;
	//os >> integer >> numerator >> denominator;
	//obj.set_integer(integer), obj.set_numerator(numerator), obj.set_denominator(denominator);
	//return os;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define COMPARISON_OPERATORS_CHECK
//#define STREAM_CHECK
//#define TYPE_CONVERTIONS_BASICS
//#define CONVERTIONS_FROM_OTHER_TO_CLASS
#define CONVERTIONS_TASK_1
#define CONVERTIONS_TASK_2

int main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A; // default
	A.print();

	Fraction B = 5; // 1arg
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E(D);
	E.print();

	Fraction F;
	F = E;
	F.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.to_improper();
	A.print(); // prefix ++ не работает
	++A.to_proper();
	A++.print();
	A.print();

	cout << delimiter << endl;

	Fraction B(3, 4, 5);
	B.print();

	cout << delimiter << endl;

	Fraction C = A * B;
	C.print();
	C *= A;
	C.print();

	cout << delimiter << endl;

	Fraction D = A / B;
	D.print();

	cout << delimiter << endl;

	Fraction E = A + B;
	E.to_proper();
	E.print();

	cout << delimiter << endl;

	Fraction ® = A - B;
	®.to_proper();
	®.print();

	cout << delimiter << endl;

	Fraction test(1, 1, 2);
	(Fraction(2, 1, 2) *= test).print();
	(Fraction(2, 1, 2) /= test).print();
	(Fraction(2, 1, 2) += test).print();
	(Fraction(2, 1, 2) -= test).print();

	cout << delimiter << endl;

	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);

	A *= B;
	A.print();

	A /= B;
	A.print();


#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef COMPARISON_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	Fraction A1(2, 3, 4);
	Fraction B(3, 4, 5);
	//cout << (Fraction(1, 2).fraction_result() << Fraction(5, 11).fraction_result() << endl;
	cout << (Fraction(1, 3) >= Fraction(5, 11)) << endl;

	//cout << (Fraction(2, 1, 2) == test) << endl;
	//cout << (Fraction(2, 1, 2) != test) << endl;
	//cout << (Fraction(2, 1, 2) > test) << endl;
	//cout << (Fraction(2, 1, 2) < test) << endl;
	//cout << (Fraction(2, 1, 2) >= test) << endl;
	//cout << (Fraction(2, 1, 2) <= test) << endl;  
#endif // COMPARISON_OPERATORS_CHECK

#ifdef STREAM_CHECK
	Fraction A(2, 3, 4);
	cout << "¬ведите дробь (цела€ часть, числитель, знаменатель): "; cin >> A;
	cout << A << endl;
#endif // STREAM_CHECK

#ifdef TYPE_CONVERTIONS_BASICS
	int a = 2;	 //No convertions
	double b = 3;//Convertion from less to more
	int c = b;	 //Convertion from more to less withous dataloss
	int d = 2.5; //Convertion from more to less with dataloss
	cout << sizeof(int) << endl;
	cout << sizeof(double) << endl;
#endif // TYPE_CONVERTIONS_BASICS

#ifdef CONVERTIONS_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5; //convertion from int to fraction
	//1 arg constructor
	cout << A << endl;

	cout << double_delimiter << endl;

	Fraction B;
	cout << delimiter << endl;
	B = Fraction(8);
	cout << B << endl;

	cout << double_delimiter << endl;
#endif // CONVERTIONS_FROM_OTHER_TO_CLASS

#ifdef CONVERTIONS_TASK_1
	Fraction A(2, 3, 4);
	cout << A << endl;

	//int a = (int)A;
	double a = (double)A;
	cout << a << endl;
#endif // CONVERTIONS_TASK_1


#ifdef CONVERTIONS_TASK_2
	Fraction B = M_PI;
	cout << B << endl;
#endif // CONVERTIONS_TASK_2


	//int a = 2;
	//int& pa = a;
	//cout << &a << tab;// << //&pa << endl;

	//cout << 3.14 - (int)(3.14);
}
