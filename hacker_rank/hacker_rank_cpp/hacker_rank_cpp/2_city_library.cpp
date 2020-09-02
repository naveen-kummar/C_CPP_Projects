#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
//#include <bits/stdc++.h>
#include <iterator>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<string> split_string(string);
bool Visited[100000];
vector<int> city_connections[100000];
int nodes = 0;

void FindNodeCount_DFS(int n)
{
    nodes++;
    Visited[n] = true;

    for (int c : city_connections[n])
    {
        if (Visited[c] == false)
        {
            FindNodeCount_DFS(c);
        }
    }
}

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {

    long cost = 0;

    for (auto road : cities)
    {
        city_connections[road[0]].push_back(road[1]);
        city_connections[road[1]].push_back(road[0]);
    }

    for (int city = 1; city <= n; city++)
    {
        if (Visited[city] == false)
        {
            nodes = 0;
            FindNodeCount_DFS(city);

            cost = cost + c_lib;

            if (c_lib > c_road)
            {
                cost = cost + ((nodes - 1) * c_road);
            }
            else
            {
                cost = cost + ((nodes - 1) * c_lib);
            }
        }
    }

    for (int i = 0; i < 100000; i++)
    {
        city_connections[i].clear();
        Visited[i] = false;
    }


    return cost;
}

int main2()
{
   // ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        std::cout << result << "\n";
    }

   // std::cout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
        });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
