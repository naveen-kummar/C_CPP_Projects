// Template_SFINE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
#include <type_traits>
using namespace std;
#pragma optimize("", off)

//tag-dispatch
template<typename T>
bool Equals(T lhs, T rhs, true_type) //floating
{
    return true;
}

template<typename T>
bool Equals(T lhs, T rhs, false_type) //non-floating
{
    return lhs == rhs;
}

template<typename T>
bool Equals(T lhs, T rhs)
{
    return Equals(lhs, rhs, conditional_t<is_floating_point<T>::value, true_type, false_type>{});
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

