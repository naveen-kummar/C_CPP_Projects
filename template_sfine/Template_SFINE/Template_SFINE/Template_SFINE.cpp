// Template_SFINE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
using namespace std;
#pragma optimize("", off)

template<typename T, typename U>
bool Equals(T lhs, U rhs)
{
    return lhs == rhs;
}

template<>
bool Equals<float>(float lhs, float rhs)
{
    return true;
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

