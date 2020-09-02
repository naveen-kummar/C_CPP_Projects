#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int dp[21][21] = { 0 };

struct Point
{
	int X;
	int Y;

	Point(int x, int y) : X{ x }, Y{ y }
	{

	}

	Point() {};

	Point operator+(const Point& p)
	{
		Point op(this->X + p.X, this->Y + p.Y);
		return op;
	}
};

int GetTotalSteps(int x, int y, int tx, int ty)
{
	//std::cout << "GetTotalSteps vals x: " << x << ", y:" << y << ", tx:" << tx << ", ty:" << ty << endl;
	if (x == tx &&
		y == ty)
	{
		//std::cout << "Reacheed destination " << std::endl;
		return dp[0][0];
	}
	else
	{
		if (dp[abs(x - tx)][abs(y - ty)] != 0)
		{
			//std::cout << "Returning val : " << dp[abs(x - tx)][abs(y - ty)] << std::endl;
			return dp[abs(x - tx)][abs(y - ty)];
		}
		else
		{
			//Based on the relative position current and destination. Knight can take two possible 
			//navigation as below
			int x1, y1, x2, y2;
			if (x <= tx) {
				if (y <= ty) {
					x1 = x + 2;
					y1 = y + 1;
					x2 = x + 1;
					y2 = y + 2;
				}
				else {
					x1 = x + 2;
					y1 = y - 1;
					x2 = x + 1;
					y2 = y - 2;
				}
			}
			else {
				if (y <= ty) {
					x1 = x - 2;
					y1 = y + 1;
					x2 = x - 1;
					y2 = y + 2;
				}
				else {
					x1 = x - 2;
					y1 = y - 1;
					x2 = x - 1;
					y2 = y - 2;
				}
			}

			dp[abs(x - tx)][abs(y - ty)] = min(GetTotalSteps(x1, y1, tx, ty),
				GetTotalSteps(x2, y2, tx, ty)) + 1;

			//std::cout << "Setting value at " << abs(x - tx) << ", " << abs(y - ty) << " as " << dp[abs(x - tx)][abs(y - ty)] << std::endl;

			dp[abs(y - ty)][abs(x - tx)] = dp[abs(x - tx)][abs(y - ty)];

			return dp[abs(x - tx)][abs(y - ty)];
		}
	}
}



int main4() {
	//code

	int test_case;

	//std::cout << "Input test cases : " << std::endl;

	std::cin >> test_case;

	int v_sizes[100];
	Point curr_pos[100];
	Point dst_pos[100];

	for (int i = 0; i < test_case; i++)
	{
		std::cin >> v_sizes[i];
		std::cin >> curr_pos[i].X;
		std::cin >> curr_pos[i].Y;
		std::cin >> dst_pos[i].X;
		std::cin >> dst_pos[i].Y;
	}

	for (int test = 0; test < test_case; test++)
	{

		for (int m = 0; m < 21; m++)
			for (int n = 0; n < 21; n++)
				dp[m][n] = 0;

		int Steps = 0;
		//When source and destination position are diagonally adjacent at the corner of chess board
		//then we have edge case where number of stesp always be 4.
		if ((abs(curr_pos[test].X - dst_pos[test].X) == 1) &&
			(abs(curr_pos[test].Y - dst_pos[test].Y) == 1) &&
			(((max(curr_pos[test].X, dst_pos[test].X) == v_sizes[test]) ||
				(min(curr_pos[test].X, dst_pos[test].X) == 1)) &&
				(((max(curr_pos[test].Y, dst_pos[test].Y) == v_sizes[test])) ||
					((min(curr_pos[test].Y, dst_pos[test].Y) == 1)))))
		{
			Steps = 4;
		}
		else
		{
			//std::cout << "Into else part: " << std::endl;
			//Lets create matrix whose index represent abs difference between X and Y
			//And value indicates number of steps to reach them in 5x5 board

			dp[1][0] = 3;
			dp[0][1] = 3;
			dp[1][1] = 2;
			dp[2][0] = 2;
			dp[0][2] = 2;
			dp[2][1] = 1;
			dp[1][2] = 1;

			Steps = GetTotalSteps(curr_pos[test].X, curr_pos[test].Y, dst_pos[test].X, dst_pos[test].Y);
		}

		cout << Steps << endl;
	}

	return 0;

}