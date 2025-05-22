#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INF 1000000

class Graph {
    int n;
    vector<vector<int>> dist;

public:
    Graph(int vertices) {
        n = vertices;
        dist.resize(n, vector<int>(n));
    }

    void inputMatrix() {
        cout << "Enter adjacency matrix (use 'INF' for infinity):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                string input;
                cin >> input;
                if (input == "INF")
                    dist[i][j] = INF;
                else
                    dist[i][j] = stoi(input);
            }
        }
    }

    void showGraph() {
        cout << "\nGraph (Adjacency List):\n";
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            for (int j = 0; j < n; j++) {
                if (dist[i][j] != INF && i != j)
                    cout << j << "(" << dist[i][j] << ") ";
            }
            cout << endl;
        }

        cout << "\nGraph (Adjacency Matrix):\n\t";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << dist[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void printMatrix(const vector<vector<int>>& mat, int step) {
        cout << "\nD" << step << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << mat[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void floydWarshall() {
        printMatrix(dist, 0);

        for (int k = 0; k < n; k++) {
            vector<vector<int>> next = dist;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        next[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
            dist = next;
            printMatrix(dist, k + 1);
        }
    }

    void showAPSP() {
        cout << "\nAll-Pairs Shortest Paths (APSP) Matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << dist[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);
    g.inputMatrix();
    g.showGraph();
    g.floydWarshall();
    g.showAPSP();

    return 0;
}
