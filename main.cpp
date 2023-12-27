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
    r.read_airlines(&g);
    r.read_airports(&g);
    r.read_flights(&g);
    while (true) {
    Menu m = Menu();
    if (m.request(g)) break;
    }
    return 0;



/*
    bool finish = false;
    while (!finish) {
        cout
                << "\nPlease select a task:\n\n[1] - Preview student timetable\n[2] - Make UC/Class change request\n[3] - Verify the occupation of a class in a UC\n[4] - Show Student List\n[5] - Save and Exit\n[6] - See Request Logs\n"
                << endl;
        string option;
        cout << ">> ";
        cin >> option;
        cout << '\n';

        if (option.length() != 1 || !isdigit(option[0])) {
            cout << "Invalid input key" << endl;
            continue;
        }
/*
        if (option == "5") {
            finish = true;
            int def;
            cout << "Select what to do:\n[1] - Save changes\n[2] - Apply changes\n[3] - Discard changes\n\n";
            cout << ">> ";
            cin >> def;
            cout << '\n';
            processExitChoice(def, manager);
        } else if (option == "1") {
            string str;
            cout << "Student Code:\n" << endl;
            cout << ">> ";
            cin >> str;
            cout << '\n';
            if (str.length() != 9 || !is_number(str)) {
                cout << "Invalid input key" << endl;
            } else {
                manager.printSchedule(stoi(str));
            }
        } else if (option == "2") {
            request(manager);
        } else if (option == "3") {
            checkOccupation(manager);
        } else if (option == "4") {
            checkStudentList(manager);
        } else if (option == "6") {
            readLogs();
        } else {
            cout << "Invalid input key" << endl;
        }
        cout << "Returning..." << endl;
    }
    */

}