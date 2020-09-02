/*Find total number of possible paths to climb staircase. Where the use
can either take 1 or 2 or 3 steps at a time*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

unsigned long long CountPathsR(int steps)
{
	if (steps < 0)
	{
		return 0;
	}
	else if (steps == 0)
	{
		return 1;
	}

	return CountPathsR(steps - 1) + CountPathsR(steps - 2) + CountPathsR(steps - 3);
}


unsigned long long CountsPathMemo(int steps, vector<unsigned long long> &v_memo)
{
	if (steps < 0)
	{
		return 0;
	}
	else if (steps == 0)
	{
		return 1;
	}

	if(v_memo[steps] == 0)
		v_memo[steps] = CountsPathMemo(steps - 1, v_memo) + CountsPathMemo(steps - 2, v_memo) + CountsPathMemo(steps - 3, v_memo);

	return v_memo[steps];
}

unsigned long long CountsPathMemo(int steps)
{
	vector<unsigned long long> memo(steps + 1);
	return CountsPathMemo(steps, memo);
}

unsigned long long CountPathDPIterative(int steps)
{
	if (steps < 0)
	{
		return 0;
	}
	else if (steps == 0)
	{
		return 1;
	}

	vector<unsigned long long> dp_approach(steps + 1);

	dp_approach[0] = 1;
	dp_approach[1] = 1;
	dp_approach[2] = 2;

	for (int i = 3; i <= steps; i++)
	{
		dp_approach[i] = dp_approach[i - 1] + dp_approach[i - 2] + dp_approach[i - 3];
	}

	return dp_approach[steps];

}

unsigned long long CountPathIterativeApproach(int steps)
{
	if (steps < 0)
	{
		return 0;
	}
	else if (steps == 0)
	{
		return 1;
	}

	vector<unsigned long long> iterative_path{1, 1, 2};

	for (int i = 3; i <= steps; i++)
	{
		unsigned long long count = iterative_path[0] + iterative_path[1] + iterative_path[2];
		iterative_path[0] = iterative_path[1];
		iterative_path[1] = iterative_path[2];
		iterative_path[2] = count;
	}

	return iterative_path[2];

}

int main()
{
	///////////////////////////////Recursion Approach/////////////////////////////
	int recursive{ 10};

	auto StartTime = high_resolution_clock::now();
	//Works till the count of 30 only for 35 and 40 it hangs in my machine
	cout << "The NUmber of Paths possible to jump (Recursive) " << recursive << " is = " << CountPathsR(recursive) <<endl;
	auto StopTime = high_resolution_clock::now();

	auto duration = duration_cast<nanoseconds>(StopTime - StartTime);

	cout << "Recursion Completed in : " << duration.count()  << " nano seconds" << endl;

	//////////////////////////////////////////MEMO Approach/////////////////////////////////
	StartTime = high_resolution_clock::now();

	int memo_path{999};
	cout << "The NUmber of Paths possible to jump (Memo) " << memo_path << " is = " << CountsPathMemo(memo_path) << endl;

	StopTime = high_resolution_clock::now();

	duration = duration_cast<nanoseconds>(StopTime - StartTime);

	cout << "Memo Completed in : " << duration.count()  <<  " nano seconds" << endl;

	///////////////////////Dynamic Propramming approach//////////////////////////////

	StartTime = high_resolution_clock::now();

	int dp_approach_path{ 999 };
	cout << "The NUmber of Paths possible to jump (Dynamic Programming) " << dp_approach_path << " is = " << CountPathDPIterative(dp_approach_path) << endl;

	StopTime = high_resolution_clock::now();

	duration = duration_cast<nanoseconds>(StopTime - StartTime);

	cout << "Dynamic Programming Completed in : " << duration.count() << " nano seconds" << endl;


	/////////////////////// Iterative Approach //////////////////////////////

	StartTime = high_resolution_clock::now();

	int iterative_approach_path{ 999 };
	cout << "The NUmber of Paths possible to jump (Iterative) " << iterative_approach_path << " is = " << CountPathIterativeApproach(iterative_approach_path) << endl;

	StopTime = high_resolution_clock::now();

	duration = duration_cast<nanoseconds>(StopTime - StartTime);

	cout << "Iterative Completed in : " << duration.count() << " nano seconds" << endl;



	getchar();
}