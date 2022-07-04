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

class B
{
    public:
        virtual void f() const {}
};

class D: public B
{
    public:
        virtual void f(){}
};

int main(int argc, char *argv[])
{
    return 0;
}
