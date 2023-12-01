#include <iostream>
#include "Flights.h"

using namespace std;

Flights::Flights(const string& source, const string& target, const string& AL_code)
        :  source_(source), target_(target), AL_code_(AL_code) {}

void Flights::print() const {
    cout << "Source: " << source_ << " | " << "Target: " << target_ <<  " | " << "Airline Code: " << AL_code_;
}
string Flights::getSource() const {
    return source_;
}
string Flights::getTarget() const {
    return target_;
}
string Flights::getAL_code() const {
    return AL_code_;
}