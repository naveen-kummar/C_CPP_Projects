
#include <iostream>
#include <vector>
#include <map>
#include <set>


using namespace std;

// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> queries) {

    vector<int> output{};


    map<int, set<int>> friend_circle{};

    for (auto query : queries)
    {
        auto friend1 = query[0];
        auto friend2 = query[1];

        cout << " >> friend1 =  " << friend1 << " and friend2 = " << friend2 << endl;


        int friend1_key{ -1 };
        int friend2_key{ -1 };
        for (auto circle : friend_circle)
        {
            if (find(circle.second.begin(), circle.second.end(), friend1) != circle.second.end())
            {
                friend1_key = circle.first;
            }

            if (find(circle.second.begin(), circle.second.end(), friend2) != circle.second.end())
            {
                friend2_key = circle.first;
            }

            if ((friend2_key != -1) && (friend1_key != -1))
            {
                break;
            }

        }

        cout << " >> friend1_key =  " << friend1_key << " and friend2_key = " << friend1_key << endl;


        if ((friend2_key != friend1_key) || (friend2_key == -1))
        {
            //Need to merge
            if ((friend2_key == -1) && (friend1_key == -1))
            {
                int key = friend_circle.size();
                friend_circle.insert({ key, { friend1, friend2 } });
            }
            else if (friend1_key == -1)
            {
                friend_circle[friend2_key].insert(friend1);
            }
            else if (friend2_key == -1)
            {
                friend_circle[friend1_key].insert(friend2);
            }
            else
            {
                int key_to_consider{};

                if (friend_circle[friend1_key].size() > friend_circle[friend2_key].size())
                {
                    for (auto fr : friend_circle[friend2_key])
                    {
                        if (find(friend_circle[friend1_key].begin(), friend_circle[friend1_key].end(), fr)
                            == friend_circle[friend1_key].end())
                        {
                            friend_circle[friend1_key].insert(fr);
                            cout << " 1 Adding frient " << fr << endl;
                        }
                    }

                    friend_circle[friend2_key].clear();
                }
                else
                {
                    for (auto fr : friend_circle[friend1_key])
                    {
                        if (find(friend_circle[friend2_key].begin(), friend_circle[friend2_key].end(), fr)
                            == friend_circle[friend2_key].end())
                        {
                            friend_circle[friend2_key].insert(fr);
                            cout << " 2 Adding frient " << fr << endl;
                        }
                    }

                    friend_circle[friend1_key].clear();
                }
            }

        }

        int max_size{ 0 };
        for (auto friend_map : friend_circle)
        {
            if (friend_map.second.size() > max_size)
            {
                max_size = friend_map.second.size();
            }
        }

        output.push_back(max_size);

    }



    return output;


}

int main()
{

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> queries(q);
    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> ans = maxCircle(queries);

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];

        if (i != ans.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";


    return 0;
}
