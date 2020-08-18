#include <iostream>
#include <memory>

class Integer {
	int* m_pInt;
public:
	Integer() {
		std::cout << ">>Normal default ctor Integer()" << std::endl;
		m_pInt = new int(0);
	}

	Integer(int value) {
		std::cout << ">>Normal Paramaterizied ctor Integer(int)" << std::endl;
		m_pInt = new int(value);
	}

	Integer(const Integer& obj) {
		std::cout << ">>Copy Ctor Integer(const Integer&)" << std::endl;
		m_pInt = new int(*obj.m_pInt);
	}

	Integer(Integer&& obj) {
		std::cout << ">>Move ctor Integer(int&&)" << std::endl;
		m_pInt = obj.m_pInt;
		obj.m_pInt = nullptr;
	}

	int GetValue() const {
		return *m_pInt;
	}

	void SetValue(int value) {
		*m_pInt = value;
	}

	~Integer() {
		std::cout << ">>Destructor ~Integer()" << std::endl;
		delete m_pInt;
	}

};

class Employee {
	std::string m_Name;
	Integer m_Id;
public:
	Employee(const std::string &name, const Integer &id) :
		m_Name{ name },
		m_Id{ id } {
		std::cout << "Employee(const std::string &name, const Integer &id)" << std::endl; 
	}

//Step-2 - Added below ctor to call move ctor of Integer but it will not
	//> The reason is that when you use Temp name it becomes L-Value and copy ctor is called.
	//> so to make it as R - Vale use std::move() as below
/*
	Employee(const std::string&& name, const Integer&& id) :
		m_Name{ name },
		m_Id{ id } {
		std::cout << "Employee(const std::string &&name, const Integer &&id)" << std::endl;
	}
*/

	//Step-3 Use std::move to call move ctor of Integer and ensure to 
	//remove const of input parameter
	Employee(std::string&& name, Integer&& id) :
		m_Name{ name },
		m_Id{ std::move(id) } {
		std::cout << "Employee(const std::string &&name, const Integer &&id)" << std::endl;
	}

};

int main()
{
	Employee emp1{ "Naveen", 100 }; //Calls copy ctor of Interger

	getchar();
	return 0;
}