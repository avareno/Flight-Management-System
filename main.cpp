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

int main() { ///< Call all the functions needed to setup the system.
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


/*! \mainpage AED Project
* Projeto realizado por: \n
* Gonçalo Morais Magalhães (202208425) \n
* Gabriel da Quinta Braga (202207784) \n
* Miguel Pascoal Cabral (202204996)
*/