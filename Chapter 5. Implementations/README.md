# Item 27: Minimize casting
Things to Remember
* Avoid casts whenever practical, especially dynamic_casts in performance-sensitive code.If adesign requires casting, try to develop a cast-free alternative.
* When casting is necessary, try to hide it inside a function. Clients can then call the function instead of putting casts in their own code.
* Prefer C++-style casts to old-style casts. They are easier to see,and they are more specific about what they do.

# Item 28： Avoid returning "handles" to object internals
* Avoid returning handles (references, pointers, or iterators) to object internals. It increases encapsulation, helps const member functions act const, and minimizes the creation of dangling handles.

# Item 29: Strive for exception-safe code 
* Exception-safe functions leak no resources and allow no data structures to become corrupted, even when exceptions are thrown. Such functions offer the basic, strong, or nothrow guarantees.
* The strong guarantee can often be implemented via copy-and-swap, but the strong guarantee is not practical for all functions.
* A function can usually offer a guarantee no stronger than the weakest guarantee of the functions it calls(一个函数异常安全等级由其调用的函数中最弱的决定（木桶效应）).

# Item 30: Understand the ins and outs of inlining
* Limit most inlining to small, frequently called functions. This facilitates debugging and binary upgradability, minimizes potential code bloat, and maximizes the chances of greater program speed
* Don't declare function templates inline just because they appear in header files

# Item 31: Minimize compilation dependencies between files
* The general idea behind minimizing compilation clependencies is to depend on declarations instead of
definitions. Two approaches based on this idea are Handle classes and Interface classes. (定义依赖-->声明依赖)
* Library header files should exist in full and deeclaration-only forms. This applies regardless of
whether templates are involved.