#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h> //c lib
#include <functional>
#include "same.h"
#include "hide.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

int main(int argc, char *argv[])
{
	cout << "*****same*****" << endl;
	same();
	cout << "*****hide*****" << endl;
	hide();
	return 0;
}
