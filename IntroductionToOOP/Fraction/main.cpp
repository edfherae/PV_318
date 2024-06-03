#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"

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
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
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

	Fraction& operator=(const Fraction& other) //возврат type& чтобы реализовывалась ситуаци€ a = b = c
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
	Fraction& operator*=(Fraction other)
	{
		/*Fraction result = *this * other; // Error C2676 (возможно, не видит перегрузку, т.к. она используетс€ до ее описани€ в коде)
		return result;*/

		this->to_improper();
		other.to_improper();
		this->numerator = this->numerator * other.numerator;
		this->denominator = this->denominator * other.denominator;
		return this->to_proper();
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this *= other.inverted();
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

	//          Methods:

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
	/*Fraction& to_common_denominator(Fraction other)
	{
		if (other.integer) other.to_improper();
		if (this->integer) this->to_improper();
		this->numerator *= other.denominator;
		this->denominator *= other.denominator;
		return *this;
	}*/
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
void reduction(Fraction& left, Fraction& right)
{
	if (left.get_numerator() == right.get_denominator())
	{
		right.to_improper();
		left.set_numerator(1);
		right.set_denominator(1);
	}
	if (left.get_denominator() == right.get_numerator())
	{
		left.to_improper();
		right.set_numerator(1);
		left.set_denominator(1);
	}
}
Fraction operator*(Fraction left, Fraction right) // & приводит к изменению данных, нарушение инкапсул€ции вроде
{
	//reduction(left, right);
	left.to_improper();
	right.to_improper();
	//reduction(right, left);
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
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
	if (left.get_denominator() == right.get_denominator())
		return left.get_numerator() == right.get_numerator();
	else
		return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();	
}
bool operator!=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_denominator() != right.get_denominator())
		return left.get_numerator() == right.get_numerator();
	else
		return left.get_numerator() * right.get_denominator() != right.get_numerator() * left.get_denominator();	
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_denominator() != right.get_denominator())
		return left.get_numerator() > right.get_numerator();
	else
		return left.get_numerator() * right.get_denominator() > right.get_numerator() * left.get_denominator();	
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_denominator() != right.get_denominator())
		return left.get_numerator() < right.get_numerator();
	else
		return left.get_numerator() * right.get_denominator() < right.get_numerator() * left.get_denominator();	
}
bool operator>=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_denominator() != right.get_denominator())
		return left.get_numerator() >= right.get_numerator();
	else
		return left.get_numerator() * right.get_denominator() >= right.get_numerator() * left.get_denominator();	
}
bool operator<=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_denominator() != right.get_denominator())
		return left.get_numerator() <= right.get_numerator();
	else
		return left.get_numerator() * right.get_denominator() <= right.get_numerator() * left.get_denominator();	
}

//#define CONSTRUCTORS_CHECK

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

	Fraction test(2, 1, 2);
	(Fraction(2, 1, 2) *= test).print();
	(Fraction(2, 1, 2) /= test).print();
	(Fraction(2, 1, 2) += test).print();
	(Fraction(2, 1, 2) -= test).print();

	cout << delimiter << endl;

	cout << (Fraction(2, 1, 2) == test) << endl;
	cout << (Fraction(2, 1, 2) != test) << endl;
	cout << (Fraction(2, 1, 2) > test) << endl;
	cout << (Fraction(2, 1, 2) < test) << endl;
	cout << (Fraction(2, 1, 2) >= test) << endl;
	cout << (Fraction(2, 1, 2) <= test) << endl;


	//cout << 3.14 - (int)(3.14);
}
