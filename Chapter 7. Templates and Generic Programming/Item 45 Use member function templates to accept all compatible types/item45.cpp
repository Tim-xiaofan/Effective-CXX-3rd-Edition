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

class Top {public:int i;};
class Middle: public Top {};
class Bottom: public Middle {};

template<typename T>
class SmartPtr
{
    public:
        explicit SmartPtr(T * realPtr):_realPtr(realPtr){}
        /** generalized copy constructor*/
        template<typename U>
        SmartPtr(const SmartPtr<U>& other):_realPtr(other.get()){}
        ~SmartPtr(void){delete _realPtr;}
        T * get(void) const {return _realPtr;}
    private:
        T * _realPtr;
};

int main(int argc, char *argv[])
{
    {
        Top *pt1 = new Middle; // convert Middle* --> Top*
        Top *pt2 = new Bottom; // convert Bottom* --> Top*
        const Top *pct2 = pt1; // convert Top* --> const Top*
        cout << (void *)pt1 << endl;
        cout << (void *)pt2 << endl;
        cout << (void *)pct2 << endl;
    }

    {
        /** program: double free*/
        SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);// convert SmartPtr<Middle> --> SmartPtr<Top>
        pt1 = SmartPtr<Bottom>(new Bottom);
        //SmartPtr<Bottom> pt2 = SmartPtr<Top>(new Top);//not compile
        cout << "done." << endl;
    }
    return 0;
}
