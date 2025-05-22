#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<int> disc, low, parent;
    vector<bool> ap;
    int timer;

public:
    Graph(int vertices) {
        n = vertices;
        adj.resize(n);
        visited.resize(n, false);
        disc.resize(n, 0);
        low.resize(n, 0);
        parent.resize(n, -1);
        ap.resize(n, false);
        timer = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void showGraph() {
        cout << "\nGraph (Adjacency List):\n";
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            for (int v : adj[i]) {
                cout << v << " ";
            }
            cout << endl;
        }

        cout << "\nGraph (Adjacency Matrix):\n\t";
        for (int j = 0; j < n; j++)
            cout << j << "\t";
        cout << endl;

        vector<vector<int>> matrix(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int v : adj[i]) {
                matrix[i][v] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            cout << i << "\t";
            for (int j = 0; j < n; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void dfs(int u) {
        visited[u] = true;
        disc[u] = low[u] = ++timer;
        int children = 0;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                dfs(v);

                low[u] = min(low[u], low[v]);

                if (parent[u] == -1 && children > 1)
                    ap[u] = true;

                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = true;
            }
            else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    bool isBiconnected() {
        fill(visited.begin(), visited.end(), false);
        fill(ap.begin(), ap.end(), false);
        fill(parent.begin(), parent.end(), -1);
        timer = 0;

        dfs(0);

        for (int i = 0; i < n; i++) {
            if (!visited[i])
                return false; // not connected
        }

        for (int i = 0; i < n; i++) {
            if (ap[i])
                return false; // has articulation point
        }

        return true;
    }

    void printArticulationPoints() {
        cout << "Articulation points: ";
        for (int i = 0; i < n; i++) {
            if (ap[i])
                cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    Graph g(n);

    cout << "Enter edges (0-based indexing):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.showGraph();

    if (g.isBiconnected())
        cout << "The graph is Biconnected.\n";
    else {
        cout << "The graph is NOT Biconnected.\n";
        g.printArticulationPoints();
    }

    return 0;
}
