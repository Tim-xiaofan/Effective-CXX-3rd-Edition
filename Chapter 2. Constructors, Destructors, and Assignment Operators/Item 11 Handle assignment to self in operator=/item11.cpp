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
            if(this == &rhs)
            {
                cout << "self assignment found\n";
                return *this;
            }
            else
            {
                x = rhs.x;
                return *this;
            }
        }
    private:
        int x;
};

class Bitmap 
{
    public:
        Bitmap()=default;
        Bitmap(const Bitmap & br) {x = br.x;};
        Bitmap & operator=(const Bitmap &) = default;
    private:
        int x;
};

class Widget1
{ 
    public:
        Widget1(){pb = new Bitmap();}
        Widget1 & operator=(const Widget1 &);
    private: 
        Bitmap *pb; // ptr to a heap-allocated object 
};

Widget1 & Widget1:: operator=(const Widget1 & wr)
{// unsafe impl. of operator= and exception-unsafe(new operator)
#ifdef SAFE
    if (this == &wr) return *this; // identity test: if a self-assignment,
#endif
    delete pb; // stop using current bitmap 
    pb = nullptr;
    pb = new Bitmap(*wr.pb); // start using a copy of rhs's bitmap 
    return *this; // see Item 10
}

static int *
ptr_test(void)
{
    int * i = new int;
    *i = 512;
    cout << "original:" << *i << endl;
    delete i;
    cout << "after deleting: " << *i << endl;
    *i = 1024;
    return i;
}

int main(int argc, char *argv[])
{
    Widget w;
    Widget & wr = w;
    Widget * wp1 = &w, *wp2 = &w; 
    w = w;
    w = wr;
    *wp1 = *wp2;

    Widget1 w1;
    w1 =  w1;

    cout << "*****ptr_test\n";
    int *i = ptr_test();
    cout << "after return:" << *i << endl;
    delete i;
    return 0;
}
