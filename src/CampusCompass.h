
#ifndef CAMPUSCOMPASS_H
#define CAMPUSCOMPASS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Parser;

class CampusCompass {
private:
    struct Student {
        string name;
        int ID;
        string locationID;
        vector<string> classes;
        Student(int ID, string name, string locationID, vector<string> classes);
    };
    vector<vector<int>> edges; // edge 1, edge 2, distance, road availability
    map<string, int> classList;
    map<int, string> locations;
    unordered_map<int, Student*> students; // students = name, locationID, classes with key = ID

public:
    CampusCompass(); // constructor
    ~CampusCompass();
    friend class Parser;

    bool insert(string name, int ID, string location, const vector<string>& classes);
    bool remove(int ID);
    bool dropClass(int ID, const string& classCode);
    bool replaceClass(int ID, const string& classCode1, const string& classCode2); // replace 1 with 2
    int removeClass(const string& classCode);
    bool toggleEdgeClosure(const string& location1, const string& location2);
    int checkEdgeStatus(const string& location1, const string& location2);
    bool isConnected(string location1, string location2);
    vector<pair<string, int>> printShortestEdges(int ID);
    int minimumSpanningTree(vector<pair<int, int>> edges);
    string getStudentName(int ID);


};

#endif