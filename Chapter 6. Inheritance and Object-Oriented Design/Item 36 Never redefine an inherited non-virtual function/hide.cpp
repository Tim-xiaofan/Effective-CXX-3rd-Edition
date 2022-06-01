#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h> //c lib
#include <functional>

#include "same.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

class B
{
	public:
		void mf(void)
		{
			cout << "B::mf" << endl;
		}
};

class D:public B
{
	public:
		void mf(void)// hides B::mf; see Item33
		{
			cout << "D::mf" << endl;
		}
};

void hide(void)
{
	D x;
	B *pB = &x;
	pB->mf();

	D * pD = &x;
	pD->mf();
}
