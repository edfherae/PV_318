#include <iostream>
using namespace std;
#define tab "\t"

class Fraction // m/n
{
    int numerator;
    int denominator;
public:
    int get_num()const
    {
        return numerator;
    }
    int get_denom()const
    {
        return denominator;
    }
    void set_num(int m)
    {
        numerator = m;
    }
    void set_denom(int n)
    {
        denominator = n;
    }

    Fraction()
    {
        numerator = denominator = 0;
    }
    Fraction(int m, int n)
    {
        numerator = m;
        denominator = n;
    }
    Fraction(const Fraction& other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
    }
    ~Fraction()
    {

    }

    Fraction& operator=(const Fraction& other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    double fraction_result()
    {
        if (denominator != 0) return numerator / denominator;
        else
        {
            cout << "«наменатель не должен быть равен нулю\n";
            return 0;
        }
    }
    /*double extract_dec_part(double &number)
    {
        double decimal_part = number - (int)(number);
        number -= decimal_part;
        return decimal_part;
    }*/
    bool is_inproper()
    {
        return numerator >= denominator; 
    }
    void print_fraction()
    {
        if (is_inproper())
            cout << "\n  " << numerator % denominator << "\n" << numerator / denominator << " -\n" << "  " << denominator << endl << endl;
        else
            cout << "\n  " << numerator << "\n  Ч\n" << "  " << denominator << endl << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "");

    Fraction proper_frac(2, 3);
    Fraction inproper_frac(7, 3);
    proper_frac.print_fraction();
    inproper_frac.print_fraction();
    //cout << 3.14 - (int)(3.14);
}
