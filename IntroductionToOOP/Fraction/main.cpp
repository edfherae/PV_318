#include "Fraction.h"

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
