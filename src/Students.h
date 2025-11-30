
#ifndef STUDENTS_H
#define STUDENTS_H

#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

class Students {
private:
    unordered_map<int, tuple<string, int, vector<int>>> students; // students = name, locationID, classes
public:
    Students(string name, int ID, int locationID, vector<int> classes);
    tuple<string, int, vector<int>> getStudent(int ID);


};



#endif //STUDENTS_H
