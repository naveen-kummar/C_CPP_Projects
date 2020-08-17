// template_umar_lone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename T>
T Max(T X, T Y)
{
    return X > Y ? X : Y;
}

int main()
{
    auto num = Max(3.5f, 8.4f);
    std::cout << num << std::endl;

    auto num2 = Max(38, 12);
    std::cout << num2 << std::endl;

    getchar();

    return 0;
}
