// multi_paradigm_programming_with_modern_c++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string_view>
#include <thread>
#include <mutex>


std::mutex mx;

int main() {

    std::unique_lock<std::mutex> lc{ mx };
    
    lc.lock();
 
    char letters[] = "abc";

    



    return 0;

}

