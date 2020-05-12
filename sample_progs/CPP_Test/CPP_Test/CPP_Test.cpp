// CPP_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

typedef struct emp_{

    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
}emp_t;

#define GET_OFFSET(struct_name, field_name) \
            (unsigned int)&((struct_name*)0)->field_name

int main()
{
    emp_t* test_struct = new emp_{};
    unsigned int t = GET_OFFSET(test_struct, salary);
    //std::cout << "The offset value =  %u" << GET_OFFSET(test_struct, salary);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
