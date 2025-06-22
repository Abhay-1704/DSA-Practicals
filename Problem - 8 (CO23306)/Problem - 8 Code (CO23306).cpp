/*Problem-8 Code
Roll-No :- co23306
Name :- Abhay Pratap Singh
Cse, 2nd Year*/

#include <bits/stdc++.h>

using namespace std;

/*Adjacency-Matrix of given graph (input)
n 1 4 n n n n
1 n 2 3 10 n n
4 2 n 6 n n 3
n 3 6 n 5 n 1
n 10 n 5 n 7 2
n n n n 7 n 5
n n 3 1 2 5 n  */

//Breadth First Search
struct Queue {
    int* arr;
    int front;
    int rear;
    int capacity;

    Queue(int size) {
        arr = new int[size];
        front = 0;
        rear = 0;
        capacity = size;
    }

    ~Queue() {
        delete[] arr;
    }

    bool isEmpty() {
        return front == rear;
    }

    void push(int value) {
        if (rear < capacity) {
            arr[rear++] = value;
        }
    }

    int pop() {
        if (!isEmpty()) {
            return arr[front++];
        }
        return -1; // Return -1 if queue is empty
    }
};

// BFS function
void bfs(int** adj, int numVertices, int start) {
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    Queue q(numVertices);
    q.push(start);
    visited[start] = true;

    while (!q.isEmpty()) {
        int vertex = q.pop();
        cout << "Visited: " << static_cast<char>('A' + vertex) << endl;

        for (int i = 0; i < numVertices; i++) {
            if (adj[vertex][i] > 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    delete[] visited;
}

// DFS function using a stack
void dfs(int** adj, int numVertices, int start) {
    vector<bool> visited(numVertices, false);
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int vertex = s.top();
        s.pop();

        if (!visited[vertex]) {
            visited[vertex] = true;
            cout << "Visited: " << static_cast<char>('A' + vertex) << endl;

            for (int i = numVertices - 1; i >= 0; i--) {
                if (adj[vertex][i] > 0 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
}

// Edge structure for Kruskal's algorithm
struct Edge {
    int src, dest, weight;
};

// Find the root of a vertex
int find(int u, vector<int>& parent) {
    if (parent[u] != u)
        parent[u] = find(parent[u], parent);
    return parent[u];
}

// Union two sets
void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = find(u, parent);
    int rootV = find(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Comparison function for sorting edges
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// Kruskal's algorithm
void kruskal(int numVertices, const vector<Edge>& edges) {
    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);
    for (int i = 0; i < numVertices; i++){
    	parent[i] = i;
	}

    vector<Edge> mst;
    int totalWeight = 0;

    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end(), compareEdges);

    for (const Edge& edge : sortedEdges) {
        int u = edge.src;
        int v = edge.dest;

        if (find(u, parent) != find(v, parent)) {
            unionSet(u, v, parent, rank);
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const Edge& edge : mst) {
        cout << static_cast<char>('A' + edge.src) << " -- "
             << static_cast<char>('A' + edge.dest) << " : "
             << edge.weight << endl;
    }
    cout << "Total Weight of Minimum Spanning Tree: " << totalWeight << endl;
}

// Find the vertex with the minimum key value for Prim's algorithm
int minKey(const vector<int>& key, const vector<bool>& included, int numVertices) {
    int min = numeric_limits<int>::max();
    int minIndex = -1;

    for (int v = 0; v < numVertices; v++) {
        if (!included[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Prim's algorithm to find the Minimum Spanning Tree
void prim(int numVertices, const vector<vector<int>>& graph) {
    vector<int> parent(numVertices, -1);
    vector<int> key(numVertices, numeric_limits<int>::max());
    vector<bool> included(numVertices, false);

    key[0] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, included, numVertices);
        included[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] > 0 && !included[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    int totalWeight = 0;
    for (int i = 1; i < numVertices; i++) {
        cout << static_cast<char>('A' + parent[i]) << " -- "
             << static_cast<char>('A' + i) << " : "
             << graph[parent[i]][i] << endl;
        totalWeight += graph[parent[i]][i];
    }
    cout << "Total Weight of Minimum Spanning Tree: " << totalWeight << endl;
}

//Main-Function
int main() {
    const int numVertices = 7;

    // Create an adjacency matrix
    int** adj = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adj[i] = new int[numVertices];
    }

    // Input the adjacency matrix
    cout << "Enter the adjacency matrix (7x7), use 'n' for no edge:\n";
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            string input;
            cin >> input; // Read input as string
            if (input == "n") {
                adj[i][j] = 0; // No edge
            } else {
                adj[i][j] = stoi(input); // Convert to integer
            }
        }
    }

    int choice;
    do {
        cout << "\nSelect an algorithm:\n";
        cout << "1. BFS\n";
        cout << "2. DFS\n";
        cout << "3. Kruskal's\n";
        cout << "4. Prim's\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Breadth-First Search starting from vertex A:\n";
                bfs(adj, numVertices, 0);
                break;
            }
            case 2: {
                cout << "Depth-First Search starting from vertex A:\n";
                dfs(adj, numVertices, 0);
                break;
            }
            case 3: {
                vector<Edge> edges;
                for (int i = 0; i < numVertices; i++) {
                    for (int j = i + 1; j < numVertices; j++) {
                        if (adj[i][j] > 0) {
                            edges.push_back({i, j, adj[i][j]});
                        }
                    }
                }
                cout << "Kruskal's algorithm:\n";
                kruskal(numVertices, edges);
                break;
            }
            case 4: {
                vector<vector<int>> graph(numVertices, vector<int>(numVertices, 0));
                for (int i = 0; i < numVertices; i++) {
                    for (int j = 0; j < numVertices; j++) {
                        graph[i][j] = adj[i][j];
                    }
                }
                cout << "Prim's algorithm:\n";
                prim(numVertices, graph);
                break;
            }
            case 5: {
                cout << "Exiting the program.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);
    
    // Clean up the adjacency matrix
    for (int i = 0; i < numVertices; i++) {
        delete[] adj[i];
    }
    delete[] adj;
    
    return 0;
}