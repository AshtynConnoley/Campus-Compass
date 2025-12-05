#include "CampusCompass.h"


using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object
}
CampusCompass::Student::Student(int ID, string name, string locationID, vector<string> classes) {
    this->ID = ID;
    this->name = name;
    this->locationID = locationID;
    this->classes = classes;
}

CampusCompass::~CampusCompass() {
    for (auto item : students) {
        delete item.second;
    }
}

string CampusCompass::getStudentName(int ID) {
    return students[ID]->name;
}

bool CampusCompass::insert(string name, int ID, string locationID, const vector<string>& classes) {
    if (students.find(ID) != students.end()) {
        return false;
    }
    for (auto item : classes) {
        if (classList.find(item) == classList.end()) {
            return false;
        }
    }
    students[ID] = new Student(ID, name, locationID, classes);
    return true;
}

bool CampusCompass::remove(int ID) {
    if (students.find(ID) == students.end()) {
        return false;
    }
    delete students[ID];
    students.erase(ID);
    return true;
}

bool CampusCompass::dropClass(int ID, const string& classCode) {
    if (students.find(ID) == students.end()) {
        return false;
    }
    Student* curr = students[ID];
    for (size_t i=0; i < curr->classes.size(); i++) {
        if (curr->classes[i] == classCode) {
            curr->classes.erase(curr->classes.begin() + i);
            if (curr->classes.size() == 0) {
                delete students[ID];
                students.erase(ID);
            }
            return true;
        }
    }
    return false;
}

bool CampusCompass::replaceClass(int ID, const string& classCode1, const string& classCode2) { // replace 1 with 2
    if (students.find(ID) == students.end()) { // student exists
        return false;
    }
    if (classList.find(classCode2) == classList.end()) {
        return false;
    }
    Student* curr = students[ID];
    for (auto item : curr->classes) { // doesn't already have class 2
        if (item == classCode2) {
            return false;
        }
    }
    for (auto& item : curr->classes) { // classes get switched
        if (item == classCode1) {
            item = classCode2;
            return true;
        }
    }
    return false;
}

int CampusCompass::removeClass(const string& classCode) {
    int count = 0;
    if (classList.find(classCode) == classList.end()) {
        return 0;
    }
    for (auto person : students) {
        for (size_t i = 0; i < person.second->classes.size(); i++) {
            if (person.second->classes[i] == classCode) {
                person.second->classes.erase(person.second->classes.begin() + i);
                if (person.second->classes.empty()) {
                    delete students[person.first];
                    students.erase(person.first);
                }
                count += 1;
            }
        }
    }
    classList.erase(classCode);
    return count;
}

bool CampusCompass::toggleEdgeClosure(const string& location1, const string& location2) {
    for (auto edge : edges) {
        if ((edge[0] == stoi(location1) && edge[1] == stoi(location2)) || edge[0] == stoi(location2) || edge[1] == stoi(location1)) {
            edge[3] == !edge[3];
            return true;
        }
    }
    return false;
}

int CampusCompass::checkEdgeStatus(const string& location1, const string& location2) {
    for (auto edge : edges) {
        if ((edge[0] == stoi(location1) && edge[1] == stoi(location2)) || (edge[0] == stoi(location2) && edge[1] == stoi(location1))) {
            return edge[3];
        }
    }
    return -1;
}

bool CampusCompass::isConnected(string location1, string location2) {
    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(stoi(location1));
    visited.insert(stoi(location1));

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == stoi(location2)) {
            return true;
        }

        for (auto edge : edges) {
            if ((edge[0] == curr && visited.find(edge[1]) == visited.end()) && edge[3] == true) {
                q.push(edge[1]);
                visited.insert(edge[1]);
            }
            else if (edge[1] == curr && visited.find(edge[0]) == visited.end() && edge[3] == true) {
                q.push(edge[0]);
                visited.insert(edge[0]);
            }
        }
    }
    return false;
}

vector<pair<string, int>> printShortestEdges(int ID); // Make sure to sort classes

int minimumSpanningTree(vector<pair<int, int>> edges);





