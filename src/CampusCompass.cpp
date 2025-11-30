#include "CampusCompass.h"


using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object
}

bool CampusCompass::ParseCSV(const string &edgeFile, const string &classFile) {
    string line;
    ifstream file = ifstream(edgeFile, ifstream::in);
    if (!file.is_open()) {
        cout << "Error opening file " << edgeFile << endl;
        return false;
    }
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        int e1 = stoi(cell);
        getline(ss, cell, ',');
        int e2 = stoi(cell);
        getline(ss, cell, ',');
        if (locations.find(e1) != locations.end()) {
            locations.insert({e1, cell});
        }
        getline(ss, cell, ',');
        if (locations.find(e2) != locations.end()) {
            locations.insert({e2, cell});
        }
        getline(ss, cell, ',');
        int time = stoi(cell);
        edges.push_back({e1, e2, time, 1}); // Last int signals if the road is available
    }
    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}
