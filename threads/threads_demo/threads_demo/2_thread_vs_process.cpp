// operator delete[] example
#include <iostream>     // std::cout

struct MyClass {
    MyClass() { std::cout << "MyClass constructed\n"; }
    ~MyClass() { std::cout << "MyClass destroyed\n"; }
};

int main2() {
    int* pt;

    pt = new int[3];
    delete pt;

    return 0;
}