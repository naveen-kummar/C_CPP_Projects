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

	//step-5 - Crazy solutioon
/*	Employee(const std::string& name, Integer&& id) :
		m_Name{ name },
		m_Id{ std::move(id) } {
		std::cout << "Employee(const std::string &name, const Integer &&id)" << std::endl;
	}*/

	//Step-5a you can use std::formward to call move ctor as below
/*	Employee(const std::string& name, Integer&& id) :
		m_Name{ name },
		m_Id{ std::forward<Integer&&>(id) } {
		std::cout << "Employee(const std::string &name, const Integer &&id)" << std::endl;
	}
*/

	//Step-5b you can use std::formward to call copy ctor as below
	/*	Employee(const std::string& name, Integer&& id) :
			m_Name{ name },
			m_Id{ std::forward<Integer&>(id) } {
			std::cout << "Employee(const std::string &name, const Integer &&id)" << std::endl;
		}
	*/

	//Step-6 Lets templatize the ctor to avoid creation of multiple ctors as above
/*	template<typename T1, typename T2>
	Employee(T1&& name, T2&& id) :
		m_Name{ name },
		m_Id{ id } {
		std::cout << "Template ctor Employee(std::string &&name,  Integer &&id)" << std::endl;

	}
*/
	//Step-7 So fix problem in step-6 lets use std::forward
	template<typename T1, typename T2>
	Employee(T1&& name, T2&& id) :
		m_Name{ std::forward<T1>(name) },
		m_Id{ std::forward<T2>(id) } {
		std::cout << "Template ctor Employee(std::string &&name,  Integer &&id)" << std::endl;

	}


};

int main()
{
	Employee emp1{ "Naveen", 100 }; //Calls copy ctor of Interger by but with step-3 move ctor will be called

	//Step-4
	const std::string str = "Naveen";
	Employee emp2{ str, 100 }; //But this will call default ctor of Employee and copy ctor of Integer
	//> This happened because first parameter is L-Value and second R-Value, so it called 
	//first ctor where second R-Value is copped to id and make it as L-Value.

	//Step-5
	//> So to handle this we need to put 4 ctors in Employee class
	//(R, R), (R,L), (L,R) and (L,L). Which is crazy 

	//Step-6
	Employee emp3{ str, Integer(100) };
	//Above code still calls copy ctor of Integer though the templatizied ctor is called

	//Though in ctor signature of templatized ctor we are passing 'Integer(100)' as 
	//R-Value reference but it is copied to m_Id via ‘id’ directly without std::move
	//(i.e. L-Value) so Copy ctor is called.

	getchar();
	return 0;
}