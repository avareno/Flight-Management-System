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

            if(AirCode.length() != 3 || aux.is_number(AirCode) || !aux.is_upper(AirCode)) {
                cout << "Invalid input key" << endl;
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

        // Add Flight
        if (input == "2") {
            string source, target, AL_code;

            cout << "Source Airport Code:" << endl;
            cout << ">> " ;
            getline(cin >> ws,source);
            cout << endl;

            if(source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
                cout << "Invalid input key" << endl;
                return false;
            }

            cout << "Target Airport Code:" << endl;
            cout << ">> " ;
            getline(cin >> ws,target);
            cout << endl;

            if(target.length() != 3 || aux.is_number(target) || !aux.is_upper(target)) {
                cout << "Invalid input key" << endl;
                return false;
            }

            cout << "Airline Code:" << endl;
            cout << ">> " ;
            getline(cin >> ws,AL_code);
            cout << endl;

            if(source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
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

        // Display Airports
        if (input == "3") {
            for (auto airport : g.getVertexSet()){
                airport->getInfo().print();
            }
            return false;
        }

        // Display Flights
        if (input == "4") {
            for (auto airport : g.getVertexSet()){
                for (auto flights : airport->getAdj()){
                    cout << "Source: " << airport->getInfo().getName() << " | " << "Destiny: " << flights.getDest()->getInfo().getName() << endl;
                }
            }
            return false;
        }

    //Search Option
    if(input == "5") {
        string n;
        cout << "Search:" << endl;
        cout << ">>1. Best Flights" << endl;
        cout << ">>2. Best FLights with filters" << endl;
        cout << ">> ";
        cin >> n;

        if(!aux.is_number(n) || stoi(n)>2 || stoi(n)<1) {
            cout << "Invalid input key" << endl;
            return false;
        }

        if(n=="1") {
            cout << "Type of input:" << endl;
            cout <<  "  >>1. Airports Codes" << endl;
            cout <<  "  >>2. Airports Cities" << endl;
            cout <<  "  >>3. Airport Coordinates" << endl;
            cin >> n;

            if(!aux.is_number(n) || stoi(n)>3 || stoi(n)<1) {
                cout << "Invalid input key" << endl;
                return false;
            }

            if(n=="1"){//code
                cout << "Source Airport code:" << endl;
                cout << ">> ";
                string source;
                cin >> source;

                if(source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << endl;
                cout << "Destination Airport code:" << endl;
                cout << ">> ";
                string dest;
                cin >> dest;

                if(dest.length() != 3 || aux.is_number(dest) || !aux.is_upper(dest)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << endl;

                Airports a1 = Airports("a", "a", "a", "a", 0.0, 0.0);
                Airports b1 = Airports("a", "a", "a", "a", 0.0, 0.0);

                for (auto &airport : g.getVertexSet()) {
                    if (airport->getInfo().getCode() == source) {
                        Airports a1 = airport->getInfo();
                    }
                    else if (airport->getInfo().getCode() == dest) {
                        Airports b1 = airport->getInfo();
                        airport->setIndegree(airport->getIndegree()+1);
                    }
                }

                if (!aux.findVertexCode(&g, source, a1) || !aux.findVertexCode(&g, dest, b1)) {
                    cout << "Invalid Airport code" << endl;
                    return false;
                }

                string res;

                cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl << "   >>";
                cin >> res;

                if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);
                if(res=="1"){
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
                }else if(res=="2"){

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


            }
            else if(n=="2"){//cities
                cout << "Source Airport City:" << endl;
                cout << ">> ";
                string source;
                cin.ignore();
                getline(cin, source);

                if(aux.is_number(source)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << endl;
                cout << "Destination Airport City:" << endl;
                cout << ">> ";
                string dest;
                getline(cin, dest);

                if(aux.is_number(dest)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << endl;


                Airports a1 = Airports("a", "a", "a", "a", 0.0, 0.0);
                Airports b1 = Airports("a", "a", "a", "a", 0.0, 0.0);

                for (auto &airport : g.getVertexSet()) {
                    if (airport->getInfo().getCode() == source) {
                        Airports a1 = airport->getInfo();
                    }
                    else if (airport->getInfo().getCode() == dest) {
                        Airports b1 = airport->getInfo();
                        airport->setIndegree(airport->getIndegree()+1);
                    }
                }
                if (!aux.findVertexCity(&g, source, a1) || !aux.findVertexCity(&g, dest, b1)) {
                    cout << "Invalid Airport city" << endl;
                }


                int min = 1000;
                vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);
                if (allPaths.size() == 0) {
                    cout << "No path found" << endl;
                } else {
                    string res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;

                    if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    for (auto path: allPaths) {
                        if (path.size() < min)min = path.size();
                    }
                    if(res=="1") {
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
                    }else if(res=="2"){
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



            }
            else if(n=="3"){//coordinates
                cout << "Source Latitude:" << endl;
                cout << ">> ";
                string slat;
                cin >> slat;

                if(!aux.is_number(slat) || stod(slat)>90 || stod(slat)<-90) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << endl;
                cout << "Source Longitude:" << endl;
                cout << ">> ";
                string slong;
                cin >> slong;

                if(!aux.is_number(slong) || stod(slong)>180 || stod(slong)<-180) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << endl;
                cout << "Destination Latitude:" << endl;
                cout << ">> ";
                string dlat;
                cin >> dlat;

                if(!aux.is_number(dlat) || stod(dlat)>90 || stod(dlat)<-90) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << endl;
                cout << "Destination Longitude:" << endl;
                cout << ">> ";
                string dlong;
                cin >> dlong;
                cout << endl;

                if(!aux.is_number(dlong) || stod(dlong)>180 || stod(dlong)<-180) {
                    cout << "Invalid input key" << endl;
                    return false;
                }


                float min1 = INT64_MAX, min2 = INT64_MAX;

                //search source airports
                vector<pair<Airports,float>> s,d;
                for(auto at : g.getVertexSet()){
                    float clong, clat;
                    clong = at->getInfo().getLongitude();
                    clat = at->getInfo().getLatitude();
                    float dis = aux.calculate_distance(stof(slong), stof(slat), clong, clat);
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
                    float dis = aux.calculate_distance(stof(dlong), stof(dlat),clong,clat);
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
                    string res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;

                    if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    if(res=="1") {
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
                    }else if(res=="2"){
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

        }else if (n=="2"){
            cout << "   >>Filter:" << endl;
            cout << "   >>1.Through Number of Airlines" << endl;
            cout << "   >>2.Through Name of Airlines" << endl;
            cout << "   >>3.Through Code of Airlines" << endl;
            cout << "  >>";

            cin >> n;

            if(!aux.is_number(n) || stoi(n)>3 || stoi(n)<1) {
                cout << "Invalid input key" << endl;
                return false;
            }

            if(n=="1"){

                cout << "Type of input" << endl;
                cout <<  "  >>1. Airports Codes" << endl;
                cout <<  "  >>2. Airports Cities" << endl;
                cout <<  "  >>3. Airport Coordinates" << endl;
                cout << "  >>";
                cin >> n;

                if(!aux.is_number(n) || stoi(n)>3 || stoi(n)<1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                string no_air;
                cout << "Input number of airlines:" << endl;
                cin >> no_air;

                if(!aux.is_number(no_air) || stoi(no_air)<1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                if(n=="1") {
                    cout << "Source Airport code:" << endl;
                    cout << ">> ";
                    string source;
                    cin >> source;

                    if(source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Airport code:" << endl;
                    cout << ">> ";
                    string dest;
                    cin >> dest;

                    if(dest.length() != 3 || aux.is_number(dest) || !aux.is_upper(dest)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;

                    Airports a1 = Airports("a", "a", "a", "a", 0.0, 0.0);
                    Airports b1 = Airports("a", "a", "a", "a", 0.0, 0.0);

                    for (auto &airport : g.getVertexSet()) {
                        if (airport->getInfo().getCode() == source) {
                            Airports a1 = airport->getInfo();
                        }
                        else if (airport->getInfo().getCode() == dest) {
                            Airports b1 = airport->getInfo();
                            airport->setIndegree(airport->getIndegree()+1);
                        }
                    }

                    if (!aux.findVertexCode(&g, source, a1) || !aux.findVertexCode(&g, dest, b1)) {
                        cout << "Invalid Airport code" << endl;
                        return false;
                    }

                    string res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;

                    if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);

                    vector<Edge<Airports>> resvector;


                    if (res == "1") {//airport codes

                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            cout << "Best Flight: " << endl;
                            int r = 0;//flag
                            for (auto path: allPaths) {
                                int minair = aux.calculate_number_of_airlines(path, &g);
                                if (minair <= stoi(no_air)) {
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
                    } else if (res == "2") {

                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            int r = 0;//flag
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                Airports beg = path[0];
                                int minair = aux.calculate_number_of_airlines(path, &g);
                                if (minair <= stoi(no_air)) {
                                    r++;
                                    for (size_t i = 0; i < path.size() - 1; ++i) {
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                    }
                                    cout << beg.getName();
                                    for (auto at: resvector) {
                                        cout << " -> " << at.getDest()->getInfo().getName() << " with "
                                             << at.getAlCode() << endl;
                                    }
                                }
                            }
                            if(r==0){
                                cout << "No Paths Found";
                            }
                        }
                    }
                }
                else if(n=="2"){//Airport Cities

                    cout << "Source Airport City:" << endl;
                    cout << ">> ";
                    string source;
                    cin.ignore();
                    getline(cin, source);

                    if(aux.is_number(source)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Airport City:" << endl;
                    cout << ">> ";
                    string dest;
                    getline(cin, dest);

                    if(aux.is_number(dest)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;


                    Airports a1 = Airports("a", "a", "a", "a", 0.0, 0.0);
                    Airports b1 = Airports("a", "a", "a", "a", 0.0, 0.0);

                    for (auto &airport : g.getVertexSet()) {
                        if (airport->getInfo().getCode() == source) {
                            Airports a1 = airport->getInfo();
                        }
                        else if (airport->getInfo().getCode() == dest) {
                            Airports b1 = airport->getInfo();
                            airport->setIndegree(airport->getIndegree()+1);
                        }
                    }

                    if (!aux.findVertexCity(&g, source, a1) || !aux.findVertexCity(&g, dest, b1)) {
                        cout << "Invalid Airport city" << endl;
                    }


                    int min = 1000;
                    vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);
                    if (allPaths.size() == 0) {
                        cout << "No path found" << endl;
                    } else {
                        string res;
                        cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                        cin >> res;

                        if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }

                        for (auto path: allPaths) {
                            if (path.size() < min)min = path.size();
                        }
                        if(res=="1") {
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                if (path.size() == min) {
                                    int minair = aux.calculate_number_of_airlines(path, &g);
                                    if(minair<=stoi(no_air)) {
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
                        }else if(res=="2"){
                            vector<Edge<Airports>> res;
                            cout << "Best Flight: " << endl;
                            int r = 0;//flag

                            for(auto path: allPaths){

                                if(path.size()==min) {
                                    Airports beg = path[0];
                                    int minair = aux.calculate_number_of_airlines(path, &g);
                                    if(minair<=stoi(no_air)) {
                                        r++;
                                        for (size_t i = 0; i < path.size() - 1; ++i) {
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), res);
                                        }
                                        cout << beg.getName();
                                        string first = res[0].getDest()->getInfo().getName();
                                        for (auto at: res) {
                                            cout << " -> " << at.getDest()->getInfo().getName() << " with " << at.getAlCode();
                                        }
                                    }
                                    cout << endl;
                                }
                            }
                            if(r==0)cout << "No Paths Found" << endl;
                        }
                    }
                }
                else if(n=="3"){//coordinates
                    cout << "Source Latitude:" << endl;
                    cout << ">> ";
                    string slat;
                    cin >> slat;

                    if(!aux.is_number(slat) || stod(slat)>90 || stod(slat)<-90) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Source Longitude:" << endl;
                    cout << ">> ";
                    string slong;
                    cin >> slong;

                    if(!aux.is_number(slong) || stod(slong)>180 || stod(slong)<-180) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Latitude:" << endl;
                    cout << ">> ";
                    string dlat;
                    cin >> dlat;

                    if(!aux.is_number(dlat) || stod(dlat)>90 || stod(dlat)<-90) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Longitude:" << endl;
                    cout << ">> ";
                    string dlong;
                    cin >> dlong;
                    cout << endl;

                    if(!aux.is_number(dlong) || stod(dlong)>180 || stod(dlong)<-180) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }


                    float min1 = INT64_MAX, min2 = INT64_MAX;//find better solution

                    //search source airports
                    vector<pair<Airports,float>> s,d;
                    for(auto at : g.getVertexSet()){
                        float clong, clat;
                        clong = at->getInfo().getLongitude();
                        clat = at->getInfo().getLatitude();
                        float dis = aux.calculate_distance(stof(slong), stof(slat), clong, clat);
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
                        float dis = aux.calculate_distance(stof(dlong),stof(dlat),clong,clat);
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
                        string res;
                        cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                        cin >> res;

                        if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }

                        if(res=="1") {
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                int minair = aux.calculate_number_of_airlines(path, &g);
                                if(minair<=stoi(no_air)) {
                                    for (size_t i = 0; i < path.size(); ++i) {
                                        cout << path[i].getName();
                                        if (i < path.size() - 1) {
                                            cout << " -> ";
                                        }
                                    }
                                }
                                cout << endl;
                            }
                        }else if(res=="2"){
                            vector<Edge<Airports>> res;
                            cout << "Best Flight: " << endl;
                            for(auto path: allPaths){
                                Airports beg = path[0];
                                int minair = aux.calculate_number_of_airlines(path, &g);
                                if(minair<=stoi(no_air)) {
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

                }//implement wrong inputs



            }
            else if(n=="2"){
                cout << "Type of input" << endl;
                cout <<  "  >>1. Airports Codes" << endl;
                cout <<  "  >>2. Airports Cities" << endl;
                cout <<  "  >>3. Airport Coordinates" << endl;
                cout << "  >>";
                cin >> n;

                if(!aux.is_number(n) || stoi(n)>3 || stoi(n)<1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                string ci_na;
                cout << "Input city of name:" << endl;
                cin >> ci_na;

                if(aux.is_number(ci_na)) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                if(n=="1") {
                    cout << "Source Airport code:" << endl;
                    cout << ">> ";
                    string source;
                    cin >> source;

                    if(source.length() != 3 || aux.is_number(source) || !aux.is_upper(source)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Airport code:" << endl;
                    cout << ">> ";
                    string dest;
                    cin >> dest;

                    if(dest.length() != 3 || aux.is_number(dest) || !aux.is_upper(dest)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;

                    Airports a1 = Airports("a", "a", "a", "a", 0.0, 0.0);
                    Airports b1 = Airports("a", "a", "a", "a", 0.0, 0.0);

                    for (auto &airport : g.getVertexSet()) {
                        if (airport->getInfo().getCode() == source) {
                            Airports a1 = airport->getInfo();
                        }
                        else if (airport->getInfo().getCode() == dest) {
                            Airports b1 = airport->getInfo();
                            airport->setIndegree(airport->getIndegree()+1);
                        }
                    }

                    if (!aux.findVertexCode(&g, source, a1) || !aux.findVertexCode(&g, dest, b1)) {
                        cout << "Invalid Airport code" << endl;
                        return false;
                    }

                    string res;
                    cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                    cin >> res;

                    if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);

                    vector<Edge<Airports>> resvector;


                    if (res == "1") {//airport codes

                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            cout << "Best Flight: " << endl;
                            int r = 0;//flag
                            for (auto path: allPaths) {
                                if (aux.has_aili(ci_na, path,&g)) {
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
                    } else if (res == "2") {

                        if (allPaths.size() == 0) {
                            cout << "No path found" << endl;
                        } else {
                            int r = 0;//flag
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                Airports beg = path[0];
                                if (aux.has_aili(ci_na, path,&g)) {
                                    r++;
                                    for (size_t i = 0; i < path.size() - 1; ++i) {
                                        g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), resvector);
                                    }
                                    cout << beg.getName();
                                    for (auto at: resvector) {
                                        cout << " -> " << at.getDest()->getInfo().getName() << " with "
                                             << at.getAlCode() << endl;
                                    }
                                }
                            }
                            if(r==0){
                                cout << "No Paths Found";
                            }
                        }
                    }
                }
                else if(n=="2"){//Airport Cities

                    cout << "Source Airport City:" << endl;
                    cout << ">> ";
                    string source;
                    cin.ignore();
                    getline(cin, source);

                    if(aux.is_number(source)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Airport City:" << endl;
                    cout << ">> ";
                    string dest;
                    getline(cin, dest);

                    if(aux.is_number(dest)) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;


                    Airports a1 = Airports("a", "a", "a", "a", 0.0, 0.0);
                    Airports b1 = Airports("a", "a", "a", "a", 0.0, 0.0);

                    for (auto &airport : g.getVertexSet()) {
                        if (airport->getInfo().getCode() == source) {
                            Airports a1 = airport->getInfo();
                        }
                        else if (airport->getInfo().getCode() == dest) {
                            Airports b1 = airport->getInfo();
                            airport->setIndegree(airport->getIndegree()+1);
                        }
                    }

                    if (!aux.findVertexCity(&g, source, a1) || !aux.findVertexCity(&g, dest, b1)) {
                        cout << "Invalid Airport city" << endl;
                        return false;
                    }


                    int min = 1000;
                    vector<vector<Airports>> allPaths = aux.best_flight(&g, a1, b1);
                    if (allPaths.size() == 0) {
                        cout << "No path found" << endl;
                    } else {
                        string res;
                        cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                        cin >> res;

                        if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }

                        for (auto path: allPaths) {
                            if (path.size() < min)min = path.size();
                        }
                        if(res=="1") {
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                if (path.size() == min) {
                                    if (aux.has_aili(ci_na, path,&g)) {
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
                        }else if(res=="2"){
                            vector<Edge<Airports>> res;
                            cout << "Best Flight: " << endl;
                            int r = 0;//flag

                            for(auto path: allPaths){

                                if(path.size()==min) {
                                    Airports beg = path[0];
                                    if(aux.has_aili(ci_na, path,&g)) {
                                        r++;
                                        for (size_t i = 0; i < path.size() - 1; ++i) {
                                            g.findVertex(path[i])->getEdge(g.findVertex(path[i + 1]), res);
                                        }
                                        cout << beg.getName();
                                        string first = res[0].getDest()->getInfo().getName();
                                        for (auto at: res) {
                                            cout << " -> " << at.getDest()->getInfo().getName() << " with " << at.getAlCode();
                                        }
                                    }
                                    cout << endl;
                                }
                            }
                            if(r==0)cout << "No Paths Found" << endl;
                        }
                    }
                }
                else if(n=="3"){//coordinates
                    cout << "Source Latitude:" << endl;
                    cout << ">> ";
                    string slat;
                    cin >> slat;

                    if(!aux.is_number(slat) || stod(slat)>90 || stod(slat)<-90) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Source Longitude:" << endl;
                    cout << ">> ";
                    string slong;
                    cin >> slong;

                    if(!aux.is_number(slong) || stod(slong)>180 || stod(slong)<-180) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Latitude:" << endl;
                    cout << ">> ";
                    string dlat;
                    cin >> dlat;

                    if(!aux.is_number(dlat) || stod(dlat)>90 || stod(dlat)<-90) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    cout << endl;
                    cout << "Destination Longitude:" << endl;
                    cout << ">> ";
                    string dlong;
                    cin >> dlong;
                    cout << endl;

                    if(!aux.is_number(dlong) || stod(dlong)>180 || stod(dlong)<-180) {
                        cout << "Invalid input key" << endl;
                        return false;
                    }

                    float min1 = INT64_MAX, min2 = INT64_MAX;//find better solution

                    //search source airports
                    vector<pair<Airports,float>> s,d;
                    for(auto at : g.getVertexSet()){
                        float clong, clat;
                        clong = at->getInfo().getLongitude();
                        clat = at->getInfo().getLatitude();
                        float dis = aux.calculate_distance(stof(slong), stof(slat), clong, clat);
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
                        float dis = aux.calculate_distance(stof(dlong),stof(dlat),clong,clat);
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
                        string res;
                        cout << "   >>1.See City" << endl << "   >>2.See Flights" << endl;
                        cin >> res;

                        if(!aux.is_number(res) || stoi(res)>2 || stoi(res)<1) {
                            cout << "Invalid input key" << endl;
                            return false;
                        }

                        if(res=="1") {
                            cout << "Best Flight: " << endl;
                            for (auto path: allPaths) {
                                if(aux.has_aili(ci_na, path,&g)) {
                                    for (size_t i = 0; i < path.size(); ++i) {
                                        cout << path[i].getName();
                                        if (i < path.size() - 1) {
                                            cout << " -> ";
                                        }
                                }
                                cout << endl;
                                }
                            }
                        }else if(res=="2"){
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
                //implement wrong inputs
            }
            else if (n=="3"){

            }else{
                cout << "Invalid Input" << endl;
                return false;
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

            if(!aux.is_number(input) || stoi(input)>6 || stoi(input)<1) {
                cout << "Invalid input key" << endl;
                return false;
            }

            cout << '\n';
            if (input.length() != 1 || !isdigit(input[0])) {
                cout << "Invalid input key" << endl;
                return false;
            } else {break;}
        }
        if (input == "1") {
            cout << '\n';
            cout << "Airport Statistics:" << endl;
            cout << "  1. Flights per Airport" << endl;
            cout << "  2. Airlines per Airport" << endl;
            cout << "  3. Countries per Airport" << endl;
            cout << "  4. Destinations per Airport"  << endl;
            cout << "  5. Return to Menu" << endl;
            while (true) {
                cout << ">> ";
                cin >> input;

                if(!aux.is_number(input) || stoi(input)>5 || stoi(input)<1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << '\n';
                if (input.length() != 1 || !isdigit(input[0])) {
                    cout << "Invalid input key" << endl;
                    return false;
                } else {break;}
            }
            if (input == "1") {
                cout << "Input Airport Code:\n>> ";
                cin >> input;

                if(!aux.is_number(input) || stoi(input)<1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << '\n';
                Airports info = Airports("a", "a", "a", "a", 0.0, 0.0);

                for (auto &airport : g.getVertexSet()) {
                    if (airport->getInfo().getCode() == input) {
                        Airports info = airport->getInfo();
                    }
                }
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

                if(!aux.is_number(input) || stoi(input)<1) {
                    cout << "Invalid input key" << endl;
                    return false;
                }

                cout << '\n';
                Airports info = Airports("a", "a", "a", "a", 0.0, 0.0);

                for (auto &airport : g.getVertexSet()) {
                    if (airport->getInfo().getCode() == input) {
                        Airports info = airport->getInfo();
                    }
                }
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

