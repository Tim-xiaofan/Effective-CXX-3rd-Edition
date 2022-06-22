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

namespace book
{
    template<typename IterT>
    struct iterator_traits
    {
        typedef typename IterT::iterator_category iterator_category;
    };

    template<typename IterT>
    struct iterator_traits<IterT*>
    {//pointer
        typedef IterT iterator_category;
    };

    /** move iter units forward; if d < 0, move iter backward */
    template<typename IterT, typename DistT>
    void advance(IterT& iter, DistT d)
    {//two problem: 1.compilation problems 2. if statement is evaluation at run time
        if(typeid(typename std::iterator_traits<IterT>::iterator_category) == 
                    typeid(std::random_access_iterator_tag))
        {
            iter += d;
        }
        else
        {
            if(d>=0){ while(d--) ++iter; }
            else{ while(d++) --iter; }
        }
    }

    /** solution: function overload*/
    template<typename IterT, typename DistT>
    void doAdvance(IterT & iter, DistT d, std::random_access_iterator_tag)
    {
        cout << "std::random_access_iterator_tag" << endl;
        iter += d;
    }
    template<typename IterT, typename DistT>
    void doAdvance(IterT & iter, DistT d, std::bidirectional_iterator_tag)
    {
        cout << "std::bidirectional_iterator_tag" << endl;
        if(d>=0){ while(d--) ++iter; }
        else{ while(d++) --iter; }
    }
    template<typename IterT, typename DistT>
    void doAdvance(IterT & iter, DistT d, std::input_iterator_tag)
    {
        cout << "std::input_iterator_tag" << endl;
        if(d>=0){ while(d--) ++iter; }
        else
        {
            throw std::out_of_range("Negative distance");
        }
    }
    template<typename IterT, typename DistT>
    void advance1(IterT& iter, DistT d)
    {
        /** use DIY iterator_traits*/
        doAdvance(iter, d, typename iterator_traits<IterT>::iterator_category());
    }
}

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

    {
        using namespace book;
        cout << "#book" << endl;
        vector<int> vi = {0,1,2,3};
        auto it = vi.begin();
        advance1(it, 2);//std::random_access_iterator_tag
        list<int> li = {0, 1, 2, 3};
        auto it1 = li.begin();
        advance1(it1, 2);//std::bidirectional_iterator_tag
    }
    return 0;
}
