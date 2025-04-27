#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100;
vector<int> g[MAX];
bool visited[MAX];
int disc[MAX], low[MAX], parent[MAX];
bool ap[MAX];
int timer;

void showGraph(int n) {
    // Adjacency List
    cout << "\nGraph (Adjacency List):\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int v : g[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    // Adjacency Matrix
    cout << "\nGraph (Adjacency Matrix):\n\t";
    int matrix[MAX][MAX] = {0};

    for (int j = 0; j < n; j++)
        cout << j << "\t";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << i << "\t";
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
        for (int v : g[i]) {
            matrix[i][v] = 1;
        }
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void dfs(int u, int n) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    int children = 0;

    for (int v : g[u]) {
        if (!visited[v]) {
            children++;
            parent[v] = u;
            dfs(v, n);

            low[u] = min(low[u], low[v]);

            if (parent[u] == -1 && children > 1)
                ap[u] = true;

            if (parent[u] != -1 && low[v] >= disc[u])
                ap[u] = true;
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

bool isBiconnected(int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        ap[i] = false;
        parent[i] = -1;
    }
    timer = 0;

    dfs(0, n);

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

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Enter edges (0-based indexing):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    showGraph(n);

    if (isBiconnected(n))
        cout << "The graph is Biconnected.\n";
    else {
        cout << "The graph is NOT Biconnected.\n";
        cout << "Articulation points: ";
        for (int i = 0; i < n; i++) {
            if (ap[i])
                cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
