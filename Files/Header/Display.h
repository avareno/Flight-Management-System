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
    int countries_per_airport(Graph<Airports> *g, Airports info);
    int destinations_per_airport(Graph<Airports> *g, Airports info);
    int destinations_per_airport(Graph<Airports> *g, Airports info, int max_distance);
    int flights_per_city(Graph<Airports> *g, string city);
    int countries_per_city(Graph<Airports> *g, string city);
    int flights_per_airline(Graph<Airports> *g, string al_code);
    int maximum_trip(Graph<Airports> *g, Airports soruce, Airports dest);
    int greatest_capacity(Graph<Airports> *g, int pos);
    int articulation_points(Graph<Airports> *g);
    //TODO: Acabar de identificar os atributos para cada função e definir todas as funções
};

#endif //PROJETO_AED_DISPLAY_H
