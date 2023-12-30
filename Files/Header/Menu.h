//
// Created by avareno on 12/26/23.
//

#ifndef PROJETO_AED_MENU_H
#define PROJETO_AED_MENU_H


#include "Airports.h"
#include "Airlines.h"
#include "AuxiliarFunctions.hpp"
#include "Display.h"

class Menu {
public:
    Menu();
    bool is_number(const std::string &input);
    bool is_upper(const std::string &input);
    bool request(Graph<Airports> g,vector<Airlines> *als);
private:
    AuxiliarFunctions aux;
    Display display;
};


#endif //PROJETO_AED_MENU_H
