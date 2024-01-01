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

class Display {
public:
    Display();
    int num_airports (Graph<Airports> *g);
    int num_flights (Graph<Airports> *g);
    int flights_per_airport(Graph<Airports> *g, Airports info, vector<Flights> &res);
    int airlines_per_airport(Graph<Airports> *g, Airports info, set<string> &res);
    int countries_per_airport(Graph<Airports> *g, Airports info, set<string> &res);

    int destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res);
    int destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res);

    int destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res, int max_distance);
    int destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res, int max_distance);

    int flights_per_city(Graph<Airports> *g, string city, vector<Flights> &res);
    int countries_per_city(Graph<Airports> *g, string city, set<string> &res);
    int flights_per_airline(Graph<Airports> *g, string al_code, vector<Flights> &res);
    int maximum_trip(Graph<Airports> *g, vector<pair<Airports,Airports>> &res);
    int articulation_points(Graph<Airports> *g);
    int bfs_max_distance(Graph<Airports> *g, const Airports &source, vector<pair<Airports,int>> &res);
};

#endif //PROJETO_AED_DISPLAY_H
