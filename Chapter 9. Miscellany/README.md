# Item 53: Pay attention to compiler warnings.
## Things to Remember
* Take compiler warnings seriously, and strive to compile warning-free at the maximum warning level supported by your compilers
* Don't become dependent on compiler warnings, because different compilers warn about different things. Porting to a new compiler may eliminate warning messages you've come to rely on.

# Item 54: Familiarize yourself with the standard library, including TR1
## Things to Remember
* The primary standard C++ library functionality consists of the STL, iostreams, and locales. The C99 standard library is also included
* TR1 adds support for smart pointers (e.g., tr1::shared_ptr), generalized function pointers (tr1::function), hash-based containers, regular expressions, and 10 other components
* TR1 itself is only a specification. To take advantage of TR1, you need an implementation. One source for implementations of TR1 components is Boost.

# Item 55: Familiarize yourself with Boost
## Things to Remember 
* Boost is a community and web site for the development of free, open source peer-reviewed C++ libraries. Boost plays an influential role in C++ standardization. 
* Boost offers implementations of many TR1 components, but it also offers many other libraries, too.