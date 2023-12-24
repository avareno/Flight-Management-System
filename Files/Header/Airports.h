//
// Created by goncalo_feup on 27-11-2023.
//
#include <string>
#include "Graph.h"
#ifndef PROJETO_AED_AIRPORTS_H
#define PROJETO_AED_AIRPORTS_H

using namespace std;

class Airports {
public:
    Airports(const string &code, const string &name, const string &city, const string &country, const float &latitude,
             const float &longitude);
    void print() const; ///< Complexity: O(1)
    string getCode() const; ///< Complexity: O(1)
    string getName() const; ///< Complexity: O(1)
    string getCity() const; ///< Complexity: O(1)
    string getCountry() const; ///< Complexity: O(1)
    float getLatitude() const; ///< Complexity: O(1)
    float getLongitude() const; ///< Complexity: O(1)
private:
    string code_;
    string name_;
    string city_;
    string country_;
    float latitude_;
    float longitude_;
};

#endif //PROJETO_AED_AIRPORTS_H
