// template_umar_lone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename T>
T Max(T X, T Y)
{
    return X > Y ? X : Y;
}

template char Max(char X, char Y); // This will create one more instance of Max function
                                    // in assembly though it is never called inside as it
                                    // is float and int

int main()
{
    //auto num = Max(3.4, 8.4f); //Both Parameters should be same type
    //auto num = Max(static_cast<float>(3), 8.4f);//Use explicit casting if argument is of different type
    auto num = Max<float>(3, 8.4f); //Skip argument deduction by explicitly specifying the type to avoid the error
    std::cout << num << std::endl;

    auto num2 = Max(38, 12);
    std::cout << num2 << std::endl;

    int (*pfn)(int, int) = Max;

    getchar();

    return 0;
}
