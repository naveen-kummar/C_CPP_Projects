#include <iostream>

//////////////////just for demonstrating R-Value usage////////////////////////

class Integer_1 {
	int* m_pInt;
public:
	Integer_1() {
		std::cout << ">>Normal default ctor Integer_1()" << std::endl;
		m_pInt = new int(0);
	}

	Integer_1(int value) {
		std::cout << ">>Normal Paramaterizied ctor Integer_1(int) for " << value << std::endl;
		m_pInt = new int(value);
	}

	Integer_1(const Integer_1& obj) {
		std::cout << ">>Copy Ctor Integer_1(const Integer_1&)" << std::endl;
		m_pInt = new int(*obj.m_pInt);
	}

	Integer_1(Integer_1&& obj) {
		std::cout << ">>Move ctor Integer_1(int&&)" << std::endl;
		m_pInt = obj.m_pInt;
		obj.m_pInt = nullptr;
	}

	int GetValue() const {
		return *m_pInt;
	}

	void SetValue(int value) {
		*m_pInt = value;
	}

	friend std::ostream& operator<<(std::ostream& out, const Integer_1& obj)
	{
		out << *obj.m_pInt;
		return out;
	}

	~Integer_1() {
		std::cout << ">>Destructor ~Integer_1()" << std::endl;
		delete m_pInt;
	}

};



///////////////////////////////////////////////////////////////////////////////

//How to pass variable number of arguments to a function?

//Step-1: Using initilizers_list but you can pass only arguments of same types.

//Works only for homogenous data types
template<typename T>
void Print(std::initializer_list<T> args) {
	for (const auto &x : args) {
		std::cout << x << " ";
	}
}

//Step-2 We can use variadic template which can accept variable number of arguments 
//of different types
void PrintV()
{
	std::cout << std::endl;
}

template<typename T, typename... Params>
//void PrintV(T a, Params... args) //- Step-3 Copy ctor will be called
void PrintV(T &&a, Params&&... args) //Ste 4- Copying is skipped and the move too (intreseting)
{
	//std::cout << sizeof...(args) << std::endl;
	//std::cout << sizeof...(Params) << std::endl;
	std::cout << a;
	if (sizeof...(args) != 0)
	{
		std::cout << ", ";
	}
	//PrintV(args...);//- Step-3 Copy ctor will be called
	PrintV(std::forward<Params>(args)...);//Step-4 without std::forward no copy or move happend

}




int main()
{
	//Print({ 1, 2, 3, 4 }); //0k
	//Print({ 1, 2, 3, 4, 5.4f }); //Error - In-Compatible types 
	PrintV(1, 2, "2.5", 3, 4, 5.4f);

	Integer_1 l_val{ 1 };
	PrintV(0, l_val, Integer_1{ 2 }); //(L, L R)
	getchar();
	return 0;
}