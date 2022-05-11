#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;

class Persion
{
	public:
		/** implicit inline*/
		int age() const{return theAge;}
		friend std::ostream & operator<<(std::ostream & os, const Persion & p)
		{
			return os << p.theAge;
		}
	private:
		int theAge;
};

/** explicit inline*/
template<typename T>
inline const T & max(const T & a, const T & b)
{
	return (a < b) ? b:a;
}

/** not recommended*/
inline int fact(int n)
{
	if(n == 1) return 1;
	return n * fact(n - 1);
}

inline void f() {} // assume compilers are willing to inline calls to f

class Base
{
	public:
		~Base(){}
		Base(){}
	private:
		std::string bm1, bm2;//base members 1 and 2
};

class Derived: public Base
{
	public:
		Derived();// Derived's ctor is empty — or is it?
	private:
		std::string dm1, dm2, dm3; // derived members 1–3
};

Derived::Derived()
{
	try
	{
		dm1 = string("");
	}
	catch(std::exception & e)
	{
		throw;
	}
}

int main(int argc, char *argv[])
{
	cout << "fact(10):" << fact(10) << endl;
	void (*pf)() = f; // pf points to f
	cout << "pf:" << (void*)pf << endl;
	f(); // this call will be inlined, because it's a "normal" call
	pf(); // this call probably won't be, because it's through a function pointer
	return 0;
}
