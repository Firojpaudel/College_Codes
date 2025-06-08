#include<iostream>
using namespace std;

// Function to find the unvisited vertex with minimum distance
int findMinDistance(int distance[], bool visited[], int V) {
    int minDist = 999999, minVertex = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && distance[v] < minDist) {
            minDist = distance[v];
            minVertex = v;
        }
    }
    return minVertex;
}

// Function to print the path from source to a vertex
void printPath(int parent[], int vertex, int src) {
    if (vertex == src) {
        cout << src;
        return;
    }
    if (parent[vertex] == -1) {
        cout << "No path exists";
        return;
    }
    printPath(parent, parent[vertex], src);
    cout << " <- " << vertex;
}

// Function to perform Dijkstra's Algorithm with step-by-step output
void dijkstra(int graph[][100], int V, int src) {
    int distance[V];  // Shortest distance from src to each vertex
    int parent[V];    // Parent array for shortest path tree
    bool visited[V];  // Track visited vertices
    int step = 1;
    
    // Step 1: Initialize distances and arrays
    cout << "Step " << step++ << ": Initializing distances" << endl;
    for (int i = 0; i < V; i++) {
        distance[i] = 999999;  // Infinity
        visited[i] = false;
        parent[i] = -1;
    }
    distance[src] = 0;
    cout << "Distance from source " << src << ": ";
    for (int i = 0; i < V; i++)
        cout << "To " << i << " = " << (distance[i] == 999999 ? "INF" : to_string(distance[i])) << " ";
    cout << endl;
    
    // Step 2: Process vertices
    for (int count = 0; count < V - 1; count++) {
        int u = findMinDistance(distance, visited, V);
        if (u == -1) break;
        
        // Mark vertex as visited
        visited[u] = true;
        cout << "Step " << step++ << ": Selected vertex " << u << " with distance " << distance[u] << endl;
        
        // Relax adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != 999999 && distance[u] + graph[u][v] < distance[v]) {
                cout << "  Relaxing edge " << u << " - " << v << " (weight " << graph[u][v] << "): ";
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
                cout << "Updated distance to " << v << " = " << distance[v] << endl;
            }
        }
    }
    
    // Print final shortest distances and paths
    cout << "Step " << step++ << ": Final shortest distances from source " << src << endl;
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << ": Distance = " << (distance[i] == 999999 ? "INF" : to_string(distance[i]));
        if (i != src) {
            cout << ", Path = ";
            printPath(parent, i, src);
        }
        cout << endl;
    }
}

int main() {
    int V, src;
    int graph[100][100];  // Adjacency matrix for graph
    
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the adjacency matrix (enter 0 for no edge):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << "Edge " << i << " to " << j << " weight: ";
            cin >> graph[i][j];
        }
    }
    cout << "Enter the source vertex: ";
    cin >> src;
    
    cout << "Graph edges:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != 0)
                cout << i << " - " << j << ": " << graph[i][j] << endl;
        }
    }
    
    // Perform Dijkstra's Algorithm
    dijkstra(graph, V, src);
    
    return 0;
}