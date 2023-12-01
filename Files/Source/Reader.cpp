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

void Reader::read_flights() { // TODO: Criar 'graph' de todos os voos 'edges' com cada voo, e posteriormente cria 'nodes'
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
    vector<string> All_Airlines;
    if (read.fileExists("airlines.csv")) {
        ifstream in("airlines.csv");
        string line;
        getline(in, line);
        while (getline(in, line)) {
            if (line.find('\r') != string::npos) line.pop_back();
            string AirCode, AirName, Callsign, AirCountry;
            istringstream iss(line);
            getline(iss, AirCode, ',');
            All_Airlines.push_back(AirCode);
            getline(iss, AirName, ',');
            All_Airlines.push_back(AirName);
            getline(iss, Callsign, ',');
            All_Airlines.push_back(Callsign);
            getline(iss, AirCountry);
            All_Airlines.push_back(AirCountry);
        }
    }
}

void Reader::read_airports() {
    Reader read;
    vector<string> All_Airports;
    if (read.fileExists("airports.csv")) {
        ifstream in("airports.csv");
        string line;
        getline(in, line);
        while (getline(in, line)) {
            if(line.find('\r') != string::npos) line.pop_back();
            string AirCode, AirName, AirCity, AirCountry, Latitude, Longitude;
            istringstream iss(line);
            getline(iss, AirCode, ',');
            All_Airports.push_back(AirCode);
            getline(iss, AirName, ',');
            All_Airports.push_back(AirName);
            getline(iss, AirCity, ',');
            All_Airports.push_back(AirCity);
            getline(iss, AirCountry, ',');
            All_Airports.push_back(AirCountry);
            getline(iss, Latitude, ',');
            All_Airports.push_back(Latitude);
            getline(iss, Longitude);
            All_Airports.push_back(Longitude);}
    }
}

int Reader::Size(vector <string> something) {


}

