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

template <typename C>
void print2nd(const C& container)
{
	if(container.size() >= 2)
	{
		typename C::const_iterator iter(container.begin());
		auto iter1 = container.begin();
		++iter;
		int value = * iter;
		cout << value << endl;
	}
}

int main(int argc, char *argv[])
{
	vector<int> v;
	v.push_back(0);
	v.push_back(1);
	print2nd(v);
	return 0;
}
