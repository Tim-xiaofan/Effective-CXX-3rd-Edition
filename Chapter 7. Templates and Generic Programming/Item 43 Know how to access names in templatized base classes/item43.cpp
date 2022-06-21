#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h> //c lib
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


class MsgInfo {};

class CompanyA
{
    public:
        void sendCleartext(const MsgInfo & msg){}
        void sendEncrypted(const MsgInfo & msg){}
};

class CompanyB
{
    public:
        void sendCleartext(const MsgInfo & msg){}
        void sendEncrypted(const MsgInfo & msg){}
};

class CompanyZ
{
    public:
        void sendEncrypted(const MsgInfo & msg){}
};


template<typename Company>
class MsgSender
{
    public:
        void sendClear(const MsgInfo & info)
        {
            std::string msg;
            Company c;
            c.sendCleartext(info);
        }
        void sendEncrypted(const MsgInfo & info)
        {
            std::string msg;
            Company c;
            c.sendEncrypted(info);
        }
};

template<typename Company>
class LoggingMsgSender:public MsgSender<Company>
{
    public:
        using MsgSender<Company>::sendClear;
        void sendClearMsg(const MsgInfo & info)
        {
            std::cout << "sendClearMsg" << std::endl;
            //sendClear(info);// not compile, if Company == CompanyZ, this function doesn't exist!
            /** method1:this->*/
            this->sendClear();
            /** method2:using declaration*/
            sendClear();
            /** method3:base::*/
            MsgSender<Company>::sendClear();
        }
};

template<>
class MsgSender<CompanyZ>
{
    public:
        void sendSecret(const MsgInfo & info)
        {
            CompanyZ c;
            c.sendEncrypted(info);
        }
};

int main(int argc, char *argv[])
{
    LoggingMsgSender<CompanyZ> zMsgSender;
    MsgInfo msgData;
    zMsgSender.sendClear(msgData);//compiler knows that CompanyZ doesn't have sendClear
	return 0;
}
