
#include "Parser.h"


bool Parser::parseCSV(const string &edgeFile, const string &classFile, CampusCompass& compass) {
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
        if (compass.locations.find(e1) != compass.locations.end()) {
            compass.locations.insert({e1, cell});
        }
        getline(ss, cell, ',');
        if (compass.locations.find(e2) != compass.locations.end()) {
            compass.locations.insert({e2, cell});
        }
        getline(ss, cell, ',');
        int distance = stoi(cell);
        compass.edges.push_back({e1, e2, distance, 1}); // Last int signals if the road is available
    }
    file.close();


    file = ifstream(classFile, ifstream::in);
    if (!file.is_open()) {
        cout << "Error opening file " << edgeFile << endl;
        return false;
    }
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        string code;
        getline(ss, code, ',');
        getline(ss, cell, ',');
        compass.classList[code] = stoi(cell);
        getline(ss, cell, ',');
        // int time1 = stoi(cell);
        getline(ss, cell, ',');
        // int time2 = stoi(cell);

    }
    file.close();

    return true;
}

bool Parser::parseCommand(const string &command, bool isTest) {
    stringstream ss(command);
    string word;
    ss >> word;
    if (word == "insert") {}
    else if (word == "remove") {}
    else if (word == "dropClass") {}
    else if (word == "replaceClass") {}
    else if (word == "removeClass") {}
    else if (word == "toggleEdgeClosure") {}
    else if (word == "checkEdgeStatus") {}
    else if (word == "isConnected") {}
    else if (word == "printShortestEdges") {}
    else if (word == "printStudentZone") {}

    return false;
}