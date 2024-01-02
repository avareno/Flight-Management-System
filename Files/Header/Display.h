//
// Created by goncalo_feup on 28-11-2023.
//
#include "Graph.h"
#include "set"
#include "Airports.h"
#include "Airlines.h"
#include "Flights.h"
#ifndef PROJETO_AED_DISPLAY_H
#define PROJETO_AED_DISPLAY_H

using namespace std;

/**
 * @class Display class provide a way to obtain all the information that will be displayed after a certain option is chosen through the Menu.
 */

class Display {
public:
    Display();
    int num_airports (Graph<Airports> *g); ///< Complexity: O(n)
    int num_flights (Graph<Airports> *g); ///< Complexity: O(n²)
    int flights_per_airport(Graph<Airports> *g, Airports info, vector<Flights> &res); ///< Complexity: O(n)
    int airlines_per_airport(Graph<Airports> *g, Airports info, set<string> &res); ///< Complexity: O(n)
    int countries_per_airport(Graph<Airports> *g, Airports info, set<string> &res); ///< Complexity: O(n)

    int destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res); ///< Complexity: O(n)
    int destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res); ///< Complexity: O(n)

    int destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res, int max_distance); ///< Complexity: O(n)
    int destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res, int max_distance); ///< Complexity: O(n)

    int flights_per_city(Graph<Airports> *g, string city, vector<Flights> &res); ///< Complexity: O(n²)
    int countries_per_city(Graph<Airports> *g, string city, set<string> &res); ///< Complexity: O(n²)
    int flights_per_airline(Graph<Airports> *g, string al_code, vector<Flights> &res); ///< Complexity: O(n²)
    int maximum_trip(Graph<Airports> *g, vector<pair<Airports,Airports>> &res); ///< Complexity: O(n²)
    int articulation_points(Graph<Airports> *g); ///< Complexity: O(n)
    int bfs_max_distance(Graph<Airports> *g, const Airports &source, vector<pair<Airports,int>> &res); ///< Complexity: O(n)
};

#endif //PROJETO_AED_DISPLAY_H
