# Item 41: Understand implicit interfaces and compile-time polymorphism
## Things to Remember
* Both classes and templates support interfaces and polymorphism.
* For classes, interfaces are explicit and centered on function signatures. Polymorphism occurs at runtime through virtual functions
* For template parameters, interfaces are implicit and based on valid expressions. Polymorphism occurs during compilation through template instantiation and function overloading resolution.

# Item 42: Understand the two meanings of typename
## Things to Remember
* When declaring template parameters, class and typename are interchangeable.
* Use typename to identify nested dependent type names, except in base class lists or as a base class identifier in a member initialization list.

# Item 43: Know how to access names in templatized base classes
## Things to Remember
* In derived class templates, refer to names in base class templates via a "this->" prefix, via using declarations, or via an explicit base class qualification.

# Item 44: Factor parameter-independent code out of templates
## Things to Remember
* Templates generate multiple classes and multiple functions, so any template code not dependent on a template parameter causes bloat
* Bloat due to non-type template parameters can often be eliminated(消除；除掉) by replacing template parameters with function parameters or class data members
* Bloat due to type parameters can be reduced by sharing implementations for instantiation types with identical binary representations

# Item 45: Use member function templates to accept all compatible types
## Things to Remember
* Use member function templates to generate functions that accept all compatible types.
* If you declare member templates for generalized copy construction or generalized assignment, you'll still need to declare the normal copy constructor and copy assignment operator, too.

# Item 46: Define non-member functions inside templates when type conversions are desired
## Things to Remember
* When writing a class template that offers functions related to the template that support implicit type conversions on all parameters, define those functions as friends inside the class template