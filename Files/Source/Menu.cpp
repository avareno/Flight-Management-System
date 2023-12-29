//
// Created by avareno on 12/26/23.
//

#include "Menu.h"
#include "Airports.h"
#include <cstdlib>
#include <iostream>

using namespace std;

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

        if(AirCode.length() != 3 || aux.is_number(AirCode) || !aux.is_upper(AirCode)) {
            cout << "Invalid input key" << endl;
            system("CLS");
            return false;
        }

        cout << "Airport Name:" << endl;
        cout << ">> " ;
        getline(cin >> ws,AirName);
        cout << endl;

        if(aux.is_number(AirName)) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport City:" << endl;
        cout << ">> " ;
        getline(cin >> ws,AirCity);
        cout << endl;

        if(aux.is_number(AirCity)) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport Country:" << endl;
        cout << ">> " ;
        getline(cin >> ws,AirCountry);
        cout << endl;


        if(aux.is_number(AirCountry)) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport Latitude:" << endl;
        cout << ">> " ;
        cin >> Latitude;
        cout << endl;

        if(!aux.is_number(Latitude) || stod(Latitude)>90 || stod(Latitude)<-90) {
            cout << "Invalid input key" << endl;
            return false;
        }

        cout << "Airport Longitude:" << endl;
        cout << ">> " ;
        cin >> Longitude;
        cout << endl;

        if(!aux.is_number(Longitude) || stod(Longitude)>180 || stod(Longitude)<-180) {
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
            cout <<  "  >>1. Airports Codes" << endl;
            cout <<  "  >>2. Airports Cities" << endl;
            cout <<  "  >>3. Airport Coordinates" << endl;
            cin >> n;

            if(n==1){
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

                vector<vector<Airports>> allPaths = aux.best_flight(&g, s, d);
                if (allPaths.size() == 0) {
                    cout << "No path found" << endl;
                } else {
                    cout << "Best Flight: " << endl;
                    for (const auto &path: allPaths) {
                        for (size_t i = 0; i < path.size(); ++i) {
                            cout << path[i].getName();
                            if (i < path.size() - 1) {
                                cout << " -> ";
                            }
                        }
                        cout << endl;
                    }
                }
            }else if(n==2){
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


                Airports s, d;
                if (!aux.findVertexCity(&g, source, s) || !aux.findVertexCity(&g, dest, d)) {
                    cout << "Invalid Airport city" << endl;
                    return false;
                }


                int min = 1000;
                vector<vector<Airports>> allPaths = aux.best_flight(&g, s, d);
                if (allPaths.size() == 0) {
                    cout << "No path found" << endl;
                } else {
                    for (const auto &path: allPaths) {
                        if(path.size()<min)min = path.size();
                    }
                    cout << "Best Flight: " << endl;
                    for (const auto &path: allPaths) {
                        if(path.size()==min){
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



            }else if(n==3){
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
                vector<pair<Airports,float>> s,d;
                for(auto at : g.getVertexSet()){
                    float clong, clat;
                    clong = at->getInfo().getLongitude();
                    clat = at->getInfo().getLatitude();
                    float dis = aux.calculate_distance(slong, slat, clong, clat);
                    if(dis <= min1){
                        min1 = dis;
                        pair<Airports,float> r (at->getInfo(), min1);
                        s.push_back(r);
                    }
                }

                for(auto at : g.getVertexSet()){
                    float clong, clat;
                    clong = at->getInfo().getLongitude();
                    clat = at->getInfo().getLatitude();
                    float dis = aux.calculate_distance(dlong,dlat,clong,clat);
                    if(dis <= min2){
                        min2 = dis;
                        pair<Airports,float> r (at->getInfo(), min2);
                        d.push_back(r);
                    }
                }

                vector<vector<Airports>> allPaths;

                for(auto at: s){
                    if(at.second==min1){
                        for(auto at2: d){
                            if(at2.second==min2){
                                //allPaths=aux.best_flight(&g,at.first,at2.first);// problem for different sources and destinations
                                for (auto at3 : aux.best_flight(&g,at.first,at2.first)){
                                    allPaths.push_back(at3);
                                }
                            }
                        }
                    }
                }

                if (allPaths.size() == 0) {
                    cout << "No path found" << endl;
                } else {
                    cout << "Best Flight: " << endl;
                    for (const auto &path: allPaths) {
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
            return false;
        }

    }

    // Exit Option
    if (input == "6") {return true;}


}

