//
// Created by avareno on 12/28/23.
//

#ifndef PROJETO_AED_AUXILIARFUNCTIONS_HPP
#define PROJETO_AED_AUXILIARFUNCTIONS_HPP


#include "Graph.h"
#include "Airports.h"
#include "Flights.h"
#include "Airlines.h"

/**
 * @class AuxiliarFunctions class provide a way to perform auxiliary procedures for the basic research to be carried out.
 */

class AuxiliarFunctions {
public:
    bool findVertexCode(Graph<Airports> *g, string code, Airports &res); ///< Complexity: O(n)

    vector<vector<Airports>>
    best_flight(const Graph<Airports>* g, const Airports &source, const Airports &destination); ///< Complexity: O(n²)

    bool findVertexCity(Graph<Airports> *g, string city, Airports &res); ///< Complexity: O(n)

    bool is_number(const string &input); ///< Complexity: O(n)

    bool is_upper(const string &text); ///< Complexity: O(n)

    float calculate_distance(float slong, float slat, float dlong, float dlat); ///< Complexity: O(1)

    int calculate_number_of_airlines(vector<Airports> res, Graph<Airports> *g); ///< Complexity: O(n)

    bool has_aili(string aili, vector<Airports> res, Graph<Airports> *g); ///< Complexity: O(n)

    Airlines findAirlineCode(vector<Airlines> *v, string alcode); ///< Complexity: O(n)

    void generateCombinations(const vector<std::vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current, int depth); ///< Complexity: O(n³)

    void generateCombinationsChosenAirlinesCode(const vector<vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current, int depth,
                                                vector<string> &chosenAirlines); ///< Complexity: O(n³)

    bool has_combination_airline_code(const vector<std::vector<Edge<Airports>>> &res, std::vector<Edge<Airports>> &current,
                                 int depth, const std::vector<std::string> &chosenAirlines); ///< Complexity: O(n⁴)

    void generateCombinationsChosenAirlinesName(const vector<vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current,
                                           int depth, vector<string> &chosenAirlines); ///< Complexity: O(n³)

    bool has_combination_airline_name(const vector<std::vector<Edge<Airports>>> &res, vector<Edge<Airports>> &current, int depth,
                                 const vector<std::string> &chosenAirlines); ///< Complexity: O(n⁴)
};


#endif //PROJETO_AED_AUXILIARFUNCTIONS_HPP
