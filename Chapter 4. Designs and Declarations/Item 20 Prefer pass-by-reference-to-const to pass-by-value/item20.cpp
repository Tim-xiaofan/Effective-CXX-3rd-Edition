#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using std::cout;
using std::endl;
using std::string;

class Person
{
    public:
        Person(){cout << "Person constructor\n";}
        virtual ~Person(){cout << "Person destructor\n";}
};

class Student:public Person
{
    public:
        Student(){ cout << "Student constructor\n";}
        ~Student(){cout << "Student destructor\n";}
};

class Window 
{ 
    public: 
        std::string name() const { return "East Window";} // return name of window
        virtual void display() const { cout << "Window\n";}  // draw window and contents 
};

class WindowWithScrollBars: public Window 
{
    public: 
        virtual void display() const {cout << "WindowWithScrollBars\n";}
};

bool validateStudent(Student s){return true;}
bool validatePerson(Person p){return true;}

void printNameAndDisplay(Window w) // incorrect! parameter 
{ // may be sliced! 
    std::cout << w.name() << ":"; 
    w.display(); 
}

void printNameAndDisplay1(const Window &  w) // incorrect! parameter 
{ // may be sliced! 
    std::cout << w.name() << ":"; 
    w.display(); 
}

int main(int argc, char *argv[])
{
    /** cost of constructor and destructor*/
    Student plato; // Plato studied under Socrates
    validateStudent(plato); // call the function

    /** slicing problem*/
    //Window w;
    //printNameAndDisplay(w);
    WindowWithScrollBars wwsb;
    printNameAndDisplay(wwsb);
    printNameAndDisplay1(wwsb);
    return 0;
}
