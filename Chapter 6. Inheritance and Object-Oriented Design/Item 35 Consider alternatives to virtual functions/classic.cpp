#include "classic.h"
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h> //c lib
#include <functional>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

class GameCharacter; // forward declaration

class HealthCalcFunc
{
	public:
		virtual int calc(const GameCharacter& gc) const
		{
			cout << "HealthCalcFunc::calc called" << endl;
			return 0;
		}
};

HealthCalcFunc defaultHealthCalc;

class GameCharacter 
{
	public:
		explicit GameCharacter(HealthCalcFunc *phcf = &defaultHealthCalc)
			:pHealthCalc(phcf)
		{
			cout << "GameCharacter::constructor:" << (void *) phcf << endl;
		}

		int healthValue1() const
		{ 
			cout << "healthValue1 called" << endl;
			return pHealthCalc->calc(*this);
		}

		int foo() const
		{ cout << "GameCharacter::foo" << endl; return 0;}

	private:
		HealthCalcFunc *pHealthCalc;
};

void classic(void)
{
	GameCharacter gc(&defaultHealthCalc);
	gc.foo();
	gc.healthValue1();
}
