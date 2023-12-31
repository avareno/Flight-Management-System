#include <iostream>
#include <fstream>
#include "Display.h"

Display::Display() {}

int Display::num_airports(Graph<Airports> *g) {
    return g->getVertexSet().size();
}

int Display::num_flights(Graph<Airports> *g) {
    int i = 0;
    for (Vertex<Airports> *v : g->getVertexSet()) {
        for (Edge<Airports> e : v->getAdj()) {
            i++;
        }
    }
    return i;
}

int Display::flights_per_airport(Graph<Airports> *g, Airports info, vector<Flights> &res) {
    int count = 0;
    Vertex<Airports> *v = g->findVertex(info);
    for (Edge<Airports> e:v->getAdj()) {
        res.emplace_back(v->getInfo().getCode(),e.getDest()->getInfo().getCode(),e.getAlCode());
        count++;
    }
    return count;
}

int Display::airlines_per_airport(Graph<Airports> *g, Airports info, set<string> &res) {
    Vertex<Airports> *v = g->findVertex(info);
    for (Edge<Airports> e:v->getAdj()) {
        res.insert(e.getAlCode());
    }
    return res.size();
}

int Display::countries_per_airport(Graph<Airports> *g, Airports info, set<string> &res) {
    Vertex<Airports> *v = g->findVertex(info);
    for (Edge<Airports> e:v->getAdj()) {
        res.insert(e.getDest()->getInfo().getCountry());
    }
    return res.size();
}

int Display::destinations_per_airport(Graph<Airports> *g, Airports info, string input, set<string> &res) {
    vector<Airports> destinations = g->dfs(info);
    if (input == "1") {
        for (Airports ap : destinations) {
            res.insert(ap.getCode());
        }
    }else if (input == "2") {
        for (Airports ap : destinations) {
            res.insert(ap.getCity());
        }
    }else if (input == "3") {
        for (Airports ap : destinations) {
            res.insert(ap.getCountry());
        }
    }
    return res.size();
}

int Display::destinations_per_airport(Graph<Airports> *g, Airports info, string input, set<string> &res, int max_distance) {
    return 0;
}

int Display::flights_per_city(Graph<Airports> *g, string city) {
    return 0;
}

int Display::countries_per_city(Graph<Airports> *g, string city) {
    return 0;
}

int Display::flights_per_airline(Graph<Airports> *g, string al_code) {
    return 0;
}

int Display::maximum_trip(Graph<Airports> *g, Airports soruce, Airports dest) {
    return 0;
}

int Display::greatest_capacity(Graph<Airports> *g, int pos) {
    return 0;
}

int Display::articulation_points(Graph<Airports> *g) {
    return 0;
}

