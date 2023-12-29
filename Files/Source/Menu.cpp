//
// Created by avareno on 12/26/23.
//

#include "Menu.h"
#include "Airports.h"
#include <cstdlib>
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
    cout << '\n';
    cout << "Select from one of the following options:" << endl;
    cout << "1. Add Airport" << endl;
    cout << "2. Add Flight" << endl;
    cout << "3. Display Airports" << endl;
    cout << "4. Display Flights" << endl;
    cout << "5. Search" << endl;
    cout << "6. Exit" << endl;
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

bool Menu::request(Graph<Airports> g) {
    string input;
    cout << ">> ";
    cin >> input;
    cout << '\n';
    if(input.length() != 1 || !isdigit(input[0])) {
        cout << "Invalid input key" << endl;
        return false;
    }

    if (input == "1") {
        string AirCode, AirName, AirCity, AirCountry, Latitude, Longitude;

        cout << "Airport Code:" << endl;
        cout << ">> " ;
        cin >> AirCode;
        cout << endl;

        if(AirCode.length() != 3 || is_number(AirCode) || !is_upper(AirCode)) {
            cout << "Invalid input key" << endl;
            system("CLS");
            return false;
        }

        cout << "Airport Name:" << endl;
        cout << ">> " ;
        getline(cin >> ws,AirName);
        cout << endl;

        if(is_number(AirName)) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport City:" << endl;
        cout << ">> " ;
        getline(cin >> ws,AirCity);
        cout << endl;

        if(is_number(AirCity)) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport Country:" << endl;
        cout << ">> " ;
        getline(cin >> ws,AirCountry);
        cout << endl;


        if(is_number(AirCountry)) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport Latitude:" << endl;
        cout << ">> " ;
        cin >> Latitude;
        cout << endl;

        if(!is_number(Latitude) || stod(Latitude)>90 || stod(Latitude)<-90) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport Longitude:" << endl;
        cout << ">> " ;
        cin >> Longitude;
        cout << endl;

        if(!is_number(Longitude) || stod(Longitude)>180 || stod(Longitude)<-180) {
            cout << "Invalid input key" << endl;
            return false;
        }

        /*
        Airports New = Airports(AirCode, AirName, AirCity, AirCountry, stod(Latitude), stod(Longitude));
        g.addVertex(New);
         */

        cout << "Airport " << AirName << " added." << endl;

        return false;
    }

    //Search Option
    if(input == "5") {
        int n;
        cout << "Search:" << endl;
        cout << ">>1. Best Flights" << endl;
        cout << ">>2. other options" << endl;
        cin >> n;
        if(n==1) {
            cout << "Source Airport code:" << endl;
            cout    << ">> ";
            string source;
            cin >> source;
            cout << endl;
            cout << "Destination Airport code:" << endl;
            cout    << ">> ";
            string dest;
            cin >> dest;
            cout << endl;

            Airports s,d;
            if(!aux.findVertex(&g,source,s) || !aux.findVertex(&g,dest,d)) {
                cout << "Invalid Airport code" << endl;
                return false;
            }





            // Print all possible minimum paths
            cout << "Best Flight: " << endl;
            vector<vector<Airports>> allPaths = aux.findAllMinimumPaths(&g,s,d);
            if(allPaths.size() == 0) {
                cout << "No path found" << endl;
            }else{
                for (const auto& path : allPaths) {
                    for (size_t i = 0; i < path.size(); ++i) {
                        cout << path[i].getName();
                        if (i < path.size() - 1) {
                            cout << " -> ";
                        }
                    }
                    cout << endl;

                }
            }


            return false;
        }

    }

    // Exit Option
    if (input == "6") {return true;}


}

