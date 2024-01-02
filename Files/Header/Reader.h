//
// Created by goncalo_feup on 28-11-2023.
//

#ifndef PROJETO_AED_READER_H
#define PROJETO_AED_READER_H

#include <string>
#include <vector>
#include "Airlines.h"
#include "Airports.h"
#include "Graph.h"
#include "Flights.h"
#include "AuxiliarFunctions.hpp"

using namespace std;

/**
 * @class Reader class provide a way to extract all the information from the dataset and place the information directly into a graph that will be used later for any type of research.
 */

class Reader {
public:
    Reader();
    bool fileExists(const string& filename); ///< Complexity: O(1)
    void read_flights(Graph<Airports> *g); ///< Complexity: O(n²)
    vector<Airlines> read_airlines(); ///< Complexity: O(n)
    void read_airports(Graph<Airports> *g); ///< Complexity: O(n)
private:
    vector<Airports> All_Airports;
    AuxiliarFunctions aux;
    // TODO: colocar grafos com info dos 'flights'
};

#endif //PROJETO_AED_READER_H
