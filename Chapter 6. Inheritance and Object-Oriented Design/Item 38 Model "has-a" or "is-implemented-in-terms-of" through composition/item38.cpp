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

template<typename T>
class set
{
	public:
		bool member(const T & item)const;
		set & insert(const T & item);
		set & remove(const T & item);
		std::size_t size()const;
		template <typename U>
		friend ostream & operator<<(ostream & os, const set<U> & s);
	private:
		std::list<T> rep;// representation for Set data
};

template <typename T>
ostream & operator<<(ostream & os, const set<T> & s)
{
	for(auto it = s.rep.begin(); it!=s.rep.end(); ++it)
	  os << *it << " ";
	return os;
}

template<typename T>
bool set<T>::member(const T & item) const
{
	return std::find(rep.begin(), rep.end(), item) != rep.end();
}

template<typename T>
set<T> &  set<T>::insert(const T & item)
{
	if(!member(item)) rep.push_back(item);
	return *this;
}

template<typename T>
set<T> & set<T>::remove(const T & item)
{
	typename std::list<T>::iterator it = 
		std::find(rep.begin(), rep.end(), item);
	if(it != rep.end()) rep.erase(it);
	return *this;
}

template<typename T>
std::size_t set<T>::size()const
{
	return rep.size();
}

int main(int argc, char *argv[])
{
	set<int> s;
	s.insert(0);
	s.insert(1);
	s.insert(2);
	cout << "***origin" << endl;
	cout << s << endl;
	cout << "***remove(0)" << endl;
	cout << s.remove(0) << endl;
	return 0;
}
