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

class shape
{
	public:
		enum shape_color{red, green, blue};
		virtual void draw(shape_color color = red) const = 0;
};

class rectangle:public shape
{
	public:
		// notice the different default parameter value — bad! 
		virtual void draw(shape_color color = green) const
		{
			cout << "rectangle::draw, color = " << color << endl;
		}
};

class circle:public shape
{
	public:
		virtual void draw(shape_color color) const
		{
			cout << "circle::draw, color = " << color << endl;
		}
};

int main(int argc, char *argv[])
{
	// static type = shape*
	shape *ps;
	// static type = shape*
	shape *pc = new circle;
	// static type = shape*
	shape *pr = new rectangle;
	pr->draw();

	// dynamic bound
	cout << "***** dynamic bound *****" << endl;
	pc->draw(shape::green);
	pr->draw(shape::green);


	//unexpect
	cout << "***** static bound parameter *****" << endl;
	pr->draw();
	ps = pr;
	ps->draw();
	return 0;
}
