#include <iostream>

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

};

int main()
{
	Employee emp1{ "Naveen", 100 }; //Calls copy ctor of Interger

	getchar();
	return 0;
}