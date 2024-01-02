//
// Created by avareno on 12/28/23.
//

#ifndef PROJETO_AED_AUXILIARFUNCTIONS_HPP
#define PROJETO_AED_AUXILIARFUNCTIONS_HPP


#include "Graph.h"
#include "Airports.h"
#include "Flights.h"
#include "Airlines.h"

class AuxiliarFunctions {
public:
    bool findVertexCode(Graph<Airports> *g, string code, Airports &res);


    vector<vector<Airports>>
    best_flight(const Graph<Airports>* g, const Airports &source, const Airports &destination);

    bool findVertexCity(Graph<Airports> *g, string city, Airports &res);

    bool is_number(const string &input);

    bool is_upper(const string &text);

    float calculate_distance(float slong, float slat, float dlong, float dlat);

    void generateCombinationsChosenAirlinesCode(const vector<vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current, int depth,
                                                vector<string> &chosenAirlines);
    bool
    has_combination_airline_code(const vector<std::vector<Edge<Airports>>> &res, std::vector<Edge<Airports>> &current,
                                 int depth, const std::vector<std::string> &chosenAirlines);

    bool
    has_combination_airline_Number(const vector<vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current,
                                   int depth,
                                   int no_air, int count, string airline);

    void
    generateCombinationsChosenAirlinesNumber(const vector<vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current,
                                             int depth, int no_air, int count, string airline);
};


#endif //PROJETO_AED_AUXILIARFUNCTIONS_HPP







