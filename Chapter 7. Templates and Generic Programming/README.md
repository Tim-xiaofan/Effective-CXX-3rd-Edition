# Item 41: Understand implicit interfaces and compile-time polymorphism
## Things to Remember
* Both classes and templates support interfaces and polymorphism.
* For classes, interfaces are explicit and centered on function signatures. Polymorphism occurs at runtime through virtual functions
* For template parameters, interfaces are implicit and based on valid expressions. Polymorphism occurs during compilation through template instantiation and function overloading resolution.

# Item 42: Understand the two meanings of typename
## Things to Remember
* When declaring template parameters, class and typename are interchangeable.
* Use typename to identify nested dependent type names, except in base class lists or as a base class identifier in a member initialization list.