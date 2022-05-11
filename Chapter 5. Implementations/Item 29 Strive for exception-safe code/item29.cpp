#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;

typedef int Mutex;
#define unlock(x) lock((x))
class Image
{
	public:
		Image(const std::istream & is){}
};

template<typename T>
void lock(T * t){}
class Lock
{
	public:
		Lock(Mutex * mutex):_mutex(mutex){lock(_mutex);}
		~Lock(){unlock(_mutex);}
	private:
		Mutex *_mutex;

};

struct PMImpl
{
	unique_ptr<Image> bgImage;
	int imageChanges;
	PMImpl(const PMImpl & impl){}
};

class PrettyMenu
{
	public:
		// change background image
		void changeBackground(std::istream& imgSrc);
		void changeBackground1(std::istream& imgSrc);
		void changeBackground2(std::istream& imgSrc);
		void changeBackground3(std::istream& imgSrc);
	private:
		Mutex mutex;	// mutex for this object 
		Image *bgImage; // current background image of times image has been changed
		unique_ptr<Image> bgImage1;
		unique_ptr<PMImpl> pImpl;
		int imageChanges;
};



void PrettyMenu::
changeBackground(std::istream& imgSrc)
{//not exception-safe
	lock(&mutex); // acquire mutex(as in Item 14)
	delete bgImage; // get rid of old background
	++imageChanges; // update image change count
	bgImage = new Image (imgSrc); // install new background(if throw)
	unlock(&mutex); // release mutex unlock(&mutex);
}

void PrettyMenu::
changeBackground1(std::istream & imgSrc)
{//exception-safe: Leak no resources
	Lock m1(&mutex); // item14: use object to manage resource

	delete bgImage;
	++imageChanges;
	bgImage = new Image(imgSrc);
}

void PrettyMenu::
changeBackground2(std::istream & imgSrc)
{//exception-safe: Leak no resources and avoid data corrupted
	Lock m1(&mutex); // item14: use object to manage resource
	bgImage1.reset(new Image(imgSrc));
	++imageChanges;
}

void PrettyMenu::
changeBackground3(std::istream & imgSrc)
{//exception-safe: copy and swap
	using std::swap;

	Lock m1(&mutex); // item14: use object to manage resource

	unique_ptr<PMImpl> pNew(new PMImpl(*pImpl));//copy

	pNew->bgImage.reset(new Image(imgSrc)); // modify the copy
	pNew->imageChanges++;

	swap(pImpl, pNew);

	bgImage1.reset(new Image(imgSrc));
	++imageChanges;
}

class foo
{
	public:
		~foo(){cout << "foo::~foo() called" << endl;}
};

int main(int argc, char *argv[])
{
	unique_ptr<foo> pf(new foo());
	pf.reset(new foo());
	cout << "*** reset" << endl;
	return 0;
}
