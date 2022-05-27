# Item 33: Avoid hiding inherited names
* Names in derived classes hide names in base classes. Under public inheritance, this is never desirable. 
* To make hidden names visible again, employ using declarations or forwarding functions.

# Item 35 Consider alternatives to virtual functions
## Summary
* Use the **non-virtual interface idiom** (NVI idiom), a form of the Template Method design pattern that wraps public non-virtual member functions around less accessible virtual functions.
* Replace virtual functions with **function pointer data members**, a stripped-down（简装） manifestation of the Strategy design pattern
* Replace virtual functions with **std::function data members**, thus allowing use of any callable entity with a signature compatible with what you need. This, too, is a form of the Strategy design pattern.
* Replace **virtual functions in one hierarchy** with virtual functions in another hierarchy. This is the conventional implementation of the Strategy design pattern.\
说明：策略模式（Strategy design pattern），一个类的行为或其算法可以在运行时更改。
## Things to Remember
* Alternatives to virtual functions include the NVI idiom and various forms of the Strategy design pattern. The NVI idiom is itself an example of the Template Method design pattern
* Adisadvantage of moving functionality from a member function to a function outside the class is that the non-member function lacks access to the class's non-public members.
* std::function objects act like generalized function pointers. Such objects support all callable entities compatible with a given target signature