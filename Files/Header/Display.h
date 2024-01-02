//
// Created by goncalo_feup on 28-11-2023.
//
#include "Graph.h"
#include "set"
#include "unordered_set"
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
    int num_airports (Graph<Airports> *g); ///< Check the number of existing airports. \n Complexity: O(n)
    int num_flights (Graph<Airports> *g); ///< Check the number of existing flights. \n Complexity: O(n²)
    int flights_per_airport(Graph<Airports> *g, Airports info, vector<Flights> &res); ///< Checks the number of flights at a specific airport. \n Complexity: O(n)
    int airlines_per_airport(Graph<Airports> *g, Airports info, set<string> &res); ///< Checks the number of airlines at a specific airport. \n Complexity: O(n)
    int countries_per_airport(Graph<Airports> *g, Airports info, set<string> &res); ///< Checks the number of countries an airport has flights to \n Complexity: O(n)

    int destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res); ///< Checks the number of destinations at a given airport. \n Complexity: O(n)
    int destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res); ///< Checks the number of destinations at a given airport. \n Complexity: O(n)

    int destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res, int max_distance); ///< Checks the number of destinations at a given airport in a specific distance. \n Complexity: O(n)
    int destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res, int max_distance); ///< Checks the number of destinations at a given airport in a specific distance. \n Complexity: O(n)

    int flights_per_city(Graph<Airports> *g, string city, vector<Flights> &res); ///< Checks the number of flights from a city. \n Complexity: O(n²)
    int countries_per_city(Graph<Airports> *g, string city, set<string> &res); ///< Checks the number of countries where there are flights from a city. \n Complexity: O(n²)
    int flights_per_airline(Graph<Airports> *g, string al_code, vector<Flights> &res); ///< Check the number of flights for an airline. \n Complexity: O(n²)
    int maximum_trip(Graph<Airports> *g, vector<pair<Airports,Airports>> &res); ///< Check the distance covered by the longest flight. \n Complexity: O(n²)
    int articulation_points(Graph<Airports> *g, vector<Airports> &res); ///< Check how many articulation points there are. \n Complexity: O(n)

    int bfs_max_distance(Graph<Airports> *g, const Airports &source, vector<pair<Airports,int>> &res); ///< Method to search for longer flight distance. \n Complexity: O(n)
    void dfs_art(Graph<Airports> *g, Vertex<Airports> *v, int &i, unordered_set<Vertex<Airports>*> &articulationPoints); ///< Method to search for articulation points. \n Complexity: O(n)
    };

#endif //PROJETO_AED_DISPLAY_H
