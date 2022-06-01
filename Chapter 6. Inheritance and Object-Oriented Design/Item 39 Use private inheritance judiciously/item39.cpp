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

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

class person{};
class student:private person{};

void eat(const person & p) {}
void study(const student & s) {}

class Timer
{
	public:
		explicit Timer(int tickFrequency):_tickFrequency(tickFrequency){}
		virtual void onTick()const{ cout << "Timer::onTick" << endl;};
	private:
		int _tickFrequency;
};

// method1:private inherit
class Widget:private Timer
{
	private:
		virtual void onTick() const { cout << "Widget::onTick" << endl;}
};

//method2:composition 
class Widget1
{
	private:
		class WidgetTimer:public Timer
		{
			public:
				virtual void onTick() const{ cout << "WidgetTimer::onTick" << endl;}
		};
		WidgetTimer timer;
};

class Empty
{
	public:
		typedef vector<int> vi;
		enum color{RED, BLUE, YELLOW};
};

class HoldsAnInt
{
	private:
		int x;
		Empty e; // should require no memory
};

class HoldsAnInt1:public Empty 
{
	private:
		int x;
};

int main(int argc, char *argv[])
{
	person p;
	student s;
	eat(p);
	//eat(s); // error! a Student isn't a Person
	study(s);

	cout << "sizeof(Empty):" << sizeof(Empty) << endl;
	cout << "sizeof(int):" << sizeof(int) << endl;
	cout << "sizeof(HoldsAnInt):" << sizeof(HoldsAnInt) << endl;
	cout << "sizeof(HoldsAnInt1):" << sizeof(HoldsAnInt1) << endl;
	return 0;
}
