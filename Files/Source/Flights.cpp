#include <iostream>
#include <cmath>
#include "Flights.h"

using namespace std;

Flights::Flights(const string& source, const string& target, const string& AL_code)
        :  source_(source), target_(target), AL_code_(AL_code) {}

void Flights::print() const {
    cout << "Source: " << source_ << " | " << "Target: " << target_ <<  " | " << "Airline Code: " << AL_code_ << endl;
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

double Flights::Haversine_d(double &lat1, double& lon1, double &lat2, double& lon2) const {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulas
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}