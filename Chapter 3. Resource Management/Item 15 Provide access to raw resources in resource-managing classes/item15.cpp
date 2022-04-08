#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::string;

class Investment 
{ // root class for a hierarchy 
    public: // of investment types 
        bool isTaxFree() const{return true;}; 
};

Investment* createInvestment() // factory function
{
    return new Investment();
}


class FontHandle {};

FontHandle getFont(){return FontHandle();} //from C API—params omitted
void releaseFont(FontHandle fh) {}; // from the same C API
void changeFontSize(FontHandle f, int newSize) {};// from C API

class Font 
{ // RAII class 
    public: 
        explicit Font(FontHandle fh) // acquire resource; 
            : f(fh) // use pass-by-value, because the 
        {} // C API does 
        ~Font() { releaseFont(f); } // release resource 
        FontHandle get() const { return f; } // explicit conversion function
        operator FontHandle() const { return f; } // implicit conversion function
    private:
        FontHandle f; // the raw font resource 
};

int main(int argc, char *argv[])
{
    /** explicit conversion*/
    std::shared_ptr<Investment> pi1(createInvestment());
    bool taxable1 = !(pi1->isTaxFree()); // access resource  via operator->
    std::shared_ptr<Investment> pi2(createInvestment());
    bool taxable2 = !((*pi2).isTaxFree());
    /** awful:frequent need to convert from Font objects to FontHandles*/
    Font f(getFont());
    int newFontSize = 14;
    changeFontSize(f.get(), newFontSize); // explicitly convert Font to FontHandle
    changeFontSize(f, newFontSize); 

    return 0;
}
