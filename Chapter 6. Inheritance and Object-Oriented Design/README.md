# Item 33: Avoid hiding inherited names
* Names in derived classes hide names in base classes. Under public inheritance, this is never desirable. 
* To make hidden names visible again, employ using declarations or forwarding functions.

# Item 35: Consider alternatives to virtual functions
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

# Item 36: Never redefine an inherited non-virtual function
## 原因
* Determining factor will have nothing to do with the object itself, but with the declared type of the pointer that points to it.
## Things to Remember
* Never redefine an inherited non-virtual function

# Item 37: Never redefine a function's inherited default parameter value
## 原因
* 默认参数是静态绑定，虚函数是动态绑定
## Things to Remember
* Never redefine an inherited default parameter value, because default parameter values are statically bound, while virtual functions — the only functions you should be overriding — are dynamically bound.

# Item 38: Model "has-a" or "is-implemented-in-terms-of" through composition
## Things to Remember
* Composition has meanings completely different from that of public inheritance.
* In the application domain, composition means has-a. In the implementation domain, it means is- implemented-in-terms-of.

# Item 39: Use private inheritance judiciously
## Things to Remember
* Private inheritance means is-implemented-in-terms of. It's usually inferior(低劣的、下级的) to composition, but it makes sense when a derived class needs access to protected base class members or needs to redefine inherited virtual functions
* Unlike composition, private inheritance can enable the empty base optimization. This can be important for library developers who strive to minimize object sizes.

# Item 40： Use multiple inheritance judiciously
## Things to Remember
* Multiple inheritance is more complex than single inheritance. It can lead to new ambiguity issues and to the need for virtual inheritance.
* Virtual inheritance imposes costs in size, speed, and complexity of initialization and assignment. It's most practical when virtual base classes have no data.
* Multiple inheritance does have legitimate(合理的、合法的) uses. One scenario involves combining public inheritance from an Interface class with private inheritance from a class that helps with implementation.