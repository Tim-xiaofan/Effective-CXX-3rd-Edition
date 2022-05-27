#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h> //c lib
#include <functional>

#include "classic.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

class  GameCharacter;
int defaultHealthCalc(const GameCharacter& gc)
{
	cout << "defaultHealthCalc called" << endl;
	return 0;
}

class GameCharacter
{
	public:
		typedef function<int (const GameCharacter&)> HealthCalcFunc;
		explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
			:healthFunc(hcf){}

		int healthValue()const
		{ return healthFunc(*this);}

	private:
		HealthCalcFunc healthFunc;
};

short calcHealth(const GameCharacter&) // not int
{
	cout << "short calcHealth called" << endl;
	return 0;
}

struct HealthCalculator
{
	int operator()(const GameCharacter &) const
	{
		cout << "HealthCalculator" << endl;
		return 0;
	}
};

class GameLevel
{
	public:
		float health(const GameCharacter&) const
		{
			cout << "float health clalled" << endl;
			return 0;
		}
};

class EvilBadGuy: public GameCharacter
{
	public:
		explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
			:GameCharacter(hcf){}
};

class EyeCandyCharacter: public GameCharacter
{
};

int main(int argc, char *argv[])
{
	cout << "The Strategy Pattern via std::function" << endl;

	EvilBadGuy ebg1(calcHealth);
	ebg1.healthValue();

	GameLevel currentLevel;
	EvilBadGuy ebg2(bind(&GameLevel::health, 
					currentLevel, 
					std::placeholders::_1));
	ebg2.healthValue();

	cout << "The \"Classic\" Strategy Pattern" << endl;
	classic();
	return 0;
}
