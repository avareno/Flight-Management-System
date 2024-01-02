//
// Created by goncalo_feup on 27-11-2023.
//
#include <string>
#include "Graph.h"
#ifndef PROJETO_AED_AIRPORTS_H
#define PROJETO_AED_AIRPORTS_H

using namespace std;

/**
 * @class Airports class provide a way to define a Airport.
 */

class Airports {
public:
    Airports(const string &code, const string &name, const string &city, const string &country, const float &latitude,
             const float &longitude);
    Airports();
    void print() const; ///< Display Airports information. \n Complexity: O(1)
    string getCode() const; ///< Get an airport code. \n Complexity: O(1)
    string getName() const; ///< Get an airport name. \n Complexity: O(1)
    string getCity() const; ///< Get an airport city. \n Complexity: O(1)
    string getCountry() const; ///< Get an airport country. \n Complexity: O(1)
    float getLatitude() const; ///< Get an airport latitude. \n Complexity: O(1)
    float getLongitude() const; ///< Get an airport longitude. \n Complexity: O(1)
    bool operator==(const Airports& other) const; ///< Compare two airports and check if they are the same. \n Complexity: O(1)
private:
    string code_;
    string name_;
    string city_;
    string country_;
    float latitude_;
    float longitude_;
};

#endif //PROJETO_AED_AIRPORTS_H
