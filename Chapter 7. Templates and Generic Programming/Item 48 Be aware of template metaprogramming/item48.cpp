#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    //std::swap
#include <exception>
#include <cstring>
#include <iterator>
#include <list>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::list;

template<unsigned n>
struct Factorial
{
    enum {value = n * Factorial<n-1>::value};
};

template<>
struct Factorial<0>
{
    enum {value = 1};
};

template<unsigned n, unsigned a>
struct power_of
{
    enum {value = a * power_of<n -1, a>::value};
};

template<unsigned a>
struct power_of<0, a>
{
    enum {value = 1};
};

int main(int argc, char *argv[])
{
    cout << "Factorial of 5:" << Factorial<5>::value << endl;//120
    cout << "Factorial of 10:" << Factorial<10>::value << endl;//3628800
    vector<unsigned> vull = {Factorial<5>::value, Factorial<10>::value};
    cout << vull[0] << endl;
    cout << vull[1] << endl;

    cout << "2^10 = " << power_of<10, 2>::value << endl; 
    cout << "2^20 = " << power_of<20, 2>::value << endl; 
    cout << "2^0 = " << power_of<0, 2>::value << endl; 
    cout << "0^0 = " << power_of<0, 0>::value << endl; //FIXME
    return 0;
}
