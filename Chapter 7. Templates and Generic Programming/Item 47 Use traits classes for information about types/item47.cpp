#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    //std::swap
#include <exception>
#include <cstring>
#include <iterator>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;

/** move iter units forward; if d < 0, move iter backward */
//template<typename IterT, typename DistT>
//void advance(IterT& iter, DistT d)
//{
//    if(iter is a random access iterator)
//    {
//        iter += d;
//    }
//    else
//    {
//        if(d>=0){ while(d--) ++iter; }
//        else{ while(d++) --iter; }
//    }
//}
//
//template<typename IterT>
//struct iterator_traits
//{};
//
//template<typename IterT>
//struct iterator_traits<IterT*>
//{
//    typedef random_access_iterator_tag iterator_category;
//};

/** Template Specialization */
template<typename T> struct is_void { static const bool value = false;};
template<> struct is_void<void> { static const bool value = true;};

/** Partial Specialization */
template<typename T> struct is_pointer{ static const bool value = false; }; 
template<typename T> struct is_pointer<T*>{ static const bool value = true; }; 


/** Implement of Traits Classes*/
template<class IterT> 
struct iterator_traits 
{
    typedef typename IterT::value_type value_type;//迭代器所指对象的类型
};
/** Partial Specialization*/
template<class IterT> 
struct iterator_traits<IterT*> 
{
    typedef IterT value_type;//指针所指对象的类型
};
void fun(int a) 
{
    cout << "fun(int) is called" << endl;
}

void fun(double a) 
{
    cout << "fun(double) is called" << endl;
}

void fun(char a) 
{
    cout << "fun(char) is called" << endl;
}

int main(int argc, char *argv[])
{
    {
        cout << "#前置知识" << endl;
        cout << "##模板特化（Template Specialization）" << endl;
        is_void<bool> t1;
        is_void<void> t2;
        cout << std::boolalpha << "t1 is void:" << t1.value << endl;
        cout << std::boolalpha << "t2 is void:" << t2.value << endl;

        cout << "##偏特化（Partial Specialization）" << endl;
        is_pointer<int> p1;
        is_pointer<int *> p2;
        is_pointer<int[]> p3;
        cout << std::boolalpha << "p1 is pointer:" << p1.value << endl;
        cout << std::boolalpha << "p2 is pointer:" << p2.value << endl;
        cout << std::boolalpha << "p3 is pointer:" << p3.value << endl;

        cout << "#实现 Traits Classes" << endl;
        iterator_traits<vector<int>::iterator>::value_type a = 0;
        fun(a);  // 输出 fun(int) is called
        iterator_traits<vector<double>::iterator>::value_type b = 0;
        fun(b);  // 输出 fun(double) is called
        iterator_traits<char*>::value_type c = 0;
        fun(c);  // 输出 fun(char) is called
    }
    return 0;
}
