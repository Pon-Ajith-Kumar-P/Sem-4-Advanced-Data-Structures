#include <iostream>
#include <vector>
using namespace std;

class Graph {
    struct Edge {
        int u, v, w;
    };

    int vertices, edgesCount;
    vector<Edge> edges;

public:
    Graph(int v, int e) {
        vertices = v;
        edgesCount = e;
        edges.resize(edgesCount);
    }

    void addEdge(int index, int u, int v, int w) {
        edges[index] = {u, v, w};
    }

    void showGraph() {
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
        vector<vector<int>> adjMatrix(vertices, vector<int>(vertices, 0));
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

    bool bellmanFord(int source, vector<int>& distance) {
        distance.resize(vertices, 1e9);
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
                return false;
            }
        }

        return true;
    }
};

int main() {
    int vertices, edgesCount;
    cout << "Enter number of vertices and edges: ";
    cin >> vertices >> edgesCount;

    Graph g(vertices, edgesCount);

    cout << "Enter each edge as: u v weight\n";
    for (int i = 0; i < edgesCount; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(i, u, v, w);
    }

    g.showGraph();

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    vector<int> distance;
    bool noNegCycle = g.bellmanFord(source, distance);

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
