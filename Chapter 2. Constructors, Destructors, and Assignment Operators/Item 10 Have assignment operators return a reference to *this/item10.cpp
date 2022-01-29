#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using std::cout;
using std::endl;
using std::string;


class Widget 
{ 
    public: 
        Widget& operator=(const Widget& rhs) // return type is a reference to
        { // the current class ... 
#ifdef RET_THIS
            return *this; // return the left-hand object 
#endif
        }
};

int main(int argc, char *argv[])
{
    Widget w1, w2, w3;
    w1 = w2 = w3;
    return 0;
}
