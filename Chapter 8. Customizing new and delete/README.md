# Item 49: Understand the behavior of the new-handler
## Things to Remember
* set_new_handler allows you to specify a function to be called when memory allocation requests cannot be satisfied
* Nothrow new is of limited utility, because it applies only to memory allocation; subsequent constructor calls may still throw exceptions

# Item 50: Understand when it makes sense to replace new and delete
## Things to Remember
* There are many valid reasons for writing custom versions of new and delete, including improving performance, debugging heap usage errors, and collecting heap usage information

# Item 51 Adhere to convention when writing new and delete
## Things to Remember
* operator new should contain an infinite loop trying to allocate memory, should call the new- handler if it can't satisfy a memory request, and should handle requests for zero bytes. Class-specific versions should handle requests for larger blocks than expected.
* operator delete should do nothing if passed a pointer that is null. Class-specific versions should handle blocks that are larger than expected.