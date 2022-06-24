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

/** operator new member functions are inherited by derived classes*/
class Base
{
    public:
        Base(void){cout << "Base::constructor is called" << endl;}
        virtual ~Base(void) {cout << "Base::destructor is called" << endl;}
        static void * operator new(std::size_t size) throw(std::bad_alloc)
        {
            cout << "Base:operator new is called, size=" << size << endl;
            return ::operator new(size);
        }
        static void * operator new[](std::size_t size) throw(std::bad_alloc)
        {
            using namespace std;
            cout << "Base:operator new[] is called, size=" << size << endl;
            if(size != sizeof(Base))
            {
                return ::operator new[](size);
            }
            while(true)
            {//infinite loop
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
        static void operator delete(void * rawMemory, std::size_t size) throw()
        {
            printf("Base:operator delete is called:addr=%p, size=%d\n", 
                        rawMemory, static_cast<int>(size));
            if(rawMemory == nullptr) return;
            if(size != sizeof(Base))
            {// size if zero or Derived size
                ::operator delete(rawMemory);
                return;
            }
            // Base size
            free(rawMemory);
            return;
        }
};

class Derived: public Base
{
    public:
        Derived():Base(){cout << "Derived:constructor is called" << endl;}
        virtual ~Derived(){cout << "Derived:destructor is called" << endl;}
    private:
        char _a[1024];
};

void outOfMem(void)
{
    cout << "Out of memory" << endl;
    std::abort();
}


int main(int argc, char *argv[])
{
    {
        cout << "# new operator overload" << endl;
        std::set_new_handler(outOfMem);
        char * p = new char[4 * 100000000L];
        delete [] p;
    }

    {//test new operator in inheriting
        cout << "\n# new operator in inheriting" << endl;
        cout << "## sizeof(Base)=" <<sizeof(Base) << endl;
        Base * q = new Base();
        cout << "pBase = " << (void *)q << endl;
        delete q;
        
        cout << "\n## sizeof(Derived)=" << sizeof(Derived) << endl;
        Derived * p = new Derived;//gcc 4.8.5 work well??
        cout << "pDerived = " << (void *)p << endl;
        delete p;
        //p = new Derived[4];
        //delete[] p;
    }
    return 0;
}
