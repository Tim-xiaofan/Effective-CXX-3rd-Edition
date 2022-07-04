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
#include <functional>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::shared_ptr;
using std::weak_ptr;
using std::vector;
using std::list;

/** 智能指针的循环引用*/
class Node
{
    public:
        shared_ptr<Node> pre;
        shared_ptr<Node> next;

        Node(int v)
        {
            value = v;
            cout << "Constructor:" << value << endl;
        }
        ~Node()
        {
            cout << "Destructor:" << value << endl;
        }
    private:
        int value;
};

class Node1
{
    public:
        weak_ptr<Node1> pre;
        shared_ptr<Node1> next;

        Node1(int v)
        {
            value = v;
            cout << "Constructor:" << value << endl;
        }
        ~Node1()
        {
            cout << "Destructor:" << value << endl;
        }
    private:
        int value;
};

/** std::function*/
void registerCallback(std::string func(int))
{
    cout << "rcb1:" << func(1) << endl;
}

void registerCallback(std::function<std::string (int)> func)
{
    cout << "rcb2:" << func(2) << endl;
}

std::string func(int x){ return "func";}
std::string func1(int x, std::string str){ return "func1";}
typedef std::string (*f_t)(int x);

int main(int argc, char *argv[])
{
    {
        cout << "*** cycle ref: src leak ***" << endl;
        shared_ptr<Node> n1 = std::make_shared<Node>(1);
        shared_ptr<Node> n2 = std::make_shared<Node>(2);
        n1->next = n2;
        n2->pre = n1;
        cout << "n1:" << n1.use_count() << endl;
        cout << "n2:" << n2.use_count() << endl;
    }
    
    {
        cout << "\n*** cycle ref : solution ***" << endl;
        shared_ptr<Node1> n1 = std::make_shared<Node1>(1);
        shared_ptr<Node1> n2 = std::make_shared<Node1>(2);
        n1->next = n2;
        n2->pre = n1;

        cout << "n1:" << n1.use_count() << endl;
        cout << "n2:" << n2.use_count() << endl;
    }
    
    {
        cout << "\n*** std::function ***" << endl;
        registerCallback(func);
        std::function<std::string (int)>  tmp  = 
            std::bind(func1, std::placeholders::_1, "");
        registerCallback(tmp);
        f_t l = [](int x)->std::string{ return "lambda";};
        registerCallback(l);
    }
    return 0;
}
