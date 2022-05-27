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

/** is-a*/
class Person {};
class Student:public Person {};
void eat(const Person & p){}
void study(const Student& s){} // only students study

class Rectangle
{
	public:
		Rectangle(int h = 5, int w = 5): _height(h), _width(w){}
		virtual ~Rectangle(){}
		virtual void setHeight(int newHeight){_height = newHeight;}
		virtual void setWidth(int newWidth){_width = newWidth;}
		virtual int height() const {return _height;} // return current values
		virtual int width() const{return _width;}
	private:
		int _height;
		int _width;
};

class Square:public Rectangle
{
	public:
		Square():Rectangle(){}
		virtual ~Square(){}
};


void makeBigger(Rectangle & r)
{
	int oldHeight = r.height();

	r.setWidth(r.width() + 10); // add 10 to r's width

	assert(r.height() == oldHeight);
}


int main(int argc, char *argv[])
{
	Person p;
	Student s;

	eat(p);
	eat(s);

	study(s);
	//study(p); //error

	{// distinct
		/** trouble*/
		class Bird
		{
		};

		class FlyingBird:public Bird
		{
			public:
				virtual void fly();
		};

		class Penguins:public Bird //Penguins arr birds
		{
		};

	}

	{//runtime error
		class Bird
		{
			virtual void fly(); // birds can fly
		};
		class Penguin: public Bird 
		{
			public:
				virtual void fly(){std::cerr << "Attempt to make a penguin fly!\n";}
		};
		Penguin pg;
		pg.fly();

	}

	{//compile error
		class Bird
		{
		};
		class Penguin: public Bird 
		{
		};
		Penguin pg;
		//pg.fly();

	}

	{
		Square s;
		assert(s.width() == s.height()); // this must be true for all squares
		makeBigger(s); // by inheritance, s is-a Rectangle
		assert(s.width() == s.height()); // this must be true for all squares
	}
	return 0;
}

