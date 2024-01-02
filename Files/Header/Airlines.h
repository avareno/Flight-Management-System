//
// Created by goncalo_feup on 27-11-2023.
//
#include <string>
#include "Graph.h"
#ifndef PROJETO_AED_AIRLINES_H
#define PROJETO_AED_AIRLINES_H

using namespace std;

/**
 * @class Airlines class provide a way to define a Airline.
 */

class Airlines {
public:
    Airlines(const string &code, const string &name, const string &callsign, const string &country);
    void print() const; ///< Display Airlines information. \n Complexity: O(1)
    string getCode() const; ///< Get an airline code. \n Complexity: O(1)
    string getName() const; ///< Get an airline name. \n Complexity: O(1)
    string getCallSign() const; ///< Get an airline callsign. \n Complexity: O(1)
    string getCountry() const; ///< Get an airline country. \n Complexity: O(1)
private:
    string code_;
    string name_;
    string callsign_;
    string country_;
};

#endif //PROJETO_AED_AIRLINES_H
