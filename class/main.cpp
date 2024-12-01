#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

using namespace std;

int node_count = 7;

struct Edge {
    int src;
    int dest;
    int weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(node_count);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " -->";
            for (Pair v : adjList[i])
                cout << "(" << i << ", " << v.first << ", " << v.second << ")";
            cout << endl;
        }
    }

    void BFS(int start) {
        vector<bool> visited(node_count, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS starting from node " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto i : adjList[v]) {
                if (!visited[i.first]) {
                    visited[i.first] = true;
                    q.push(i.first);
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        vector<bool> visited(node_count, false);
        stack<int> s;
        s.push(start);

        cout << "DFS starting from node " << start << ": ";

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";
            }

            for (auto i : adjList[v]) {
                if (!visited[i.first]) {
                    s.push(i.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0, 1, 12}, {0, 2, 8}, {0, 3, 21}, {2, 3, 6}, {2, 6, 2}, {5, 6, 6}, {4, 5, 9}, {2, 4, 4}, {2, 5, 5}
    };

    Graph grp = Graph(edges);

    grp.printGraph();
    grp.BFS(0);
    grp.DFS(0);

    return 0;
}

