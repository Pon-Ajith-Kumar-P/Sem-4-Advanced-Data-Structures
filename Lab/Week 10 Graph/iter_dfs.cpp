#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int v) {
        vertices = v;
        adjList.resize(v);
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // For undirected graph
    }

    // Display graph (Adjacency List and Adjacency Matrix)
    void viewGraph() {
        // Adjacency List
        cout << "\nGraph (Adjacency List):\n";
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
        for (int i = 0; i < vertices; i++) {
            for (int v : adjList[i]) {
                adjMatrix[i][v] = 1; // There is an edge between i and v
            }
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

    // Iterative DFS
    void iterativeDFS(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;

        s.push(start);

        cout << "Iterative DFS: ";
        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;
            }

            // Push unvisited neighbors
            for (auto it = adjList[node].rbegin(); it != adjList[node].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    cout << "Enter the number of edges: ";
    cin >> edges;

    Graph g(vertices);

    cout << "Enter the edges (source and destination):\n";
    for (int i = 0; i < edges; ++i) {
        int src, dest;
        cin >> src >> dest;
        g.addEdge(src, dest);
    }

    // Show the graph in both adjacency list and matrix formats
    g.viewGraph();

    int startNode;
    cout << "Enter the starting node for DFS: ";
    cin >> startNode;
    g.iterativeDFS(startNode);

    return 0;
}
