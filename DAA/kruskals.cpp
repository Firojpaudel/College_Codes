#include<iostream>
#include<algorithm> // For sort
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure for disjoint-set
struct DisjointSet {
    int *parent, *rank;
    int n;
    
    DisjointSet(int n) {
        this->n = n;
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Each vertex is its own parent
            rank[i] = 0;
        }
    }
    
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }
    
    void unionSet(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        if (rank[pu] < rank[pv])
            parent[pu] = pv;
        else if (rank[pu] > rank[pv])
            parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }
};

// Function to compare edges by weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to perform Kruskal's Algorithm with concise output
void kruskalMST(Edge edges[], int V, int E) {
    int step = 1;
    
    // Step 1: Sort edges by weight
    cout << "Step " << step++ << ": Sorting edges by weight" << endl;
    sort(edges, edges + E, compare);
    for (int i = 0; i < E; i++)
        cout << "Edge " << edges[i].src << " - " << edges[i].dest << ": " << edges[i].weight << endl;
    
    // Step 2: Initialize disjoint-set and MST
    DisjointSet ds(V);
    Edge mst[V - 1]; // MST will have V-1 edges
    int mst_weight = 0, mst_index = 0;
    
    // Step 3: Process edges
    cout << "Step " << step++ << ": Building MST" << endl;
    for (int i = 0 ;i < E && mst_index < V - 1; i++) {
        int u = edges[i].src, v = edges[i].dest, w = edges[i].weight;
        cout << "Considering edge " << u << " - " << v << " (weight " << w << "): ";
        
        if (ds.find(u) != ds.find(v)) {
            mst[mst_index++] = edges[i];
            mst_weight += w;
            ds.unionSet(u, v);
            cout << "Added to MST" << endl;
            cout << "MST after step " << step++ << ": ";
            for (int j = 0; j < mst_index; j++)
                cout << mst[j].src << "-" << mst[j].dest << " ";
            cout << "(Total weight = " << mst_weight << ")" << endl;
        } else {
            cout << "Skipped (forms cycle)" << endl;
        }
    }
    
    // Print final MST
    cout << "Final MST: ";
    for (int i = 0; i < V - 1; i++)
        cout << mst[i].src << "-" << mst[i].dest << " ";
    cout << endl << "Total weight: " << mst_weight << endl;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    
    Edge edges[E];
    cout << "Enter " << E << " edges (source destination weight):" << endl;
    for (int i = 0; i < E; i++) {
        cout << "Edge " << i + 1 << ": ";
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }
    
    cout << "Graph edges:" << endl;
    for (int i = 0; i < E; i++)
        cout << edges[i].src << " - " << edges[i].dest << ": " << edges[i].weight << endl;
    
    // Perform Kruskal's Algorithm
    kruskalMST(edges, V, E);
    
    return 0;
}