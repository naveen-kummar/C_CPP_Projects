// threads_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

using ull = unsigned long long;

ull odd_sum{0};
ull even_sum{0};

void FindEven(ull start, ull end)
{
    for (ull i = start; i <= end; i++)
    {
        if ((i & 1) == 0)
        {
            even_sum++;
        }
    }
}

void FindOdd(ull start, ull end)
{
    for (ull i = start; i <= end; i++)
    {
        if ((i & 1) == 1)
        {
            odd_sum++;
        }
    }
}

int main()
{
    ull start{ 0 };
    ull end{ 1900000000 };

    auto StartTime = high_resolution_clock::now();

    std::thread t1(FindOdd, start, end);
    std::thread t2(FindEven, start, end);

    t1.join();
    t2.join();
 
    auto StopTime = high_resolution_clock::now();



    auto duration = duration_cast<microseconds>(StopTime - StartTime);

    cout << "OddSum: " << odd_sum << endl;
    cout << "EvenSum: " << even_sum << endl;

    cout << duration.count() / 1000000 << endl;

    return 0;
}

