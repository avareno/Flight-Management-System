//
// Created by avareno on 12/26/23.
//

#ifndef PROJETO_AED_MENU_H
#define PROJETO_AED_MENU_H


#include "Airports.h"
#include "AuxiliarFunctions.hpp"

class Menu {
public:
    Menu();
    int getOption() const;
    void setOption(int option);
    bool request(Graph<Airports> g);
private:
    int option;
    AuxiliarFunctions aux;
};


#endif //PROJETO_AED_MENU_H
