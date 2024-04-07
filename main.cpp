/*Madushan Rajendran
 * 07/04/2024
 * This program takes input from a text file and converts it into a graph with BFS and DFS Traversal*/

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

// Function to read graph from file and create adjacency matrix
int** readGraph(string filename, int& numVertices) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Unable to open the file.\n";
        exit(1);
    }

    infile >> numVertices;
    int** adjMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            adjMatrix[i][j] = 0;
        }
    }

    int source, target, weight;
    while (infile >> source >> target >> weight) {
        adjMatrix[source][target] = weight;
    }

    infile.close();
    return adjMatrix;
}

void calculateDegrees(int** adjMatrix, int numVertices) {
    int* inDegree = new int[numVertices]();
    int* outDegree = new int[numVertices]();

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (adjMatrix[i][j] != 0) {
                ++outDegree[i];
                ++inDegree[j];
            }
        }
    }

    // Output in-degree and out-degree for each vertex
    cout << "Vertex\tIn-Degree\tOut-Degree\n";
    for (int i = 0; i < numVertices; ++i) {
        cout << i << "\t" << inDegree[i] << "\t\t" << outDegree[i] << endl;
    }

    delete[] inDegree;
    delete[] outDegree;
}

// Function to display adjacency matrix
void displayGraph(int** adjMatrix, int numVertices) {
    cout << "Adjacency Matrix:\n";
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            cout << adjMatrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Depth-First Search (DFS) Algorithm
void DFS(int** adjMatrix, int numVertices, int startVertex) {
    cout << "DFS Traversal: ";
    bool* visited = new bool[numVertices]();
    stack<int> stack;
    stack.push(startVertex);
    visited[startVertex] = true;

    while (!stack.empty()) {
        int currentVertex = stack.top();
        stack.pop();
        cout << currentVertex << " ";

        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[currentVertex][i] && !visited[i]) {
                stack.push(i);
                visited[i] = true;
            }
        }
    }

    delete[] visited;
}

// Breadth-First Search (BFS) Algorithm
void BFS(int** adjMatrix, int numVertices, int startVertex) {
    cout << "BFS Traversal: ";
    bool* visited = new bool[numVertices]();
    queue<int> queue;
    queue.push(startVertex);
    visited[startVertex] = true;

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        cout << currentVertex << " ";

        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[currentVertex][i] && !visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }

    delete[] visited;
}

int main() {

    string textfilename;
    cout << "Enter the filename: ";
    cin >> textfilename;
    string filename = "C:/Users/madus/Downloads/graphs/" + textfilename + ".txt";
    int numVertices;
    int** adjMatrix = readGraph(filename, numVertices);

    cout << "Graph read from file:\n";
    displayGraph(adjMatrix, numVertices);
    cout << endl;

    calculateDegrees(adjMatrix, numVertices);
    cout << endl;

    int dstartVertex;
    cout << "Enter the start vertex for DFS : ";
    cin >> dstartVertex;
    cout << endl;


    int bstartVertex;
    cout << "Enter the start vertex for BFS : ";
    cin >> bstartVertex;
    cout << endl;

    DFS(adjMatrix, numVertices, dstartVertex);
    cout << endl;
    BFS(adjMatrix, numVertices, bstartVertex);
    cout << endl;


    // Free allocated memory
    for (int i = 0; i < numVertices; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;

    return 0;
}
