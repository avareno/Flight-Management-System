//
// Created by avareno on 12/28/23.
//

#include "AuxiliarFunctions.hpp"
#include "Airports.h"
#include <math.h>
#include <queue>

using namespace std;

bool AuxiliarFunctions::findVertexCode(Graph<Airports>* g, string code, Airports &res) {
    for (auto v : g->getVertexSet()) {
        if (v->getInfo().getCode() == code) {
            res = v->getInfo();
            return true;
        }
    }
    return false;
}

bool AuxiliarFunctions::findVertexCity(Graph<Airports>* g, string city, Airports &res) {
    for (auto v : g->getVertexSet()) {
        if (v->getInfo().getCity() == city) {
            res = v->getInfo();
            return true;
        }
    }
    return false;
}



vector<vector<Airports>> AuxiliarFunctions::best_flight(const Graph<Airports>* g, const Airports& source, const Airports& destination) {

    vector<vector<Airports>> allPaths;
    vector<Airports> currentPath;


    vector<Vertex<Airports>*> vertices = g->getVertexSet();
    Vertex<Airports>* sourceVertex = g->findVertex(source);
    Vertex<Airports>* destinationVertex = g->findVertex(destination);
    queue<pair<Vertex<Airports>*, vector<Airports>>> bfsQueue;

    for(auto vertex : vertices) {
        vertex->setVisited(false);
    }

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
            }//test why this verification

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

    return allPaths;
}


bool AuxiliarFunctions::is_number(const std::string &input) {
    bool hasDecimal = false;

    for (char c : input) {
        if (!std::isdigit(c)) {
            if ((c == '.' || c == ',') && !hasDecimal) {
                hasDecimal = true;
            } else {
                return false;
            }
        }
    }

    return true;
}

bool AuxiliarFunctions::is_upper(const string& text) {
    for (char c : text) {
        if (!isupper(c)) {
            return false;
        }
    }
    return true;
}


float AuxiliarFunctions::calculate_distance(float slong, float slat, float dlong, float dlat) {// usage of haversine formula
    float res;
    float fmem = pow(sin((dlat - slat) / 2),2);
    float smem = cos(slat) * cos(dlat) * pow(sin((dlong - slong) / 2), 2);
    res = 2 * atan2(sqrt(fmem + smem), sqrt(1 - fmem - smem));
    return res;
}