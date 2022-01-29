#include <iostream>
#include <string>
#include <cstdint>
using std::cout;
using std::endl;
using std::string;

class TimeKeeper 
{ 
    public: 
        TimeKeeper(){};
#ifdef VIRTUAL
        virtual 
#endif
        ~TimeKeeper(){cout <<"Base destructor\n";}
};

class AtomicClock: public TimeKeeper 
{
    ~AtomicClock(){cout << "AtomicClock destructor\n";}
}; 

class WaterClock: public TimeKeeper 
{
    ~WaterClock(){cout << "WaterClock destructor\n";}
}; 

class WristWatch: public TimeKeeper 
{
    ~WristWatch(){cout << "WristWatch destructor\n";};
};

static TimeKeeper * 
getTimeKeeper(int type)
{
    switch(type)
    {
        case 0:return new AtomicClock();
        case 1:return new WaterClock();
        case 2:return new WristWatch();
    }
    return nullptr;
}

class Point 
{ // a 2D point public:
    public:
        Point(int xCoord, int yCoord); 
#ifdef VIRTUAL
        /**
          requires that objects carry information 
          that can be used at runtime to determine 
          which virtual functions should be invoked on the objec
         */
        virtual
#endif
        ~Point();
    private:
        uint32_t x, y;
};

class SpecialString: public std::string 
{ 
    // bad idea! std::string has a ... // non-virtual destructor 
    ~SpecialString(){cout << "SpecialString destructor\n";}
};

int main(int argc, char *argv[])
{
    TimeKeeper * ptk; 
    for(int i = 0 ; i < 3; ++i)
    {
        ptk = getTimeKeeper(i);
        delete ptk;
    }

    /** 虚函数vptr占用空间*/
    cout << "sizeof(TimeKeeper): " << sizeof(TimeKeeper) << endl;
    string info = (sizeof(Point) == 64) ? "is":"is not";
    cout << "sizeof(Point): " << sizeof(Point) << " "<< info << " 8 bytes" << endl;

    /** 未定义的行为*/
    SpecialString *pss = new SpecialString();
    std::string *ps;
    ps = pss;// SpecialString* std::string*// SpecialString* std::string*
    /**
      undefined! In practice, 
     *ps's SpecialString resources  will be leaked, 
     because the SpecialString destructor won't be called.
     */
    delete ps;
    return 0;
}
