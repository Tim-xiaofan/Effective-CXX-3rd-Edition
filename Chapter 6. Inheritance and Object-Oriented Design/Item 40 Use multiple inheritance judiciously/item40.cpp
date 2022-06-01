#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h> //c lib
#include <functional>
#include <list>
#include <cstring>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

class BorrowableItem 
{ // something a library lets you borrow
	public:
		void checkOut(){cout << "BorrowableItem::checkOut" << endl;}
};

class ElectronicGadget
{
	private:
		bool checkOut(){cout << "ElectronicGadget::checkOut" << endl; return false;}
};

class MP3Player: public BorrowableItem, public ElectronicGadget
{};

//deadly MI diamond
class File 
{
	public:
		std::size_t size(void) const {return 0;}
		~File(void){cout << "File destructor" << endl;}
		File(void){cout << "File constructor" << endl;}
	private:
		int _fd;;
};
class InputFile:public File {};
class OutputFile:public File {};
class IOFile:public InputFile, public OutputFile{};


class InputFile1:virtual public File {};
class OutputFile1:virtual public File {};
class IOFile1:public InputFile1, public OutputFile1{};

class IPerson
{
	public:
		virtual ~IPerson(){}
		virtual std::string name() const = 0;
		virtual std::string birthday() const = 0;
};

typedef int DatabaseID;

// function to get a database ID from the user
DatabaseID askUserForDatabaseID()
{
	static DatabaseID id = 0;
	return id++;
}

class PersonInfo
{
	public:
		explicit PersonInfo(DatabaseID pid){}
		virtual ~PersonInfo(){}
		virtual const char * theName() const 
		{
			static char value[128];
			static int i = 0;
			const char * names[3] = {"Tom", "Jerry", "Spike"};
			// write opening delimiter
			std::strcpy(value, valueDelimOpen());
			std::strcat(value, names[i]);
			i = (i + 1) % 3;
			// write closing delimiter
			std::strcat(value, valueDelimClose());
			return value;
		}
		virtual const char * theBithday() const {return "1949-10-1";}
	private:
		virtual const char * valueDelimOpen() const {return "[";}
		virtual const char * valueDelimClose() const {return "]";}
};

class CPerson: public IPerson, private PersonInfo
{
	public:
		virtual ~CPerson(){}
		explicit CPerson( DatabaseID pid): PersonInfo(pid) {}
		virtual std::string name() const {return PersonInfo::theName();}
		virtual std::string birthday() const {return PersonInfo::theBithday();}
	private:
		const char * valueDelimOpen() const{return "";}
		const char * valueDelimClose() const{return "";}
};

// factory function to create a Person object from a unique database ID; 
// see Item 18 for why the return type isn't a raw pointer
std::unique_ptr<IPerson> makePerson(DatabaseID personIdentifier)
{
	return std::unique_ptr<IPerson>(new CPerson(personIdentifier));
}

int main(int argc, char *argv[])
{
	MP3Player mp;
	//mp.checkOut(); //ambiguous
	mp.BorrowableItem::checkOut();
	//mp.ElectronicGadget::checkOut(); // error, call private member

	cout << "sizeof(File):" << sizeof(File)<<endl;
	cout << "sizeof(InputFile):" << sizeof(InputFile) << endl;
	cout << "sizeof(InputFile1):" << sizeof(InputFile1)<< endl;
	cout << "sizeof(OutputFile)" << sizeof(OutputFile) << endl;
	cout << "sizeof(OutputFile1)" << sizeof(OutputFile1) << endl;
	
	{
		cout << "*****sizeof(IOFile):" << sizeof(IOFile) << endl;
		IOFile iof;
		//iof.size(); //ambiguous
	}

	{
		cout << "\n*****sizeof(IOFile1):" << sizeof(IOFile1) << endl;
		IOFile1 iof1;
		iof1.size();
	}


	DatabaseID id(askUserForDatabaseID());
	std::unique_ptr<IPerson> pp(makePerson(id));
	cout << pp->name() << endl;
	cout << pp->birthday() << endl;
	return 0;
}
