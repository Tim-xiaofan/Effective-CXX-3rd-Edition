#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using std::cout;
using std::endl;
using std::string;


class Rational
{
    public:
        Rational(int numerator = 0, // see Item 24 for why this 
                    int denominator = 1)
            :n(numerator), d(denominator){cout << "Constructor\n";} // ctor isn't declared explicit ... 
    private: 
        int n, d; // numerator and denominator 
        friend const Rational // see Item 3 for why the 
            operator*(const Rational& lhs, // return type is const 
                        const Rational& rhs); 
};

inline const Rational operator*(const Rational& lhs, const Rational& rhs) 
{
    return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}

int main(int argc, char *argv[])
{
    return 0;
}
