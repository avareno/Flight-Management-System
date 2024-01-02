#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Reader.h"
#include "Menu.h"

using namespace std;

bool checkIfEmpty(const string& filename){ ///< Checks if the file is empty. \n Complexity: O(1)
    ifstream fin(filename);
    fin.seekg(0, ios::end);
    if (fin.tellg() == 0) {
        fin.close();
        return true;
    }
    fin.close();
    return false;
}

int main() { ///< Displays the menu of choices for the user.
    Reader r;
    Graph<Airports> g;
    vector<Airlines> als = r.read_airlines();
    r.read_airports(&g);
    r.read_flights(&g);
    while (true) {
    Menu m = Menu();
    if (m.request(g,&als)) break;
    }
    return 0;
}