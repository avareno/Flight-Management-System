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

using namespace std;

class Reader {
public:
    Reader();
    bool fileExists(const string& filename);
    void read_flights(Graph<Airports> *g);
    vector<Airlines> read_airlines(Graph<Airports> *g);
    void read_airports(Graph<Airports> *g);
    int Size(vector <string> something);
private:
    vector<Airports> All_Airports;
    // TODO: colocar grafos com info dos 'flights'
};

#endif //PROJETO_AED_READER_H
