// Template_SFINE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
using namespace std;
#pragma optimize("", off)

//SIFNE - Below 'enable_if_t<is_floating_point<T>::value>' act as a class type 
//of 'void' if T is floating type otherwise no thirsd parameter present.
template<typename T>
bool Equals(T lhs, T rhs, enable_if_t<is_floating_point<T>::value>* = nullptr) //floating
{
    return true;
}

template<typename T>
bool Equals(T lhs, T rhs, enable_if_t<!is_floating_point<T>::value>* = nullptr) //non-floating
{
    return lhs == rhs;
}


int main()
{
    Equals(1, 1);
    Equals(1.f, 1.f);
    Equals(1., 1.);
    Equals(1u, 1u);
    bool b = Equals(0.42f - 0.4f, 0.02f);
    return 0;
}

