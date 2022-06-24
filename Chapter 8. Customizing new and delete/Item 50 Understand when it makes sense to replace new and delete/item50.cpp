#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    //std::swap
#include <exception>
#include <cstring>
#include <iterator>
#include <list>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::list;

static const int signature = 0xDEADBEEF;
typedef unsigned char Byte;

void* operator new(std::size_t size) throw(std::bad_alloc)
{
    using namespace std;
    size_t realSize = size + 2 * sizeof(int);
    void *pMem = malloc(realSize);
    if(!pMem) throw bad_alloc();

    *(static_cast<int *>(pMem)) = signature;
    *(reinterpret_cast<int *>(static_cast<Byte *>(pMem) + realSize - sizeof(int))) 
        = signature;

    return static_cast<Byte *>(pMem) + sizeof(int);
}

int main(int argc, char *argv[])
{
    return 0;
}
