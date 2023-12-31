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

bool Menu::request(Graph<Airports> g,vector<Airlines> *als) {
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
                cout << "Type of input:" << endl;
                cout <<  "  >>1. Airports Codes" << endl;
                cout <<  "  >>2. Airports Cities" << endl;
                cout <<  "  >>3. Airport Coordinates" << endl;
                cin >> n;

                if(n==1){//code
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
                            vector<vector<Edge<Airports>>> resvector;
                            cout << "Best Flight: " << endl;
                            for(auto path: allPaths){
                                Airports beg = path[0];
                                for(size_t i = 0; i < path.size()-1; ++i){
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i+1]), resvector);
                                }
                                cout << "From: " << beg.getName()<<endl;
                                vector<Edge<Airports>> temp;
                                aux.generateCombinations(resvector, temp, 0);
                                resvector={};
                                }
                            }
                        }
                    }
                else if(n==2){//cities
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
                            vector<vector<Edge<Airports>> >resvector;
                            cout << "Best Flight: " << endl;
                            for(auto path: allPaths){

                                if(path.size()==min) {
                                    Airports beg = path[0];
                                    for (size_t i = 0; i < path.size() - 1; ++i) {
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                    }
                                    cout << "From: " << beg.getName()<<endl;
                                    vector<Edge<Airports>> temp;
                                    aux.generateCombinations(resvector, temp, 0);

                                    resvector={};
                                }
                            }
                        }
                    }



                }
                else if(n==3){//coordinates
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
                            vector<vector<Edge<Airports>>> resvector;
                            cout << "Best Flight: " << endl;
                            for(auto path: allPaths){
                                Airports beg = path[0];
                                for(size_t i = 0; i < path.size()-1; ++i){
                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i+1]), resvector);
                                }
                                cout << "From: " << beg.getName()<<endl;
                                vector<Edge<Airports>> temp;
                                aux.generateCombinations(resvector, temp, 0);
                                resvector={};

                            }
                        }
                    }

                }

            }
            else if (n==2){
                cout << "   >>Filter:" << endl;
                cout << "   >>1.Through Number of Airlines" << endl;//minimum number of airlines
                cout << "   >>2.Through Code of Airlines" << endl;//only has this airline
                cout << "   >>3.Through Name of Airlines" << endl;//only has this airline
                cout << "  >>";

                cin >> n;

                if(n==1){// number of airlines

                    cout << "Type of input" << endl;
                    cout <<  "  >>1. Airports Codes" << endl;
                    cout <<  "  >>2. Airports Cities" << endl;
                    cout <<  "  >>3. Airport Coordinates" << endl;
                    cout << "  >>";
                    cin >> n;
                    int no_air;
                    cout << "Input number of airlines:" << endl;
                    cin >> no_air;
                    //loop infinito se input invalido

                    if(n==1) {
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

                        vector<vector<Edge<Airports>> >resvector;


                        if (res == 1) {//airport codes

                            if (allPaths.size() == 0) {
                                cout << "No path found" << endl;
                            } else {
                                cout << "Best Flight: " << endl;
                                int r = 0;//flag
                                for (auto path: allPaths) {
                                    int minair = aux.calculate_number_of_airlines(path, &g);
                                    if (minair <= no_air) {
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
                        else if (res == 2) {

                            if (allPaths.size() == 0) {
                                cout << "No path found" << endl;
                            } else {
                                int r = 0;//flag
                                cout << "Best Flight: " << endl;
                                for (auto path: allPaths) {
                                    Airports beg = path[0];
                                    int minair = aux.calculate_number_of_airlines(path, &g);
                                    if (minair <= no_air) {
                                        r++;
                                        for (size_t i = 0; i < path.size() - 1; ++i) {
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                        }
                                        cout << "From: " << beg.getName()<<endl;
                                        vector<Edge<Airports>> temp;
                                        aux.generateCombinations(resvector, temp, 0);
                                        resvector={};
                                    }
                                }
                                if(r==0){
                                    cout << "No Paths Found";
                                }
                            }
                        }
                    }
                    else if(n==2){//Airport Cities

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
                                        int minair = aux.calculate_number_of_airlines(path, &g);
                                        if(minair<=no_air) {
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
                            }else if(res==2){
                                vector<vector<Edge<Airports>>> resvector;
                                cout << "Best Flight: " << endl;
                                int r = 0;//flag

                                for(auto path: allPaths){

                                    if(path.size()==min) {
                                        Airports beg = path[0];
                                        int minair = aux.calculate_number_of_airlines(path, &g);
                                        if(minair<=no_air) {
                                            r++;
                                            for (size_t i = 0; i < path.size() - 1; ++i) {
                                                g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                            }
                                            cout << "From: " << beg.getName()<<endl;
                                            vector<Edge<Airports>> temp;
                                            aux.generateCombinations(resvector, temp, 0);
                                            resvector={};
                                        }
                                        cout << endl;
                                    }
                                }
                                if(r==0)cout << "No Paths Found" << endl;
                            }
                        }
                    }
                    else if(n==3){//coordinates
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
                                    int minair = aux.calculate_number_of_airlines(path, &g);
                                    if(minair<=no_air) {
                                        for (size_t i = 0; i < path.size(); ++i) {
                                            cout << path[i].getName();
                                            if (i < path.size() - 1) {
                                                cout << " -> ";
                                            }
                                        }
                                    }
                                    cout << endl;
                                }
                            }else if(res==2){
                                vector<vector<Edge<Airports>>> resvector;
                                cout << "Best Flight: " << endl;
                                for(auto path: allPaths){
                                    Airports beg = path[0];
                                    int minair = aux.calculate_number_of_airlines(path, &g);
                                    if(minair<=no_air) {
                                        for(size_t i = 0; i < path.size()-1; ++i){
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i+1]), resvector);
                                        }
                                    }
                                    cout << "From: " << beg.getName()<<endl;
                                    vector<Edge<Airports>> temp;
                                    aux.generateCombinations(resvector, temp, 0);



                                }
                            }
                        }

                    }//implement wrong inputs



                }
                else if(n==2){
                    cout << "Type of input" << endl;
                    cout <<  "  >>1. Airports Codes" << endl;
                    cout <<  "  >>2. Airports Cities" << endl;
                    cout <<  "  >>3. Airport Coordinates" << endl;
                    cout << "  >>";
                    cin >> n;
                    cout << endl;
                    cout << "Code of Airlines:" << endl;
                    cout << ">> ";
                    vector<string> airlines;
                    string airline;
                    int num=0;
                    cout << "number of airlines" << endl;
                    cin >> num;
                    if(num>0)cout << endl << "Introduce airlines:" << endl;

                    while(num--){
                        cout << ">> ";
                        cin >> airline;
                        airlines.push_back(airline);
                    }

                    if(n==1) {//Airport codes
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
                                    if(aux.has_combination_airline_code(resvector, temp, 0, airlines)) {
                                        for (size_t i = 0; i < path.size(); ++i) {
                                            cout << path[i].getName();
                                            if (i < path.size() - 1) {
                                                cout << " -> ";
                                            }
                                        }
                                        r++;

                                        cout << endl;
                                    }
                                    resvector={};

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
                                    resvector={};
                                    cout << "From: " << beg.getName()<<endl;
                                    vector<Edge<Airports>> temp;
                                    aux.generateCombinationsChosenAirlinesCode(resvector, temp, 0, airlines);
                                    resvector={};
                                }


                            }
                        }
                    }
                    else if(n==2){//Airport Cities

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
                                            {
                                                vector<vector<Edge<Airports>>> resvector;
                                                for (size_t i = 0; i < path.size() - 1; ++i) {
                                                    g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                                }
                                                vector<Edge<Airports>> temp;
                                                if(aux.has_combination_airline_code(resvector, temp, 0, airlines)) {
                                                    for (size_t i = 0; i < path.size(); ++i) {
                                                        cout << path[i].getName();
                                                        if (i < path.size() - 1) {
                                                            cout << " -> ";
                                                        }
                                                    }
                                                }
                                                resvector={};
                                                cout << endl;
                                            }

                                        }

                                }
                            }
                            else if(res==2){
                                vector<vector<Edge<Airports>>> resvector;
                                cout << "Best Flight: " << endl;
                                int r = 0;//flag

                                for(auto path: allPaths){

                                    if(path.size()==min) {
                                        Airports beg = path[0];
                                            r++;
                                            for (size_t i = 0; i < path.size() - 1; ++i) {
                                                g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                            }
                                            vector<Edge<Airports>> temp;
                                        aux.generateCombinationsChosenAirlinesCode(resvector, temp, 0, airlines);
                                        }
                                        resvector={};
                                        cout << endl;
                                    }

                                if(r==0)cout << "No Paths Found" << endl;
                            }
                        }
                    }
                    else if(n==3){//coordinates
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
                                    vector<vector<Edge<Airports>>> resvector;
                                    for (size_t i = 0; i < path.size() - 1; ++i) {
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                    }
                                    vector<Edge<Airports>> temp;
                                    if(aux.has_combination_airline_code(resvector, temp, 0, airlines)) {
                                        for (size_t i = 0; i < path.size(); ++i) {
                                            cout << path[i].getName();
                                            if (i < path.size() - 1) {
                                                cout << " -> ";
                                            }
                                        }
                                    }
                                    resvector={};
                                    cout << endl;

                                }
                            }else if(res==2){
                                vector<vector<Edge<Airports>> >resvector;
                                cout << "Best Flight: " << endl;
                                for(auto path: allPaths){
                                    Airports beg = path[0];
                                    for(size_t i = 0; i < path.size()-1; ++i){
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i+1]), resvector);
                                    }
                                    vector<Edge<Airports>> temp;
                                    aux.generateCombinationsChosenAirlinesCode(resvector, temp, 0, airlines);
                                    resvector={};


                                }
                            }
                        }

                    }
                    //implement wrong inputs
                }
                else if (n==3){
                    cout << "Type of input" << endl;
                    cout <<  "  >>1. Airports Codes" << endl;
                    cout <<  "  >>2. Airports Cities" << endl;
                    cout <<  "  >>3. Airport Coordinates" << endl;
                    cout << "  >>";
                    cin >> n;
                    cout << endl;
                    cout << "Name of Airlines:" << endl;
                    cout << ">> ";
                    vector<string> airlines;
                    string airline;
                    int num=0;
                    cout << "number of airlines" << endl;
                    cin >> num;
                    if(num>0)cout << endl << "Introduce airlines:" << endl;

                    while(num--){
                        cout << ">> ";
                        cin >> airline;
                        airlines.push_back(airline);
                    }

                    if(n==1) {//Airport codes
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
                        if (res == 1) {//see city

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
                                    if(aux.has_combination_airline_name(resvector, temp, 0, airlines)) {
                                        for (size_t i = 0; i < path.size(); ++i) {
                                            cout << path[i].getName();
                                            if (i < path.size() - 1) {
                                                cout << " -> ";
                                            }
                                        }
                                        r++;

                                        cout << endl;
                                    }
                                    resvector={};

                                }
                                if (r == 0)cout << "No Paths found" << endl;
                            }
                        }
                        else if (res == 2) {//see flights

                            if (allPaths.size() == 0) {
                                cout << "No path found" << endl;
                            } else {
                                cout << "Best Flight: " << endl;
                                for (auto path: allPaths) {
                                    Airports beg = path[0];
                                    for (size_t i = 0; i < path.size() - 1; ++i) {
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                    }
                                    resvector={};
                                    cout << "From: " << beg.getName()<<endl;
                                    vector<Edge<Airports>> temp;
                                    aux.generateCombinationsChosenAirlinesName(resvector, temp, 0, airlines);
                                    //create func to check if found anything or not and print Not founf case not found
                                }

                            }
                        }
                    }
                    else if(n==2){//Airport Cities

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
                            if(res==1) {// see cities
                                cout << "Best Flight: " << endl;
                                for (auto path: allPaths) {
                                    if (path.size() == min) {
                                        {
                                            vector<vector<Edge<Airports>>> resvector;
                                            for (size_t i = 0; i < path.size() - 1; ++i) {
                                                g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                            }
                                            vector<Edge<Airports>> temp;
                                            if(aux.has_combination_airline_name(resvector, temp, 0, airlines)) {
                                                for (size_t i = 0; i < path.size(); ++i) {
                                                    cout << path[i].getName();
                                                    if (i < path.size() - 1) {
                                                        cout << " -> ";
                                                    }
                                                }
                                            }
                                            resvector={};
                                            cout << endl;
                                        }

                                    }

                                }
                            }
                            else if(res==2){
                                vector<vector<Edge<Airports>>> resvector;
                                cout << "Best Flight: " << endl;
                                int r = 0;//flag

                                for(auto path: allPaths){

                                    if(path.size()==min) {
                                        Airports beg = path[0];
                                        r++;
                                        for (size_t i = 0; i < path.size() - 1; ++i) {
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                        }
                                        vector<Edge<Airports>> temp;
                                        aux.generateCombinationsChosenAirlinesName(resvector, temp, 0, airlines);
                                    }
                                    resvector={};
                                    cout << endl;
                                }

                                if(r==0)cout << "No Paths Found" << endl;
                            }
                        }
                    }
                    else if(n==3){//coordinates
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
                                    vector<vector<Edge<Airports>>> resvector;
                                    for (size_t i = 0; i < path.size() - 1; ++i) {
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                    }
                                    vector<Edge<Airports>> temp;
                                    if(aux.has_combination_airline_name(resvector, temp, 0, airlines)) {
                                        for (size_t i = 0; i < path.size(); ++i) {
                                            cout << path[i].getName();
                                            if (i < path.size() - 1) {
                                                cout << " -> ";
                                            }
                                        }
                                    }
                                    resvector={};
                                    cout << endl;

                                }
                            }
                            else if(res==2){
                                vector<vector<Edge<Airports>> >resvector;
                                cout << "Best Flight: " << endl;
                                for(auto path: allPaths){
                                    Airports beg = path[0];
                                    for(size_t i = 0; i < path.size()-1; ++i){
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i+1]), resvector);
                                    }
                                    vector<Edge<Airports>> temp;
                                    aux.generateCombinationsChosenAirlinesName(resvector, temp, 0, airlines);
                                    resvector={};


                                }
                            }
                        }

                    }
                    //implement wrong inputs
                }
                else{
                    cout << "Invalid Input" << endl;
                }

            }


            return false;
        }

    if (input == "6") {
        cout << '\n';
        cout << "Statistics:" << endl;
        cout << "  1. Airport Statistics" << endl;
        cout << "  2. City Statistics" << endl;
        cout << "  3. Airline Statistics" << endl;
        cout << "  4. Total Number of Airports"  << endl;
        cout << "  5. Total Number of Flights" << endl;
        cout << "  6. Return to Menu" << endl;
        while (true) {
            cout << ">> ";
            cin >> input;
            cout << '\n';

            if(!aux.is_number(input) || stoi(input)>6 || stoi(input)<1) {
                cout << "Invalid input key" << endl;
            }else{break;}
            cout << '\n';
        }
        if (input == "1") {
            cout << "Airport Statistics:" << endl;
            cout << "  1. Flights per Airport" << endl;
            cout << "  2. Airlines per Airport" << endl;
            cout << "  3. Countries per Airport" << endl;
            cout << "  4. Reachable Destinations per Airport"  << endl;
            cout << "  5. Return to Menu" << endl;
            while (true) {
                cout << ">> ";
                cin >> input;

                if(!aux.is_number(input) || stoi(input)>5 || stoi(input)<1) {
                    cout << "Invalid input key" << endl;
                }else{break;}
                cout << '\n';
            }
            if (input == "1") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;

                cout << '\n';
                Airports info = Airports("a", "a", "a", "a", 0.0, 0.0);

                if (aux.findVertexCode(&g, input, info)) {
                    vector<Flights> res;
                    cout << "The airport '" << info.getName() << "' has a total of: " <<  display.flights_per_airport(&g,info,res) << " flights." << endl;
                    for (Flights f:res) {
                        f.print();
                    }
                    cout << '\n';
                }else{
                    cout << "Invalid Airport Code." << endl;
                    return false;
                }
            }
            if (input == "2") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;

                cout << '\n';
                Airports info = Airports("a", "a", "a", "a", 0.0, 0.0);

                if (aux.findVertexCode(&g, input, info)) {
                    set<string> res;
                    cout << "The airport '" << info.getName() << "' has a total of: " <<  display.airlines_per_airport(&g,info,res) << " airlines." << endl;
                    for (string al_code:res) {
                        aux.findAirlineCode(als,al_code).print();
                        cout << '\n';
                    }
                }else{
                    cout << "Invalid Airport Code." << endl;
                    return false;
                }
            }
            if (input == "3") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;

                cout << '\n';
                Airports info = Airports("a", "a", "a", "a", 0.0, 0.0);

                if (aux.findVertexCode(&g, input, info)) {
                    set<string> res;
                    cout << "The airport '" << info.getName() << "' flies to: " <<  display.countries_per_airport(&g,info,res) << " countries." << endl;
                    for (string country : res) {
                        cout << country << endl;
                    }
                }else{
                    cout << "Invalid Airport Code." << endl;
                    return false;
                }
            }
            if (input == "4") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;
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

                    if(!aux.is_number(option) || stoi(option)>3 || stoi(option)<1) {
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

                    if(!aux.is_number(layovers) || stoi(layovers)>2 || stoi(layovers)<1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    if (layovers == "1") {
                        cout << "Input Maximum Number of Stops:\n"
                                ">> ";
                        string distance;
                        cin >> distance;
                        if(!aux.is_number(distance)) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }
                        max_distance = stoi(distance);
                    }

                    if (option == "1") {
                        if (layovers == "2")
                            cout << "The airport '" << info.getName() << "' can reach a total of: " << display.destinations_per_airport_ap(&g,info,res_ap) << " airports." << endl;
                        if (layovers == "1")
                            cout << "The airport '" << info.getName() << "' can reach a total of: " << display.destinations_per_airport_ap(&g,info,res_ap,max_distance) << " airports in " << max_distance << " stops." << endl;
                    }else if(option == "2") {
                        if (layovers == "2")
                            cout << "The airport '" << info.getName() << "' can reach a total of: " << display.destinations_per_airport_string(&g,info,"2",res) << " cities." << endl;
                        if (layovers == "1")
                            cout << "The airport '" << info.getName() << "' can reach a total of: " << display.destinations_per_airport_string(&g,info,"2",res,max_distance) << " cities in " << max_distance << " stops." << endl;
                    }else if(option == "3") {
                        if (layovers == "2")
                            cout << "The airport '" << info.getName() << "' can reach a total of: " << display.destinations_per_airport_string(&g,info,"3",res) << " countries." << endl;
                        if (layovers == "1")
                            cout << "The airport '" << info.getName() << "' can reach a total of: " << display.destinations_per_airport_string(&g,info,"3",res,max_distance) << " countries in " << max_distance << " stops." << endl;
                    }
                    if(option == "1") {
                        for (Airports dest : res_ap) {
                            dest.print();
                        }
                    }else {
                        for (string dest : res) {
                            cout << dest << endl;
                        }
                    }
                }else{
                    cout << "Invalid Airport Code." << endl;
                    return false;
                }
            }
            return false;
        }

        if (input == "2") {
            cout << "City Statistics:" << endl;
            cout << "  1. Flights per City" << endl;
            cout << "  2. Countries per City" << endl;
            cout << "  3. Return to Menu" << endl;
            while (true) {
                cout << ">> ";
                cin >> input;
                cout << '\n';

                if(!aux.is_number(input) || stoi(input)>3 || stoi(input)<1) {
                    cout << "Invalid input key" << endl;
                }else{break;}
                cout << '\n';
            }
            string city_name;
            if (input == "1") {
                cout << "Input City Name:\n"
                        ">> ";
                cin >> city_name;
                cout << '\n';
                vector<Flights> res;
                int num = display.flights_per_city(&g,city_name,res);
                if (num == 0) {
                    cout << city_name << " has no available flights, or does not exist." << endl;
                } else {
                    cout << city_name << " has a total of " << num << " flights." << endl;
                    for (Flights f : res) {
                        f.print();
                    }
                }
            }
            if (input == "2") {
                cout << "Input City Name:\n"
                        ">> ";
                cin >> city_name;
                cout << '\n';
                set<string> res;
                int num = display.countries_per_city(&g,city_name,res);
                if (num == 0) {
                    cout << city_name << " does not have flights leading to any country, or does not exist." << endl;
                } else {
                    cout << city_name << " has flights leading to a total of " << num << " countries." << endl;
                    for (string c : res) {
                        cout << c << endl;
                    }
                }
            }
            return false;
        }

        if (input == "3") {
            cout << "Airline Statistics:" << endl;
            cout << "  1. Flights per Airline" << endl;
            cout << "  2. Return to Menu" << endl;
            while (true) {
                cout << ">> ";
                cin >> input;
                cout << '\n';

                if(!aux.is_number(input) || stoi(input)>2 || stoi(input)<1) {
                    cout << "Invalid input key" << endl;
                }else{break;}
                cout << '\n';
            }
            string al_code;
            if (input == "1") {
                cout << "Input Airline Code:\n"
                        ">> ";
                cin >> al_code;
                cout << '\n';
                Airlines al = aux.findAirlineCode(als,al_code);
                if (al.getName() == "") {
                    cout << "Invalid Airline Code" << endl;
                    return false;
                }
                vector<Flights> res;
                cout << al.getName() << " has a total of " << display.flights_per_airline(&g,al_code,res) << " flights." << endl;
                for (Flights f : res) {
                    f.print();
                }
            }
            return false;
        }

        if (input == "4") {
            cout << "There are " << display.num_airports(&g) << " airports." << endl;
            return false;
        }

        if (input == "5") {
            cout << "There are " << display.num_flights(&g) << " total flights." << endl;
            return false;
        }
    }

    // Exit Option
    if (input == "7") {return true;}
}

