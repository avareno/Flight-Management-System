//
// Created by avareno on 12/26/23.
//

#ifndef PROJETO_AED_MENU_H
#define PROJETO_AED_MENU_H


#include "Airports.h"
#include "Airlines.h"
#include "AuxiliarFunctions.hpp"
#include "Display.h"

/**
 * @class Menu class provide a way to show the user the different search options available in an interactive way, where the user can select what they want.
 */

class Menu {
public:
    Menu();
    bool request(Graph<Airports> g,vector<Airlines> *als); ///< Displays the menu of choices for the user. \n Complexity: O(n⁴)
private:
    AuxiliarFunctions aux;
    Display display;
};


#endif //PROJETO_AED_MENU_H
