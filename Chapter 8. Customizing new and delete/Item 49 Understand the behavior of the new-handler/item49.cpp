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

void outOfMem()
{
    cout << "Unable to satisfy request for memory\n";
    abort();
}

class X
{
    public:
        static void outOfMemory()
        {
            cout << "X:unable to satisfy request for memory\n";
            abort();
        }
    private:
        int _a[1000000000L];
};

class Y
{
    public:
        static void outOfMemory()
        {
            cout << "Y:unable to satisfy request for memory\n";
            abort();
        }
    private:
        int _a[1000000000L];
};

class Widget
{
    public:
        Widget(){}
        static std::new_handler set_new_handler(std::new_handler p) throw();
        static void * operator new(std::size_t size) throw(std::bad_alloc);
    private:
        static std::new_handler currentHandler;
        char a[4 * 100000000L];
};

std::new_handler Widget::currentHandler = nullptr;

std::new_handler Widget::set_new_handler(std::new_handler p) throw()
{
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

class NewHandlerHolder
{//use to recover old handler
    public:
        explicit NewHandlerHolder(std::new_handler nh):handler(nh){}
        ~NewHandlerHolder(){std::set_new_handler(handler);}
        NewHandlerHolder(const NewHandlerHolder &) = delete;
        NewHandlerHolder & operator=(const NewHandlerHolder &) = delete;
    private:
        std::new_handler handler;
};

void * Widget::operator new(std::size_t size) throw(std::bad_alloc)
{
    cout << "Widget::operator new called, size=" << size << endl;
    NewHandlerHolder 
        h(std::set_new_handler(currentHandler));//install Widget's handler
    return ::operator new(size);
}

/** mixin-style base class*/
template<typename T>
class NewHandlerSupport
{
    public:
        static std::new_handler set_new_handler(std::new_handler p) throw();
        static void * operator new(std::size_t size) throw(std::bad_alloc);
    private:
        static std::new_handler currentHandler;
};

template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = nullptr;

template<typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

template<typename T>
void * NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
    cout << "NewHandlerSupport::operator new called, size=" << size << endl;
    NewHandlerHolder 
        h(std::set_new_handler(currentHandler));//install Widget's handler
    return ::operator new(size);
}

class Widget1:public NewHandlerSupport<Widget1>{};

/** The template parameter T just distinguishes one inheriting class from another*/
class A
{
    public:
        static int i;
};

int A::i = 0;
class B:public A{};
class C:public A{};

template <typename T>
class Ax
{
    public:
        static int i;
};
template<typename T> int Ax<T>::i = 0;
class Bx:public Ax<Bx>{};
class Cx:public Ax<Cx>{};

int main(int argc, char *argv[])
{
    {
        cout << "# base" << endl;
        cout << (void *)std::set_new_handler(outOfMem) << endl;
        //int *p =  new int[1000000000L];
        //cout << "p=" << (void *)p << endl; 
        //X *p1 = new X();
    }

    {
        cout << "\n# DIY" << endl;
        
        Widget::set_new_handler(outOfMem);
        
        Widget * pw1 = new Widget;

        string *ps = new std::string;

        Widget1::set_new_handler(outOfMem);
        Widget1 * pw2 = new Widget1;

    }

    {//test static data member in class inherit
        cout << "\n# template parameter T" << endl;
        cout << "## No T" << endl;
        B::i = 1;
        cout << A::i << endl;//1
        cout << C::i << endl;//1
        cout << "## With T" << endl;
        Bx::i = 1;
        cout << Ax<Bx>::i << endl;//1
        cout << Ax<Cx>::i << endl;//0
        cout << Cx::i << endl;//0
    }

    {
        std::set_new_handler(nullptr);
        cout << "\n# Test std::nothrow" << endl;
        try
        {
            char *p = new char[10000000000L];
            if(p == NULL) // this test must fail
            {
                cout << "new failed" << endl;
            }
        }
        catch(std::exception & e)
        {
            cout << e.what() << endl;
        }

        char *p = new (std::nothrow) char[10000000000L];
        if(p == NULL) // this test may success
        {
            cout << "new failed" << endl;
        }

        cout << "## constructor throw" << endl;
        class foo
        {
            public:
                foo(void){throw "just thow";}
        };
        try
        {
            foo * pf = new (std::nothrow) foo;
            if(pf == NULL) // this test must failed
            {
                cout << "new failed" << endl;
            }
        }
        catch(const char * e)
        {
            cout << e << endl;
        }
    }
    return 0;
}
