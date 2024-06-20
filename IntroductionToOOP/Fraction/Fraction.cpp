#include "Fraction.h"

int Fraction::get_integer()const
{
	return integer;
}
int Fraction::get_numerator()const
{
	return numerator;
}
int Fraction::get_denominator()const
{
	return denominator;
}
Fraction& Fraction::set_integer(int integer)
{
	this->integer = integer;
	return *this;
}
Fraction& Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
	return *this;
}
Fraction& Fraction::set_denominator(int denominator)
{
	if (denominator == 0) denominator = 1;
	this->denominator = denominator;
	return *this;
}

//          Constructors:

Fraction::Fraction() //E0339: может быть вызван без параметров
{
	integer = 0;
	numerator = 0;
	denominator = 1;
	cout << "DefaultConstructor:\t" << this << endl;
}
Fraction::Fraction(int integer) //explicit - €вный, implicit - не€вный
{
	this->integer = integer;
	this->numerator = 0;
	this->denominator = 1;
	cout << "1argConstructor:\t" << this << endl;
}
Fraction::Fraction(double decimal)
{
	decimal += 1e-10;
	integer = decimal;
	decimal -= integer;
	denominator = 1e+9; // 1 * 10^9
	numerator = decimal * denominator;
	reduce();
	cout << "1argConstructor:\t" << this << endl;
}
Fraction::Fraction(int numerator, int denominator)
{
	this->integer = 0;
	this->numerator = numerator;
	this->set_denominator(denominator);
	cout << "Constructor:\t\t" << this << endl;
}
Fraction::Fraction(int integer, int numerator, int denominator) //E0339: тоже может быть вызван без параметров, если есть знач. по умолч.
{
	this->integer = integer;
	this->numerator = numerator;
	this->set_denominator(denominator);
	cout << "Constructor:\t\t" << this << endl;
}
Fraction::Fraction(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	cout << "CopyConstructor:\t" << this << endl;
}
Fraction::~Fraction()
{
	cout << "Destructor:\t\t" << this << endl;
}

//          Operators:

Fraction& Fraction::operator=(const Fraction& other) //возврат type&, чтобы реализовывалась ситуаци€ a = b = c
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	cout << "CopyAssignment:\t\t" << this << endl;
	return *this;
}
Fraction& Fraction::operator++()
{
	integer++;
	return *this;
}
Fraction Fraction::operator++(int)
{
	Fraction old = *this;
	integer++;
	return old;
}
Fraction& Fraction::operator*=(const Fraction& other)
{
	return *this = *this * other;
}
Fraction& Fraction::operator/=(const Fraction& other)
{
	return *this = *this / other;
}
Fraction& Fraction::operator+=(Fraction other)
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
Fraction& Fraction::operator-=(Fraction other)
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

//			Type-cast operators

Fraction::operator int()const
{
	return integer;
}
Fraction::operator double()
{
	return integer + (double)numerator / denominator; //приоритет: / принимает int и int, на выходе Int, дробна€ часть тер€етс€
}

//		  Methods:

Fraction& Fraction::reduce()
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
Fraction& Fraction::to_proper()
{
	integer += numerator / denominator;
	numerator %= denominator;
	return *this; //чтобы не создавать внутри класса новый объект, а вернуть уже измененный объект
}
Fraction& Fraction::to_improper()
{
	numerator += integer * denominator;
	integer = 0;
	return *this;
}
Fraction Fraction::inverted()const
{
	Fraction inverted = *this;
	inverted.to_improper();
	swap(inverted.numerator, inverted.denominator);
	return inverted;
}
double Fraction::fraction_result()
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
void Fraction::print()const
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
}
