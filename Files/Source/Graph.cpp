#include <iostream>
#include <queue>
#include <valarray>
#include <stack>
#include "Graph.h"

using namespace std;

Graph::Graph(int num, bool dir)
        : n(num), hasDir(dir), nodes(num+1) {}

void Graph::addEdge(const string& src, const string& dest, const string& al_code, double dist) {
    Edge newEdge;
    newEdge.src = src;
    newEdge.dest = dest;
    newEdge.al_code = al_code;
    newEdge.dist = dist;

    nodes[getNodeIndex(src)].adj.push_back(newEdge);

    // If the graph is undirected, add the edge in both directions
    if (!hasDir) {
        Edge reverseEdge;
        reverseEdge.src = dest;
        reverseEdge.dest = src;
        reverseEdge.al_code = al_code;
        reverseEdge.dist = dist;

        nodes[getNodeIndex(dest)].adj.push_back(reverseEdge);
    }
}

int Graph::getNodeIndex(const string& label) {
    for (int i = 0; i < n; ++i) {
        if (nodes[i].adj.size() > 0 && nodes[i].adj.front().src == label) {
            return i;
        }
    }
    return -1; // Node not found
}

void Graph::dfs(const string& startNode) {
    // Find the index of the start node
    int startIndex = getNodeIndex(startNode);
    if (startIndex == -1) {
        cout << "Start node not found in the graph." << endl;
        return;
    }

    // Reset visited flag for all nodes
    for (int i = 0; i < n; ++i) {
        nodes[i].visited = false;
    }

    // Create a stack for DFS
    stack<int> dfsStack;

    // Push the start node onto the stack
    dfsStack.push(startIndex);

    while (!dfsStack.empty()) {
        // Pop a vertex from the stack and print it
        int currentNodeIndex = dfsStack.top();
        dfsStack.pop();

        if (!nodes[currentNodeIndex].visited) {
            cout << "Visited node: " << nodes[currentNodeIndex].adj.front().src << endl;
            nodes[currentNodeIndex].visited = true;
        }

        // Visit all adjacent vertices of the current vertex and push them onto the stack if not visited
        for (const auto& edge : nodes[currentNodeIndex].adj) {
            int neighborIndex = getNodeIndex(edge.dest);
            if (neighborIndex != -1 && !nodes[neighborIndex].visited) {
                dfsStack.push(neighborIndex);
            }
        }
    }
}

void Graph::bfs(const string& startNode) {
    // Find the index of the start node
    int startIndex = getNodeIndex(startNode);
    if (startIndex == -1) {
        cout << "Start node not found in the graph." << endl;
        return;
    }

    // Reset visited flag for all nodes
    for (int i = 0; i < n; ++i) {
        nodes[i].visited = false;
    }

    // Create a queue for BFS
    queue<int> bfsQueue;

    // Mark the current node as visited and enqueue it
    nodes[startIndex].visited = true;
    bfsQueue.push(startIndex);

    while (!bfsQueue.empty()) {
        // Dequeue a vertex from the queue and print it
        int currentNodeIndex = bfsQueue.front();
        cout << "Visited node: " << nodes[currentNodeIndex].adj.front().src << endl;
        bfsQueue.pop();

        // Get all adjacent vertices of the dequeued vertex currentNodeIndex.
        // If an adjacent has not been visited, then mark it visited and enqueue it
        for (const auto& edge : nodes[currentNodeIndex].adj) {
            int neighborIndex = getNodeIndex(edge.dest);
            if (neighborIndex != -1 && !nodes[neighborIndex].visited) {
                nodes[neighborIndex].visited = true;
                bfsQueue.push(neighborIndex);
            }
        }
    }
}

int Graph::connectedComponents() {
    int counter = 0;

    // Reset visited flag for all nodes
    for (int v = 0; v < n; v++) {
        nodes[v].visited = false;
    }

    for (int v = 0; v < n; v++) {
        if (!nodes[v].visited) {
            counter++;
            cout << "Connected component: ";
            dfs(nodes[v].adj.front().src); // Call DFS from the current node
            cout << endl;
        }
    }
    return counter;
}

double Graph::Haversine_d(double &lat1, double& lon1, double &lat2, double& lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulas
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}