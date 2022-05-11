#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::shared_ptr;
using std::vector;

// class for representing points
class Point
{
	public:
		Point(int x,int y){};
		void setX(int newVal){};
		void setY(int newVal){};
};
// Point data for a Rectangle 
struct RectData 
{
	Point ulhc; // ulhc = " upper left-hand corner"
	Point lrhc; // lrhc =" lower right-hand corner"
};

class Rectangle
{
	public:
		~Rectangle(){cout << "~Rectangle() called" << endl;}
		Rectangle(){};
		Rectangle(const Point & p1, const Point & p2){}
		/** self-contradictory: const member but return reference
		  can be modified)*/
		Point& upperLeft() const {return pData->ulhc;} 
		Point& lowerRight() const {return pData->lrhc;}
		/**solution: add const */
		const Point& upperLeft1() const {return pData->ulhc;} 
		const Point& lowerRight1() const {return pData->lrhc;}
	private:
		shared_ptr<RectData> pData;
};

class GUIObject{};
const Rectangle boundingBox(const GUIObject & obj)
{
	return Rectangle();
}


int main(int argc, char *argv[])
{
	/** problem1: modifiy const object*/
	{
		cout << "\n\n******problem1*****" << endl;
		Point coord1(0, 0);
		Point coord2(100, 100);
		const Rectangle rec(coord1, coord2);//const
		rec.upperLeft().setX(50);//but,const has been modified
		//rec.upperLeft1().setX(50);//compile error
	}

	/** problem2: dangling handle--handles that refer to parts of objects 
	  that don't exist any longer */
	{
		cout << "\n\n*****problem2*****" << endl;
		GUIObject * pgo = new GUIObject();
		const Point * pUpperLeft = & (boundingBox(*pgo).upperLeft1());
	}
	return 0;
}
