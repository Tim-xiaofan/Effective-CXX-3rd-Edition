#include <iostream>
#include "User.h"
#include "Person.h"
#include <memory>

std::string name; 
Date dateOfBirth; 
Address address;

int main(int argc, char *argv[])
{
	User usr("Name");
	usr.setSalary(3200);
	std::unique_ptr<Person> pp(Person::create(name, dateOfBirth, address));
	std::cout << pp->name() << " was born on "
		<<pp->birthday()
		<< " and now lives at "
		<< pp->address()
		<< std::endl;
	return 0;
}
