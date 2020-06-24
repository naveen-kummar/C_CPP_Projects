#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

bool Visited[9][9] = { false };

int GetRegionCount(vector<vector<int>>& grid, int n, int m, int curr_n, int curr_m)
{

    if ((curr_n >= 0) && (curr_n < n)
        && (curr_m >= 0) && (curr_m < m) && (grid[curr_n][curr_m] == 1) && (Visited[curr_n][curr_m] == false))
    {
        Visited[curr_n][curr_m] = true;

        return GetRegionCount(grid, n, m, curr_n - 1, curr_m) +
            GetRegionCount(grid, n, m, curr_n - 1, curr_m + 1) +
            GetRegionCount(grid, n, m, curr_n, curr_m + 1) +
            GetRegionCount(grid, n, m, curr_n + 1, curr_m + 1) +
            GetRegionCount(grid, n, m, curr_n + 1, curr_m) +
            GetRegionCount(grid, n, m, curr_n + 1, curr_m - 1) +
            GetRegionCount(grid, n, m, curr_n, curr_m - 1) +
            GetRegionCount(grid, n, m, curr_n - 1, curr_m - 1) + 1;

    }
    else
    {
        return 0;
    }

}

// Complete the maxRegion function below.
int maxRegion(vector<vector<int>> grid) {

    int n = grid.size();

    if (n <= 0)
        return 0;

    int m = grid[0].size();

    for (int iv = 0; iv < 10; iv++)
    {
        for (int jv = 0; jv < 10; jv++)
        {
            Visited[iv][jv] = false;
        }
    }



    int max_region = 0;
    int current_count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ((Visited[i][j] == false) && (grid[i][j] == 1))
            {
                current_count += GetRegionCount(grid, n, m, i, j);
                if (current_count > max_region)
                {
                    max_region = current_count;
                }
                current_count = 0;
            }
        }
    }



    return max_region;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int res = maxRegion(grid);

    cout << res << "\n";

   // fout.close();

    return 0;
}
