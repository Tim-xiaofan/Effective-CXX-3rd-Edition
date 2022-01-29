#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using std::cout;
using std::endl;
using std::string;


class Widget 
{ 
    public: ~Widget() {throw "exception in Widget destructor";} // assume this might emit an exception 
};

void doSomething() { std::vector<Widget> v; } // v is automatically destroyed here

class DBConnection
{
    public:
        /**
         * function to return DBConnection objects;
         * params omitted for simplicity
         * */
        static DBConnection create();
        /**
         * close connection; throw an  exception if closing fails
         */
        void close(){throw "close failed";}
};

class DBConn
{ // class to manage DBConnection
    public:
        ~DBConn() 
        {
            try {db.close();}
            catch(const char *e)
            {
                cout << e << endl;
                std::abort();
            }
        }

    private:
        DBConnection db;
};

int main(int argc, char *argv[])
{
    DBConn db;
    return 0;
}
