#include <iostream>
#include <fstream>
#include <sstream>
#include "Reader.h"
#include "Airlines.h"
#include "Airports.h"
#include "Graph.h"

using namespace std;

Reader::Reader() = default;

bool Reader::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void Reader::read_flights() { // TODO: Criar 'graph' de todos os voos, 'edges' com cada voo, e posteriormente cria 'nodes'
    Reader read;
    if (read.fileExists("flights.csv")) {
        ifstream in("flights.csv");
        string line;
        getline(in, line);
        // TODO: continue
    }
}

void Reader::read_airlines() {
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
            All_Airlines.emplace_back(AirCode, AirName, Callsign, AirCountry);
        }
    }
}

void Reader::read_airports() {
    Reader read;
    vector<Airports> All_Airports;
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
            All_Airports.emplace_back(AirCode, AirName, AirCity, AirCountry, Lat, Long);
        }
    }
}

int Reader::Size(vector <string> something) {


}

