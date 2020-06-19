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

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {

    map<int, std::set<int>> circles;

    int number_of_roads = cities.size();

    for (auto road : cities)
    {
        circles[road[0]].emplace(road[0]);
        circles[road[0]].emplace(road[1]);
        int current_src = road[0];
        int current_dst = road[1];


        auto dst_iter = std::find_if(std::begin(cities), std::end(cities), [&current_dst](auto v)
            {return (current_dst == v[0]); });
#if 1
        //Find is above src is part of circle
        while ((current_src != current_dst) &&
            (dst_iter != std::end(cities)))
        {
            current_src = (*dst_iter)[0];
            current_dst = (*dst_iter)[1];

            if (std::find(std::begin(circles[road[0]]), std::end(circles[road[0]]), current_dst) != std::end(circles[road[0]]))
            {
                break;
            }
            else
            {
                circles[road[0]].insert(current_dst);
            }

        }
#endif
        //std::sort(std::begin(dst_list), std::end(dst_list));

        //if (std::find_if(std::begin(circles), std::end(circles), [&dst_list](vector<int> v)
        //    {return v == dst_list; }) == std::end(circles))
        //{
        //    circles.push_back(dst_list);
        //}

        //dst_list.clear();

    }

    int lib_in_all_cities = n * c_lib;


    int n_lib = 0;
    int n_paths = 0;
    set<int> unique_src_cities;
    set<int> unique_cities;
    int lib_in_select_cities = 0;
#if 1
    for (auto path : circles)
    {
        if (std::find(std::begin(unique_src_cities), std::end(unique_src_cities), path.first) == std::end(unique_src_cities))
        {
            unique_src_cities.insert(path.first);
            ++n_lib;

        }

        if (unique_cities.size() < n)
        {
            for (auto city : path.second)
            {
                if (std::find(std::begin(unique_cities), std::end(unique_cities), city) == std::end(unique_cities))
                {
                    unique_cities.insert(city);
                }

                if (unique_cities.size() == n)
                {
                    break;
                }
            }
        }

        n_paths += path.second.size() - 1;

        lib_in_select_cities = (n_lib * c_lib) + (n_paths * c_road) + ((n - unique_cities.size()) * c_lib);

        if (lib_in_select_cities > lib_in_all_cities)
        {
            break;
        }
    }
#endif

    std::cout << "Number of libs:  " << n_lib << std::endl;
    std::cout << "Number of n_paths:  " << n_paths << std::endl;
    std::cout << "Number of left out city:  " << ((n - unique_cities.size()) << std::endl;

    return (lib_in_select_cities < lib_in_all_cities) ? lib_in_select_cities : lib_in_all_cities;

}

int main()
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
