#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Point
{
	int X;
	int Y;

	Point(int x, int y) : X{ x }, Y{y}
	{

	}

	Point() {};

	Point operator+(const Point& p)
	{
		Point op(this->X + p.X, this->Y + p.Y);
		return op;
	}
};

Point  possible_points[] = { {1, 2} , {2, 1} , {-1, 2}, {1, -2}, {-1, -2}, {-2, 1}, {2, -1}, {-2, -1} };

struct Cell
{
	Point pos;
	int dist;
	Cell() {}
	Cell(int X, int Y, int D) : pos{ X, Y }, dist(D) {}
};

bool IsPositionValid(int X, int Y, int N)
{
	if ((X >= 1) && (X <= N) && (Y >= N) && (Y <= N))
		return true;
	else
		return false;
}

int main3() {
	//code

	int test_case;

	std::cout << "Input test cases : " << std::endl;

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


	for (int i = 0; i < test_case; i++)
	{
		std::queue<Cell> q;

		q.push({ curr_pos[i].X, curr_pos[i].Y, 0 });

		bool Visited[21][21];

		for (int i = 0; i < 21; i++)
			for (int j = 0; j < 21; j++)
				Visited[i][j] == false;

		int Steps = 0;

		while (q.empty() == false)
		{
			Cell t = q.front();
			q.pop();

			if ((t.pos.X == dst_pos[i].X) &&
				(t.pos.Y == dst_pos[i].Y))
			{
				Steps = t.dist;
				break;
			}

			for (int pos = 0; pos < 8; pos++)
			{
				Cell new_pos{};
				new_pos.pos = t.pos + possible_points[pos];
				new_pos.dist = t.dist + 1;

				if ((IsPositionValid(new_pos.pos.X, new_pos.pos.Y, v_sizes[i]))
					&& (Visited[new_pos.pos.X][new_pos.pos.Y] == false))
				{
					Visited[new_pos.pos.X][new_pos.pos.Y] = true;
					q.push(new_pos);
				}
			}
		}

		cout << Steps << endl;

	}


	return 0;
}