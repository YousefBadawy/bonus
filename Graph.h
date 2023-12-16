#pragma once
#pragma once
#include <vector>
#include <string>
using namespace std;

const int Vmax = 50;
const int Emax = Vmax * (Vmax - 1) / 2;

class Edge {
public:
    int source, destination, weight;

    Edge(int src, int dest, int w) : source(src), destination(dest), weight(w) {}
};

class Graph {
public:
    // Constructor for the Graph class
    Graph(const vector<Edge>& edges, int numVertices, const vector<string>& cities);

    // Depth First Search traversal
    void DFS(int startCityIndex) const;

    // Dijkstra's algorithm for finding shortest paths
    void Dijkstra(int startCityIndex) const;

private:
    vector< vector<int>> adjacencyMatrix;
    vector<Edge> edges;
    vector< string> cities;

    // Helper function for DFS
    void DFSHelper(int cityIndex, vector<bool>& visited) const;

    // Helper function to get the index of the vertex with the minimum distance
    int getMinDistance(const vector<int>& distances, const vector<bool>& visited) const;

    // Helper function to print the path from source to destination
    void printPath(const vector<int>& parents, int currentCityIndex) const;
};
