#pragma once
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
	int get_integer()const;
	int get_numerator()const;
	int get_denominator()const;
	Fraction& set_integer(int integer);
	Fraction& set_numerator(int numerator);
	Fraction& set_denominator(int denominator);

	//          Constructors:

	Fraction();
	explicit Fraction(int integer);
	Fraction(double decimal);
	Fraction(int numerator, int denominator);
	Fraction(int integer, int numerator, int denominator);
	Fraction(const Fraction& other);
	~Fraction();

	//          Operators:

	Fraction& operator=(const Fraction& other);
	Fraction& operator++();
	Fraction operator++(int);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);
	Fraction& operator+=(Fraction other);
	Fraction& operator-=(Fraction other);

	//			Type-cast operators

	explicit operator int()const;
	operator double();

	//		  Methods:

	Fraction& reduce();
	Fraction& to_proper();
	Fraction& to_improper();
	Fraction inverted()const;
	double fraction_result();
	void print()const;
};

Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);
bool operator==(Fraction left, Fraction right);
bool operator!=(const Fraction& left, const Fraction& right);
bool operator>(Fraction left, Fraction right);
bool operator<(const Fraction& left, const Fraction& right);
bool operator>=(const Fraction& left, const Fraction& right);
bool operator<=(const Fraction& left, const Fraction& right);
std::ostream& operator<<(std::ostream& os, const Fraction& obj);
std::istream& operator>>(std::istream& is, Fraction& obj);
