
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <cassert>


using namespace std;

struct friend_data
{

    int circle_id{ -1 };
    int count{ -1 };
    int id{-1};

    friend_data()
    {}

    friend_data(int i) : id{ i }
    {}


    int link_friend(std::shared_ptr<friend_data> fr)
    {
        int return_count = 0;
        if (circle_id > 0 && fr->circle_id == circle_id)
        {

        }
        else if(fr == nullptr)
        { }
        else 
        {
            int this_circle_id = circle_id;
            int this_circle_count = count;
            if (pNext != nullptr)
            {
                while (pNext != nullptr)
                {
                    this_circle_id = pNext->circle_id;
                    this_circle_count = pNext->count;
                    if (pNext->pNext == nullptr)
                    {
                        break;
                    }
                    pNext = pNext->pNext;
                }
            }

            int link_circle_id = fr->circle_id;
            int link_circle_count = fr->count;
            if (fr->pNext != nullptr)
            {
                link_circle_id = fr->pNext->circle_id;
                link_circle_count = fr->pNext->count;
                while (fr->pNext != nullptr)
                {
                    if (fr->pNext == nullptr)
                    {
                        break;
                    }
                    fr = fr->pNext;
                }
            }

            if ((link_circle_id == -1) || (link_circle_id != this_circle_id))
            {
                if (pNext == nullptr)
                {
                    pNext = fr;
                    if (fr->count == -1 && count == -1)
                    {
                        fr->count = 2;
                    }
                    else if (fr->count == -1 && count != -1)
                    {
                        fr->count = count + 1;
                        count = -1;
                    }
                    else if (fr->count != -1 && count == -1)
                    {
                        fr->count += 1;
                    }
                    else
                    {
                        fr->count += count;
                        count = -1;
                    }

                    if (fr->circle_id == -1 && circle_id == -1)
                    {
                        fr->circle_id = id;
                    }
                    else if (fr->circle_id == -1 && circle_id != -1)
                    {
                        fr->circle_id = circle_id;
                        circle_id = -1;
                    }
                    else
                    {
                        fr->circle_id = circle_id;
                        circle_id = -1;
                    }
                }
                else
                {
                    pNext->pNext = fr;
                    if (fr->count == -1 && pNext->count == -1)
                    {
                        fr->count = 2;
                    }
                    else if (fr->count == -1 && pNext->count != -1)
                    {
                        fr->count = pNext->count + 1;
                        pNext->count = -1;
                    }
                    else if (fr->count != -1 && pNext->count == -1)
                    {
                        fr->count += 1;
                    }
                    else
                    {
                        fr->count += pNext->count;
                        pNext->count = -1;
                    }

                    if (fr->circle_id == -1 && pNext->circle_id == -1)
                    {
                        fr->circle_id = pNext->id;
                    }
                    else if (fr->circle_id == -1 && pNext->circle_id != -1)
                    {
                        fr->circle_id = pNext->circle_id;
                        pNext->circle_id = -1;
                    }
                    else
                    {
                        fr->circle_id = pNext->circle_id;
                        pNext->circle_id = -1;
                    }

                    pNext = pNext->pNext;
                }
            }                       
        }



        int retval{count};
        if (pNext != nullptr)
        {
            retval = pNext->count;

            if (pNext->id == 91)
            {
                int n = 0;
            }
        }



        return retval;
    }

    shared_ptr<friend_data> pNext{ nullptr };

};

// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> queries) {

    vector<int> output{};

    int max_size{0};

    map<int, std::shared_ptr<friend_data>> friend_circles{};

    for (auto query : queries)
    {
        auto friend1 = query[0];
        auto friend2 = query[1];

        if (friend_circles[friend1] == nullptr &&
            friend_circles[friend2] == nullptr)
        {
            auto fr1 = std::make_shared<friend_data>(friend1);
           // fr1->circle_id = friend1;

            friend_circles[friend1] = fr1;

            auto fr2 = std::make_shared<friend_data>(friend2);

            friend_circles[friend2] =  fr2;

            int sz = friend_circles[friend1]->link_friend(friend_circles[friend2]);
            if (sz > max_size)
            {
                max_size = sz;
            }

        }
        else if (friend_circles[friend1] != nullptr &&
            friend_circles[friend2] != nullptr)
        {
            int sz = friend_circles[friend1]->link_friend(friend_circles[friend2]);
            if (sz > max_size)
            {
                max_size = sz;
            }
        }
        else if (friend_circles[friend1] != nullptr)
        {
            auto fr2 = std::make_shared<friend_data>(friend2);
            friend_circles[friend2] = fr2 ;

            int sz = friend_circles[friend1]->link_friend(friend_circles[friend2]);
            if (sz > max_size)
            {
                max_size = sz;
            }
        }
        else
        {
            auto fr1 = std::make_shared<friend_data>(friend1);
            friend_circles[friend1] = fr1;

            int sz = friend_circles[friend2]->link_friend(friend_circles[friend1]);
            if (sz > max_size)
            {
                max_size = sz;
            }
        }

        output.push_back(max_size);
    }

    return output;
}


// Complete the maxCircle function below.
vector<int> maxCircle1(vector<vector<int>> queries) {

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


    vector<vector<int>> queries{ 
/*
 {78 ,72},
        {67, 74},
        {65, 57},
        {65, 52},
        {70, 55},
        {74, 70},
        {58, 51},
        {70, 76},
        {69, 55},
        {64, 78},
        {67, 72},
        {69, 63},
        {77, 59},
        {69, 64},
        {70, 80},
        {66, 67},
        {71, 52},
        {60, 77},
        {80, 66},
        {70, 61},
*/
        {13, 54},
{4, 70},
{56, 48},
{86, 61},
{85, 31},
{61, 18},
{53, 52},
{78, 71},
{95, 72},
{4, 22},
{46, 81},
{88, 65},
{54, 9},
{72, 46},
{35, 98},
{12, 100},
{3, 68},
{21, 58},
{15, 59},
{70, 51},
{89, 31},
{69, 93},
{82, 98},
{15, 28},
{21, 19},
{49, 66},
{99, 89},
{83, 4},
{97, 6},
{49, 84},
{55, 13},
{35, 58},
{80, 7},
{15, 94},
{17, 85},
{44, 6},
{67, 64},
{50, 100},
{62, 65},
{28, 82},
{83, 28},
{100, 33},
{68, 34},
{36, 17},
{39, 85},
{52, 46},
{97, 86},
{3, 28},
{44, 69},
{21, 61},
{5, 16},
{18, 71},
{80, 67},
{71, 93},
{83, 50},
{26, 17},
{29, 77},
{49, 97},
{10, 85},
{13, 1},
{21, 64},
{46, 69},
{1, 48},
{96, 44},
{16, 68},
{56, 73},
{83, 73},
{43, 14},
{92, 65},
{6, 74},
{14, 84},
{91, 43},
{60, 39},
{91, 70},
{75, 55},
{70, 47},
{70, 15},
{15, 70},
{14, 62},
{65, 81},
{29, 73},
{53, 12},
{45, 96},
{77, 36},
{60, 35},
{62, 26},
{18, 52},
{20, 77},
{42, 62},
{98, 69},
{16, 19},
{15, 85},
{85, 30},
{6, 98},
{43, 22},
{79, 72},
{94, 31},
{35, 91},
{78, 11},
{78, 90}
};
    //for (int i = 0; i < q; i++) {
    //    queries[i].resize(2);

    //    for (int j = 0; j < 2; j++) {
    //        cin >> queries[i][j];
    //    }

    //    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //}

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
