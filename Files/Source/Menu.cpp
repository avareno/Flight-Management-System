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
            if(!findVertex(&g,source,s) || !findVertex(&g,dest,d)) {
                cout << "Invalid Airport code" << endl;
                return false;
            }


            cout << "Best Flight: " << endl;
            for(auto at : bestFlight(&g,s,d)) {
                cout <<at.getCode() << " -> ";
                cout << endl;

            }


        }

    }

    // Exit Option
    if (input == "6") {return true;}


}

bool Menu::findVertex(Graph<Airports>* g, string code, Airports &res) {
    for (auto v : g->getVertexSet()) {
        if (v->getInfo().getCode() == code) {
            res = v->getInfo();
            return true;
        }
    }
    return false;
}

vector<Airports> Menu::bestFlight(Graph<Airports>* g,Airports &source, Airports &dest ) {
    vector<Airports> res;
    auto s = g->findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<Airports> *> q;
    for (auto v : g->getVertexSet())
        v->setVisited(false);
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        if(v->getInfo()==dest)break;
        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            if ( ! w->isVisited() ) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}