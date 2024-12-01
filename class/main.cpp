#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <string>

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
            cout << "Location not found: " << startLocation << endl;
            return;
        }

        vector<bool> visited(node_count, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS starting from location " << startLocation << ": ";

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

    void travelTime(string startLocation, string endLocation) {
        int start = findLocationIndex(startLocation);
        int end = findLocationIndex(endLocation);

        if (start == -1 || end == -1) {
            cout << "Invalid locations provided!" << endl;
            return;
        }

        cout << "Travel time between " << startLocation << " and " << endLocation << ":" << endl;

        for (auto i : adjList[start]) {
            if (i.first == end) {
                cout << "Direct travel time: " << i.second << " mins" << endl;
                cout << "Number of locations traveled: 2 (including start and end)" << endl;
                return;
            }
        }

        cout << "No direct route found!" << endl;
    }

    void travelTimeFromHome() {
        cout << "Travel times and location counts from Home:" << endl;

        for (int i = 1; i < node_count; i++) { // Exclude the start node itself
            cout << "To " << locations[i] << ": ";

            bool directRoute = false;
            for (auto edge : adjList[0]) {
                if (edge.first == i) {
                    cout << edge.second << " mins, ";
                    cout << "Locations: 2 (including start and end)" << endl;
                    directRoute = true;
                    break;
                }
            }

            if (!directRoute)
                cout << "No direct route available!" << endl;
        }
    }

    void DFS(string startLocation) {
        int start = findLocationIndex(startLocation);
        if (start == -1) {
            cout << "Location not found: " << startLocation << endl;
            return;
        }

        vector<bool> visited(node_count, false);
        stack<int> s;
        s.push(start);

        cout << "DFS starting from location " << startLocation << ": ";

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


private:
    int findLocationIndex(string locationName) {
        for (int i = 0; i < locations.size(); i++) {
            if (locations[i] == locationName)
                return i;
        }
        return -1; // Location not found
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
    grp.travelTime("Home", "Library");
    grp.travelTime("Home", "Cinema");
    grp.travelTimeFromHome();


    return 0;
}

