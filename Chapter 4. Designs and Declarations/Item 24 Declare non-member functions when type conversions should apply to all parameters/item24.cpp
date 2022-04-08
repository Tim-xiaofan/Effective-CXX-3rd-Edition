#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include "my"
using std::cout;
using std::endl;
using std::string;
using std::ostream;

class Rational
{
    public:
        Rational(int numerator = 0, // see Item 24 for why this 
                    int denominator = 1)
            :n(numerator), d(denominator){} // ctor isn't declared explicit ... 
        int numerator() const { return n;} // accessors for numerator and 
        int denominator() const {return d;}; // denominator — see Item 22
#ifndef NON_MEMBER
        const Rational operator*(const Rational& rhs) const { return Rational(n * rhs.n, d * rhs.d);}
#endif
        friend ostream & operator<<(ostream & , const Rational &);
    private: 
        int n, d; // numerator and denominator 
};

ostream & operator<<(ostream & os, const Rational & R)
{
    os << '(' << R.n << '/' << R.d << ')';
    return os;
}

#ifdef NON_MEMBER
const Rational operator*(const Rational& lhs, const Rational& rhs) // function 
{ 
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator()); 
}
#endif

int main(int argc, char *argv[])
{
    Rational oneEighth(1, 8);
    cout << oneEighth << endl;
    Rational oneHalf(1, 2);
    cout << oneHalf << endl;

    Rational result = oneHalf * oneEighth; // fine
    cout << oneEighth << " * " << oneHalf << ": ";
    cout << result << endl;

    Rational tmp = result;
    result = result * oneEighth; // fine
    cout << tmp << " * " << oneEighth << ": ";
    cout << result << endl;

    result = oneHalf * 2; // fine
    cout << oneHalf << " * " << 2 << ": ";
    cout << result << endl;

    result = 2 * oneHalf; // error!
    return 0;
}
