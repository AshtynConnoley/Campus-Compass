#include "Students.h"


Students::Students(string name, int ID, int locationID, vector<int> classes) {
    students.insert({ID, tuple<string, int, vector<int>>(name, locationID, classes)});
}

tuple<string, int, vector<int>> Students::getStudent(int ID) {
    if (students.find(ID) != students.end()) {
        return students[ID];
    }
    else {
        return tuple<string, int, vector<int>>(string(), 0, 0);
    }
}

