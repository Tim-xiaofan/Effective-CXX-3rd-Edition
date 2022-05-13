#include "Person.h"

std::unique_ptr<Person> Person::
create(const std::string & name,
			const Date & birthday,
			const Address & addr)
{
	return std::unique_ptr<Person>(new RealPerson(name, birthday, addr));
}

std::string RealPerson::name()const
{
	return std::string("Tom");
}

std::string RealPerson::birthday()const
{
	return std::string("1940");
}

std::string RealPerson::address()const
{
	return std::string("Tom and Jerry");
}
