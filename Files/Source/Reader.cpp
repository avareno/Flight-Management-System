#include <iostream>
#include <fstream>
#include <sstream>
#include "Reader.h"
#include "Airlines.h"
#include "Airports.h"
#include "Graph.h"
#include "Flights.h"

using namespace std;

Reader::Reader() = default;

bool Reader::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void Reader::read_flights(Graph<Airports> *g) { // TODO: Criar 'graph' de todos os voos, 'edges' com cada voo, e posteriormente cria 'nodes'
    Reader read;
    if (read.fileExists("flights.csv")) {
        ifstream in("flights.csv");
        string line;
        getline(in, line);
        while (getline(in, line)) {
            if (line.find('\r') != string::npos) line.pop_back();
            string Source, Target, AL_code;
            istringstream iss(line);
            getline(iss, Source, ',');
            getline(iss, Target, ',');
            getline(iss, AL_code, ',');
            Flights New = Flights(Source, Target, AL_code);

            double lat1, lon1, lat2, lon2;

            for (auto airport : g->getVertexSet()) {
                if (airport->getInfo().getCode() == Source) {
                    lat1 = airport->getInfo().getLatitude();
                    lon1 = airport->getInfo().getLongitude();
                    Airports s = airport->getInfo();
                }
                else if (airport->getInfo().getCode() == Target) {
                    lat2 = airport->getInfo().getLatitude();
                    lon2 = airport->getInfo().getLongitude();
                    Airports t = airport->getInfo();
                }
            }
            g->addEdge(Source, Target, New.Haversine_d(lat1, lon1, lat2, lon2), AL_code);
        }
    }
}

vector<Airlines> Reader::read_airlines(Graph<Airports> *g) {
    Reader read;
    vector<Airlines> All_Airlines;
    if (read.fileExists("airlines.csv")) {
        ifstream in("airlines.csv");
        string line;
        getline(in, line);
        while (getline(in, line)) {
            if (line.find('\r') != string::npos) line.pop_back();
            string AirCode, AirName, Callsign, AirCountry;
            istringstream iss(line);
            getline(iss, AirCode, ',');
            getline(iss, AirName, ',');
            getline(iss, Callsign, ',');
            getline(iss, AirCountry);
            Airlines New = Airlines(AirCode, AirName, Callsign, AirCountry);
            All_Airlines.push_back(New);
        }
    }
    return All_Airlines;
}

void Reader::read_airports(Graph<Airports> *g) {
    Reader read;
    if (read.fileExists("airports.csv")) {
        ifstream in("airports.csv");
        string line;
        getline(in, line);
        while (getline(in, line)) {
            if(line.find('\r') != string::npos) line.pop_back();
            string AirCode, AirName, AirCity, AirCountry, Latitude, Longitude;
            istringstream iss(line);
            getline(iss, AirCode, ',');
            getline(iss, AirName, ',');
            getline(iss, AirCity, ',');
            getline(iss, AirCountry, ',');
            getline(iss, Latitude, ',');
            float Lat = stof(Latitude);
            getline(iss, Longitude);
            float Long = stof(Longitude);
            Airports New = Airports(AirCode, AirName, AirCity, AirCountry, Lat, Long);
            g->addVertex(New);
        }
    }
}

int Reader::Size(vector <string> something) {


}

