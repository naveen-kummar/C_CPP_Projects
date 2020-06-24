#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Graph {
public:
    Graph(int n) : m_nodes{ n }
    {
        Nodes.resize(m_nodes + 1);
        Visited.resize(m_nodes + 1);
    }

    void add_edge(int u, int v) {

        Nodes[u].push_back(v);
        Nodes[v].push_back(u);
    }

    vector<int> shortest_reach(int start) {

        //cout << "Starting node is " << start << endl;

        vector<int> output;
        //output.resize(m_nodes);

        for (int node = 1; node <= m_nodes; node++)
        {
            //cout << "About to Processing node " << node << endl;
            if (node == start)
                continue;
            //cout << "Processing node " << node << endl;

            queue<Point> q;
            std::fill(std::begin(Visited), std::end(Visited), false);
            Visited[0] = true;

            q.push({ start, 0 });

            int Steps = -1;

            while (q.empty() == false)
            {
                Point t = q.front();
                q.pop();

                //cout << "Popped Node " << t.num << endl;

                if (t.num == node)
                {
                    //cout << "Reached node " << node << " from " << start << " in " << t.dist << " Steps." << endl;
                    Steps = t.dist;
                    break;
                }
                //cout << "Size of Node " << t.num << " is = " << Nodes[t.num].size() << endl;

                for (size_t pos = 0; pos < Nodes[t.num].size(); pos++)
                {
                    Point new_pos{};
                    new_pos.num = Nodes[t.num][pos];
                    new_pos.dist = t.dist + 6;

                    if (Visited[new_pos.num] == false)
                    {
                        //cout << "Visiting Node " << new_pos.num << endl;
                        Visited[new_pos.num] = true;
                        q.push(new_pos);
                    }

                }
            }

            //cout << ">>> Pushing value " << Steps << " at pos " << output.size() - 1 << endl;
            output.push_back(Steps);

        }
        return output;
    }

    int m_nodes;
    vector<vector<int>> Nodes;
    vector<bool> Visited;

    struct Point
    {
        int num;
        int dist;

        Point() {};
        Point(int n, int d) : num{ n }, dist{ d }{};
    };
};

int main() {
    int queries;
    cin >> queries;

    for (int t = 0; t < queries; t++) {

        int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            // u--, v--;
             // add each edge to the graph
            graph.add_edge(u, v);
        }
        int startId;
        cin >> startId;
        //startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (size_t i = 0; i < distances.size(); i++) {
            // if (i != startId) 
            {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
