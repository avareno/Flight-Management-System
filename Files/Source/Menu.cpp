//
// Created by avareno on 12/26/23.
//
#include "Menu.h"
#include "Airports.h"
#include "Flights.h"
#include "Display.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <cstdint>

using namespace std;
Menu::Menu() {
    cout << '\n';
    cout << "Select from one of the following options:" << endl;
    cout << "1. Add Airport" << endl;
    cout << "2. Add Flight" << endl;
    cout << "3. Display Airports" << endl;
    cout << "4. Display Flights" << endl;
    cout << "5. Search" << endl;
    cout << "6. Statistics" << endl;
    cout << "7. Exit" << endl;
}
bool Menu::request(Graph<Airports> g,vector<Airlines> *als) {
    string input;
    cout << ">> ";
    cin >> input;
    cout << '\n';
    if (!aux.is_number(input) || stoi(input) > 7 || stoi(input) < 1) {
        cout << "Invalid input key" << endl;
        cout << '\n';
        return false;
    }
    // Add Airport
    if (input == "1") {
        string AirCode, AirName, AirCity, AirCountry, Latitude, Longitude;
        cout << "Airport Code:" << endl;
        cout << ">> ";
        cin >> AirCode;
        cout << endl;
        if (AirCode.length() != 3 || aux.is_number(AirCode) || !aux.is_upper(AirCode)) {
            cout << "Invalid input key" << endl;
            return false;
        }
        cout << "Airport Name:" << endl;
        cout << ">> ";
        getline(cin >> ws, AirName);
        cout << endl;
        if (aux.is_number(AirName)) {
            cout << "Invalid input key" << endl;
            return false;
        }
        cout << "Airport City:" << endl;
        cout << ">> ";
        getline(cin >> ws, AirCity);
        cout << endl;
        if (aux.is_number(AirCity)) {
            cout << "Invalid input key" << endl;
            return false;
        }
        cout << "Airport Country:" << endl;
        cout << ">> ";
        getline(cin >> ws, AirCountry);
        cout << endl;
        if (aux.is_number(AirCountry)) {
            cout << "Invalid input key" << endl;
            return false;
        }
        cout << "Airport Latitude:" << endl;
        cout << ">> ";
        cin >> Latitude;
        cout << endl;
        if (!aux.is_number(Latitude) || stod(Latitude) > 90 || stod(Latitude) < -90) {
            cout << "Invalid input key" << endl;
            return false;
        }
        cout << "Airport Longitude:" << endl;
        cout << ">> ";
        cin >> Longitude;
        cout << endl;
        if (!aux.is_number(Longitude) || stod(Longitude) > 180 || stod(Longitude) < -180) {
            cout << "Invalid input key" << endl;
            return false;
        }

        Airports New = Airports(AirCode, AirName, AirCity, AirCountry, stod(Latitude), stod(Longitude));
        g.addVertex(New);

        cout << "Airport " << AirName << " added." << endl;
        return false;
    }
    // Add Flight
    if (input == "2") {
        string source, target, AL_code;
        cout << "Source Airport Code:" << endl;
        cout << ">> ";
        getline(cin >> ws, source);
        cout << endl;
        if (source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
            cout << "Invalid input key" << endl;
            return false;
        }
        cout << "Target Airport Code:" << endl;
        cout << ">> ";
        getline(cin >> ws, target);
        cout << endl;
        if (target.length() != 3 || aux.is_number(target) || !aux.is_upper(target)) {
            cout << "Invalid input key" << endl;
            return false;
        }
        cout << "Airline Code:" << endl;
        cout << ">> ";
        getline(cin >> ws, AL_code);
        cout << endl;
        if (source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
            cout << "Invalid input key" << endl;
            return false;
        }
        Flights New = Flights(source, target, AL_code);
        double lat1, lon1, lat2, lon2;
        Airports s;
        Airports t;
        for (auto &airport: g.getVertexSet()) {
            if (airport->getInfo().getCode() == source) {
                lat1 = airport->getInfo().getLatitude();
                lon1 = airport->getInfo().getLongitude();
                s = airport->getInfo();
                airport->setOutdegree(airport->getOutdegree() + 1);
            } else if (airport->getInfo().getCode() == target) {
                lat2 = airport->getInfo().getLatitude();
                lon2 = airport->getInfo().getLongitude();
                t = airport->getInfo();
                airport->setIndegree(airport->getIndegree() + 1);
            }
        }

        if (g.addEdge(s, t, aux.calculate_distance(lat1, lon1, lat2, lon2), AL_code))
            cout << "Flight from " << s.getName() << " to " << t.getName() << " added." << endl;
        else cout << "Impossible to add this flight";

        return false;
    }
    // Display Airports
    if (input == "3") {
        for (auto airport: g.getVertexSet()) {
            airport->getInfo().print();
        }
        return false;
    }
    // Display Flights
    if (input == "4") {
        for (auto airport: g.getVertexSet()) {
            for (auto flights: airport->getAdj()) {
                cout << "Source: " << airport->getInfo().getName() << " | " << "Destiny: "
                     << flights.getDest()->getInfo().getName() << endl;
            }
        }
        return false;
    }
    //Search Option
    if (input == "5") {
        string n;
        cout << "Search:" << endl;
        cout << ">>1. Best Flights" << endl;
        cout << ">>2. Best FLights with filters" << endl;
        cout << ">> ";
        cin >> n;
        if (!aux.is_number(n) || stoi(n) > 2 || stoi(n) < 1) {
            cout << "Invalid input key" << endl;
            return false;
        }
        if (n == "1") {
            cout << "Type of input:" << endl;
            cout << "  >>1. Airports Codes" << endl;
            cout << "  >>2. Airports Cities" << endl;
            cout << "  >>3. Airport Coordinates" << endl;
            cin >> n;
            if (!aux.is_number(n) || stoi(n) > 3 || stoi(n) < 1) {
                cout << "Invalid input key" << endl;
                return false;
            }
            //CODE
            if (n == "1") {//code
                cout << "Source Airport code:" << endl;
                cout << ">> ";
                string source;
                cin >> source;
                if (source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << endl;
                cout << "Destination Airport code:" << endl;
                cout << ">> ";
                string dest;
                cin >> dest;
                if (dest.length() != 3 || aux.is_number(dest) || !aux.is_upper(dest)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << endl;
                Airports a1;
                Airports b1;
                for (auto &airport: g.getVertexSet()) {
                    if (airport->getInfo().getCode() == source) {
                        Airports a1 = airport->getInfo();
                    } else if (airport->getInfo().getCode() == dest) {
                        Airports b1 = airport->getInfo();
                        airport->setIndegree(airport->getIndegree() + 1);
                    }
                }
                if (!aux.findVertexCode(&g, source, a1) || !aux.findVertexCode(&g, dest, b1)) {
                    cout << "Invalid Airport code" << endl;
                    return false;
                }
                string res;
                cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl << "   >>";
                cin >> res;
                if (!aux.is_number(res) || stoi(res) > 2 || stoi(res) < 1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);
                vector<vector<Edge<Airports>>> resvector;
                if (res == "1") {
                    if (allPaths.size() == 0) {
                        cout << "No path found" << endl;
                    } else {
                        cout << "Best Flight: " << endl;
                        for (auto path: allPaths) {
                            for (size_t i = 0; i < path.size(); ++i) {
                                cout << path[i].getName();
                                if (i < path.size() - 1) {
                                    cout << " -> ";
                                }
                            }
                            cout << endl;
                        }
                    }
                }
                else if (res == "2") {
                    if (allPaths.size() == 0) {
                        cout << "No path found" << endl;
                    } else {
                        vector<Edge<Airports>> res;
                        cout << "Best Flight: " << endl;
                        for (auto path: allPaths) {
                            Airports beg = path[0];
                            for (size_t i = 0; i < path.size() - 1; ++i) {
                                g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                            }
                            cout << "From: " << beg.getName() << endl;
                            vector<Edge<Airports>> temp;
                            aux.generateCombinationsChosenAirlinesNumber(resvector, temp, 0, 100000, 0, "");
                        }
                    }
                }
            }
                //cities
            else if (n == "2") {//cities
                cout << "Source Airport City:" << endl;
                cout << ">> ";
                string source;
                cin.ignore();
                getline(cin, source);
                if (aux.is_number(source)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << endl;
                cout << "Destination Airport City:" << endl;
                cout << ">> ";
                string dest;
                getline(cin, dest);
                if (aux.is_number(dest)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << endl;
                Airports a1;
                Airports b1;
                vector<Airports> src;
                vector<Airports> dests;

                for (auto &airport: g.getVertexSet()) {
                    if (airport->getInfo().getCity() == source) {
                        a1 = airport->getInfo();
                        src.push_back(airport->getInfo());
                    } else if (airport->getInfo().getCity() == dest) {
                        b1 = airport->getInfo();
                        airport->setIndegree(airport->getIndegree() + 1);
                        dests.push_back(airport->getInfo());
                    }
                }
                if (!aux.findVertexCity(&g, source, a1) || !aux.findVertexCity(&g, dest, b1)) {
                    cout << "Invalid Airport city" << endl;
                }
                int min = INT64_MAX;
                vector<vector<vector<Airports>>> allairports;
                for  (auto at: src) {
                    for(auto at2: dests){
                        vector<vector<Airports>> allPaths = aux.best_flight(&g, at, at2);
                        allairports.push_back(allPaths);
                    }
                }
                int c = 1;
                for (auto allpath: allairports) {
                    c++;
                    if (allpath.size() == 0) {
                        cout << "No path found" << endl;
                    } else {
                        string res;
                        cout << c << "Airport" << endl;
                        cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                        cin >> res;
                        if (!aux.is_number(res) || stoi(res) > 2 || stoi(res) < 1) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }
                        for (auto path: allpath) {
                            if (path.size() < min)min = path.size();
                        }
                        if (res == "1") {
                            cout << "Best Flight: " << endl;
                            for (auto path: allpath) {
                                if (path.size() == min) {
                                    for (size_t i = 0; i < path.size(); ++i) {
                                        cout << path[i].getName();
                                        if (i < path.size() - 1) {
                                            cout << " -> ";
                                        }
                                    }
                                    cout << endl;
                                }
                            }
                        }
                        else if (res == "2") {
                            vector<vector<Edge<Airports>>> resvector;
                            cout << "Best Flight: " << endl;
                            for (auto path: allpath) {
                                if (path.size() == min) {
                                    Airports beg = path[0];
                                    for (size_t i = 0; i < path.size() - 1; ++i) {
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                    }
                                    cout << "From: " << beg.getName() << endl;
                                    vector<Edge<Airports>> temp;
                                    aux.generateCombinationsChosenAirlinesNumber(resvector, temp, 0, 100000, 0, "");
                                }
                            }
                        }
                    }
                }

            }
                //coordinates
            else if (n == "3") {//coordinates
                cout << "Source Latitude:" << endl;
                cout << ">> ";
                string slat;
                cin >> slat;
                if (!aux.is_number(slat) || stod(slat) > 90 || stod(slat) < -90) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << endl;
                cout << "Source Longitude:" << endl;
                cout << ">> ";
                string slong;
                cin >> slong;
                if (!aux.is_number(slong) || stod(slong) > 180 || stod(slong) < -180) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << endl;
                cout << "Destination Latitude:" << endl;
                cout << ">> ";
                string dlat;
                cin >> dlat;
                if (!aux.is_number(dlat) || stod(dlat) > 90 || stod(dlat) < -90) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << endl;
                cout << "Destination Longitude:" << endl;
                cout << ">> ";
                string dlong;
                cin >> dlong;
                cout << endl;
                if (!aux.is_number(dlong) || stod(dlong) > 180 || stod(dlong) < -180) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                float min1 = INT64_MAX, min2 = INT64_MAX;
                //search source airports
                vector<pair<Airports, float>> s, d;
                for (auto at: g.getVertexSet()) {
                    float clong, clat;
                    clong = at->getInfo().getLongitude();
                    clat = at->getInfo().getLatitude();
                    float dis = aux.calculate_distance(stof(slong), stof(slat), clong, clat);
                    if (dis <= min1) {
                        min1 = dis;
                        pair<Airports, float> r(at->getInfo(), min1);
                        s.push_back(r);
                    }
                }
                for (auto at: g.getVertexSet()) {
                    float clong, clat;
                    clong = at->getInfo().getLongitude();
                    clat = at->getInfo().getLatitude();
                    float dis = aux.calculate_distance(stof(dlong), stof(dlat), clong, clat);
                    if (dis <= min2) {
                        min2 = dis;
                        pair<Airports, float> r(at->getInfo(), min2);
                        d.push_back(r);
                    }
                }
                vector<vector<Airports>> allPaths;
                for (auto at: s) {
                    if (at.second == min1) {
                        for (auto at2: d) {
                            if (at2.second == min2) {
                                for (auto at3: aux.best_flight(&g, at.first, at2.first)) {
                                    allPaths.push_back(at3);
                                }
                            }
                        }
                    }
                }
                if (allPaths.size() == 0) {
                    cout << "No path found" << endl;
                } else {
                    string res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;
                    if (!aux.is_number(res) || stoi(res) > 2 || stoi(res) < 1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    if (res == "1") {
                        cout << "Best Flight: " << endl;
                        for (auto path: allPaths) {
                            for (size_t i = 0; i < path.size(); ++i) {
                                cout << path[i].getName();
                                if (i < path.size() - 1) {
                                    cout << " -> ";
                                }
                            }
                            cout << endl;
                        }
                    }
                    else if (res == "2") {
                        vector<vector<Edge<Airports>>> resvector;
                        cout << "Best Flight: " << endl;
                        for (auto path: allPaths) {
                            Airports beg = path[0];
                            for (size_t i = 0; i < path.size() - 1; ++i) {
                                g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                            }
                            cout << "From: " << beg.getName() << endl;
                            vector<Edge<Airports>> temp;
                            aux.generateCombinationsChosenAirlinesNumber(resvector, temp, 0, 100000, 0, "");
                        }
                    }
                }
            }
        }
        else if (n == "2") {
            cout << "   >>Filter:" << endl;
            cout << "   >>1.Through Number of Airlines" << endl;
            cout << "   >>2.Through Code of Airlines" << endl;
            cout << "  >>";
            cin >> n;
            if (!aux.is_number(n) || stoi(n) > 3 || stoi(n) < 1) {
                cout << "Invalid input key" << endl;
                return false;
            }
            //Number of airlines
            if (n == "1") {
                cout << "Type of input" << endl;
                cout << "  >>1. Airports Codes" << endl;
                cout << "  >>2. Airports Cities" << endl;
                cout << "  >>3. Airport Coordinates" << endl;
                cout << "  >>";
                cin >> n;
                if (!aux.is_number(n) || stoi(n) > 3 || stoi(n) < 1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                string no_air;
                cout << "Input number of airlines:" << endl;
                cin >> no_air;
                if (!aux.is_number(no_air) || stoi(no_air) < 1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                //airport codes
                if (n == "1") {
                    cout << "Source Airport code:" << endl;
                    cout << ">> ";
                    string source;
                    cin >> source;
                    if (source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    cout << endl;
                    cout << "Destination Airport code:" << endl;
                    cout << ">> ";
                    string dest;
                    cin >> dest;
                    if (dest.length() != 3 || aux.is_number(dest) || !aux.is_upper(dest)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    cout << endl;
                    Airports a1;
                    Airports b1;
                    for (auto &airport: g.getVertexSet()) {
                        if (airport->getInfo().getCode() == source) {
                            Airports a1 = airport->getInfo();
                        } else if (airport->getInfo().getCode() == dest) {
                            Airports b1 = airport->getInfo();
                            airport->setIndegree(airport->getIndegree() + 1);
                        }
                    }
                    if (!aux.findVertexCode(&g, source, a1) || !aux.findVertexCode(&g, dest, b1)) {
                        cout << "Invalid Airport code" << endl;
                        return false;
                    }
                    string res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;
                    if (!aux.is_number(res) || stoi(res) > 2 || stoi(res) < 1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);
                    vector<vector<Edge<Airports>>> resvector;

                    if (res == "1") {
                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            cout << "Best Flight: " << endl;
                            int r = 0;//flag
                            for (auto path: allPaths) {
                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                }
                                string f="";
                                vector<Edge<Airports>> temp;
                                if (aux.has_combination_airline_Number(resvector, temp, 0, stoi(no_air), 0,f)) {
                                    for (size_t i = 0; i < path.size(); ++i) {
                                        cout << path[i].getName();
                                        if (i < path.size() - 1) {
                                            cout << " -> ";
                                        }
                                    }
                                    r++;
                                }
                                cout << endl;
                            }
                            if (r == 0)cout << "No Paths found" << endl;
                        }
                    }
                    else if (res == "2") {
                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            int r = 0;//flag
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                Airports beg = path[0];
                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                }
                                cout << "From: " << beg.getName() << endl;
                                vector<Edge<Airports>> temp;
                                aux.generateCombinationsChosenAirlinesNumber(resvector, temp, 0, stoi(no_air), 0, "");

                            }
                        }
                    }
                }
                    //airport city
                else if (n == "2") {//Airport Cities
                    cout << "Source Airport City:" << endl;
                    cout << ">> ";
                    string source;
                    cin.ignore();
                    getline(cin, source);
                    if (aux.is_number(source)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    cout << endl;
                    cout << "Destination Airport City:" << endl;
                    cout << ">> ";
                    string dest;
                    getline(cin, dest);
                    if (aux.is_number(dest)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    cout << endl;
                    Airports a1;
                    Airports b1;
                    vector<Airports> src;
                    vector<Airports> dests;

                    for (auto &airport: g.getVertexSet()) {
                        if (airport->getInfo().getCity() == source) {
                            a1 = airport->getInfo();
                            src.push_back(airport->getInfo());
                        } else if (airport->getInfo().getCity() == dest) {
                            b1 = airport->getInfo();
                            airport->setIndegree(airport->getIndegree() + 1);
                            dests.push_back(airport->getInfo());
                        }
                    }
                    if (!aux.findVertexCity(&g, source, a1) || !aux.findVertexCity(&g, dest, b1)) {
                        cout << "Invalid Airport city" << endl;
                    }
                    int min = INT64_MAX;
                    vector<vector<vector<Airports>>> allairports;
                    for  (auto at: src) {
                        for(auto at2: dests){
                            vector<vector<Airports>> allPaths = aux.best_flight(&g, at, at2);
                            allairports.push_back(allPaths);
                        }
                    }
                    int c = 0;
                    for (auto allpath: allairports) {
                        c++;
                        if (allpath.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            string res;
                            vector<vector<Edge<Airports>>> resvector;
                            cout << c << " Airport" << endl;
                            cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                            cin >> res;
                            if (!aux.is_number(res) || stoi(res) > 2 || stoi(res) < 1) {
                                cout << "Invalid input key" << endl;
                                return false;
                            }
                            for (auto path: allpath) {
                                if (path.size() < min)min = path.size();
                            }
                            if (res == "1") {
                                cout << "Best Flight: " << endl;
                                for (auto path: allpath) {
                                    if (path.size() == min) {
                                        for (size_t i = 0; i < path.size() - 1; ++i) {
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                        }
                                        string f="";
                                        vector<Edge<Airports>> temp;
                                        if (aux.has_combination_airline_Number(resvector, temp, 0, stoi(no_air), 0,f)) {
                                            for (size_t i = 0; i < path.size(); ++i) {
                                                cout << path[i].getName();
                                                if (i < path.size() - 1) {
                                                    cout << " -> ";
                                                }
                                            }
                                        }
                                        cout << endl;

                                    }
                                }
                            }
                            else if (res == "2") {
                                vector<Edge<Airports>> res;
                                cout << "Best Flight: " << endl;
                                for (auto path: allpath) {
                                    if (path.size() == min) {
                                        Airports beg = path[0];

                                        for (size_t i = 0; i < path.size() - 1; ++i) {
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                        }
                                        cout << "From: " << beg.getName() << endl;
                                        vector<Edge<Airports>> temp;
                                        aux.generateCombinationsChosenAirlinesNumber(resvector, temp, 0, stoi(no_air), 0, "");

                                        cout << endl;
                                    }
                                }
                            }
                        }
                    }
                }
                    //location
                else if (n == "3") {//coordinates
                    cout << "Source Latitude:" << endl;
                    cout << ">> ";
                    string slat;
                    cin >> slat;
                    if (!aux.is_number(slat) || stod(slat) > 90 || stod(slat) < -90) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    cout << endl;
                    cout << "Source Longitude:" << endl;
                    cout << ">> ";
                    string slong;
                    cin >> slong;
                    if (!aux.is_number(slong) || stod(slong) > 180 || stod(slong) < -180) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    cout << endl;
                    cout << "Destination Latitude:" << endl;
                    cout << ">> ";
                    string dlat;
                    cin >> dlat;
                    if (!aux.is_number(dlat) || stod(dlat) > 90 || stod(dlat) < -90) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    cout << endl;
                    cout << "Destination Longitude:" << endl;
                    cout << ">> ";
                    string dlong;
                    cin >> dlong;
                    cout << endl;
                    if (!aux.is_number(dlong) || stod(dlong) > 180 || stod(dlong) < -180) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }
                    float min1 = INT64_MAX, min2 = INT64_MAX;//find better solution
                    //search source airports
                    vector<pair<Airports, float>> s, d;
                    for (auto at: g.getVertexSet()) {
                        float clong, clat;
                        clong = at->getInfo().getLongitude();
                        clat = at->getInfo().getLatitude();
                        float dis = aux.calculate_distance(stof(slong), stof(slat), clong, clat);
                        if (dis <= min1) {
                            min1 = dis;
                            pair<Airports, float> r(at->getInfo(), min1);
                            s.push_back(r);
                        }
                    }
                    for (auto at: g.getVertexSet()) {
                        float clong, clat;
                        clong = at->getInfo().getLongitude();
                        clat = at->getInfo().getLatitude();
                        float dis = aux.calculate_distance(stof(dlong), stof(dlat), clong, clat);
                        if (dis <= min2) {
                            min2 = dis;
                            pair<Airports, float> r(at->getInfo(), min2);
                            d.push_back(r);
                        }
                    }
                    vector<vector<Airports>> allPaths;
                    for (auto at: s) {
                        if (at.second == min1) {
                            for (auto at2: d) {
                                if (at2.second == min2) {
                                    for (auto at3: aux.best_flight(&g, at.first, at2.first)) {
                                        allPaths.push_back(at3);
                                    }
                                }
                            }
                        }
                    }
                    if (allPaths.size() == 0) {
                        cout << "No path found" << endl;
                    } else {
                        vector<vector<Edge<Airports>>> resvector;
                        string res;
                        cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                        cin >> res;
                        if (!aux.is_number(res) || stoi(res) > 2 || stoi(res) < 1) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }
                        if (res == "1") {
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {


                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                }
                                string f="";
                                vector<Edge<Airports>> temp;
                                if (aux.has_combination_airline_Number(resvector, temp, 0, stoi(no_air), 0,f)) {
                                    for (size_t i = 0; i < path.size(); ++i) {
                                        cout << path[i].getName();
                                        if (i < path.size() - 1) {
                                            cout << " -> ";
                                        }
                                    }
                                }
                                cout << endl;

                                cout << endl;
                            }
                        }
                        else if (res == "2") {
                            vector<Edge<Airports>> res;
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                Airports beg = path[0];
                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                }
                                cout << "From: " << beg.getName() << endl;
                                vector<Edge<Airports>> temp;
                                aux.generateCombinationsChosenAirlinesNumber(resvector, temp, 0, stoi(no_air), 0, "");

                            }
                        }
                    }

                }
            }
                //Code of airlines
            else if (n == "2") {
                cout << "Type of input" << endl;
                cout << "  >>1. Airports Codes" << endl;
                cout << "  >>2. Airports Cities" << endl;
                cout << "  >>3. Airport Coordinates" << endl;
                cout << "  >>";
                cin >> n;
                cout << endl;

                vector<string> airlines;
                string airline;
                int num = 0;
                cout << "number of airlines" << endl;
                cin >> num;
                if (num > 0)cout << endl << "Introduce airlines:" << endl;

                while (num--) {
                    cout << ">> ";
                    cin >> airline;
                    airlines.push_back(airline);
                }

                if (n == "1") {//Airport codes
                    cout << "Source Airport code:" << endl;
                    cout << ">> ";
                    string source;
                    cin >> source;
                    cout << endl;
                    cout << "Destination Airport code:" << endl;
                    cout << ">> ";
                    string dest;
                    cin >> dest;
                    cout << endl;

                    Airports s, d;
                    if (!aux.findVertexCode(&g, source, s) || !aux.findVertexCode(&g, dest, d)) {
                        cout << "Invalid Airport code" << endl;
                        return false;
                    }

                    int res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;
                    vector<vector<Airports>> allPaths = aux.best_flight(&g, s, d);

                    vector<vector<Edge<Airports>>> resvector;
                    if (res == 1) {//airport codes

                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            cout << "Best Flight: " << endl;
                            int r = 0;//flag
                            for (auto path: allPaths) {
                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                }

                                vector<Edge<Airports>> temp;
                                if (aux.has_combination_airline_code(resvector, temp, 0, airlines)) {
                                    for (size_t i = 0; i < path.size(); ++i) {
                                        cout << path[i].getName();
                                        if (i < path.size() - 1) {
                                            cout << " -> ";
                                        }
                                    }
                                    r++;

                                    cout << endl;
                                }

                            }
                            if (r == 0)cout << "No Paths found" << endl;
                        }
                    }
                    else if (res == 2) {

                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                Airports beg = path[0];
                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                }
                                cout << "From: " << beg.getName() << endl;
                                vector<Edge<Airports>> temp;
                                aux.generateCombinationsChosenAirlinesCode(resvector, temp, 0, airlines);
                            }

                        }
                    }
                }//done
                else if (n == "2") {//Airport Cities

                    cout << "Source Airport City:" << endl;
                    cout << ">> ";
                    string source;
                    cin.ignore();
                    getline(cin, source);
                    cout << endl;
                    cout << "Destination Airport City:" << endl;
                    cout << ">> ";
                    string dest;
                    getline(cin, dest);
                    cout << endl;

                    Airports a1;
                    Airports b1;
                    vector<Airports> src;
                    vector<Airports> dests;

                    for (auto &airport: g.getVertexSet()) {
                        if (airport->getInfo().getCity() == source) {
                            a1 = airport->getInfo();
                            src.push_back(airport->getInfo());
                        } else if (airport->getInfo().getCity() == dest) {
                            b1 = airport->getInfo();
                            airport->setIndegree(airport->getIndegree() + 1);
                            dests.push_back(airport->getInfo());
                        }
                    }
                    if (!aux.findVertexCity(&g, source, a1) || !aux.findVertexCity(&g, dest, b1)) {
                        cout << "Invalid Airport city" << endl;
                    }
                    int min = INT64_MAX;
                    vector<vector<vector<Airports>>> allairports;
                    for  (auto at: src) {
                        for(auto at2: dests){
                            vector<vector<Airports>> allPaths = aux.best_flight(&g, at, at2);
                            allairports.push_back(allPaths);
                        }
                    }
                    int c = 0;
                    for (auto allpath: allairports)
                    {
                        c++;
                        if (allpath.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            int res;
                            cout << c << " Airport" << endl;
                            cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                            cin >> res;
                            for (auto path: allpath) {
                                if (path.size() < min)min = path.size();
                            }
                            if (res == 1) {
                                cout << "Best Flight: " << endl;
                                for (auto path: allpath) {
                                    if (path.size() == min) {
                                        {
                                            for (size_t i = 0; i < path.size(); ++i) {
                                                cout << path[i].getName();
                                                if (i < path.size() - 1) {
                                                    cout << " -> ";
                                                }
                                            }
                                            cout << endl;
                                        }

                                    }

                                }
                            }
                            else if (res == 2) {
                                vector<vector<Edge<Airports>>> res;
                                cout << "Best Flight: " << endl;
                                int r = 0;//flag

                                for (auto path: allpath) {

                                    if (path.size() == min) {
                                        Airports beg = path[0];
                                        r++;
                                        for (size_t i = 0; i < path.size() - 1; ++i) {
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), res);
                                        }
                                        vector<Edge<Airports>> temp;
                                        aux.generateCombinationsChosenAirlinesCode(res, temp, 0, airlines);
                                    }
                                    cout << endl;
                                }

                                if (r == 0)cout << "No Paths Found" << endl;
                            }
                        }
                    }
                }//done
                else if (n == "3") {//coordinates
                    cout << "Source Latitude:" << endl;
                    cout << ">> ";
                    float slat;
                    cin >> slat;
                    cout << endl;
                    cout << "Source Longitude:" << endl;
                    cout << ">> ";
                    float slong;
                    cin >> slong;
                    cout << endl;

                    cout << "Destination Latitude:" << endl;
                    cout << ">> ";
                    float dlat;
                    cin >> dlat;
                    cout << endl;
                    cout << "Destination Longitude:" << endl;
                    cout << ">> ";
                    float dlong;
                    cin >> dlong;
                    cout << endl;

                    //create verification in case input is incorrect
                    //if latitude and longitude aren't in the globe?

                    float min1 = 1000000000, min2 = 1000000000;//find better solution

                    //search source airports
                    vector<pair<Airports, float>> s, d;
                    for (auto at: g.getVertexSet()) {
                        float clong, clat;
                        clong = at->getInfo().getLongitude();
                        clat = at->getInfo().getLatitude();
                        float dis = aux.calculate_distance(slong, slat, clong, clat);
                        if (dis <= min1) {
                            min1 = dis;
                            pair<Airports, float> r(at->getInfo(), min1);
                            s.push_back(r);
                        }
                    }

                    for (auto at: g.getVertexSet()) {
                        float clong, clat;
                        clong = at->getInfo().getLongitude();
                        clat = at->getInfo().getLatitude();
                        float dis = aux.calculate_distance(dlong, dlat, clong, clat);
                        if (dis <= min2) {
                            min2 = dis;
                            pair<Airports, float> r(at->getInfo(), min2);
                            d.push_back(r);
                        }
                    }

                    vector<vector<Airports>> allPaths;

                    for (auto at: s) {
                        if (at.second == min1) {
                            for (auto at2: d) {
                                if (at2.second == min2) {
                                    for (auto at3: aux.best_flight(&g, at.first, at2.first)) {
                                        allPaths.push_back(at3);
                                    }
                                }
                            }
                        }
                    }

                    if (allPaths.size() == 0) {
                        cout << "No path found" << endl;
                    } else {
                        int res;
                        cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                        cin >> res;
                        if (res == 1) {
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                for (size_t i = 0; i < path.size(); ++i) {
                                    cout << path[i].getName();
                                    if (i < path.size() - 1) {
                                        cout << " -> ";
                                    }
                                }
                                cout << endl;

                            }
                        } else if (res == 2) {
                            vector<vector<Edge<Airports>>> res;
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                Airports beg = path[0];
                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), res);
                                }
                                vector<Edge<Airports>> temp;
                                aux.generateCombinationsChosenAirlinesCode(res, temp, 0, airlines);


                            }
                        }
                    }

                }

            }
            else {
                cout << "Invalid Input" << endl;
                return false;
            }
            return false;
        }
        return false;
    }

    if (input == "6") {
        cout << '\n';
        cout << "Statistics:" << endl;
        cout << "  1. Airport Statistics" << endl;
        cout << "  2. City Statistics" << endl;
        cout << "  3. Airlines Statistics" << endl;
        cout << "  4. Total Number of Airports" << endl;
        cout << "  5. Total Number of Flights" << endl;
        cout << "  6. Maximum Trip" << endl;
        cout << "  7. Essential Airports (Articulation Points)" << endl;
        cout << "  8. Return to Menu" << endl;
        while (true) {
            cout << ">> ";
            cin >> input;
            if (!aux.is_number(input) || stoi(input) > 7 || stoi(input) < 1) {
                cout << "Invalid input key" << endl;
            } else { break; }
            cout << '\n';
        }
        if (input == "1") {
            cout << '\n';
            cout << "Airport Statistics:" << endl;
            cout << "  1. Flights per Airport" << endl;
            cout << "  2. Airlines per Airport" << endl;
            cout << "  3. Countries per Airport" << endl;
            cout << "  4. Reachable Destinations per Airport" << endl;
            cout << "  5. Greatest Capacity Airports" << endl;
            cout << "  6. Return to Menu" << endl;
            while (true) {
                cout << ">> ";
                cin >> input;
                if (!aux.is_number(input) || stoi(input) > 6 || stoi(input) < 1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                if (input.length() != 1 || !isdigit(input[0])) {
                    cout << "Invalid input key" << endl;
                    return false;
                } else { break; }
            }
            if (input == "1") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;
                if (aux.is_number(input) || input.length() != 3 || aux.is_number(input) || !aux.is_upper(input)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                Airports info;
                for (auto &airport: g.getVertexSet()) {
                    if (airport->getInfo().getCode() == input) {
                        Airports info = airport->getInfo();
                    }
                }
                if (aux.findVertexCode(&g, input, info)) {
                    vector<Flights> res;
                    cout << "The airport '" << info.getName() << "' has a total of: "
                         << display.flights_per_airport(&g, info, res) << " flights." << endl;

                    cout << '\n';
                } else {
                    cout << "Invalid Airport Code." << endl;
                    return false;
                }
            }
            if (input == "2") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;
                if (aux.is_number(input) || input.length() != 3 || aux.is_number(input) || !aux.is_upper(input)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                Airports info;
                for (auto &airport: g.getVertexSet()) {
                    if (airport->getInfo().getCode() == input) {
                        Airports info = airport->getInfo();
                    }
                }
                if (aux.findVertexCode(&g, input, info)) {
                    set<string> res;
                    cout << "The airport '" << info.getName() << "' has a total of: "
                         << display.airlines_per_airport(&g, info, res) << " airlines." << endl;

                } else {
                    cout << "Invalid Airport Code." << endl;
                    return false;
                }
            }

            if (input == "3") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;
                if (aux.is_number(input) || input.length() != 3 || aux.is_number(input) || !aux.is_upper(input)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                Airports info;
                for (auto &airport: g.getVertexSet()) {
                    if (airport->getInfo().getCode() == input) {
                        Airports info = airport->getInfo();
                    }
                }
                if (aux.findVertexCode(&g, input, info)) {
                    set<string> res;
                    cout << "The airport '" << info.getName() << "' flies to a total of: "
                         << display.countries_per_airport(&g, info, res) << " countries." << endl;
                } else {
                    cout << "Invalid Airport Code." << endl;
                    return false;
                }
            }

            if (input == "4") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;
                if (aux.is_number(input) || input.length() != 3 || aux.is_number(input) || !aux.is_upper(input)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';

                Airports info = Airports("a", "a", "a", "a", 0.0, 0.0);

                if (aux.findVertexCode(&g, input, info)) {
                    vector<Airports> res_ap;
                    set<string> res;
                    int max_distance;

                    cout << "Display:\n"
                            "  1. Reachable Airports\n"
                            "  2. Reachable Cities\n"
                            "  3. Reachable Countries\n"
                            ">> ";
                    string option;
                    cin >> option;
                    cout << '\n';

                    if (!aux.is_number(option) || stoi(option) > 3 || stoi(option) < 1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << "Do you wish to define a maximum number of stops (lay-overs)?\n"
                            "  1. Yes\n"
                            "  2. No\n"
                            ">> ";
                    string layovers;
                    cin >> layovers;
                    cout << '\n';

                    if (!aux.is_number(layovers) || stoi(layovers) > 2 || stoi(layovers) < 1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    if (layovers == "1") {
                        cout << "Input Maximum Number of Stops:\n"
                                ">> ";
                        string distance;
                        cin >> distance;
                        if (!aux.is_number(distance)) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }
                        max_distance = stoi(distance);
                    }

                    if (option == "1") {
                        if (layovers == "2")
                            cout << "The airport '" << info.getName() << "' can reach a total of: "
                                 << display.destinations_per_airport_ap(&g, info, res_ap) << " airports." << endl;
                        if (layovers == "1")
                            cout << "The airport '" << info.getName() << "' can reach a total of: "
                                 << display.destinations_per_airport_ap(&g, info, res_ap, max_distance)
                                 << " airports in " << max_distance << " stops." << endl;
                    } else if (option == "2") {
                        if (layovers == "2")
                            cout << "The airport '" << info.getName() << "' can reach a total of: "
                                 << display.destinations_per_airport_string(&g, info, "2", res) << " cities." << endl;
                        if (layovers == "1")
                            cout << "The airport '" << info.getName() << "' can reach a total of: "
                                 << display.destinations_per_airport_string(&g, info, "2", res, max_distance)
                                 << " cities in " << max_distance << " stops." << endl;
                    } else if (option == "3") {
                        if (layovers == "2")
                            cout << "The airport '" << info.getName() << "' can reach a total of: "
                                 << display.destinations_per_airport_string(&g, info, "3", res) << " countries."
                                 << endl;
                        if (layovers == "1")
                            cout << "The airport '" << info.getName() << "' can reach a total of: "
                                 << display.destinations_per_airport_string(&g, info, "3", res, max_distance)
                                 << " countries in " << max_distance << " stops." << endl;
                    }
                    if (option == "1") {
                        for (Airports dest: res_ap) {
                            dest.print();
                        }
                    } else {
                        for (string dest: res) {
                            cout << dest << endl;
                        }
                    }
                }
                    return false;
            }

            if (input == "5") {
                list<Vertex<Airports> *> leaderboard;
                for (Vertex<Airports> *v : g.getVertexSet()) {
                    leaderboard.push_back(v);
                }
                leaderboard.sort(Vertex<Airports>::CompareByDegree);
                cout << "Top 10 Leaderboard:" << endl;
                for (int i = 0; i <= 9; i++) {
                    auto it = leaderboard.begin();
                    advance(it, i);
                    cout << "  " << i+1 << ". " << (*it)->getInfo().getName() << " | "
                         << (*it)->getInfo().getCity() << " | "
                         << (*it)->getInfo().getCountry() << " | "
                         << (*it)->getOutdegree() + (*it)->getIndegree() << " flights ("
                         << (*it)->getIndegree() << " incoming and " << (*it)->getOutdegree()
                         << " outgoing)." << endl;
                }
                cout << '\n';

                while (true) {

                    cout << "Select from one of the following:\n"
                            "  1. Check Airport at N Position in the Leaderboard\n"
                            "  2. Return to Menu.\n"
                            ">> ";
                    cin >> input;
                    cout << '\n';

                    if (!aux.is_number(input) || stoi(input) > 2 || stoi(input) < 1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    if (input == "1") {
                        cout << "Input Leaderboard Position (1 - " << g.getVertexSet().size() << "):\n>> ";
                        cin >> input;
                        cout << '\n';
                        if (!aux.is_number(input) || stoi(input) > g.getVertexSet().size() || stoi(input) < 1) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }
                        auto it = leaderboard.begin();
                        advance(it, stoi(input) - 1);
                        cout << "  " << input << ". " << (*it)->getInfo().getName() << " | "
                             << (*it)->getInfo().getCity() << " | "
                             << (*it)->getInfo().getCountry() << " | "
                             << (*it)->getOutdegree() + (*it)->getIndegree() << " flights ("
                             << (*it)->getIndegree() << " incoming and " << (*it)->getOutdegree()
                             << " outgoing)." << endl;
                        cout << '\n';
                    } else if (input == "2") { break; }
                }
                return false;
            }

            if (input == "6") {
                return false;
            }

            return false;
        }

        if (input == "2") {
            cout << '\n';
            cout << "City Statistics:" << endl;
            cout << "  1. Flights per City" << endl;
            cout << "  2. Countries per City" << endl;
            cout << "  3. Return to Menu" << endl;
            while (true) {
                cout << ">> ";
                cin >> input;
                if (!aux.is_number(input) || stoi(input) > 3 || stoi(input) < 1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                if (input.length() != 1 || !isdigit(input[0])) {
                    cout << "Invalid input key" << endl;
                    return false;
                } else { break; }
            }
            if (input == "1") {
                cout << "Input City:\n>> ";
                cin >> input;
                if (aux.is_number(input)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                Airports info;
                for (auto &airport: g.getVertexSet()) {
                    if (airport->getInfo().getCity() == input) {
                        Airports info = airport->getInfo();
                    }
                }
                if (aux.findVertexCode(&g, input, info)) {
                    vector<Flights> res;
                    cout << "City '" << info.getCity() << "' has a total of: "
                         << display.flights_per_city(&g, info.getCity(), res) << " flights." << endl;

                    cout << '\n';
                } else {
                    cout << "Invalid City." << endl;
                    return false;
                }
            }
            if (input == "2") {
                cout << "Input City:\n>> ";
                cin >> input;
                if (aux.is_number(input)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                Airports info;
                for (auto &airport: g.getVertexSet()) {
                    if (airport->getInfo().getCity() == input) {
                        Airports info = airport->getInfo();
                    }
                }
                if (aux.findVertexCode(&g, input, info)) {
                    set<string> res;
                    cout << "City '" << info.getCity() << "' has flights to a total of: "
                         << display.countries_per_city(&g, info.getCity(), res) << " countries." << endl;

                    cout << '\n';
                } else {
                    cout << "Invalid City." << endl;
                    return false;
                }
            }

            if (input == "3") {
                return false;
            }

            return false;
        }

        if (input == "3") {
            cout << '\n';
            cout << "Airline Statistics:" << endl;
            cout << "  1. Flights per Airline" << endl;
            cout << "  2. Return to Menu" << endl;
            while (true) {
                cout << ">> ";
                cin >> input;
                if (!aux.is_number(input) || stoi(input) > 2 || stoi(input) < 1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                if (input.length() != 1 || !isdigit(input[0])) {
                    cout << "Invalid input key" << endl;
                    return false;
                } else { break; }
            }
            if (input == "1") {
                cout << "Input Airline Code:\n>> ";
                cin >> input;
                if (aux.is_number(input)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }
                cout << '\n';
                Airlines info = Airlines("a", "a", "a", "a");
                for (auto &airlines: *als) {
                    if (airlines.getCode() == input) {
                        Airlines info = airlines;
                    }
                }
                if (info.getCode() != "a" && info.getName() != "a" && info.getCountry() != "a" &&
                    info.getCallSign() != "a") {
                    vector<Flights> res;
                    cout << "Airline '" << info.getName() << "' has a total of: "
                         << display.flights_per_airline(&g, info.getCode(), res) << " flights." << endl;

                    cout << '\n';
                } else {
                    cout << "Invalid Airline Code." << endl;
                    return false;
                }

                if (input == "2") {
                    return false;
                }

                return false;
            }
        }

        if (input == "4") {
            cout << '\n';
            cout << "There are " << display.num_airports(&g) << " airports." << endl;
            return false;
        }
        if (input == "5") {
            cout << '\n';
            cout << "There are " << display.num_flights(&g) << " total flights." << endl;
            return false;
        }
        if (input == "6") {
            cout << '\n';
            cout << "Current Maximum Trips are:" << '\n';
            vector<pair<Airports,Airports>> res;
            int max_distance = display.maximum_trip(&g,res);
            for (pair<Airports,Airports> p : res) {
                cout << "  " << p.first.getName() << " | "
                     << p.first.getCity() << " | "
                     << p.first.getCountry() << " -> "
                     << p.second.getName() << " | "
                     << p.second.getCity() << " | "
                     << p.second.getCountry() << endl;
            }
            cout << "With " << max_distance << " stops." << endl;
            cout << '\n';

            return false;
        }
        if (input == "7") {
            vector<Airports> res;
            cout << "There are " << display.articulation_points(&g,res) << " airports that are essential to the network’s circulation capability." << endl;
            for (Airports ap : res) {
                ap.print();
            }
            cout << '\n';
            return false;
        }
    }
    // Exit Option
    if (input == "7") { return true; }
    return false;
}