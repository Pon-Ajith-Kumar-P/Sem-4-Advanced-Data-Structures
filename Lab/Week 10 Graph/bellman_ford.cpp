#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, w;
};

void showGraph(int vertices, vector<Edge>& edges) {
    // Adjacency List
    cout << "\nGraph (Adjacency List):\n";
    vector<vector<int>> adjList(vertices);
    for (auto& edge : edges) {
        adjList[edge.u].push_back(edge.v);
    }
    for (int i = 0; i < vertices; i++) {
        cout << i << ": ";
        for (int v : adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    // Adjacency Matrix
    cout << "\nGraph (Adjacency Matrix):\n";
    vector<vector<int>> adjMatrix(vertices, vector<int>(vertices, 0)); // Initialize matrix with 0
    for (auto& edge : edges) {
        adjMatrix[edge.u][edge.v] = edge.w;
    }

    cout << "  ";
    for (int i = 0; i < vertices; i++)
        cout << i << " ";
    cout << endl;

    for (int i = 0; i < vertices; i++) {
        cout << i << " ";
        for (int j = 0; j < vertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool bellmanFord(int vertices, int edgesCount, vector<Edge>& edges, int source, vector<int>& distance) {
    distance.resize(vertices, 1e9); // Infinity
    distance[source] = 0;

    // Step 1: Relax all edges |V| - 1 times
    for (int i = 1; i <= vertices - 1; ++i) {
        for (int j = 0; j < edgesCount; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (distance[u] != 1e9 && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Step 2: Check for negative-weight cycles
    for (int j = 0; j < edgesCount; ++j) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (distance[u] != 1e9 && distance[u] + w < distance[v]) {
            return false; // Negative cycle found
        }
    }

    return true; // No negative cycle
}

int main() {
    int vertices, edgesCount;
    cout << "Enter number of vertices and edges: ";
    cin >> vertices >> edgesCount;

    vector<Edge> edges(edgesCount);

    cout << "Enter each edge as: u v weight\n";
    for (int i = 0; i < edgesCount; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Show the graph
    showGraph(vertices, edges);

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    vector<int> distance;
    bool noNegCycle = bellmanFord(vertices, edgesCount, edges, source, distance);

    if (noNegCycle) {
        cout << "Shortest distances from source " << source << ":\n";
        for (int i = 0; i < vertices; ++i) {
            if (distance[i] == 1e9)
                cout << i << " : INF\n";
            else
                cout << i << " : " << distance[i] << "\n";
        }
    } else {
        cout << "Graph contains a negative-weight cycle.\n";
    }

    return 0;
}
