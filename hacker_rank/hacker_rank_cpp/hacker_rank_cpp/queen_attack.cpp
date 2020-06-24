#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <algorithm>

using namespace std;

vector<string> split_string1(string);

// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {

    int attacks = 0;
    int d_x[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int d_y[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

    for (int dir = 0; dir < 8; dir++)
    {
        int curr_r = r_q;
        int curr_c = c_q;

        while (true)
        {
            curr_r += d_x[dir];
            curr_c += d_y[dir];
            if ((curr_r > 0) && (curr_r <= n) && (curr_c > 0) && (curr_c <= n) &&
                ((std::find_if(std::begin(obstacles), std::end(obstacles), [curr_r, curr_c](auto v) {return ((v[0] == curr_r) && (v[1] == curr_c)); }) == std::end(obstacles))))
            {
                ++attacks;
            }
            else
            {
                break;
            }
        }
    }

    return attacks;
}

int main()
{
    //ofstream fout(_dupenv_s("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string1(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string1(r_qC_q_temp);

    int r_q = stoi(r_qC_q[0]);

    int c_q = stoi(r_qC_q[1]);

    vector<vector<int>> obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

    cout << result << "\n";

    //fout.close();

    return 0;
}

vector<string> split_string1(string input_string) {
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
