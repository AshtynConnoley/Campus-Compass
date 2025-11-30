
#ifndef STUDENTS_H
#define STUDENTS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class CampusCompass {
private:
    vector<vector<int>> edges; // edge 1, edge 2, time, road availability
    map<int, string> locations;
public:
        // Think about what helper functions you will need in the algorithm
        CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);

};

#endif