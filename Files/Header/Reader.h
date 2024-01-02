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
    bool fileExists(const string& filename); ///< Checks if a file exists. \n Complexity: O(1)
    void read_flights(Graph<Airports> *g); ///< Extracts information about flights and creates edges in the graph with information about flights and their distance. \n Complexity: O(n²)
    vector<Airlines> read_airlines(); ///< Extracts information about airlines and saves them in a vector so that it can be used later. \n Complexity: O(n)
    void read_airports(Graph<Airports> *g); ///< Extracts information about airports and creates vertexes in the graph with information about each airport. \n Complexity: O(n)
private:
    vector<Airports> All_Airports;
    AuxiliarFunctions aux;
};

#endif //PROJETO_AED_READER_H
