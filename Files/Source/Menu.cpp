//
// Created by avareno on 12/26/23.
//

#include "Menu.h"
#include <iostream>
using namespace std;

int Menu::getOption() const {
    return option;
}

void Menu::setOption(int option) {
    Menu::option = option;
}

Menu::Menu() {
    cout << "1. Add Airport" << endl;
    cout << "2. Add Flight" << endl;
    cout << "3. Display Airports" << endl;
    cout << "4. Display Flights" << endl;
    cout << "5. Exit" << endl;
}
