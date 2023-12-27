//
// Created by avareno on 12/26/23.
//

#include "Menu.h"
#include "Airports.h"
#include <iostream>
#include <algorithm>

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

bool is_number(const std::string &input) {
    bool hasDecimal = false;

    for (char c : input) {
        if (!std::isdigit(c)) {
            if ((c == '.' || c == ',') && !hasDecimal) {
                hasDecimal = true;
            } else {
                return false;
            }
        }
    }

    return true;
}

bool is_upper(const string& text) {
    for (char c : text) {
        if (!isupper(c)) {
            return false;
        }
    }
    return true;
}

void Menu::request(Graph<Airports> g) {
    string input;
    cout << ">> ";
    cin >> input;
    cout << '\n';
    if(input.length() != 1 || !isdigit(input[0])) {
        cout << "Invalid input key" << endl;
        return;
    }

    if (input == "1") {
        string AirCode, AirName, AirCity, AirCountry, Latitude, Longitude;

        cout << "Airport Code:" << endl;
        cout << ">> " ;
        cin >> AirCode;
        cout << endl;

        if(AirCode.length() != 3 || is_number(AirCode) || !is_upper(AirCode)) {
            cout << "Invalid input key" << endl;
            return;
        }

        cout << "Airport Name:" << endl;
        cout << ">> " ;
        cin >> AirName;
        cout << endl;

        if(is_number(AirName)) {
            cout << "Invalid input key" << endl;
            return;
        }

        cout << "Airport City:" << endl;
        cout << ">> " ;
        cin >> AirCity;
        cout << endl;

        if(is_number(AirCity)) {
            cout << "Invalid input key" << endl;
            return;
        }

        cout << "Airport Country:" << endl;
        cout << ">> " ;
        cin >> AirCountry;
        cout << endl;


        if(is_number(AirCountry)) {
            cout << "Invalid input key" << endl;
            return;
        }

        cout << "Airport Latitude:" << endl;
        cout << ">> " ;
        cin >> Latitude;
        cout << endl;

        if(!is_number(Latitude) || stod(Latitude)>90 || stod(Latitude)<-90) {
            cout << "Invalid input key" << endl;
            return;
        }

        cout << "Airport Longitude:" << endl;
        cout << ">> " ;
        cin >> Longitude;
        cout << endl;

        if(!is_number(Longitude) || stod(Longitude)>180 || stod(Longitude)<-180) {
            cout << "Invalid input key" << endl;
            return;
        }
        /*
        Airports New = Airports(AirCode, AirName, AirCity, AirCountry, stod(Latitude), stod(Longitude));
        g.addVertex(New);
         */

        cout << "Airport " << AirName << " added." << endl;

        return;
    }
}
