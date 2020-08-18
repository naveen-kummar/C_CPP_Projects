#include <iostream>


template<int size>
void Print()
{
	//++size;//Error it is constant always
	std::cout << size << std::endl;
}

template<typename T>
T Sum(T* parr, int size)
{
	T sum{};
	for (int i = 0; i < size; i++)
	{
		sum += parr[size];
	}

	return sum;
}

template<typename T, int size>
T Sum2(T (&parr)[size])
{
	T sum{};
	for (int i = 0; i < size; i++)
	{
		sum += parr[size];
	}

	return sum;
}

int main()
{
	//Print<3>(); //OK

	unsigned long long int i = 3;
	//Print<i>(); //Error
	Print<sizeof(i)>(); //Ok

	/*So argument to non-type template should 
	be contant expressions and should be compute at compile time.*/

	//Out-of scope tips..
	int arr[]{ 3, 9, 7, 1 };
	//int(&ref)[] = arr; //Error
	//int(&ref)[100] = arr; //Error
	int(&ref)[4] = arr; //Ok

	int sum1 = Sum(arr, 4); //Explicity are passing size

	std::cout << sum1 << std::endl;

	int sum1 = Sum2(arr); //See the beauty once size is made as non-type argument.
						  //Then no need to pass the size explicitly.
						  //This same concept in STL’s std::begin(v) and std::end(v)


	getchar();
	return 0;
}