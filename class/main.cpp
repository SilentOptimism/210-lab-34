#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <string>
#include <set>
#include <climits>

using namespace std;

int node_count = 13; // Total number of nodes

struct Edge {
    int src;
    int dest;
    int weight; // Travel time in minutes
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;
    vector<string> locations;

    Graph(vector<Edge> const &edges, vector<string> const &locationNames) {
        adjList.resize(node_count);
        locations = locationNames;

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list (locations and travel times):" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << locations[i] << " -->";
            for (Pair v : adjList[i])
                cout << " (" << locations[i] << " -> " << locations[v.first] << ", " << v.second << " mins)";
            cout << endl;
        }
    }

    void BFS(string startLocation) {
        int start = findLocationIndex(startLocation);
        if (start == -1) {
            cout << "Location not found." << endl;
            return;
        }

        vector<bool> visited(node_count, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS traversal starting from " << locations[start] << ": ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << locations[v] << " ";

            for (auto i : adjList[v]) {
                if (!visited[i.first]) {
                    visited[i.first] = true;
                    q.push(i.first);
                }
            }
        }
        cout << endl;
    }

    void DFS(string startLocation) {
        int start = findLocationIndex(startLocation);
        if (start == -1) {
            cout << "Location not found." << endl;
            return;
        }

        vector<bool> visited(node_count, false);
        stack<int> s;
        s.push(start);

        cout << "DFS traversal starting from " << locations[start] << ": ";
        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << locations[v] << " ";
            }

            for (auto i : adjList[v]) {
                if (!visited[i.first]) {
                    s.push(i.first);
                }
            }
        }
        cout << endl;
    }

    void travelTimeFromHome() {
        vector<int> travelTime(node_count, INT_MAX);
        vector<int> locationsCount(node_count, INT_MAX);
        vector<bool> visited(node_count, false);

        int start = 0; // Home index
        travelTime[start] = 0;
        locationsCount[start] = 0;

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start}); // {travel time, location}

        while (!pq.empty()) {
            int time = pq.top().first;
            int location = pq.top().second;
            pq.pop();

            if (visited[location]) continue;
            visited[location] = true;

            for (auto &[next, weight] : adjList[location]) {
                if (time + weight < travelTime[next]) {
                    travelTime[next] = time + weight;
                    locationsCount[next] = locationsCount[location] + 1;
                    pq.push({travelTime[next], next});
                }
            }
        }

        // Output travel times
        cout << "Travel time and locations count from Home:" << endl;
        for (int i = 0; i < node_count; i++) {
            cout << locations[i] << ": ";
            if (travelTime[i] == INT_MAX) {
                cout << "No route available" << endl;
            } else {
                cout << travelTime[i] << " mins, through " << locationsCount[i] << " locations" << endl;
            }
        }
    }

    void findMST() {
        vector<bool> inMST(node_count, false); // Track visited nodes
        vector<int> key(node_count, INT_MAX); // Minimum edge weights
        vector<int> parent(node_count, -1);   // Track parents in MST
        int start = 0;                        // Start at node 0 (Home)

        // Priority queue to select edges with minimum weights
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start}); // (weight, node)
        key[start] = 0;

        while (!pq.empty()) {
            int u = pq.top().second; // Extract node with minimum key value
            pq.pop();

            if (inMST[u]) continue; // If already in MST, skip
            inMST[u] = true;

            // Traverse all adjacent vertices of u
            for (auto &[v, weight] : adjList[u]) {
                if (!inMST[v] && weight < key[v]) {
                    // If a smaller edge weight is found
                    key[v] = weight;
                    pq.push({weight, v});
                    parent[v] = u;
                }
            }
        }

        // Output the MST
        cout << "Minimum Spanning Tree (MST):" << endl;
        int totalWeight = 0;
        for (int i = 1; i < node_count; i++) {
            if (parent[i] != -1) {
                cout << locations[parent[i]] << " --(" << key[i] << " mins)--> " << locations[i] << endl;
                totalWeight += key[i];
            }
        }
        cout << "Total weight of MST: " << totalWeight << " mins" << endl;
    }

private:
    int findLocationIndex(string locationName) {
        for (int i = 0; i < locations.size(); i++) {
            if (locations[i] == locationName)
                return i;
        }
        return -1; // Not found
    }
};

int main() {
    vector<Edge> edges = {
        {0, 1, 12}, {0, 2, 8}, {0, 3, 21}, {2, 3, 6}, {2, 4, 4},
        {3, 7, 15}, {7, 8, 10}, {8, 9, 5}, {9, 10, 8}, {10, 11, 7}, {11, 12, 3}, {12, 7, 6}
    };

    vector<string> locationNames = {
        "Home", "Supermarket", "Park", "Library", "School",
        "Cafe", "Gym", "Mall", "Cinema", "Stadium", "Hospital", "Airport", "Train Station"
    };

    Graph grp(edges, locationNames);

    grp.printGraph();
    grp.BFS("Home");
    grp.DFS("Home");
    grp.travelTimeFromHome();
    grp.findMST();

    return 0;
}
