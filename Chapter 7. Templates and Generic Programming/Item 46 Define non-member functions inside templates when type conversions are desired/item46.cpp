#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    //std::swap
#include <exception>
#include <assert.h>     //c lib
#include <functional>
#include <list>
#include <cstring>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

//template<typename T>
//class Rational;
//
//template<typename T>
//const Rational<T> operator*(const Rational<T>&, const Rational<T>&);

template<typename T>
class Rational
{
    public:
        Rational(const T& numerator = 0, const T& denominator = 1)
            :_numerator(numerator),_denominator(denominator){}
        const T numerator() const{ return _numerator;}
        const T denominator() const{ return _denominator;}
        friend const Rational operator*(const Rational& lhs, const Rational& rhs)
        { return doMultiply(lhs, rhs); }
        friend std::ostream & operator<<(std::ostream & os, const Rational & r)
        { return dumpRational(os, r); }
    private:
        T _numerator, _denominator;
};

template<typename T>
std::ostream & dumpRational(std::ostream & os, const Rational<T> & r)
{
    return os << "<" << r.numerator() << "," << r.denominator() << ">";
}

template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs)
{
    return Rational<T>(lhs.numerator() * rhs.numerator(), 
                lhs.numerator() * rhs.numerator());
}

int main(int argc, char *argv[])
{
    Rational<int> oneHalf(1, 2);
    Rational<int> result = oneHalf * 2; // error! wont't compile
    cout << result << endl;
    return 0;
}
