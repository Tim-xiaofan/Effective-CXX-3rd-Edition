#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

void logCall(const std::string& funcName)// make a log entry 
{
    cout << funcName << endl;
}

class Date 
{
    public:
        Date(int dt):x(dt){}
        Date() = default;
        Date(const Date & ) = default;
        Date & operator=(const Date &) = default;
        friend ostream & operator<<(ostream & , const Date &);
    private:
        int x;
}; // for dates in time

ostream & operator<<(ostream & os, const Date & d)
{
    os << d.x;
    return os;
}

class Customer 
{
    public:  
        Customer(const string & mname = "unkown", int dt = 1024) 
            :name(mname), lastTransaction(dt){ cout << "Customer construct" << endl;}
#ifdef DIY
        Customer(const Customer& rhs); 
        Customer & operator=(const Customer& rhs); 
#endif
        friend ostream & operator<<(ostream & , const Customer &);
    private: 
        std::string name;
        Date lastTransaction;
};

ostream & operator<<(ostream & os, const Customer & c)
{
    os << "name: " << c.name << ", lastTransaction: " << c.lastTransaction;
    return os;
}

#ifdef DIY
Customer::Customer(const Customer& rhs) 
        : name(rhs.name) // copy rhs's data 
{ 
    logCall("Customer copy constructor"); 
}

Customer& Customer::operator=(const Customer& rhs) 
{ 
    logCall("Customer copy assignment operator"); 
    name = rhs.name; // copy rhs's data
    return *this;
}
#endif


class PriorityCustomer: public Customer 
{ // a derived class 
    public:
        PriorityCustomer() = default;
        PriorityCustomer(const string & mname):Customer(mname){}
        PriorityCustomer(const PriorityCustomer& rhs);
        PriorityCustomer& operator=(const PriorityCustomer& rhs); 
        friend ostream & operator<<(ostream & , const PriorityCustomer &);
    private: 
        int priority;
};

ostream & operator<<(ostream & os, const PriorityCustomer & pc)
{
    os << (const Customer &) pc << ",priority:" << pc.priority;
    return os;
}

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) : 
#ifdef CALLBASE
    Customer(rhs),
#endif
    priority(rhs.priority) 
{
    logCall("PriorityCustomer copy constructor"); 
}

PriorityCustomer & PriorityCustomer::operator=(const PriorityCustomer& rhs) 
{
    logCall("PriorityCustomer copy assignment operator"); 
#ifdef CALLBASE
    Customer::operator=(rhs);
#endif
    priority = rhs.priority; 
    return *this;
}


int main(int argc, char *argv[])
{
    cout << "*****Customer\n";
    Customer c("c");
    cout << "c:"<< c << endl;
    Customer c1(c);
    cout << "c1:" << c1 << endl;
    Customer c2("c2", 2048);
    c2 = c1;
    cout << "c2:" << c2 << endl;
    cout << "*****PriorityCustomer\n";
    PriorityCustomer pc("pc"), pc1(pc);
    cout << "pc:" << pc << endl;
    cout << "pc1:" << pc1 << endl;
    pc1 = pc;
    cout << "pc2:" << pc1 << endl;
    return 0;
}
