#include <iostream>
#include "Airlines.h"

using namespace std;

Airlines::Airlines(const string &code, const string &name, const string &callsign, const string &country,
                   string basicString,
                   string string1)
        :  code_(code), name_(name), callsign_(callsign), country_(country) {}

void Airlines::print() const{
    cout << "Code: " << code_ << " | " << "Name: " << name_ << " | " << "Call Sign: " << callsign_ << " | " << "Country: " << country_;
}
string Airlines::getCode() const{
    return code_;
}
string Airlines::getName() const{
    return name_;
}
string Airlines::getCallSign() const{
    return callsign_;
}
string Airlines::getCountry() const{
    return country_;
}