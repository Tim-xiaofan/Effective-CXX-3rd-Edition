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

//#define G_OVERLOAD
#ifdef G_OVERLOAD
void * operator new(std::size_t size) throw(std::bad_alloc)
{
    using namespace std;
    
    cout << "My new operator is called:size=" << size << endl;
    if(size == 0)
    {
        size = 1;
    }

    while(true)
    {
        void * pMem = malloc(size);
        if(pMem != nullptr)
        {
            return pMem;
        }
        else
        {
            new_handler globalHandler = set_new_handler(nullptr);
            set_new_handler(globalHandler);
            if(globalHandler != nullptr)
            {
                (*globalHandler)();
            }
            else
            {
                throw bad_alloc();
            }
        }
    }
}

void operator delete(void *rawMemory) throw()
{
    cout << "delete is called" << endl;
    if(rawMemory == nullptr) return;
    free(rawMemory);
}
#endif

class Widget
{
    public:
        Widget(void)
        {
            cout << "Widget::Widget() is called" << endl;
           // throw "Just throw";
        }
        ~Widget(void)
        {
            cout << "Widget::~Widget() is called" << endl;
        }
        static void * operator new(std::size_t size, std::ostream & logStream)
            throw(std::bad_alloc)
        {
            logStream << "Widget::operator new(placement) is called" << endl;
            return ::operator new(size);
        }

        static void operator delete(void *pMemory) throw()
        {
            cout << "Widget::operator delete(normal) is called" << endl;
            ::operator delete(pMemory);
        }
        static void operator delete(void *pMemory, std::ostream & logStream) throw()
        {
            cout << "Widget::operator delete(placement) is called" << endl;
            ::operator delete(pMemory);
        }
};

class Base
{
    public:
        /** Hide gloabl one*/
        static void * operator new(std::size_t size, std::ostream & logStream)
            throw(std::bad_alloc)
        {
            logStream << "Base::operator new(placement) is called" << endl;
            return ::operator new(size);
        }
};

class Derived: public Base
{
    public:
        /** hide both global and inherited versions*/
        static void * operator new(std::size_t size)
            throw(std::bad_alloc)
        {
            cout << "Derived::operator new(normal) is called" << endl;
            return ::operator new(size);
        }
};

int main(int argc, char *argv[])
{
    {
        cout << "# Problem1: first call succeeds, but the second "
            "call results in an exception being thrown" << endl;
        Widget *pw = new(std::cout) Widget;//placement one is called
        delete pw;//normal one is called
    }

    {
        cout << "\n# Problem2: hide" << endl;
        //Base *pb = new Base;//error, noraml form is hidden
        Base *pb = new(std::cerr) Base;//fine
        delete pb;

        //Derived *pd = new (std::cerr) Derived; // error
        Derived * pd = new Derived;
        delete pd;
    }
    return 0;
}
