
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
#include <algorithm>
#include <climits>

using namespace std;

struct Parser; // To use as friend class

class Graph {
private:
    struct Student {
        string name;
        int ID;
        string locationID;
        vector<string> classes;
        Student(int ID, string name, string locationID, vector<string> classes);
    };
    vector<vector<int>> edges; // edge 1, edge 2, distance, road availability
    unordered_map<string, int> classList;
    unordered_map<int, string> locations;
    unordered_map<int, Student*> students; // students = name, locationID, classes with key = ID

public:
    Graph(); // constructor
    ~Graph();
    friend struct Parser;

    bool insert(string name, int ID, string locationID, const vector<string>& classes);
    bool remove(int ID);
    bool dropClass(int ID, const string& classCode);
    bool replaceClass(int ID, const string& classCode1, const string& classCode2); // replace 1 with 2
    int removeClass(const string& classCode);
    bool toggleEdgeClosure(const string& location1, const string& location2);
    int checkEdgeStatus(const string& location1, const string& location2);
    bool isConnected(string location1, string location2);

    pair<int, vector<int>> dijkstra(int start, int end);
    vector<pair<string, int>> printShortestEdges(int ID);
    bool printStudentZone(int ID  );


};

#endif