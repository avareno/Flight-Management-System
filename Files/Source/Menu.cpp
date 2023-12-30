//
// Created by avareno on 12/26/23.
//

#include "Menu.h"
#include "Airports.h"
#include "Flights.h"
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

bool Menu::is_number(const std::string &input) {
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

bool Menu::is_upper(const std::string &input) {
    for (char c : input) {
        if (!std::isupper(c)) {
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

        // Add Airport
        if (input == "1") {
            string AirCode, AirName, AirCity, AirCountry, Latitude, Longitude;

            cout << "Airport Code:" << endl;
            cout << ">> " ;
            cin >> AirCode;
            cout << endl;

            if(AirCode.length() != 3 || is_number(AirCode) || !is_upper(AirCode)) {
                cout << "Invalid input key" << endl;
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

        // Add Flight
        if (input == "2") {
            string source, target, AL_code;

            cout << "Source Airport Code:" << endl;
            cout << ">> " ;
            getline(cin >> ws,source);
            cout << endl;

            if(is_number(source)) {
                cout << "Invalid input key" << endl;
                return false;
            }

            cout << "Target Airport Code:" << endl;
            cout << ">> " ;
            getline(cin >> ws,target);
            cout << endl;

            if(is_number(target)) {
                cout << "Invalid input key" << endl;
                return false;
            }

            cout << "Airline Code:" << endl;
            cout << ">> " ;
            getline(cin >> ws,AL_code);
            cout << endl;

            if(is_number(AL_code)) {
                cout << "Invalid input key" << endl;
                return false;
            }

            Flights New = Flights(source, target, AL_code);
            double lat1, lon1, lat2, lon2;
            Airports s = Airports("a", "a", "a", "a", 0.0, 0.0);
            Airports t = Airports("a", "a", "a", "a", 0.0, 0.0);

            for (auto &airport : g.getVertexSet()) {
                if (airport->getInfo().getCode() == source) {
                    lat1 = airport->getInfo().getLatitude();
                    lon1 = airport->getInfo().getLongitude();
                    s = airport->getInfo();
                    airport->setOutdegree(airport->getOutdegree()+1);
                }
                else if (airport->getInfo().getCode() == target) {
                    lat2 = airport->getInfo().getLatitude();
                    lon2 = airport->getInfo().getLongitude();
                    t = airport->getInfo();
                    airport->setIndegree(airport->getIndegree()+1);
                }
            }
            /*
            if(g.addEdge(s, t, New.Haversine_d(lat1, lon1, lat2, lon2), AL_code))
                cout << "Flight from " << s.getName() << " to " << t.getName() << " added." << endl;

            else cout << "Impossible to add this flight";
            */
            return false;
        }

        // Display Airports and total number of Airports
        if (input == "3") {
            int n_airports = 0;
            for (auto airport : g.getVertexSet()){
                airport->getInfo().print();
                n_airports++;
            }
            cout << "\nGlobal number of Airports: " << n_airports << endl;
            return false;
        }

        // Display Flights and total number of Airports
        if (input == "4") {
            int n_flights = 0;
            for (auto airport : g.getVertexSet()){
                for (auto flights : airport->getAdj()){
                    cout << "Source: " << airport->getInfo().getName() << " | " << "Destiny: " << flights.getDest()->getInfo().getName() << endl;
                    n_flights++;
                }
            }
            cout << "\nGlobal number of Flights: " << n_flights << endl;
            return false;
        }

    //Search Option
    if(input == "5") {
        int n;
        cout << "Search:" << endl;
        cout << ">>1. Best Flights" << endl;
        cout << ">>2. Best FLights with filters" << endl;
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

                int res;

                cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                cin >> res;
                vector<vector<Airports>> allPaths = aux.best_flight(&g, s, d);
                if(res==1){
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
                }else if(res==2){

                    if (allPaths.size() == 0) {
                        cout << "No path found" << endl;
                    }else{
                        vector<Edge<Airports>> res;
                        cout << "Best Flight: " << endl;
                        for(auto path: allPaths){
                            Airports beg = path[0];
                            for(size_t i = 0; i < path.size()-1; ++i){
                                g.findVertex(path[i])->getEdge(g.findVertex(path[i+1]), res);
                            }
                            cout << beg.getName();
                            for(auto at: res){
                                cout << " -> " << at.getDest()->getInfo().getName() << " with " << at.getAlCode() << endl;
                            }
                        }
                    }
                }
                return false;

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
                    int res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;
                    for (auto path: allPaths) {
                        if (path.size() < min)min = path.size();
                    }
                    if(res==1) {
                        cout << "Best Flight: " << endl;
                        for (auto path: allPaths) {
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
                    }else if(res==2){
                        vector<Edge<Airports>> res;
                        cout << "Best Flight: " << endl;
                        for(auto path: allPaths){

                            if(path.size()==min) {
                                Airports beg = path[0];
                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), res);
                                }
                                cout << beg.getName();
                                for (auto at: res) {
                                    cout << " -> " << at.getDest()->getInfo().getName() << " with "
                                         << at.getAlCode() << endl;
                                }
                            }
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
                    int res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;
                    if(res==1) {
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
                    }else if(res==2){
                        vector<Edge<Airports>> res;
                        cout << "Best Flight: " << endl;
                        for(auto path: allPaths){
                            Airports beg = path[0];
                            for(size_t i = 0; i < path.size()-1; ++i){
                                g.findVertex(path[i])->getEdge(g.findVertex(path[i+1]), res);
                            }
                            cout << beg.getName();
                            for(auto at: res){
                                cout << " -> " << at.getDest()->getInfo().getName() << " with " << at.getAlCode() << endl;
                            }
                        }
                    }
                }

            }

        }else if (n==2){
            cout << "   >>Filter:" << endl;
            cout << "   >>1.Through Number of Airlines" << endl;
            cout << "   >>2.Through Name of Airlines" << endl;
            cout << "   >>3.Through Code of Airlines" << endl;
            cin >> n;

            if(n==1){

            }else if(n==2){

            }else if (n==3){

            }else{
                cout << "Invalid Input" << endl;
            }

        }


        return false;
    }

    // Exit Option
    if (input == "6") {return true;}


}

