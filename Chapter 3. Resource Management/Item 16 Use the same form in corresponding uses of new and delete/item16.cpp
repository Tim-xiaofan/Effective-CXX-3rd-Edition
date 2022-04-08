#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::string;

class foo
{
    private:
        static int cnt;
    public:
        ~foo(){cout << cnt++ << " foo destructor\n";}
};

int foo::cnt = 0;

int main(int argc, char *argv[])
{
    foo *fooArray = new foo[3];
    delete [] fooArray;
    foo *fooPtr1 = new foo;
    delete [] fooPtr1;
    return 0;
}
