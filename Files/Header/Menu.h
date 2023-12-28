//
// Created by avareno on 12/26/23.
//

#ifndef PROJETO_AED_MENU_H
#define PROJETO_AED_MENU_H


#include "Airports.h"

class Menu {
public:
    Menu();
    int getOption() const;
    void setOption(int option);
    bool request(Graph<Airports> g);
private:
    int option;

    bool findVertex(Graph<Airports> *g, string code, Airports &res);

    vector<Airports> bestFlight(Graph<Airports> *g, Airports &source, Airports &dest);
};


#endif //PROJETO_AED_MENU_H
