#include <iostream>
#include <string>

class DeclAutoDemo
{
public:
	DeclAutoDemo() : member_string_{"This is member string"}
	{
			
	}

	std::string LookUp1()
	{
		return "This is local string";
	}

	std::string& LookUp2()
	{
		return member_string_;
	}

	//in C++ 11
	//std::string  look_up_a_string_1() { return LookUp1(); }
	//std::string& look_up_a_string_2() { return LookUp2(); }

	//In C++ 14
	//decltype(auto) look_up_a_string_1() { return LookUp1(); }
	//decltype(auto) look_up_a_string_2() { return LookUp2(); }

	auto look_up_a_string_1() { return LookUp1(); }
	decltype(auto) look_up_a_string_2() { return LookUp2(); }

private:
	std::string member_string_;
};

int main()
{
	DeclAutoDemo obj;
	obj.look_up_a_string_2() += " + Appended additionla data";

	std::cout << obj.look_up_a_string_2() << std::endl;

	getchar();
	return 0;
}