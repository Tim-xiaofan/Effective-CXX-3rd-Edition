#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using std::cout;
using std::endl;
using std::string;

class Transaction
{
    public:
        Transaction(){init();}//这样能通过编译
        virtual void logTransaction() const = 0;//pure virtual function
    private:
        void init() const{logTransaction();};
};

class BuyTransaction : public Transaction
{
    public:
        virtual void logTransaction() const{cout << "A BuyTransaction\n";}
};

class SellTransaction : public Transaction
{
    public:
        virtual void logTransaction() const{cout << "A SellTransaction\n";}
};

int main(int argc, char *argv[])
{
    BuyTransaction bt;
    SellTransaction st;
    return 0;
}
