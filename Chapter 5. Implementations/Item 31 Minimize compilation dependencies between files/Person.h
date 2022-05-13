#pragma once
#include <memory>
#include <string>

typedef int Address;
typedef int Date;

class Person
{
	public:
		virtual ~Person(){}
		virtual std::string name () const = 0;
		virtual std::string birthday() const = 0;
		virtual std::string address() const = 0;
		static std::unique_ptr<Person>
			create(const std::string & name,
						const Date & birthday,
						const Address & addr);
};

class RealPerson:public Person
{
	public:
		RealPerson(const std::string& name, const Date& birthday, 
					const Address& addr) 
			: theName(name), theBirthDate(birthday), theAddress(addr) {}

		virtual ~RealPerson(){}
		std::string name()const;
		std::string birthday()const;
		std::string address()const;

	private:
		std::string theName;
		Date theBirthDate;
		Address theAddress;
};
