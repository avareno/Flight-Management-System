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

    vector<Flights> Airports_to_flights(vector<Airports>);

    int calculate_number_of_airlines(vector<Airports> res, Graph<Airports> *g);

    bool has_aili(string aili, vector<Airports> res, Graph<Airports> *g);

    Airlines findAirlineCode(vector<Airlines> *v, string alcode);

    void
    generateCombinations(const vector<std::vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current, int depth);

    void generateCombinationsChosenAirlines(const vector<vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current, int depth,
                                            vector<string> &chosenAirlines);
};


#endif //PROJETO_AED_AUXILIARFUNCTIONS_HPP
