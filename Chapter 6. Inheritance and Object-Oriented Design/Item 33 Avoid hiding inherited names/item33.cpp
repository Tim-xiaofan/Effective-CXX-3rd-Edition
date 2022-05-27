#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h> //c lib

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;



int main(int argc, char *argv[])
{
	{//public inherit
		class Base 
		{
			private:
				int x;
			public:
				virtual void mf1() = 0;
				virtual void mf1(int){ cout << "Base::mf1(int)\n";}
				virtual void mf2(){cout << "Base::mf2()\n";}
				void mf3 (){cout << "Base::mf3()\n";}
				void mf3 (double){cout << "Base::mf3()\n";} 
		};

		class Derived: public Base
		{
			public:
				using Base::mf1; // make all things in Base named mf1 and mf3 
				using Base::mf3; // visible (and public) in Derived's scope
				virtual void mf1(){cout << "Derived::mf1()\n";} 
				void mf3(){cout << "Derived::mf3()\n";} 
				void mf4(){cout << "Derived::mf4()\n";} 
		};

		Derived d;
		int x = -1;

		d.mf1();// fine,calls Derived::mfl
		d.mf1(x);// error! Derived::mfl hides Base::mf1
		d.mf2();// fine,calls Base::mf2
		d.mf3();// fine,calls Derived::mf3
		d.mf3(x);// error! Derived::mf3 hides Base::mf3
	}

	{
		class Base 
		{
			private:
				int x;
			public:
				virtual void mf1() = 0;
				virtual void mf1(int){ cout << "Base::mf1(int)\n";}
				virtual void mf2(){cout << "Base::mf2()\n";}
				void mf3 (){cout << "Base::mf3()\n";}
				void mf3 (double){cout << "Base::mf3()\n";} 
		};

		class Derived: private Base
		{
			public:
				/** forwarding function; implicitly inline (see Item 30)*/
				virtual void mf1(){Base::mf1();} 
		};

		Derived d;
		int x = -1;
		d.mf1(); // fine, calls Derived::mf1
		d.mf1(x); // error! Base::mf1() is hidden

	}

	return 0;
}

