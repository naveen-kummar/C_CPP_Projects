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


    long lib_in_all_cities = n * c_lib;

    if (cities.size() == 0)
        return lib_in_all_cities;

    for (auto& path : cities)
    {
        std::sort(std::begin(path), std::end(path));
    }

    std::sort(std::begin(cities), std::end(cities));

    //int unique_cities = 0;
    int unique_paths = cities.size();
    int processed_paths = 0;

    int prev_road = -1;
    map<int, set<int>> circles;
    int n_paths = 0;
    long lib_in_select_cities = 0;
    set<int> unique_cities{};
    set<int> unique_src_cities{};
    int perfect_circle = 0;


    for (auto road : cities)
    {
        if (circles.empty())
        {
            circles[road[0]].insert({ road[1] });
            unique_src_cities.insert({ road[0] });
            ++n_paths;
        }
        else
        {
            bool city_added_earlier = false;
            for (auto& circle : circles)
            {

                if (((std::find(std::begin(circle.second), std::end(circle.second), road[0]) != std::end(circle.second))) &&
                    ((std::find(std::begin(circle.second), std::end(circle.second), road[1]) != std::end(circle.second))))
                {
                    city_added_earlier = true;
                    ++perfect_circle;
                    ++n_paths;
                    break;
                }
                else  if (std::find(std::begin(circle.second), std::end(circle.second), road[0]) != std::end(circle.second))
                {
                    circle.second.insert(road[1]);
                    city_added_earlier = true;
                    ++n_paths;

                    break;
                }

            }



            if (city_added_earlier == false)
            {
                circles[road[0]].insert({ road[1] });
                unique_src_cities.insert({ road[0] });
                ++n_paths;
            }
        }

        if (unique_cities.size() < n)
        {
            unique_cities.insert(road[0]);
            unique_cities.insert(road[1]);

        }

        //perfect_circle = std::count_if(std::begin(circles), std::end(circles), [](auto v)
        //    {return (std::find(std::begin(v.second), std::end(v.second), v.first) != std::end(v.second)); });


        lib_in_select_cities = (unique_src_cities.size() * c_lib) + ((n_paths - perfect_circle) * c_road) + ((n - unique_cities.size()) * c_lib);

        if (lib_in_select_cities > lib_in_all_cities)
        {
            break;
        }
    }

    std::cout << "Number perfect_circle:  " << perfect_circle << std::endl;

    std::cout << "Number of libs:  " << unique_src_cities.size() << std::endl;
    std::cout << "Number of n_paths:  " << n_paths << std::endl;
    std::cout << "Number of left out city:  " << (n - unique_cities.size()) << std::endl;


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
