//
// Created by goncalo_feup on 27-11-2023.
//
#include <string>
#ifndef PROJETO_AED_AIRLINES_H
#define PROJETO_AED_AIRLINES_H

using namespace std;

class Airlines {
public:
    Airlines(const string &code, const string &name, const string &callsign, const string &country, string basicString,
             string string1);
    void print() const; ///< Complexity: O(1)
    string getCode() const; ///< Complexity: O(1)
    string getName() const; ///< Complexity: O(1)
    string getCallSign() const; ///< Complexity: O(1)
    string getCountry() const; ///< Complexity: O(1)
private:
    string code_;
    string name_;
    string callsign_;
    string country_;
};

#endif //PROJETO_AED_AIRLINES_H
