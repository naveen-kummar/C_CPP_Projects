
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int main()
{
	string my_string = "11010220004050";
	map<char, int> char_count;

	for (auto s = begin(my_string); s != end(my_string); s++)
	{
		cout << "The Value = " << *s << endl;

		char_count[*s] += 1;

		cout << "The count of " << *s  << " is = " << char_count[*s]  << endl;


	}

	getchar();
}