#include "Graph.h"
#include <iostream>
#include <climits>
#include <vector>
#include <stack>

Graph::Graph(const vector<Edge>& edges, int numVertices, const vector<string>& cities)
    : edges(edges), cities(cities) {

    // Initialize the adjacency matrix with zeros
    adjacencyMatrix.resize(Vmax, vector<int>(Vmax, 0));

    // Populate the adjacency matrix based on the edges
    for (const Edge& edge : edges) {
        adjacencyMatrix[edge.source][edge.destination] = edge.weight;
        adjacencyMatrix[edge.destination][edge.source] = edge.weight;
    }
}

void Graph::DFSHelper(int cityIndex, vector<bool>& visited) const {
    // Mark the current city as visited and print it
    visited[cityIndex] = true;
    cout << cities[cityIndex] << " ";

    // Recursive DFS for adjacent cities
    for (int i = 0; i < Vmax; ++i) {
        if (adjacencyMatrix[cityIndex][i] && !visited[i]) {
            DFSHelper(i, visited);
        }
    }
}

void Graph::DFS(int startCityIndex) const {
    vector<bool> visited(Vmax, false);
    cout << "DFS traversal starting from city " << cities[startCityIndex] << ":\n";
    DFSHelper(startCityIndex, visited);
    cout << "\n";
}

void Graph::Dijkstra(int startCityIndex) const {
    int numCities = cities.size();

    // Initialize distance, visited, and parent arrays
    vector<int> distances(numCities, INT_MAX);
    vector<bool> visited(numCities, false);
    vector<int> parents(numCities, -1);

    distances[startCityIndex] = 0;

    // Dijkstra's algorithm
    for (int i = 0; i < numCities - 1; ++i) {
        int minDistanceIndex = getMinDistance(distances, visited);
        visited[minDistanceIndex] = true;

        for (int j = 0; j < numCities; ++j) {
            if (!visited[j] && adjacencyMatrix[minDistanceIndex][j] &&
                distances[minDistanceIndex] != INT_MAX &&
                distances[minDistanceIndex] + adjacencyMatrix[minDistanceIndex][j] < distances[j]) {
                distances[j] = distances[minDistanceIndex] + adjacencyMatrix[minDistanceIndex][j];
                parents[j] = minDistanceIndex;
            }
        }
    }

    // Print shortest paths
    cout << "\nShortest Paths from Node " << cities[startCityIndex] << "\n";
    for (int i = 0; i < numCities; ++i) {
        cout << "" << distances[i] << " " << cities[startCityIndex];
        printPath(parents, i);
        cout << "\n";
    }
}

int Graph::getMinDistance(const vector<int>& distances, const vector<bool>& visited) const {
    int minDistance = INT_MAX, minDistanceIndex = -1;
    int numCities = distances.size();

    // Find the index of the vertex with the minimum distance
    for (int i = 0; i < numCities; ++i) {
        if (!visited[i] && distances[i] <= minDistance) {
            minDistance = distances[i];
            minDistanceIndex = i;
        }
    }

    return minDistanceIndex;
}

void Graph::printPath(const vector<int>& parents, int currentCityIndex) const {
    // Recursive function to print the path from source to destination
    if (parents[currentCityIndex] == -1) {
        return;
    }

    printPath(parents, parents[currentCityIndex]);
    cout << "" << cities[currentCityIndex];
}
