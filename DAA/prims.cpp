#include<iostream>
using namespace std;

#define INF 99999 // Represent infinity for non-edges

// Function to find the vertex with minimum key value
int findMinKey(int key[], bool visited[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!visited[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    return min_index;
}

// Function to perform Prim's Algorithm with concise output
void primMST(int graph[][100], int V) {
    int step = 1;
    int parent[V], key[V];
    bool visited[V];
    
    // Initialize arrays
    for (int i = 0; i < V; i++) {
        key[i] = INF;    // Key values to pick minimum weight edge
        visited[i] = false; // Track visited vertices
        parent[i] = -1;  // Store MST edges
    }
    key[0] = 0; // Start from vertex 0
    
    cout << "Step " << step++ << ": Starting from vertex 0" << endl;
    
    // Build MST
    for (int count = 0; count < V - 1; count++) {
        int u = findMinKey(key, visited, V);
        visited[u] = true;
        
        cout << "Step " << step++ << ": Added vertex " << u << " to MST" << endl;
        
        // Update key values and parent for adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
                cout << "Updated edge " << u << " - " << v << " (weight " << graph[u][v] << ")" << endl;
            }
        }
        
        // Print current MST
        cout << "MST after step " << step - 1 << ": ";
        for (int i = 1; i < V; i++)
            if (parent[i] != -1)
                cout << parent[i] << "-" << i << " ";
        cout << endl;
    }
    
    // Calculate and print total weight
    int mst_weight = 0;
    for (int i = 0; i < V; i++)
        if (key[i] != INF)
            mst_weight += key[i];
    
    cout << "Final MST: ";
    for (int i = 1; i < V; i++)
        if (parent[i] != -1)
            cout << parent[i] << "-" << i << " ";
    cout << endl << "Total weight: " << mst_weight << endl;
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;
    
    int graph[100][100]; // Adjacency matrix (max 100 vertices for simplicity)
    cout << "Enter the adjacency matrix (" << V << "x" << V << "):" << endl;
    cout << "Use " << INF << " for no edge between vertices" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }
    
    cout << "Graph adjacency matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    
    // Perform Prim's Algorithm
    primMST(graph, V);
    
    return 0;
}