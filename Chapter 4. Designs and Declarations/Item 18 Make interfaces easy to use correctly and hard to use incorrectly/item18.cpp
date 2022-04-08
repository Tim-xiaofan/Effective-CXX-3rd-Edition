#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using std::cout;
using std::endl;
using std::string;

class Date 
{
    public:
        Date(int month, int day, int year){}
};

struct Day
{
    explicit Day(int d):val(d){}
    int val;
};

struct Month
{
    explicit Month(int m):val(m){}
    int val;
};

struct Year
{
    explicit Year(int y):val(y){}
    int val;
};

class Date1
{
    public:
        Date1(const Month& m, const Day& d, const Year& y){}
};


class Month1 
{ 
    public: 
        static Month1 Jan() { return Month1(1); } // functions returning all valid 
        static  Month1 Feb() { return Month1(2); } // Month values; 
        static  Month1 Mar() { return Month1(3); } // Month values; 
        static Month1 Dec() { return Month1(12); } // objects 
        //... // other member functions 
    private: 
        explicit Month1(int m):val(m){}; 
        // prevent creation of new // Month values ... // month-specific data 
        int val;
};


class Date2
{
    public:
        Date2(const Month1 & m, const Day& d, const Year& y){}
};

int main(int argc, char *argv[])
{
    /** noting*/
    Date d(30, 3, 1995); // Oops! Should be "3, 30" , not "30, 3"
    Date d1(2, 20, 1995); // Oops! Should be "3, 30" , not "2, 20"

    /** struct*/
    //Date1 d2(30, 3, 1995); // error! wrong types
    //Date1 d3(Day(30), Month(3), Year(1995)); // error! wrong types
    Date1 d4(Month(3), Day(30), Year(1995)); // okay, types are correct

    /** use class instead function*/
    Date2 d5(Month1::Mar(), Day(30), Year(1995));
    return 0;
}
