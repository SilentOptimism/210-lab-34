#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

int node_count = 13; // Number of nodes

struct Edge {
    int src;
    int dest;
    int weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;
    unordered_map<int, string> locationMap; // Map to store node to location name

    Graph(vector<Edge> const &edges, unordered_map<int, string> const &locations) {
        adjList.resize(node_count);
        locationMap = locations; // Copy location mapping

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list (locations):" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << locationMap[i] << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << locationMap[v.first] << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void BFS(int start) {
        vector<bool> visited(node_count, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS starting from " << locationMap[start] << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << locationMap[v] << " ";

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

        cout << "DFS starting from " << locationMap[start] << ": ";

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << locationMap[v] << " ";
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
        {0, 1, 12}, {0, 2, 8}, {0, 3, 21}, {2, 3, 6}, {2, 4, 4},
        {3, 7, 15}, {7, 8, 10}, {8, 9, 5}, {9, 10, 8}, {10, 11, 7}, {11, 12, 3}, {12, 7, 6}
    };

    unordered_map<int, string> locations = {
        {0, "Park Entrance"},
        {1, "Visitor Center"},
        {2, "Lake"},
        {3, "Playground"},
        {4, "Garden"},
        {7, "Mountain Trail Start"},
        {8, "Trail Midpoint"},
        {9, "Trail Overlook"},
        {10, "Picnic Area"},
        {11, "River Crossing"},
        {12, "Mountain Summit"}
    };

    Graph grp(edges, locations);

    grp.printGraph();
    grp.BFS(0);
    grp.DFS(0);

    return 0;
}
