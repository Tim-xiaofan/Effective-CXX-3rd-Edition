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

class Widget
{
	public:
		Widget(){}
		virtual ~Widget(){}
		virtual std::size_t size() const{return 0;};
		virtual void normalize(){};
		void swap(Widget & other){};
		bool operator!=(const Widget & w){return true;}
};

Widget someNastyWidget;

void doProcessing(Widget& w)
{
	cout << "Non-template is called" << endl;
	if(w.size() > 10 && w !=someNastyWidget)
	{
		Widget temp(w);
		temp.normalize();
		temp.swap(w);
	}
}

template<typename T>
void doProcessing(T& w)
{
	cout << "Template is called" << endl;
	if(w.size() > 10 && w !=someNastyWidget)
	{
		T temp(w);
		temp.normalize();
		temp.swap(w);
	}
}

int main(int argc, char *argv[])
{
	Widget w;
	doProcessing(w);
	return 0;
}
