#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INF 1000000

void showGraph(const vector<vector<int>>& mat) {
    int n = mat.size();

    // Adjacency List
    cout << "\nGraph (Adjacency List):\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != INF && i != j) {
                cout << j << "(" << mat[i][j] << ") ";
            }
        }
        cout << endl;
    }

    // Adjacency Matrix
    cout << "\nGraph (Adjacency Matrix):\n\t";
    for (int j = 0; j < n; j++)
        cout << j << "\t";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << i << "\t";
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == INF)
                cout << "INF\t";
            else
                cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

void printMatrix(const vector<vector<int>>& mat, int step) {
    cout << "\nD" << step << ":\n";
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat.size(); j++) {
            if (mat[i][j] == INF)
                cout << "INF\t";
            else
                cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));

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

    // Show original graph structure
    showGraph(dist);

    // Show D0 (Initial matrix)
    printMatrix(dist, 0);

    // Floyd-Warshall Algorithm
    for (int k = 0; k < n; k++) {
        vector<vector<int>> next = dist;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    next[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
        dist = next;
        printMatrix(dist, k + 1); // Show D(k+1)
    }

    // Final All-Pairs Shortest Paths Matrix (APSP)
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

    return 0;
}
