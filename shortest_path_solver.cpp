#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Function to read a CSV file and return a matrix
vector<vector<int>> readCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            vector<int> row;
            int value;

            while (iss >> value) {
                row.push_back(value);
                if (iss.peek() == ',')
                    iss.ignore();
            }

            matrix.push_back(row);
        }
        file.close();
    }

    return matrix;
}

int main() {
    // Read test and cities graph matrices from CSV files
    vector<vector<int>> testGraphMatrix = readCSV("TestG.txt");
    vector<vector<int>> citiesGraphMatrix = readCSV("CitiesG.txt");

    // Create edges from matrices
    vector<Edge> testGraphEdges;
    vector<Edge> citiesGraphEdges;

    for (int i = 0; i < testGraphMatrix.size(); ++i) {
        for (int j = 0; j < testGraphMatrix[i].size(); ++j) {
            if (testGraphMatrix[i][j] != 0) {
                testGraphEdges.push_back(Edge(i, j, testGraphMatrix[i][j]));
            }
        }
    }

    for (int i = 0; i < citiesGraphMatrix.size(); ++i) {
        for (int j = 0; j < citiesGraphMatrix[i].size(); ++j) {
            if (citiesGraphMatrix[i][j] != 0) {
                citiesGraphEdges.push_back(Edge(i, j, citiesGraphMatrix[i][j]));
            }
        }
    }

    // Create test and cities graphs
    Graph testGraph(testGraphEdges, testGraphMatrix.size(), { "A", "B", "C", "D", "E", "F", "G" });
    Graph citiesGraph(citiesGraphEdges, citiesGraphMatrix.size(),
        { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N" });

    // Perform DFS and Dijkstra's algorithm on test and cities graphs
    testGraph.DFS(0);
    cout << endl;
    testGraph.Dijkstra(0);
    cout << endl;

    citiesGraph.DFS(0);
    cout << endl;
    citiesGraph.Dijkstra(0);
    cout << endl;

    return 0;
}
