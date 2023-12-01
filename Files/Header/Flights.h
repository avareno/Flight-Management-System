//
// Created by goncalo_feup on 27-11-2023.
//

#ifndef PROJETO_AED_FLIGHTS_H
#define PROJETO_AED_FLIGHTS_H

#include <string>

using namespace std;

class Flights {
public:
    Flights(const string& source, const string& target, const string& AL_code);
    void print() const; ///< Complexity: O(1)
    string getSource() const; ///< Complexity: O(1)
    string getTarget() const; ///< Complexity: O(1)
    string getAL_code() const; ///< Complexity: O(1)
private:
    string source_;
    string target_;
    string AL_code_;
};

#endif //PROJETO_AED_FLIGHTS_H
