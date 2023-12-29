//
// Created by avareno on 12/28/23.
//

#include "AuxiliarFunctions.hpp"
#include "Airports.h"
#include <iostream>
#include <queue>

using namespace std;

bool AuxiliarFunctions::findVertex(Graph<Airports>* g, string code, Airports &res) {
    for (auto v : g->getVertexSet()) {
        if (v->getInfo().getCode() == code) {
            res = v->getInfo();
            return true;
        }
    }
    return false;
}

int AuxiliarFunctions::bestflight(Graph<Airports>* g,Airports &source, Airports &dest ) {
    int count =0;
    auto s = g->findVertex(source);
    if (s == NULL)return -1;
    queue<Vertex<Airports> *> q;
    for (auto v : g->getVertexSet())
        v->setVisited(false);
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if(v->getInfo()==dest)break;
        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            if ( ! w->isVisited() ) {
                q.push(w);
                w->setVisited(true);
            }
        }
        count++;
    }
    return count;
}

vector<vector<Airports>> AuxiliarFunctions::findAllMinimumPaths(const Graph<Airports>& flightGraph, const Airports& source, const Airports& destination) {
    vector<vector<Airports>> allPaths;
    vector<Airports> currentPath;

    vector<Vertex<Airports>*> vertices = flightGraph.getVertexSet();
    Vertex<Airports>* sourceVertex = nullptr;
    Vertex<Airports>* destinationVertex = nullptr;

    for (auto vertex : vertices) {
        if (vertex->getInfo() == source) {
            sourceVertex = vertex;
        }
        if (vertex->getInfo() == destination) {
            destinationVertex = vertex;
        }
    }

    if (sourceVertex == nullptr || destinationVertex == nullptr) {
        cout << "Source or destination airport not found in the graph." << endl;
        return allPaths;  // Return an empty vector
    }

    queue<pair<Vertex<Airports>*, vector<Airports>>> bfsQueue;
    sourceVertex->setVisited(true);
    bfsQueue.push({sourceVertex, {source}});

    while (!bfsQueue.empty()) {
        auto currentPair = bfsQueue.front();
        auto currentVertex = currentPair.first;
        auto currentPath = currentPair.second;
        bfsQueue.pop();

        if (currentVertex == destinationVertex) {
            // Found a path to the destination
            if (allPaths.empty() || currentPath.size() < allPaths[0].size()) {
                allPaths.clear();
                allPaths.push_back(currentPath);
            } else if (currentPath.size() == allPaths[0].size()) {
                allPaths.push_back(currentPath);
            }
        }

        const vector<Edge<Airports>>& edges = currentVertex->getAdj();
        for (const Edge<Airports>& edge : edges) {
            auto neighborVertex = edge.getDest();
            if (!neighborVertex->isVisited()) {
                neighborVertex->setVisited(true);
                vector<Airports> newPath = currentPath;
                newPath.push_back(neighborVertex->getInfo());
                bfsQueue.push({neighborVertex, newPath});
            }
        }
    }

    // Reset visited status for all vertices after BFS
    for (auto vertex : vertices) {
        vertex->setVisited(false);
    }

    return allPaths;
}