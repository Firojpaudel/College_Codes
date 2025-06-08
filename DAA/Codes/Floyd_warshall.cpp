#include<iostream>
using namespace std;
const int INF = 999999;  // Infinity for no edge

// Function to print the path from i to j using predecessor matrix
void printPath(int pred[][100], int i, int j) {
    if (i == j) {
        cout << i;
        return;
    }
    if (pred[i][j] == -1) {
        cout << "No path";
        return;
    }
    printPath(pred, i, pred[i][j]);
    cout << " -> " << j;
}

// Function to perform Floyd-Warshall with step-by-step output
void floydWarshall(int graph[][100], int V) {
    int dist[100][100];  // Shortest distance matrix
    int pred[100][100];  // Predecessor matrix for path reconstruction
    int step = 1;
    
    // Step 1: Initialize distance and predecessor matrices
    cout << "Step " << step++ << ": Initializing distance and predecessor matrices" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            if (i == j)
                pred[i][j] = -1;
            else if (graph[i][j] != INF && graph[i][j] != 0)
                pred[i][j] = i;
            else
                pred[i][j] = -1;
        }
    }
    
    // Print initial distance matrix
    cout << "Initial distance matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    
    // Step 2: Update distances using intermediate vertices
    for (int k = 0; k < V; k++) {
        cout << "Step " << step++ << ": Considering vertex " << k << " as intermediate" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    cout << "  Updating path " << i << " to " << j << " via " << k << ": ";
                    cout << dist[i][j] << " -> " << dist[i][k] + dist[k][j] << endl;
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }
    
    // Step 3: Print final shortest distances and paths
    cout << "Step " << step++ << ": Final shortest distances" << endl;
    cout << "Shortest distances between all pairs:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Paths between all pairs:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << "Path from " << i << " to " << j << ": ";
            printPath(pred, i, j);
            cout << endl;
        }
    }
}

int main() {
    int V;
    int graph[100][100];  // Adjacency matrix for graph
    
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the adjacency matrix (enter 999999 for no edge):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << "Edge " << i << " to " << j << " weight: ";
            cin >> graph[i][j];
        }
    }
    
    cout << "Graph edges:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != INF && graph[i][j] != 0)
                cout << i << " -> " << j << ": " << graph[i][j] << endl;
        }
    }
    
    // Perform Floyd-Warshall Algorithm
    floydWarshall(graph, V);
    
    return 0;
}