// threads_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

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

void FindOdd(std::promise<ull>&& OddSumPromise  ,ull start, ull end)
{
    for (ull i = start; i <= end; i++)
    {
        if ((i & 1) == 1)
        {
            odd_sum++;
        }
    }

    OddSumPromise.set_value(odd_sum);
}

int main()
{
    ull start{ 0 };
    ull end{ 1900000000 };

    std::promise<ull> OddSum;
    std::future<ull> OddFuture = OddSum.get_future();



    auto StartTime = high_resolution_clock::now();

    std::thread t1(FindOdd, std::move(OddSum), start, end);

    cout << "OddSum: " << OddFuture.get() << endl;

    t1.join();
 
    auto StopTime = high_resolution_clock::now();



    auto duration = duration_cast<microseconds>(StopTime - StartTime);

    cout << "Completed in : " << duration.count()/1000000 << endl;

    getchar();
    return 0;
}

