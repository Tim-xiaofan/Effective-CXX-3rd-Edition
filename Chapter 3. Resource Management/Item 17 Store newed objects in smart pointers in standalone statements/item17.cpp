#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::string;

class Widget
{
    public:
        Widget(){cout << "constructor" << endl; ptr = new int;}
        ~Widget(){cout << "destructor" << endl; delete ptr;}
    private:
        int * ptr;
};

int priority(){throw "noting";return 0;}; 
void processWidget(std::shared_ptr<Widget> pw, int priority){};

int main(int argc, char *argv[])
{
    /** this call may leak resources, if the call to priority yields an exception*/
    processWidget(std::shared_ptr<Widget>(new Widget), priority());
    //processWidget(new Widget, priority());//compile error
    return 0;
}
