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

class Shape 
{
	public:
		virtual void draw() const = 0;
		virtual void error(const std::string & msg) {cout << msg << endl;}
		int objectID()const;
};

void Shape::draw() const 
{
	cout << "You must provide a draw function" << endl;
}

class Rectangle:public Shape
{
	public:
		~Rectangle(){}
		virtual void draw() const {cout << "Rectangle::draw()\n";}
		//virtual void error(const std::string & msg) {cout << msg << endl;}
};

class Ellipse:public Shape
{
	public:
		~Ellipse(){}
		virtual void draw() const {cout << "Ellipse::draw()\n";}
		virtual void error(const std::string & msg) {cout << msg << endl;}
};

class Airport{};

class Airplane
{
	public:
		virtual void fly(const Airport& destination)=0;
};

void Airplane::fly(const Airplane & destination)
{
	cout  << "Airplane::fly()" << endl;
}

int main(int argc, char *argv[])
{
	cout << "Pure virtual function definition" << endl;
	//Shape *ps = new Shape; // error! Shape is abstract

	Shape *ps1 = new Rectangle; // fine
	ps1->draw(); // calls Rectangle::draw

	Shape *ps2 = new Ellipse; // fine
	ps2->draw();// calls Ellipse::draw  

	ps1->Shape::draw();// calls Shape::draw 
	ps2->Shape::draw();// calls Shape::draw

	{// 显示使用默认实现(fly): 分离
		class Airplane
		{
			public:
				virtual void fly(const Airport& destination)=0;
			protected:
				void defaultFly(const Airport& destination)
				{
					cout << "Airport::fly()" << endl;
				}
		};
		class ModelA: public Airplane 
		{
			public:
				virtual void fly(const Airport & destination)
				{ 
					defaultFly(destination);
				}

		};

		class ModelB: public Airplane 
		{
			public:
				virtual void fly(const Airport & destination)
				{ 
					defaultFly(destination);
				}

		};

		class ModelC: public Airplane 
		{
			public:
				virtual void fly(const Airport & destination)
				{
					cout << "ModelC::fly()" << endl;
				}
		};


		cout << "\n\nSimple virtual function" << endl;
		Airport PDX; // PDX is the airport near my home
		ModelC *pa = new ModelC;
		pa->fly(PDX); // calls Airplane::fly
	}

	{//take advantage of the ability to define a pure virtual function(不分离)

		class ModelA: public Airplane 
		{
			public:
				virtual void fly(const Airport & destination)
				{ 
					Airplane::fly(destination);
				}

		};

		class ModelB: public Airplane 
		{
			public:
				virtual void fly(const Airport & destination)
				{ 
					Airport::fly(destination);
				}

		};

		class ModelC: public Airplane 
		{
			public:
				virtual void fly(const Airport & destination)
				{
					cout << "ModelC::fly()" << endl;
				}
		};
		
		cout << "\n\nPure virtual function" << endl;
		Airport PDX; // PDX is the airport near my home
		ModelC *pa = new ModelC;
		pa->fly(PDX); // calls Airplane::fly
	}

	return 0;
}

