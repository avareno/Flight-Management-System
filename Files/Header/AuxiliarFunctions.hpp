//
// Created by avareno on 12/28/23.
//

#ifndef PROJETO_AED_AUXILIARFUNCTIONS_HPP
#define PROJETO_AED_AUXILIARFUNCTIONS_HPP


#include "Graph.h"
#include "Airports.h"

class AuxiliarFunctions {
public:
    bool findVertex(Graph<Airports> *g, string code, Airports &res);


    vector<vector<Airports>>
    findAllMinimumPaths(const Graph<Airports>* flightGraph, const Airports &source, const Airports &destination);
};


#endif //PROJETO_AED_AUXILIARFUNCTIONS_HPP
