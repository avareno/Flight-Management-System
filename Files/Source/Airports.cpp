#include <iostream>
#include "Airports.h"

using namespace std;

Airports::Airports(const string &code, const string &name, const string &city, const string &country, const float &latitude, const float &longitude)
        :  code_(code), name_(name), city_(city), country_(country), latitude_(latitude), longitude_(longitude) {}

void Airports::print() const {
    cout << "Code: " << code_ << " | " << "City: " << city_ <<  " | " << "Country: " << country_ <<  " | " << "Latitude: " << latitude_ <<  " | " << "Longitude: " << longitude_;
}
string Airports::getCode() const {
    return code_;
}
string Airports::getName() const {
    return name_;
}
string Airports::getCity() const {
    return city_;
}
string Airports::getCountry() const {
    return country_;
}
float Airports::getLatitude() const {
    return latitude_;
}
float Airports::getLongitude() const {
    return longitude_;
}
bool Airports::operator==(const Airports& other) const {
    return (code_ == other.code_ && name_ == other.name_ && city_ == other.city_ && country_ == other.country_ && latitude_ == other.latitude_ && longitude_ == other.longitude_);
}


